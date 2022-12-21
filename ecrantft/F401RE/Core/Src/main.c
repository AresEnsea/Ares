/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "spi.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include "ili9341.h"
#include "fonts.h"
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

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
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
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
  ILI9341_Unselect();
  ILI9341_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	// Check border
	ILI9341_FillScreen(ILI9341_BLACK);

	for(int x = 0; x < ILI9341_WIDTH; x++) {
	  ILI9341_DrawPixel(x, 0, ILI9341_RED);
	  ILI9341_DrawPixel(x, ILI9341_HEIGHT-1, ILI9341_RED);
	}

	for(int y = 0; y < ILI9341_HEIGHT; y++) {
	  ILI9341_DrawPixel(0, y, ILI9341_RED);
	  ILI9341_DrawPixel(ILI9341_WIDTH-1, y, ILI9341_RED);
	}

	HAL_Delay(3000);

	// Check fonts
	ILI9341_FillScreen(ILI9341_BLACK);
	ILI9341_WriteString(0, 0, "GIGA BG", Font_7x10, ILI9341_RED, ILI9341_BLACK);
	ILI9341_WriteString(0, 3*10, "GIGA BG", Font_11x18, ILI9341_GREEN, ILI9341_BLACK);
	ILI9341_WriteString(0, 3*10+3*18, "GIGA BG", Font_16x26, ILI9341_BLUE, ILI9341_BLACK);

	HAL_Delay(1000);
	ILI9341_InvertColors(true);
	HAL_Delay(1000);
	ILI9341_InvertColors(false);

	HAL_Delay(5000);

	// Check colors
	ILI9341_FillScreen(ILI9341_WHITE);
	ILI9341_WriteString(0, 0, "GIGA BG", Font_11x18, ILI9341_BLACK, ILI9341_WHITE);
	HAL_Delay(500);

	ILI9341_FillScreen(ILI9341_BLUE);
	ILI9341_WriteString(0, 0, "GIGA BG", Font_11x18, ILI9341_BLACK, ILI9341_BLUE);
	HAL_Delay(500);

	ILI9341_FillScreen(ILI9341_RED);
	ILI9341_WriteString(0, 0, "GIGA BG", Font_11x18, ILI9341_BLACK, ILI9341_RED);
	HAL_Delay(500);

	ILI9341_FillScreen(ILI9341_GREEN);
	ILI9341_WriteString(0, 0, "GIGA BG", Font_11x18, ILI9341_BLACK, ILI9341_GREEN);
	HAL_Delay(500);

	ILI9341_FillScreen(ILI9341_CYAN);
	ILI9341_WriteString(0, 0, "GIGA BG", Font_11x18, ILI9341_BLACK, ILI9341_CYAN);
	HAL_Delay(500);

	ILI9341_FillScreen(ILI9341_MAGENTA);
	ILI9341_WriteString(0, 0, "GIGA BG", Font_11x18, ILI9341_BLACK, ILI9341_MAGENTA);
	HAL_Delay(500);

	ILI9341_FillScreen(ILI9341_YELLOW);
	ILI9341_WriteString(0, 0, "GIGA BG", Font_11x18, ILI9341_BLACK, ILI9341_YELLOW);
	HAL_Delay(500);

	ILI9341_FillScreen(ILI9341_BLACK);
	ILI9341_WriteString(0, 0, "GIGA BG", Font_11x18, ILI9341_WHITE, ILI9341_BLACK);
	HAL_Delay(500);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
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

#ifdef  USE_FULL_ASSERT
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
