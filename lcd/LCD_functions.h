#ifndef LCD_FUNCTIONS_H
#define LCD_FUNCTIONS_H

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "printf.h"

#define LCD_D0_PIN  (GPIO_Pin_6)
#define LCD_D0_PORT  (GPIOC)
#define LCD_D0_PORT_RCC  (RCC_APB2Periph_GPIOC)

#define LCD_D1_PIN  (GPIO_Pin_7)
#define LCD_D1_PORT  (GPIOC)
#define LCD_D1_PORT_RCC  (RCC_APB2Periph_GPIOC)

#define LCD_D2_PIN  (GPIO_Pin_8)
#define LCD_D2_PORT  (GPIOC)
#define LCD_D2_PORT_RCC  (RCC_APB2Periph_GPIOC)

#define LCD_D3_PIN  (GPIO_Pin_9)
#define LCD_D3_PORT  (GPIOC)
#define LCD_D3_PORT_RCC  (RCC_APB2Periph_GPIOC)

#define LCD_D4_PIN  (GPIO_Pin_10)
#define LCD_D4_PORT  (GPIOC)
#define LCD_D4_PORT_RCC  (RCC_APB2Periph_GPIOC)

#define LCD_D5_PIN  (GPIO_Pin_11)
#define LCD_D5_PORT  (GPIOC)
#define LCD_D5_PORT_RCC  (RCC_APB2Periph_GPIOC)

#define LCD_D6_PIN  (GPIO_Pin_12)
#define LCD_D6_PORT  (GPIOC)
#define LCD_D6_PORT_RCC  (RCC_APB2Periph_GPIOC)

#define LCD_D7_PIN  (GPIO_Pin_2)
#define LCD_D7_PORT  (GPIOD)
#define LCD_D7_PORT_RCC  (RCC_APB2Periph_GPIOD)

#define LCD_ENABLE_PIN  (GPIO_Pin_13)
#define LCD_ENABLE_PORT  (GPIOB)
#define LCD_ENABLE_PORT_RCC  (RCC_APB2Periph_GPIOB)

#define LCD_RW_PIN  (GPIO_Pin_14)
#define LCD_RW_PORT  (GPIOB)
#define LCD_RW_PORT_RCC  (RCC_APB2Periph_GPIOB)


#define LCD_RS_PIN  (GPIO_Pin_15)
#define LCD_RS_PORT  (GPIOB)
#define LCD_RS_PORT_RCC  (RCC_APB2Periph_GPIOB)

#define TIME_DELAY_BEFORE_ENABLE (4000)
#define TIME_DELAY_BEFORE_DISABLE (8000)

void RCC_Configuration();
void GPIO_Configuration();
void not_exact_time_delay(int delay);
void LCD_Configuration(void);
void RCC_Configuration(void);
void send_bit_to_port_and_pin(GPIO_TypeDef *port, int pin_number, uint8_t bit_state);
void lcd_enable();
void lcd_set_to_write();
void lcd_set_to_read();
void lcd_set_cursor_location_20_4(uint8_t x, uint8_t y);
void lcd_send_float(float a, uint8_t len);
void lcd_character_mode();
void lcd_instruction_mode();
void lcd_send_byte(char character);
void lcd_send_char(char character);
void lcd_send_int(int a, uint8_t len);
void lcd_send_instruction(char character);
void lcd_send_string(char *str);

#endif