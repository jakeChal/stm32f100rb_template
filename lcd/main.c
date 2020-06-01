#include "stm32f10x.h"
#include "stm32f10x_init.h"
#include "LCD_functions.h"

int main(void)
{

    STM32_Configuration();

    // Send a character (byte) "A" 0100 0001 to port C and D pin
    send_char_to_lcd('F');

    while (1) {

    }
}
