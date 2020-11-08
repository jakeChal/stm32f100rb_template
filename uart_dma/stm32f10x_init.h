#ifndef __STM32F10x_INIT_H
#define __STM32F10x_INIT_H

#include "stm32f10x.h"

void STM32_Configuration(void);
void RCC_Configuration(void);
void GPIO_Configuration(void);
void NVIC_Configuration(void);
void TIM_Configuration(void);
void EXTI_Configuration(void);
void USART_Configuration(void);
void DMA_Configuration(void);

#define countof(a) (sizeof(a) / sizeof(*(a)))
#define data_size (countof(data))

#endif
