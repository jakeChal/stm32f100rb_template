#include "stm32f10x_init.h"
#include "stm32f10x_tim.h"

void Timers_Configuration()
{
    /* ms timer */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

    TIM_TimeBaseInitTypeDef TIM;
    TIM_TimeBaseStructInit(&TIM);
    TIM.TIM_Prescaler = (uint16_t)(SystemCoreClock / 1000) - 1;
    TIM.TIM_Period = UINT16_MAX;
    TIM.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM1, &TIM);

    TIM_Cmd(TIM1, ENABLE);

    /* us timer */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);

    TIM_TimeBaseStructInit(&TIM);
    TIM.TIM_Prescaler = (uint16_t)(SystemCoreClock / 1000000) - 1;
    TIM.TIM_Period = UINT16_MAX;
    TIM.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM15, &TIM);

    TIM_Cmd(TIM15, ENABLE);
}
void STM32_Configuration(void)
{
    LCD_Configuration();
    lcd_send_instruction(0b00000001); // Clear display (Table 13 in datasheet)

    Timers_Configuration();
}
