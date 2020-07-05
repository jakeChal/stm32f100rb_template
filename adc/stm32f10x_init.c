#include "stm32f10x_init.h"
#include "stm32f10x_adc.h"

void STM32_Configuration(void)
{
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);

    /* Enable ADC1 clock and configure LCD */
    LCD_Configuration();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    //////////////// ADC configuration ///////////////////
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);

    //wake up temperature sensor
    ADC_TempSensorVrefintCmd(ENABLE);
    /* ADC1 regular channel14 configuration */ 
    ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1, ADC_SampleTime_41Cycles5);

    //////////////// ADC enable ///////////////////
    ADC_Cmd(ADC1, ENABLE);

}



