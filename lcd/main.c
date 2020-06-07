#include "stm32f10x.h"
#include "LCD_functions.h"

int main(void)
{

    STM32_Configuration();

    // Send a character (byte) "A" 0100 0001 to port C and D pin
    char letter = 'A';

    for (int i = 0; i < 30; i++) {
        lcd_send_char('A'+i);
    }

    send_bit_to_port_and_pin(LCD_RW_PORT, LCD_RW_PIN, 1);
    send_bit_to_port_and_pin(LCD_RS_PORT, LCD_RS_PIN, 1);

    while (1) {

    }
}
