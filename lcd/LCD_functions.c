#include "LCD_functions.h"

#define PRECISION_POINTS (10) // 1 decimal point

void not_exact_time_delay(int delay) {
    volatile int i = 0;

    for(i = 0; i < delay; i++) {

    }
}
void LCD_Configuration(void)
{
    /* System Clocks Configuration */
    RCC_Configuration();

    /* GPIO Configuration */
    GPIO_Configuration();

    lcd_send_instruction(0b00000001); // Clear display (Table 13 in datasheet)

    lcd_send_instruction(0b00111000);   // Sets to 8-bit operation and selects 2-line 
                                        // display and 5 × 8dot character font

    lcd_send_instruction(0b00001110);   // Turns on display and cursor.

    lcd_send_instruction(0b00000110);   // Sets mode to increment the address by one and to shift the
                                        // cursor to the right at the time of write to the DD/CGRAM.

}

void RCC_Configuration(void)
{
    /* clock enable for needed ports*/
    RCC_APB2PeriphClockCmd(LCD_D0_PORT_RCC | LCD_D1_PORT_RCC | LCD_D2_PORT_RCC | LCD_D3_PORT_RCC |
                           LCD_D4_PORT_RCC | LCD_D5_PORT_RCC | LCD_D6_PORT_RCC | LCD_D7_PORT_RCC |
                           LCD_ENABLE_PORT_RCC | LCD_RW_PORT_RCC | LCD_RS_PORT_RCC,
                           ENABLE);

}

void GPIO_Configuration(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIO Configuration for needed pins*/
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;

    GPIO_InitStructure.GPIO_Pin = LCD_D0_PIN;
    GPIO_Init(LCD_D0_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_D1_PIN;
    GPIO_Init(LCD_D1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_D2_PIN;
    GPIO_Init(LCD_D2_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_D3_PIN;
    GPIO_Init(LCD_D3_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_D4_PIN;
    GPIO_Init(LCD_D4_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_D5_PIN;
    GPIO_Init(LCD_D5_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_D6_PIN;
    GPIO_Init(LCD_D6_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_D7_PIN;
    GPIO_Init(LCD_D7_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_ENABLE_PIN;
    GPIO_Init(LCD_ENABLE_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_RW_PIN;
    GPIO_Init(LCD_RW_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = LCD_RS_PIN;
    GPIO_Init(LCD_RS_PORT, &GPIO_InitStructure);
}

void send_bit_to_port_and_pin(GPIO_TypeDef *port, int pin_number, uint8_t bit_state) {
    if (bit_state) {
        port->BSRR |= pin_number;
    }
    else {
        port->BRR |= pin_number;
    }
}

void lcd_enable() {
    not_exact_time_delay(TIME_DELAY_BEFORE_ENABLE);
    send_bit_to_port_and_pin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, 1);
}

void lcd_set_to_write() {
    send_bit_to_port_and_pin(LCD_RW_PORT, LCD_RW_PIN, 0);
}

void lcd_set_to_read() {
    send_bit_to_port_and_pin(LCD_RW_PORT, LCD_RW_PIN, 1);
}

void lcd_instruction_mode() {
    send_bit_to_port_and_pin(LCD_RS_PORT, LCD_RS_PIN, 0);
}

void lcd_character_mode() {
    send_bit_to_port_and_pin(LCD_RS_PORT, LCD_RS_PIN, 1);
}

void lcd_send_byte(char character) {
    send_bit_to_port_and_pin(LCD_D0_PORT, LCD_D0_PIN, character & 0b00000001);
    send_bit_to_port_and_pin(LCD_D1_PORT, LCD_D1_PIN, character & 0b00000010);
    send_bit_to_port_and_pin(LCD_D2_PORT, LCD_D2_PIN, character & 0b00000100);
    send_bit_to_port_and_pin(LCD_D3_PORT, LCD_D3_PIN, character & 0b00001000);
    send_bit_to_port_and_pin(LCD_D4_PORT, LCD_D4_PIN, character & 0b00010000);
    send_bit_to_port_and_pin(LCD_D5_PORT, LCD_D5_PIN, character & 0b00100000);
    send_bit_to_port_and_pin(LCD_D6_PORT, LCD_D6_PIN, character & 0b01000000);
    send_bit_to_port_and_pin(LCD_D7_PORT, LCD_D7_PIN, character & 0b10000000);

    not_exact_time_delay(TIME_DELAY_BEFORE_DISABLE);
    send_bit_to_port_and_pin(LCD_ENABLE_PORT, LCD_ENABLE_PIN, 0);

}

void lcd_send_char(char character) {
    lcd_set_to_write();
    lcd_character_mode();
    lcd_enable();

    lcd_send_byte(character);
}

void lcd_send_instruction(char character) {
    lcd_set_to_write();
    lcd_instruction_mode();
    lcd_enable();

    lcd_send_byte(character);
}

void lcd_send_string(char *str) {

    while (*str)
        lcd_send_char(*str++);
}

void lcd_send_int(int a, uint8_t len)
{

    char num2str[len];
    sprintf(num2str, "%d", a);

    lcd_send_string(num2str);
}

void lcd_send_float(float a, uint8_t len) {

    // shitty workaround ... 
    // TODO: use a libc with float support for printfs
    char num2str[len];
    int integer_part = (int) a;
    int decimal_part = ((int)(a * PRECISION_POINTS) % PRECISION_POINTS);

    sprintf(num2str, "%d", integer_part);
    lcd_send_string(num2str);

    sprintf(num2str, ".%d", decimal_part);
    lcd_send_string(num2str);

}

void lcd_set_cursor_location_20_4(uint8_t x, uint8_t y) {
    uint8_t row_offset[4] = {0x0, 0x40, 0x14, 0x54};
    lcd_send_instruction(0b10000000 + y + row_offset[x]);
}