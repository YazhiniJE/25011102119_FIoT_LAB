#include "main.h"
#include "bme280.h"
#include <string.h>
#include <stdio.h>
#include <stdint.h>

I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
void Error_Handler(void);

/* Check in Keil Watch if the program stops:
   1=BME init, 2=BME settings, 3=BME mode,
   4=ESP reset, 5=ATE0, 6=Wi-Fi mode, 7=Wi-Fi join,
   8=TCP mode, 9=TCP connection, 10=MQTT connect,
   11=BME read, 12=MQTT publish */
volatile uint8_t debug_stage = 0;

static struct bme280_dev bme;
static struct bme280_settings bmeSettings;
static struct bme280_data bmeData;
static uint8_t bmeAddress = BME280_I2C_ADDR_PRIM; /* I2C address 0x76 */
static int8_t bmeStatus;
static char mqttJson[160];

/* ---------- ESP8266 AT/TCP helpers ---------- */

static void ESP_DrainRx(void)
{
  uint8_t ch;

  while (HAL_UART_Receive(&huart1, &ch, 1, 5) == HAL_OK)
  {
    /* Discard old ESP responses. */
  }
}

static uint8_t ESP_WaitFor(const char *expected, uint32_t timeoutMs)
{
  uint32_t start = HAL_GetTick();
  uint8_t ch;
  uint16_t matchedExpected = 0;
  uint16_t matchedError = 0;
  uint16_t matchedFail = 0;
  uint16_t expectedLength = (uint16_t)strlen(expected);

  while ((HAL_GetTick() - start) < timeoutMs)
  {
    if (HAL_UART_Receive(&huart1, &ch, 1, 50) == HAL_OK)
    {
      if (ch == (uint8_t)expected[matchedExpected])
      {
        matchedExpected++;
        if (matchedExpected == expectedLength)
          return 1;
      }
      else
      {
        matchedExpected = (ch == (uint8_t)expected[0]) ? 1 : 0;
      }

      if (ch == (uint8_t)"ERROR"[matchedError])
      {
        matchedError++;
        if (matchedError == 5)
          return 0;
      }
      else
      {
        matchedError = (ch == (uint8_t)'E') ? 1 : 0;
      }

      if (ch == (uint8_t)"FAIL"[matchedFail])
      {
        matchedFail++;
        if (matchedFail == 4)
          return 0;
      }
      else
      {
        matchedFail = (ch == (uint8_t)'F') ? 1 : 0;
      }
    }
  }

  return 0;
}

static uint8_t ESP_SendAT(const char *cmd, const char *expected,
                          uint32_t timeoutMs)
{
  ESP_DrainRx();

  if (HAL_UART_Transmit(&huart1, (uint8_t *)cmd,
                        (uint16_t)strlen(cmd), 3000) != HAL_OK)
    return 0;

  return ESP_WaitFor(expected, timeoutMs);
}

static uint8_t ESP_SendMqttPacket(const uint8_t *packet,
                                  uint16_t packetLength)
{
  char cmd[32];

  ESP_DrainRx();
  snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%u\r\n",
           (unsigned int)packetLength);

  if (HAL_UART_Transmit(&huart1, (uint8_t *)cmd,
                        (uint16_t)strlen(cmd), 3000) != HAL_OK)
    return 0;

  if (!ESP_WaitFor(">", 5000))
    return 0;

  if (HAL_UART_Transmit(&huart1, (uint8_t *)packet,
                        packetLength, 5000) != HAL_OK)
    return 0;

  return ESP_WaitFor("SEND OK", 10000);
}

/* ---------- Bosch BME280 I2C interface ---------- */

static int8_t BME_Read(uint8_t regAddr, uint8_t *data,
                       uint32_t len, void *intfPtr)
{
  uint8_t address = (uint8_t)(*(uint8_t *)intfPtr << 1);

  if (HAL_I2C_Mem_Read(&hi2c1, address, regAddr,
                       I2C_MEMADD_SIZE_8BIT, data, len, 100) == HAL_OK)
    return BME280_OK;

  return BME280_E_COMM_FAIL;
}

