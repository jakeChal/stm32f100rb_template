#include "stm32f10x.h"

void GPIO_toggle(GPIO_TypeDef* port, uint32_t pin) {
    port->ODR ^= 1<<pin;
}

void EXTI0_IRQHandler() {
    if(EXTI_GetITStatus(EXTI_Line0) != RESET) {
        GPIO_toggle(GPIOC, 9);
    }

    EXTI_ClearITPendingBit(EXTI_Line0);
}

int main(void) {
    // /* Initialize system */
    STM32_Configuration();

    while (1)
    {

    }
}
