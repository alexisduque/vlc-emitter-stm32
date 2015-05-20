
/**
  ******************************************************************************
  * @file    Inc/4b6b.h
  * @author  Alexis Duque
  * @version V0.0.1
  * @date    16-May-2015
  * @brief   4B6B conversion
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __4B6B_H
#define __4B6B_H

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#define CODE_4B6B_0          (uint8_t)15
#define CODE_4B6B_1          (uint8_t)23
#define CODE_4B6B_2          (uint8_t)27
#define CODE_4B6B_3          (uint8_t)29
#define CODE_4B6B_4          (uint8_t)30
#define CODE_4B6B_5          (uint8_t)39
#define CODE_4B6B_6          (uint8_t)43
#define CODE_4B6B_7          (uint8_t)45
#define CODE_4B6B_8          (uint8_t)46
#define CODE_4B6B_9          (uint8_t)47
#define CODE_4B6B_10         (uint8_t)51
#define CODE_4B6B_11         (uint8_t)53
#define CODE_4B6B_12         (uint8_t)54
#define CODE_4B6B_13         (uint8_t)57
#define CODE_4B6B_14         (uint8_t)58
#define CODE_4B6B_15         (uint8_t)60

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
uint16_t convertFrom8To16(uint8_t dataFirst, uint8_t dataSecond);
uint8_t *convertFrom16To4(uint16_t dataAll);
uint8_t encode4b6b(uint8_t value);
#endif

/*****************************END OF FILE**************************************/
