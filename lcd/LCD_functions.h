#ifndef LCD_FUNCTIONS_H
#define LCD_FUNCTIONS_H


#define LCD_D0_PIN  (6)
#define LCD_D0_PORT  (GPIOC)
#define LCD_D1_PIN  (7)
#define LCD_D1_PORT  (GPIOC)
#define LCD_D2_PIN  (8)
#define LCD_D2_PORT  (GPIOC)
#define LCD_D3_PIN  (9)
#define LCD_D3_PORT  (GPIOC)
#define LCD_D4_PIN  (10)
#define LCD_D4_PORT  (GPIOC)
#define LCD_D5_PIN  (11)
#define LCD_D5_PORT  (GPIOC)
#define LCD_D6_PIN  (12)
#define LCD_D6_PORT  (GPIOC)
#define LCD_D7_PIN  (2)
#define LCD_D7_PORT  (GPIOD)

void send_bits_to_port_and_pin(GPIO_TypeDef *port, int pin_number, uint8_t bit_state) {
    if (bit_state) {
        port->BSRR |= (1 << pin_number);
    }
    else {
        port->BRR |= (1 << pin_number);
    }
}

void send_char_to_lcd(char character) {
    send_bits_to_port_and_pin(LCD_D0_PORT, LCD_D0_PIN, character & 0b00000001);
    send_bits_to_port_and_pin(LCD_D1_PORT, LCD_D1_PIN, character & 0b00000010);
    send_bits_to_port_and_pin(LCD_D2_PORT, LCD_D2_PIN, character & 0b00000100);
    send_bits_to_port_and_pin(LCD_D3_PORT, LCD_D3_PIN, character & 0b00001000);
    send_bits_to_port_and_pin(LCD_D4_PORT, LCD_D4_PIN, character & 0b00010000);
    send_bits_to_port_and_pin(LCD_D5_PORT, LCD_D5_PIN, character & 0b00100000);
    send_bits_to_port_and_pin(LCD_D6_PORT, LCD_D6_PIN, character & 0b01000000);
    send_bits_to_port_and_pin(LCD_D7_PORT, LCD_D7_PIN, character & 0b10000000);
}

#endif