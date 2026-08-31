#ifndef __ADC_H__
#define __ADC_H__

#include "stm32h7xx_hal.h"

void MG_adc_Init(void);
extern ADC_HandleTypeDef hadc3;
extern DMA_HandleTypeDef hdma1;
extern volatile uint16_t joystick_buffer[2];

#endif