#include "main.h"
#include "adc.h"
#include "stm32h7xx_hal.h"

ADC_HandleTypeDef hadc3 = {0};
DMA_HandleTypeDef hdma1 = {0};
GPIO_InitTypeDef pc0X = {0};
GPIO_InitTypeDef pf8Y = {0};


volatile uint16_t joystick_buffer[2];


void MG_adc_Init(void){

    __ADC3_CLK_ENABLE();

    hadc3.Instance = ADC3;

    hadc3.Init.ClockPrescaler = ADC_CLOCKPRESCALER_PCLK_DIV1;
    hadc3.Init.Resolution = ADC_RESOLUTION_16B;
    hadc3.Init.ContinuousConvMode = ENABLE;
    hadc3.Init.ScanConvMode = ADC_SCAN_ENABLE;
    hadc3.Init.EOCSelection = ADC_EOC_SEQ_CONV;
    hadc3.Init.LowPowerAutoWait = DISABLE;
    hadc3.Init.NbrOfConversion = 2;
    hadc3.Init.DiscontinuousConvMode = DISABLE;
    hadc3.Init.NbrOfDiscConversion = 0;
    hadc3.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc3.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
    hadc3.Init.ConversionDataManagement = ADC_CONVERSIONDATA_DMA_CIRCULAR;
    hadc3.Init.Overrun = ADC_OVR_DATA_OVERWRITTEN; //TODO
    hadc3.Init.LeftBitShift = ADC_LEFTBITSHIFT_NONE;
    hadc3.Init.OversamplingMode = DISABLE;
    hadc3.Init.Oversampling.RightBitShift = DISABLE;
    hadc3.Init.Oversampling.TriggeredMode = DISABLE;
    hadc3.Init.Oversampling.OversamplingStopReset = DISABLE;

   if( HAL_ADC_Init(&hadc3) != HAL_OK ){
        Error_Handler();
   }

   ADC_ChannelConfTypeDef ch7;
   ch7.Channel = ADC_CHANNEL_7;
   ch7.Rank = ADC_REGULAR_RANK_1;
   ch7.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;
   ch7.SingleDiff = ADC_SINGLE_ENDED;
   ch7.OffsetNumber = ADC_OFFSET_NONE;
   ch7.OffsetRightShift = DISABLE;
   ch7.OffsetSignedSaturation = DISABLE;

   if(HAL_ADC_ConfigChannel(&hadc3, &ch7) != HAL_OK){
        Error_Handler();
   }

   ADC_ChannelConfTypeDef ch10;
   ch10.Channel = ADC_CHANNEL_10;
   ch10.Rank = ADC_REGULAR_RANK_2;
   ch10.SamplingTime = ADC_SAMPLETIME_810CYCLES_5;
   ch10.SingleDiff = ADC_SINGLE_ENDED;
   ch10.OffsetNumber = ADC_OFFSET_NONE;
   ch10.OffsetRightShift = DISABLE;
   ch10.OffsetSignedSaturation = DISABLE;

   if(HAL_ADC_ConfigChannel(&hadc3, &ch10) != HAL_OK){
        Error_Handler();
   }

   //DMA init
   __HAL_RCC_DMA1_CLK_ENABLE();

   hdma1.Instance = DMA1_Stream0;
   hdma1.Init.Request = DMA_REQUEST_ADC3;
   hdma1.Init.Direction = DMA_PERIPH_TO_MEMORY;
   hdma1.Init.PeriphInc = DMA_PINC_DISABLE;
   hdma1.Init.MemInc = DMA_MINC_ENABLE;
   hdma1.Init.PeriphDataAlignment = DMA_PDATAALIGN_HALFWORD;
   hdma1.Init.MemDataAlignment = DMA_MDATAALIGN_HALFWORD;
   hdma1.Init.Mode = DMA_CIRCULAR;
   hdma1.Init.Priority = DMA_PRIORITY_LOW;
   hdma1.Init.FIFOMode = DMA_FIFOMODE_DISABLE;

   if(HAL_DMA_Init(&hdma1) != HAL_OK){
        Error_Handler();
   }


   //hadc3.DMA_Handle = &hdma1;
   __HAL_LINKDMA(&hadc3, DMA_Handle, hdma1);


   //TODO init PC0 PF8
   __HAL_RCC_GPIOC_CLK_ENABLE();
   __HAL_RCC_GPIOF_CLK_ENABLE();

   pc0X.Pin = GPIO_PIN_0;
   pc0X.Mode = GPIO_MODE_ANALOG;
   pc0X.Pull = GPIO_NOPULL;
   pc0X.Speed = GPIO_SPEED_FREQ_LOW;

   HAL_GPIO_Init(GPIOC, &pc0X);

   pf8Y.Pin = GPIO_PIN_8;
   pf8Y.Mode = GPIO_MODE_ANALOG;
   pf8Y.Pull = GPIO_NOPULL;
   pf8Y.Speed = GPIO_SPEED_FREQ_LOW;

   HAL_GPIO_Init(GPIOF, &pf8Y);

}