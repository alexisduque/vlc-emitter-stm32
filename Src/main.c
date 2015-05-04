/**
  ******************************************************************************
  * @file    Src/main.c
  * @author  Alexis Duque
  * @version V0.0.1
  * @date    30-March-2015
  * @brief   Main ADC conversion with buffering
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);

GPIO_InitTypeDef GPIO_InitStruct;

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    SysTick_Init();

    __GPIOA_CLK_ENABLE();

    /* -2- Configure PA.5 IO in output push-pull mode to
           drive external LEDs */
    GPIO_InitStruct.Pin = (GPIO_PIN_5);
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
/*
    while (1)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
    }
*/
    while (1)
    {
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
        HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
    }

}


/** System Clock Configuration
*/
void SystemClock_Config(void)
{

    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;
    RCC_PeriphCLKInitTypeDef PeriphClkInit;

    __PWR_CLK_ENABLE();

    __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
    RCC_OscInitStruct.HSIState = RCC_HSI_ON;
    RCC_OscInitStruct.HSICalibrationValue = 16;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
    RCC_OscInitStruct.PLL.PLLMUL = RCC_PLLMUL_4;
    RCC_OscInitStruct.PLL.PLLDIV = RCC_PLLDIV_2;
    HAL_RCC_OscConfig(&RCC_OscInitStruct);

    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_SYSCLK;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;
    HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1);

    __SYSCFG_CLK_ENABLE();
}

/**
  * @brief  This function is executed in case of error occurrence.
  * @param  None
  * @retval None
  */
void Error_Handler(void)
{
}

#ifdef USE_FULL_ASSERT

/**
   * @brief Reports the name of the source file and the source line number
   * where the assert_param error has occurred.
   * @param file: pointer to the source file name
   * @param line: assert_param error line source number
   * @retval None
   */
void assert_failed(uint8_t* file, uint32_t line)
{
    printf("Wrong parameters value: file %s on line %d\r\n", file, line);
}

#endif

/**
  * @}
  */

/**
  * @}
*/

/*****************************END OF FILE**************************************/
