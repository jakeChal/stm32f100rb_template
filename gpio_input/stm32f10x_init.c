#include "stm32f10x.h"
#include "stm32f10x_init.h"

void STM32_Configuration(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    /* Set SysTick to 1ms */
    SysTick_Config(SystemCoreClock / 1000);
}

void RCC_Configuration(void)
{
    /* GPIOC clock enable (LED3/LED4) */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

    /* GPIOA clock enable (USER Button) */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIOC Configuration: LED3 Output Push-Pull */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /* GPIOA Configuration: User Button Input Floating */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;

    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* Select GPIOA Pin 0 as EXTI Line 0 */
    // GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

}

