#include "stm32f10x.h"
#include "stm32f10x_misc.h"

#include "stm32f10x_init.h"
#include "printf.h"

void __io_putchar(void* p, char ch)
{
    /* Write a character to the USART */
    USART_SendData(USART1, (uint8_t) ch);

    /* Loop until the end of transmission */
    while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}
}


int main(void)
{
    /* Initialize system */
    STM32_Configuration();
    char button_pressed = 0;
    int button_pressed_conf_level = 0;
    int button_released_conf_level = 0;
    char LED_state = 0;
    int confidence_thresh = 300;

    while (1) {
        // turn on the LED when button is pressed
        // if the button is pressed (IDR input data register)
        if (GPIOA->IDR & GPIO_Pin_0) {
            if (!button_pressed) {
                // Increase button pressed confidence
                if (button_pressed_conf_level > confidence_thresh) {
                    if (!LED_state) {
                        GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_SET);
                    }
                    else {
                        GPIO_WriteBit(GPIOC, GPIO_Pin_9, Bit_RESET);
                    }
                    LED_state = !LED_state;
                    button_pressed = 1;
                }
                else {
                    button_pressed_conf_level++;
                    button_released_conf_level = 0;
                }            
            }
        }
        else {

            if (button_pressed) {
                // Increase button pressed confidence
                if (button_released_conf_level > confidence_thresh) {
                    button_pressed = 0;
                }
                else {
                    button_released_conf_level++;
                    button_pressed_conf_level = 0;
                }            
            }
        }

    }
}
