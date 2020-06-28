#include "stm32f10x_init.h"
#include "stm32f10x_misc.h"

void Delay_ms(uint16_t nTime)
{
    TIM1->CNT = 0;
    while (TIM1->CNT < nTime);
}

void Delay_us(uint16_t nTime)
{
    TIM15->CNT = 0;
    while (TIM15->CNT < nTime);
}

int main(void)
{
    STM32_Configuration();

    lcd_set_cursor_location_20_4(0, 0);
    lcd_send_string("temperature:");

    lcd_set_cursor_location_20_4(2, 0);
    lcd_send_string("Humidity:");
    int foo = 0;

    while (1)
    {
        // lcd_set_cursor_location_20_4(1, 0);
        // lcd_send_int(foo, 5);

        // lcd_set_cursor_location_20_4(3, 0);
        // Delay_ms(1000);
        // for (int i = 0; i < 100; i++) {
        //     Delay_us(10000);
        // }
        // foo++;
    }
}
