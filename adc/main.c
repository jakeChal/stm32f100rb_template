#include "stm32f10x.h"
#include "stm32f10x_init.h"

uint16_t AD_value;

// Reference voltage is 3.3V - [Voltage drop at D1] = 3.3 - 0.3 = 3V
const uint16_t V25 = 1925;// V25=1.41V @ ref 3.3V => (1.41/3)*4096 = 1925
const uint16_t Avg_Slope = 6; // avg_slope=4.3mV/C @ ref 3V => (0.0043/3.3)*4096 = 5.83
uint16_t TemperatureC;

int main(void)
{
    STM32_Configuration();

    //////////////// ADC calibration ///////////////////
    lcd_set_cursor_location_20_4(0, 0);
    lcd_send_string("Starting calibration");
    not_exact_time_delay(50000);

    /* Enable ADC1 reset calibaration register */
    ADC_ResetCalibration(ADC1);
    /* Check the end of ADC1 reset calibration register */
    while(ADC_GetResetCalibrationStatus(ADC1));

    /* Start ADC1 calibration */
    ADC_StartCalibration(ADC1);
    /* Check the end of ADC1 calibration */
    while(ADC_GetCalibrationStatus(ADC1));

    lcd_set_cursor_location_20_4(0, 0);
    lcd_send_string("Finished calibration");
    
    not_exact_time_delay(50000);

    lcd_send_instruction(0b00000001);   // Clear display (Table 13 in datasheet)

    while (1) {
        //Start ADC1 Software Conversion
        ADC_SoftwareStartConvCmd(ADC1, ENABLE);

        //wait for conversion complete
        while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC)){}


        //read ADC value
        AD_value=ADC_GetConversionValue(ADC1);
        //clear EOC flag
        ADC_ClearFlag(ADC1, ADC_FLAG_EOC);

        TemperatureC = (uint16_t)((V25-AD_value)/Avg_Slope+25);

        lcd_set_cursor_location_20_4(0, 0);
        lcd_send_string("ADC value:");
        lcd_set_cursor_location_20_4(1, 0);
        lcd_send_int(AD_value, 5);

        lcd_set_cursor_location_20_4(2, 0);
        lcd_send_string("Temperature:");
        lcd_set_cursor_location_20_4(3, 0);
        lcd_send_int(TemperatureC, 6);  
        not_exact_time_delay(800000);

    }
}
