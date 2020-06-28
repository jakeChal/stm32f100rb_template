#include "stm32f10x_init.h"

int main(void)
{
    STM32_Configuration();

    lcd_set_cursor_location_20_4(0, 0);
    lcd_send_string("counter:");

    lcd_set_cursor_location_20_4(2, 0);
    lcd_send_string("prescaler:");
    while (1) {

        lcd_set_cursor_location_20_4(1, 0);
        lcd_send_int(TIM1->CNT, 5);

        lcd_set_cursor_location_20_4(3, 0);
        lcd_send_int(TIM1->PSC, 5);
        not_exact_time_delay(80000);
    }
}
