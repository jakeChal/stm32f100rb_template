#include "stm32f10x.h"
#include "stm32f10x_init.h"
int main(void)
{
    /* Initialize system */
    STM32_Configuration();

    while (1)
    {
    // turn on the LED when button is pressed
    // if the button is pressed (IDR input data register)
        if (GPIOA->IDR & GPIO_Pin_0) {
            GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_SET);
        }
        else {
            GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_RESET);
        }

    }

}
