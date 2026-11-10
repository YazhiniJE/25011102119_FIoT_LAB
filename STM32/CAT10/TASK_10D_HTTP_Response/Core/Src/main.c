/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2026 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include <string.h>
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
	uint8_t rx_data[800];
	uint8_t rx_char;
	uint16_t array_index;
	uint8_t cmd1[] = "AT\r\n";
	uint8_t cmd2[] = "AT+CWMODE=1\r\n";
	uint8_t cmd3[] = "AT+CWJAP=\"YOUR_WIFI_SSID\",\"YOUR_WIFI_PASSWORD\"\r\n";
	uint8_t cmd4[] = "AT+CIFSR\r\n";
	uint8_t cmd5[] = "AT+CIPMUX=1\r\n";
	uint8_t cmd6[] = "AT+CIPSERVER=1,80\r\n";
	char response[300];
	char cmd[50];
	uint32_t counter = 0;
	char body[150];

	void clear_buffer(void)
	{
		memset(rx_data, 0, sizeof(rx_data));
		array_index = 0;
		}
		void receive_response(void)
		{
			while (1)
			{
			if (HAL_UART_Receive(&huart2, &rx_char, 1, 20000) == HAL_OK)
			{
				if (array_index < 799)
				{
				rx_data[array_index] = rx_char;
				array_index++;
				rx_data[array_index] = '\0';
				}

				if (strstr((char *)rx_data, "OK") != NULL)
				{
				break;
				}
				if (strstr((char *)rx_data, "ERROR") != NULL ||
				strstr((char *)rx_data, "FAIL") != NULL)
				{
				break;
				}
				if (strstr((char *)rx_data, "<") != NULL)
				{
				break;
				}
				}
			else
				{
				break;
				}
	}
	}

void send_http_response(void)
{
    counter++;

    sprintf(body,
            "<html><body>"
						"<h1>New num %lu</h1>"
            "</body></html>",
            (unsigned long)counter);

    sprintf(response,
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length: %d\r\n"
            "Connection: close\r\n"
            "\r\n"
            "%s",
            (int)strlen(body), body);

    sprintf(cmd, "AT+CIPSEND=0,%d\r\n", (int)strlen(response));

    HAL_UART_Transmit(&huart2, (uint8_t *)cmd, strlen(cmd), 1000);

    while (HAL_UART_Receive(&huart2, &rx_char, 1, 5000) == HAL_OK)
    {
        if (rx_char == '>')
            break;
    }

    HAL_UART_Transmit(&huart2, (uint8_t *)response, strlen(response), 5000);

    receive_response();

    HAL_UART_Transmit(&huart2, (uint8_t *)"AT+CIPCLOSE=0\r\n", 15, 1000);
}

int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_Delay(2000);
	clear_buffer();
	HAL_UART_Transmit(&huart2, cmd1, strlen((char *)cmd1), HAL_MAX_DELAY);
	receive_response();
	clear_buffer();
	HAL_UART_Transmit(&huart2, cmd2, strlen((char *)cmd2), HAL_MAX_DELAY);
	receive_response();
	clear_buffer();
	HAL_UART_Transmit(&huart2, cmd3, strlen((char *)cmd3), HAL_MAX_DELAY);
	receive_response();
	clear_buffer();
	HAL_UART_Transmit(&huart2, cmd4, strlen((char *)cmd4), HAL_MAX_DELAY);
	receive_response();
	clear_buffer();
	HAL_UART_Transmit(&huart2, cmd5, strlen((char *)cmd5), HAL_MAX_DELAY);
	receive_response();
	clear_buffer();
	HAL_UART_Transmit(&huart2, cmd6, strlen((char *)cmd6), HAL_MAX_DELAY);
	receive_response();

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		if (HAL_UART_Receive(&huart2, &rx_char, 1, HAL_MAX_DELAY) == HAL_OK)
    {
        if (array_index < sizeof(rx_data) - 1)
        {
            rx_data[array_index++] = rx_char;
            rx_data[array_index] = '\0';
        }

        if (strstr((char *)rx_data, "+IPD,0,") != NULL &&
            strstr((char *)rx_data, "GET /") != NULL)
        {
            send_http_response();

            clear_buffer();
        }
			}
		}
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */


/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  /* USER CODE BEGIN MX_GPIO_Init_1 */

  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /* USER CODE BEGIN MX_GPIO_Init_2 */

  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
