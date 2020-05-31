#include "stm32f10x.h"

int main(void)
{

    // Setup each pin for output (Mode, Type, Speed, PUPD)
    // RCC APB2
    RCC->APB2ENR |= RCC_APB2Periph_GPIOC;
    RCC->APB2ENR |= RCC_APB2Periph_GPIOD;

    //user button clock
    RCC->APB2ENR |= RCC_APB2Periph_GPIOA;


    /* GPIOC Configuration: LED3 Output Push-Pull */

    // Output high on Port C pin 9, with PP
    GPIOC->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOC->CRH &= ~GPIO_CRH_CNF9_1;

    // Configure speed
    GPIOC->CRH |= GPIO_CRH_MODE9_1;
    GPIOC->CRH &= ~GPIO_CRH_MODE9_0;


    /* GPIOA Configuration: User Button Input Floating */

    // Floating input for pin 0
    GPIOA->CRL &= ~GPIO_CRL_CNF0_1;
    GPIOA->CRL |= GPIO_CRL_CNF0_0;

    // Input mode
    GPIOA->CRL &= ~GPIO_CRL_MODE0_1;
    GPIOA->CRL &= ~GPIO_CRL_MODE0_0;
    

    while (1) {
        if (GPIOA->IDR & GPIO_Pin_0) {
            GPIOC->BSRR |= GPIO_BSRR_BS9;
        }
        else {
            GPIOC->BSRR |= GPIO_BSRR_BR9;
        }
    }
}
