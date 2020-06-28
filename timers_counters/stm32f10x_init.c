#include "stm32f10x_init.h"

void STM32_Configuration(void)
{
    LCD_Configuration();
    lcd_send_instruction(0b00000001);   // Clear display (Table 13 in datasheet)

    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    TIM1->CR1 |= TIM_CR1_CEN | TIM_CR1_DIR | TIM_CR1_CMS_0;
    TIM1->PSC = 60000;
    TIM1->ARR = 1000;
}



