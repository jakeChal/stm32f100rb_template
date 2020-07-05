#ifndef __STM32F10X_MISC_H__
#define __STM32F10X_MISC_H__

#include "stm32f10x.h"

/* a=target variable, b=bit number to act upon 0-n */
#define BIT_SET(a,b) ((a) |= (1ULL<<(b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b))))        // '!!' to make sure this returns 0 or 1

/* x=target variable, y=mask */
#define BITMASK_SET(x,y) ((x) |= (y))
#define BITMASK_CLEAR(x,y) ((x) &= (~(y)))
#define BITMASK_FLIP(x,y) ((x) ^= (y))
#define BITMASK_CHECK_ALL(x,y) (((x) & (y)) == (y))   // warning: evaluates y twice
#define BITMASK_CHECK_ANY(x,y) ((x) & (y))

/* Cortex M3 bit banding macros */

#define BITBAND_SRAM_REF   0x20000000
#define BITBAND_SRAM_BASE  0x22000000
#define BITBAND_SRAM(ptr,n) ((volatile uint32_t*)((BITBAND_SRAM_BASE + \
                                (((uint32_t)ptr)-BITBAND_SRAM_REF)*32 + (n*4))))
#define BITBAND_PERI_REF   0x40000000
#define BITBAND_PERI_BASE  0x42000000
#define BITBAND_PERI(ptr,n) ((volatile uint32_t*)((BITBAND_PERI_BASE + \
                                (((uint32_t)ptr)-BITBAND_PERI_REF)*32 + (n*4))))
                                
/* Cortex M3 Delay functions */
void TimingDelay_Decrement(void);
// void Delay(__IO uint32_t nTime);
// void Delay_ms(__IO uint32_t nTime);

/* STM32F10x GPIO helper functions */

#define GPIO_ToggleBit(port, pin) GPIO_WriteBit(port, pin, \
                            (BitAction) (1-GPIO_ReadOutputDataBit(port, pin)))

/* STM32F10x TIM helper functions */

typedef enum {UP = 0, DOWN = 1} TIM_Direction;

TIM_Direction TIM_ReadDirection(TIM_TypeDef* TIMx);

#endif
