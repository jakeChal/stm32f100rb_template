#include "stm32f10x.h"
#include "LCD_functions.h"

int main(void)
{

    STM32_Configuration();

    lcd_send_instruction(0b00000001);   // Clear display (Table 13 in datasheet)

    lcd_send_instruction(0b00111000);   // Sets to 8-bit operation and selects 2-line 
                                        // display and 5 × 8dot character font

    lcd_send_instruction(0b00001110);   // Turns on display and cursor.

    lcd_send_instruction(0b00000110);   // Sets mode to increment theaddress by one and to shift the
                                        // cursor to the right at the time of write to the DD/CGRAM.

    lcd_send_char('H');
    lcd_send_char('E');
    lcd_send_char('L');
    lcd_send_char('L');
    lcd_send_char('O');
    lcd_send_char('!');

    lcd_send_instruction(0b11000000);   // Sets DDRAM address so thatthe cursor is positioned at the
                                        // head of the second line



    while (1) {

    }
}
