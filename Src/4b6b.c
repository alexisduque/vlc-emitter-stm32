/**
  ******************************************************************************
  * @file    Src/4b6b.c
  * @author  Alexis Duque
  * @version V0.0.1
  * @date    16-May-2015
  * @brief   4B6B conversion
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "4b6b.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

uint8_t encode4b6b(uint8_t value)
{
    switch (value)
    {
    case 1:
        return CODE_4B6B_1;
        break;
    case 2:
        return CODE_4B6B_2;
        break;
    case 3:
        return CODE_4B6B_3;
        break;
    case 4:
        return CODE_4B6B_4;
        break;
    case 5:
        return CODE_4B6B_5;
        break;
    case 6:
        return CODE_4B6B_6;
        break;
    case 7:
        return CODE_4B6B_7;
        break;
    case 8:
        return CODE_4B6B_8;
        break;
    case 9:
        return CODE_4B6B_9;
        break;
    case 10:
        return CODE_4B6B_10;
        break;
    case 11:
        return CODE_4B6B_11;
        break;
    case 12:
        return CODE_4B6B_12;
        break;
    case 13:
        return CODE_4B6B_13;
        break;
    case 14:
        return CODE_4B6B_14;
        break;
    case 15:
        return CODE_4B6B_15;
        break;
    case 0:
        return CODE_4B6B_0;
        break;
    default:
        return CODE_4B6B_0;
    }
}

uint16_t convertFrom8To16(uint8_t dataFirst, uint8_t dataSecond) {
    uint16_t dataBoth = 0x0000;

    dataBoth = dataFirst;
    dataBoth = dataBoth << 8;
    dataBoth |= dataSecond;
    return dataBoth;
}

uint8_t *convertFrom16To4(uint16_t dataAll) {
    static uint8_t arrayData[4] = { 0x00, 0x00, 0x00, 0x00 };

    *(arrayData) = (dataAll >> 12) & 0x000F;
    arrayData[1] = (dataAll >> 8) & 0x000F;
    arrayData[2] = (dataAll >> 4) & 0x000F;
    arrayData[3] = (dataAll & 0x000F);
    return arrayData;
}
/**
  * @}
  */

/**
  * @}
*/

/*****************************END OF FILE**************************************/
