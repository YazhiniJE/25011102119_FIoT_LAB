#include "main.h"
#include "bme280.h"
#include <stdint.h>

/* Peripheral handles */
I2C_HandleTypeDef hi2c1;
UART_HandleTypeDef huart1;

/* BME280 driver structures */
struct bme280_dev dev;
struct bme280_data comp_data;
struct bme280_settings settings;

/* Diagnostic variables: add these to Keil Watch 1 */
volatile int8_t rslt = BME280_OK;
volatile uint8_t error_stage = 0;
volatile uint8_t detected_address = 0;
volatile uint8_t address_76_status = 255;
volatile uint8_t address_77_status = 255;
volatile uint8_t chip_id = 0;
volatile uint32_t i2c_hal_error = 0;

/* Sensor readings */
volatile float temperature = 0.0f;
volatile float pressure = 0.0f;
volatile float humidity = 0.0f;

/* BME280 I2C address */
static uint8_t dev_addr = BME280_I2C_ADDR_PRIM;

/* Function prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
void Error_Handler(void);

int8_t user_i2c_read(uint8_t reg_addr,
                     uint8_t *reg_data,
                     uint32_t len,
                     void *intf_ptr);

int8_t user_i2c_write(uint8_t reg_addr,
                      const uint8_t *reg_data,
                      uint32_t len,
                      void *intf_ptr);

void user_delay_us(uint32_t period, void *intf_ptr);

int main(void)
{
    HAL_Init();

    SystemClock_Config();

    MX_GPIO_Init();
    MX_I2C1_Init();
    MX_USART1_UART_Init();

    /* Stage 1: Check I2C addresses */

    error_stage = 1;

    address_76_status = HAL_I2C_IsDeviceReady(
        &hi2c1, (uint16_t)(0x76U << 1), 3, 100
    );

    address_77_status = HAL_I2C_IsDeviceReady(
        &hi2c1, (uint16_t)(0x77U << 1), 3, 100
    );

    if (address_76_status == HAL_OK)
    {
        detected_address = 0x76;
    }
    else if (address_77_status == HAL_OK)
    {
        detected_address = 0x77;
    }
    else
    {
        i2c_hal_error = HAL_I2C_GetError(&hi2c1);
        Error_Handler();
    }

    dev_addr = detected_address;

    /* Stage 2: Configure Bosch driver interface */

    error_stage = 2;

    dev.intf_ptr = &dev_addr;
    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_us = user_delay_us;

    /* Stage 3: Initialize BME280 */

    error_stage = 3;

    rslt = bme280_init(&dev);

    if (rslt != BME280_OK)
    {
        i2c_hal_error = HAL_I2C_GetError(&hi2c1);
        Error_Handler();
    }

    /* Read chip ID: BME280 chip ID is 0x60 */

    error_stage = 4;

    if (user_i2c_read(0xD0, (uint8_t *)&chip_id,
                      1, &dev_addr) != BME280_OK)
    {
        i2c_hal_error = HAL_I2C_GetError(&hi2c1);
        Error_Handler();
    }

    if (chip_id != 0x60)
    {
        Error_Handler();
    }

    /* Stage 5: Configure sensor settings */

    error_stage = 5;

    settings.osr_t = BME280_OVERSAMPLING_1X;
    settings.osr_p = BME280_OVERSAMPLING_1X;
    settings.osr_h = BME280_OVERSAMPLING_1X;
    settings.filter = BME280_FILTER_COEFF_OFF;

    rslt = bme280_set_sensor_settings(
        BME280_SEL_OSR_PRESS |
        BME280_SEL_OSR_TEMP |
        BME280_SEL_OSR_HUM |
        BME280_SEL_FILTER,
        &settings,
        &dev
    );

    if (rslt != BME280_OK)
    {
        i2c_hal_error = HAL_I2C_GetError(&hi2c1);
        Error_Handler();
    }

    /* Stage 6: Enable normal mode */

    error_stage = 6;

    rslt = bme280_set_sensor_mode(
        BME280_POWERMODE_NORMAL,
        &dev
    );

    if (rslt != BME280_OK)
    {
        i2c_hal_error = HAL_I2C_GetError(&hi2c1);
        Error_Handler();
    }

    /* Stage 7: Sensor is initialized */

    error_stage = 7;

    while (1)
    {
        rslt = bme280_get_sensor_data(
            BME280_ALL,
            &comp_data,
            &dev
        );

        if (rslt == BME280_OK)
        {
            temperature = comp_data.temperature;
            pressure = comp_data.pressure / 100.0f;
            humidity = comp_data.humidity;

            error_stage = 8;
        }
        else
        {
            i2c_hal_error = HAL_I2C_GetError(&hi2c1);
            error_stage = 9;
        }

        HAL_Delay(1000);
    }
}

/* BME280 I2C read callback */
int8_t user_i2c_read(uint8_t reg_addr,
                     uint8_t *reg_data,
                     uint32_t len,
                     void *intf_ptr)
{
    uint8_t address = *(uint8_t *)intf_ptr;

    HAL_StatusTypeDef status;

    status = HAL_I2C_Mem_Read(
        &hi2c1,
        (uint16_t)(address << 1),
        reg_addr,
        I2C_MEMADD_SIZE_8BIT,
        reg_data,
        (uint16_t)len,
        100
    );

    if (status == HAL_OK)
        return BME280_OK;

    return BME280_E_COMM_FAIL;
}

/* BME280 I2C write callback */
int8_t user_i2c_write(uint8_t reg_addr,
                      const uint8_t *reg_data,
                      uint32_t len,
                      void *intf_ptr)
{
    uint8_t address = *(uint8_t *)intf_ptr;

    HAL_StatusTypeDef status;

    status = HAL_I2C_Mem_Write(
        &hi2c1,
        (uint16_t)(address << 1),
        reg_addr,
        I2C_MEMADD_SIZE_8BIT,
        (uint8_t *)reg_data,
        (uint16_t)len,
        100
    );

    if (status == HAL_OK)
        return BME280_OK;

    return BME280_E_COMM_FAIL;
}

/* Bosch driver delay callback */
void user_delay_us(uint32_t period, void *intf_ptr)
{
    uint32_t delay_ms = (period + 999U) / 1000U;

    if (delay_ms > 0U)
        HAL_Delay(delay_ms);
}

/* System clock configuration */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    __HAL_RCC_PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(
        PWR_REGULATOR_VOLTAGE_SCALE2
    );

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

    RCC_ClkInitStruct.ClockType =
        RCC_CLOCKTYPE_HCLK |
        RCC_CLOCKTYPE_SYSCLK |
        RCC_CLOCKTYPE_PCLK1 |
        RCC_CLOCKTYPE_PCLK2;

    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

    if (HAL_RCC_ClockConfig(
        &RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
        Error_Handler();
}

/* I2C1 initialization */
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

/* USART1 initialization */
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

/* GPIO clock initialization */
static void MX_GPIO_Init(void)
{
    __HAL_RCC_GPIOH_CLK_ENABLE();
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
}

/* Error handler: error_stage remains visible in Watch 1 */
void Error_Handler(void)
{
    __disable_irq();

    while (1)
    {
        /* Inspect error_stage, rslt and i2c_hal_error */
    }
}