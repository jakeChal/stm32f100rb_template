#include "stm32f10x_init.h"
#include "stm32f10x_misc.h"
#define DHT22_PORT (GPIOB)
#define DHT22_PIN (GPIO_Pin_8)

void delay_ms(uint16_t nTime)
{
    TIM1->CNT = 0;
    while (TIM1->CNT < nTime)
        ;
}

void delay_us(uint16_t nTime)
{
    TIM15->CNT = 0;
    while (TIM15->CNT < nTime)
        ;
}

void set_pin_output(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIO Configuration for needed pins*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void set_pin_input(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
{

    GPIO_InitTypeDef GPIO_InitStructure;

    /* GPIO Configuration for needed pins*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

void DHT22_Start()
{
    set_pin_output(DHT22_PORT, DHT22_PIN);
    GPIO_WriteBit(DHT22_PORT, DHT22_PIN, 0);

    // Delay 1-10ms
    delay_ms(2);
    GPIO_WriteBit(DHT22_PORT, DHT22_PIN, 1);
    // Delay for 20-40 us
    delay_us(30);
    set_pin_input(DHT22_PORT, DHT22_PIN);
}

uint8_t DHT22_Check_response()
{
    uint8_t response = 0;

    delay_us(40);

    // if pin is low...
    if (!GPIO_ReadInputDataBit(DHT22_PORT, DHT22_PIN))
    {

        delay_us(80);

        // then pin is high...
        if (GPIO_ReadInputDataBit(DHT22_PORT, DHT22_PIN))
        {
            response = 1; // all good!
        }
        else
        {
            response = -1;
        }
    }

    // wait for the pin to go low
    while (GPIO_ReadInputDataBit(DHT22_PORT, DHT22_PIN))
    {

    }

    return response;
}

uint8_t DHT22_Read(void)
{
    uint8_t result = 0;

    for (int i = 0; i < 8; i++)
    {
        // wait for the pin to go high
        while (!GPIO_ReadInputDataBit(DHT22_PORT, DHT22_PIN));
        delay_us(40);

        if (GPIO_ReadInputDataBit(DHT22_PORT, DHT22_PIN))
        {
            BIT_SET(result, 7 - i);
        }
        else
        {
            BIT_CLEAR(result, 7 - i);
        }
        // wait for the pin to go low
        while (GPIO_ReadInputDataBit(DHT22_PORT, DHT22_PIN));
    }
    return result;
}

int main(void)
{
    STM32_Configuration();

    lcd_set_cursor_location_20_4(0, 0);
    lcd_send_string("Temperature:");

    lcd_set_cursor_location_20_4(2, 0);
    lcd_send_string("Humidity:");
    int response = 0;

    uint8_t humidity_byte1;
    uint8_t humidity_byte2;
    uint8_t temp_byte1;
    uint8_t temp_byte2;
    uint8_t checksum;

    uint16_t humidity;
    uint16_t temperature;

    while (1)
    {

        DHT22_Start();
        response = DHT22_Check_response();

        if (response)
        {
            humidity_byte1 = DHT22_Read();
            humidity_byte2 = DHT22_Read();
            temp_byte1 = DHT22_Read();
            temp_byte2 = DHT22_Read();
            checksum = DHT22_Read();

            humidity = (humidity_byte1 << 8) | humidity_byte2;
            temperature = (temp_byte1 << 8) | temp_byte2;

            // Write Temperature
            lcd_set_cursor_location_20_4(1, 0);
            lcd_send_float((float)(temperature / 10.f), 5);
            lcd_send_string(" C");
            // Write Humidity
            lcd_set_cursor_location_20_4(3, 0);
            lcd_send_float((float)(humidity / 10.f), 5);
            lcd_send_string(" %");
        }

        delay_ms(1000);
    }
}
