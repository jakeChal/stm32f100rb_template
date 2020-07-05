#include "stm32f10x.h"
#include "LCD_functions.h"

int main(void)
{

    LCD_Configuration();

    // Memory map for 20x4 HD44780 here: http://web.alfredstate.edu/faculty/weimandn/lcd/lcd_addressing/lcd_addressing_index.html

    lcd_send_string("Iaso kokla");
    lcd_send_instruction(0b11000000);   // Sets DDRAM address so thatthe cursor is positioned at the
                                        // head of the second line (+ 40h)

    lcd_send_int(123, 3);
    lcd_send_instruction(0b10010100);   // Sets DDRAM address so thatthe cursor is positioned at the
                                        // head of the 3rd line (+ 14h)

    lcd_send_float(1.667f, 6);

    while (1) {

    }
}
