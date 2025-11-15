/* Header */
/**
 ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/

#include "main.h"
#include <stm32f4xx_hal_rcc.h>
#include <stdio.h>

/* Private includes ----------------------------------------------------------*/


/* Private typedef -----------------------------------------------------------*/


/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/


/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/

void SystemClock_Config(void);
void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);
void task5_handler(void);
// void ITM_Init(void)
// {
//     // Włącz TRCENA
//     *((volatile uint32_t*)0xE000EDFC) |= (1 << 24);

//     // Odblokuj ITM
//     *((volatile uint32_t*)0xE0000FB0) = 0xC5ACCE55;

//     // Włącz ITM i port 0
//     *((volatile uint32_t*)0xE0000E00) = 0x0001000D; // ITMENA | SYNCENA | SWOENA
//     *((volatile uint32_t*)0xE0000E00 + 0x0) = 1;     // TER port 0
// }
/* Private user code ---------------------------------------------------------*/
#include <stdint.h>

// Rejestry ITM i debug
#define ITM_STIMULUS_PORT0  (*((volatile uint32_t*)0xE0000000U))
#define ITM_TCR             (*((volatile uint32_t*)0xE0000E00U))
#define ITM_TER             (*((volatile uint32_t*)0xE0000E00U + 0x0))
#define DEMCR               (*((volatile uint32_t*)0xE000EDFCU))
#define ITM_LAR             (*((volatile uint32_t*)0xE0000FB0U))

// -----------------------------------------------------------------------------
// Funkcja inicjalizuje ITM i port 0
// -----------------------------------------------------------------------------
void ITM_Init(void)
{
    // Włącz TRCENA (Debug Exception and Monitor Control)
    DEMCR |= (1 << 24);

    // Odblokuj ITM
    ITM_LAR = 0xC5ACCE55;

    // Włącz ITM (ITMENA), synchronizację (SYNCENA) i SWOENA
    ITM_TCR = 0x0001000D;

    // Włącz port 0
    ITM_TER = 1;
}

// -----------------------------------------------------------------------------
// Funkcja wysyła znak przez port 0 ITM
// -----------------------------------------------------------------------------
// void ITM_SendChar(uint8_t ch)
// {
//     // Czekaj, aż ITM jest włączone
//     while ((ITM_TCR & 1) == 0);

//     // Czekaj, aż port 0 gotowy do przyjęcia znaku
//     while (!(ITM_STIMULUS_PORT0 & 1));

//     // Wyślij znak
//     ITM_STIMULUS_PORT0 = ch;
// }


int main(void)
{
  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();
 uint16_t dupa = 0; 
 dupa ++;
//  ITM_Init();

ITM_Init();

setvbuf(stdout, NULL, _IONBF, 0);  // wyłącz buforowanie to wszystko bylo przez buforowanie xddddd
  /* USER CODE BEGIN Init */
  /* USER CODE END Init */
  
  /* Configure the system clock */
  SystemClock_Config();
  
  /* Initialize all configured peripherals */
  
  /* Infinite loop */
  while (1)
  {
    task1_handler();

        // Proste opóźnienie
        for (volatile int j = 0; j < 1000000; j++);}
}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

void task1_handler(void)
{
  printf("I'm in task 1");
}
void task2_handler(void)
{
  printf("I'm in task 2");
}
void task3_handler(void)
{
  printf("I'm in task 3");
}
void task4_handler(void)
{
  printf("I'm in task 4");
}
void task5_handler(void)
{
  printf("I'm in task 5");
}

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
