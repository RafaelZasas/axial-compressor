/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "hardware/adc.h"

#define LED_PIN 14
#define POT_PIN 26
#define SWITCH 26

float map(long x, long in_min, long in_max, long out_min, long out_max) {
	return (x - in_min) * (out_max - out_min)/ (in_max - in_min) + out_min;
}


int main() {
    stdio_init_all();
    printf("ADC Example, measuring GPIO26\n");
 
    adc_init();
 
    // Make sure GPIO is high-impedance, no pullups etc
    adc_gpio_init(POT_PIN);
    // Select ADC input 0 (GPIO26)
    adc_select_input(0);
    gpio_set_function(LED_PIN, GPIO_FUNC_PWM);
    uint slice_num = pwm_gpio_to_slice_num(LED_PIN);

    pwm_set_wrap(slice_num, 255);
    pwm_set_chan_level(slice_num, PWM_CHAN_A, 0);
    pwm_set_enabled(slice_num, true);

    gpio_set_dir(SWITCH, GPIO_IN)


 
    while (1) {
        // 12-bit conversion, assume max value == ADC_VREF == 3.3 V
        uint16_t result = adc_read();
	    long pwm_value = map(result, 0, 4095, 0, 255);
        uint switch_value = gpio_get(SWITCH)
        printf("Switch: %d \n", switch_value)

        printf("Raw value: %d \n PWM: %d \n", result, pwm_value);

        pwm_set_chan_level(slice_num, PWM_CHAN_A, pwm_value);

        sleep_ms(50);
    }

}
