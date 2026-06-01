/*
 * Copyright (c) 2026 Wild Grove
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>
#include <zephyr/sys/printk.h>
#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

static const struct gpio_dt_spec red_led = GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);
static const struct gpio_dt_spec green_led = GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec btn_1 = GPIO_DT_SPEC_GET(DT_ALIAS(sw0), gpios);
static const struct gpio_dt_spec btn_2 = GPIO_DT_SPEC_GET(DT_ALIAS(sw1), gpios);

static int device_state = 1; // 0 for OFF, 1 for ON

void button_pressed(const struct device *dev, struct gpio_callback *cb, uint32_t pins){
    if (pins & BIT(btn_1.pin)) {
        printk("Button 1 pressed, device off\n");
        device_state = 0; // Set device state to OFF
        gpio_pin_set_dt(&red_led, 0); // Set red LED pin to 0 (logic 0)
        gpio_pin_set_dt(&green_led, 0); // Set green LED pin to 0 (logic 0)
    }
    if (pins & BIT(btn_2.pin)) {
        printk("Button 2 pressed, device on\n");
        if (device_state == 0) {
            device_state = 1; // Set device state to ON
            gpio_pin_set_dt(&red_led, 1); // Set red LED pin to 0 (logic 0)
            gpio_pin_set_dt(&green_led, 0); // Set green LED pin to 0 (logic 0)
        }
        else {
            printk("Device is already ON\n");
        }
    }
}

static struct gpio_callback button_cb_data = {
    .handler = button_pressed,
    .pin_mask = BIT(btn_1.pin) | BIT(btn_2.pin)
};

int main(void){
	printk("Pipe Dream: Blinky Alternate with ON & OFF\n");
    int ret;
    bool red_led_state = true;
    bool green_led_state = false;

    // Check if the GPIO devices are ready for the LEDs and buttons
    if (!gpio_is_ready_dt(&red_led) || !gpio_is_ready_dt(&green_led) || !gpio_is_ready_dt(&btn_1) || !gpio_is_ready_dt(&btn_2)) {
        return 0;
    }

    // Configure the GPIO pin for the red LED (logic 1)
    ret = gpio_pin_configure_dt(&red_led, GPIO_OUTPUT_ACTIVE);
    if (ret < 0) {
        return 0;
    }

    // Configure the GPIO pin for the green LED (logic 0)
    ret = gpio_pin_configure_dt(&green_led, GPIO_OUTPUT_INACTIVE);
    if (ret < 0) {
        return 0;
    }

    // Configure the GPIO pins for the buttons as input
    gpio_pin_configure_dt(&btn_1, GPIO_INPUT);
    gpio_pin_configure_dt(&btn_2, GPIO_INPUT);

    // Configure interrupts for the buttons
    gpio_pin_interrupt_configure_dt(&btn_1, GPIO_INT_EDGE_RISING);
    gpio_pin_interrupt_configure_dt(&btn_2, GPIO_INT_EDGE_RISING);

    // Set the callback function for the buttons
    gpio_add_callback_dt(&btn_1, &button_cb_data);
    gpio_add_callback_dt(&btn_2, &button_cb_data);

    while (1) {
        if (device_state == 1) {
            // Toggle the red LED state
            ret = gpio_pin_toggle_dt(&red_led);
            if (ret < 0) {
                return 0;
            }

            // Toggle the green LED state        
            ret = gpio_pin_toggle_dt(&green_led);
            if (ret < 0) {
                return 0;
            }

            // Print the current state of the LEDs
            red_led_state = !red_led_state;
            green_led_state = !green_led_state;
            printk("LED state: Red=%s, Green=%s\n", red_led_state ? "ON" : "OFF", green_led_state ? "ON" : "OFF");
        } else {
            printk("Device is OFF\n");
        }

        k_msleep(1000);
    }
	return 0;
}
