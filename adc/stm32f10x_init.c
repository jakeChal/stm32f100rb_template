#include "stm32f10x_init.h"

void STM32_Configuration(void)
{
    RCC_ADCCLKConfig(RCC_PCLK2_Div2); 

    /* Enable ADC1 clock and configure LCD */
    LCD_Configuration();
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
}