static int8_t BME_Write(uint8_t regAddr, const uint8_t *data,
                        uint32_t len, void *intfPtr)
{
  uint8_t address = (uint8_t)(*(uint8_t *)intfPtr << 1);

  if (HAL_I2C_Mem_Write(&hi2c1, address, regAddr,
                        I2C_MEMADD_SIZE_8BIT, (uint8_t *)data,
                        len, 100) == HAL_OK)
    return BME280_OK;

  return BME280_E_COMM_FAIL;
}

static void BME_DelayUs(uint32_t period, void *intfPtr)
{
  (void)intfPtr;
  HAL_Delay((period + 999U) / 1000U);
}

/* ---------- MQTT JSON publish helper ---------- */

static uint8_t MQTT_PublishJson(const char *topic, const char *payload)
{
  uint8_t packet[256];
  uint16_t pos = 0;
  uint16_t topicLen = (uint16_t)strlen(topic);
  uint16_t payloadLen = (uint16_t)strlen(payload);
  uint32_t remaining = 2U + topicLen + payloadLen;
  uint32_t value = remaining;

  if ((remaining + 5U) > sizeof(packet))
    return 0;

  packet[pos++] = 0x30; /* MQTT PUBLISH, QoS 0 */

  /* MQTT remaining-length encoding */
  do
  {
    uint8_t digit = (uint8_t)(value % 128U);
    value /= 128U;

    if (value > 0U)
      digit |= 0x80U;

    packet[pos++] = digit;
  } while (value > 0U);

  packet[pos++] = (uint8_t)(topicLen >> 8);
  packet[pos++] = (uint8_t)topicLen;

  memcpy(&packet[pos], topic, topicLen);
  pos += topicLen;

  memcpy(&packet[pos], payload, payloadLen);
  pos += payloadLen;

  return ESP_SendMqttPacket(packet, pos);
}

