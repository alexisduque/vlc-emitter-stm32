/**
  ******************************************************************************
  * @file    Src/main.c
  * @author  Alexis Duque
  * @version V0.0.1
  * @date    30-Avril-2015
  * @brief   VLC Emitter Driver
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "4b6b.h"
#include "stm32l0xx_it.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define BIT_PERIOD      1
//#define CODE_4B6B
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart2;

uint8_t aRxBuffer[RXBUFFERSIZE];
uint8_t message[] = "11011101";
uint16_t counter = 0;
int i = 0;
/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
void GPIO_Init();
void sendManchesterMessage(void);
void sendManchesterCounter(void);
void send4B6BCounter();
void send4B6BEncoded6Bits(uint8_t bits);
void sendManchesterDefaultMessage(void);
void sendPreambule(void);
void sendStartBit(void);
void sendStopBit(void);
void sendNoData(void);
void delay (int a);
void send0(void);
void send1(void);
long time = 0;
//void USART2_UART_Init();

GPIO_InitTypeDef GPIO_InitStruct;

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    SysTick_Init();
    GPIO_Init();
    //USART2_UART_Init();
    BSP_PB_Init(BUTTON_KEY, BUTTON_MODE_EXTI);
    while (1)
    {
        time++;
        if (time > 10)
        {
            sendPreambule();
            //sendStartBit();
            send4B6BCounter();
            sendStopBit();
            counter++;
            time = 0;
        }
        else
        {
            sendNoData();
        }

    }
}


/**
  * @brief EXTI line detection callback.
  * @param GPIO_Pin: Specifies the pins connected EXTI line
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)


{
    if(GPIO_Pin == KEY_BUTTON_PIN)
    {
        sendPreambule();
        sendStartBit();
#ifndef CODE_4B6B
        sendManchesterDefaultMessage();
        //sendManchesterCounter();
#else
        send4B6BCounter();
#endif
        sendStopBit();
        counter++;
    }

}

void delay (int a)
{
    volatile int i,j;

    for (i=0 ; i < a ; i++)
    {
        j++;
    }

    return;
}

/** Configure pins as
        * Analog
        * Input
        * Output
        * EVENT_OUT
        * EXTI
*/
void GPIO_Init(void)
{

    GPIO_InitTypeDef GPIO_InitStruct;

    /* GPIO Ports Clock Enable */
    __GPIOC_CLK_ENABLE();
    __GPIOH_CLK_ENABLE();
    __GPIOA_CLK_ENABLE();

    /*Configure GPIO pin : PC13 */
    GPIO_InitStruct.Pin = GPIO_PIN_13;
    GPIO_InitStruct.Mode = GPIO_MODE_EVT_RISING;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* -2- Configure PA.5 IO in output push-pull mode to
           drive external LEDs */
    GPIO_InitStruct.Pin = (GPIO_PIN_5);
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FAST;

    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
}

void sendPreambule(void)
{
    send1();
    send1();
    send0();
    send1();
    send0();
    send0();

    send0();
    send0();
    send1();
    send0();
    send1();
    send1();
}

void sendStartBit(void)
{
    send0();
}

void sendStopBit(void)
{
    send0();
    send0();
    send1();
    send0();
    send1();
    send1();
}

void sendManchesterDefaultMessage(void)
{
    send1();
    send0();
    send1();
    send0();
    send0();
    send1();
    send1();
    send0();
    send1();
    send0();
    send1();
    send0();
    send0();
    send1();
    send1();
    send0();
}

void sendManchesterMessage()
{
    for(i=0; i<sizeof(message); i++)
    {
        switch(message[i])
        {
        case 0:
            send0();
            send1();
            break;

        case 1:
            send1();
            send0();
            break;

        default:
            break;
        }
    }
}
void sendManchesterCounter()
{
    for(i=16; i>0; i--)
    {
        if (counter & (1 << (i-1)))
        {
            send1();
            send0();
        }
        else
        {
            send0();
            send1();
        }
    }
}

void send4B6BCounter()
{
    int i = 0;
    uint8_t * splitedCounter = convertFrom16To4(counter);
    for(i=0;i<4;i++)
    {
        send4B6BEncoded6Bits(encode4b6b(splitedCounter[i]));
    }
    /*
    uint8_t first4b6b = encode4b6b(splitedCounter[0]);
    uint8_t sec4b6b = encode4b6b(splitedCounter[1]);
    uint8_t sec4b6b = encode4b6b(splitedCounter[2]);
    uint8_t sec4b6b = encode4b6b(splitedCounter[3]);
    send4B6BEncoded6Bits(first4b6b);
    send4B6BEncoded6Bits(sec4b6b);
    */
}

void send4B6BEncoded6Bits(uint8_t bits)
{
    int i = 0;
    for (i=6; i>0; i--)
    {
        if (bits & (1 << (i-1)))
        {
            send1();
        }
        else
        {
            send0();
        }
    }
}

void sendNoData()
{
    send1();
    send1();
    send1();
    send0();
    send0();
    send0();

    send0();
    send0();
    send0();
    send1();
    send1();
    send1();
}

void send1()
{
    GPIOA->BSRR = GPIO_PIN_5;
    delay(BIT_PERIOD);
}

void send0()
{
    GPIOA->BRR = GPIO_PIN_5 ;
    delay(BIT_PERIOD);
}

/** System Clock Configuration
*/
void SystemClock_Config(void)
{

    RCC_OscInitTypeDef RCC_OscInitStruct;
    RCC_ClkInitTypeDef RCC_ClkInitStruct;

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

#ifdef UART_ENABLED

/* USART2 init function */
void USART2_UART_Init(void)
{

    huart2.Instance = USART2;
    huart2.Init.BaudRate = 9600;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    huart2.Init.OneBitSampling = UART_ONEBIT_SAMPLING_DISABLED;
    huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
    HAL_UART_Init(&huart2);

}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart2)
{
    while(1)
    {
    }
}

/**
  * @brief  Rx Transfer completed callback
  * @param  UartHandle: UART handle
  * @note   This example shows a simple way to report end of IT Rx transfer, and
  *         you can add your own implementation.
  * @retval None
  */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart2)
{
    /* Set transmission flag: trasfer complete*/
    HAL_UART_Transmit(huart2, (uint8_t*)&"OK\r\n", 6, 10);
}

#endif
/**
  * @}
  */

/**
  * @}
*/

/*****************************END OF FILE**************************************/