int main(void)
{
  static const uint8_t mqttConnectPacket[] =
  {
    0x10, 0x1B, /* MQTT CONNECT, remaining length 27 */
    0x00, 0x04, 'M', 'Q', 'T', 'T',
    0x04,       /* MQTT 3.1.1 */
    0x02,       /* Clean session */
    0x00, 0x3C, /* Keepalive 60 seconds */
    0x00, 0x0F, /* Client ID length 15 */
    's','t','m','3','2','-','b','a','v','a','n','a','-','0','1'
  };

  char wifiCmd[160];
  uint8_t settingsSelect;

  HAL_Init();
  SystemClock_Config();

  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();

  /* Initialize and configure BME280 */
  debug_stage = 1;

  bme.intf = BME280_I2C_INTF;
  bme.intf_ptr = &bmeAddress;
  bme.read = BME_Read;
  bme.write = BME_Write;
  bme.delay_us = BME_DelayUs;

  bmeStatus = bme280_init(&bme);
  if (bmeStatus != BME280_OK)
    Error_Handler();

  debug_stage = 2;

  bmeSettings.osr_t = BME280_OVERSAMPLING_1X;
  bmeSettings.osr_p = BME280_OVERSAMPLING_1X;
  bmeSettings.osr_h = BME280_OVERSAMPLING_1X;
  bmeSettings.filter = BME280_FILTER_COEFF_OFF;
  bmeSettings.standby_time = BME280_STANDBY_TIME_1000_MS;

  settingsSelect = BME280_SEL_OSR_PRESS |
                   BME280_SEL_OSR_TEMP |
                   BME280_SEL_OSR_HUM |
                   BME280_SEL_FILTER |
                   BME280_SEL_STANDBY;

  bmeStatus = bme280_set_sensor_settings(settingsSelect,
                                          &bmeSettings, &bme);
  if (bmeStatus != BME280_OK)
    Error_Handler();

  debug_stage = 3;

  bmeStatus = bme280_set_sensor_mode(BME280_POWERMODE_NORMAL, &bme);
  if (bmeStatus != BME280_OK)
    Error_Handler();

  /* Reset ESP8266 and connect it to Wi-Fi */
  HAL_Delay(2000);

  debug_stage = 4;
  if (HAL_UART_Transmit(&huart1, (uint8_t *)"AT+RST\r\n",
                        8, 3000) != HAL_OK ||
      !ESP_WaitFor("ready", 10000))
    Error_Handler();

  HAL_Delay(500);

  debug_stage = 5;
  if (!ESP_SendAT("ATE0\r\n", "OK", 3000))
    Error_Handler();

  debug_stage = 6;
  if (!ESP_SendAT("AT+CWMODE=1\r\n", "OK", 3000))
    Error_Handler();

  debug_stage = 7;
  snprintf(wifiCmd, sizeof(wifiCmd),
           "AT+CWJAP=\"vivo\",\"Yazh0505\"\r\n");

  if (!ESP_SendAT(wifiCmd, "OK", 30000))
    Error_Handler();

  /* Open TCP connection to the MQTT broker */
  debug_stage = 8;
  if (!ESP_SendAT("AT+CIPMUX=0\r\n", "OK", 3000))
    Error_Handler();

  debug_stage = 9;
  if (!ESP_SendAT(
        "AT+CIPSTART=\"TCP\",\"broker.emqx.io\",1883\r\n",
        "OK", 15000))
    Error_Handler();

  /* Send MQTT CONNECT packet */
  debug_stage = 10;
  if (!ESP_SendMqttPacket(mqttConnectPacket,
                          sizeof(mqttConnectPacket)))
    Error_Handler();

  HAL_Delay(500);

  /* Publish new sensor readings once per second */
  while (1)
  {
    int32_t temperature100;
    uint32_t humidity100;
    uint32_t pressureHpa100;
    uint32_t temperatureAbs;
    char temperatureText[20];

    debug_stage = 11;
    bmeStatus = bme280_get_sensor_data(BME280_ALL, &bmeData, &bme);
    if (bmeStatus != BME280_OK)
      Error_Handler();

#ifdef BME280_DOUBLE_ENABLE
    temperature100 = (int32_t)(bmeData.temperature * 100.0);
    humidity100 = (uint32_t)(bmeData.humidity * 100.0);
    /* Bosch double output pressure is Pa; Pa equals hPa x 100. */
    pressureHpa100 = (uint32_t)bmeData.pressure;
#else
    temperature100 = bmeData.temperature;
    humidity100 = (uint32_t)(((uint64_t)bmeData.humidity * 100U) / 1024U);
#ifdef BME280_64BIT_ENABLE
    /* Bosch 64-bit integer pressure is 100 x Pa. */
    pressureHpa100 = bmeData.pressure / 100U;
#else
    /* Bosch 32-bit integer pressure is Pa. */
    pressureHpa100 = bmeData.pressure;
#endif
#endif

    temperatureAbs = (temperature100 < 0)
                     ? (uint32_t)(-temperature100)
                     : (uint32_t)temperature100;

    snprintf(temperatureText, sizeof(temperatureText), "%s%lu.%02lu",
             (temperature100 < 0) ? "-" : "",
             (unsigned long)(temperatureAbs / 100U),
             (unsigned long)(temperatureAbs % 100U));

    snprintf(mqttJson, sizeof(mqttJson),
             "{\"status\":\"success\",\"temperature\":%s,"
             "\"humidity\":%lu.%02lu,\"pressure\":%lu.%02lu}",
             temperatureText,
             (unsigned long)(humidity100 / 100U),
             (unsigned long)(humidity100 % 100U),
             (unsigned long)(pressureHpa100 / 100U),
             (unsigned long)(pressureHpa100 % 100U));

    debug_stage = 12;
    if (!MQTT_PublishJson("/yazhini", mqttJson))
      Error_Handler();

    debug_stage = 0;
    HAL_Delay(1000);
  }
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 84;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    Error_Handler();

  RCC_ClkInitTypeDef RCC_ClkInitStruct2 = {0};
  RCC_ClkInitStruct2.ClockType = RCC_CLOCKTYPE_HCLK |
                                 RCC_CLOCKTYPE_SYSCLK |
                                 RCC_CLOCKTYPE_PCLK1 |
                                 RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct2.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct2.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct2.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct2.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct2, FLASH_LATENCY_2) != HAL_OK)
    Error_Handler();
}

static void MX_I2C1_Init(void)
{
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
    Error_Handler();
}

static void MX_USART1_UART_Init(void)
{
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;

  if (HAL_UART_Init(&huart1) != HAL_OK)
    Error_Handler();
}

static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
}

void Error_Handler(void)
{
  __disable_irq();
  while (1)
  {
  }
}

#ifdef USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line)
{
  (void)file;
  (void)line;
}
#endif