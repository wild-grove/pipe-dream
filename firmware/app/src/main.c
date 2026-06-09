/*
 * Copyright (c) 2026 Wild Grove
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include <stdio.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define SERVO_PWM_NODE DT_NODELABEL(pwm0)
#define SERVO_PWM_CHANNEL 0
#define SERVO_PERIOD PWM_MSEC(20)
#define SERVO_MOVE_DELAY_MS 1000

static const struct pwm_dt_spec servo_pwm = {
    .dev = DEVICE_DT_GET(SERVO_PWM_NODE),
    .channel = SERVO_PWM_CHANNEL,
    .period = SERVO_PERIOD,
    .flags = PWM_POLARITY_INVERTED
};

int main(void)
{
    uint32_t pulse_width = 500;     // Initial pulse width in microseconds
    uint32_t pulse_step = 250;      // Initial pulse step direction

    // Check if the servo PWM is ready
    if (!pwm_is_ready_dt(&servo_pwm)) {
        printk("PWM device is not ready\n");
        return 0;
    }

	printk("Pipe Dream: Servo sweep on DIO23\n");

	while (1) {
        // Set the servo pulse width
        if (pwm_set_pulse_dt(&servo_pwm, PWM_USEC(pulse_width)) != 0) {
            printk("Failed to set servo pulse %lu ns\n", PWM_USEC(pulse_width));
            return 0;
        }

        // Print the current pulse width in microseconds
		printk("Servo pulse: %lu us\n", PWM_USEC(pulse_width) / NSEC_PER_USEC);
		k_msleep(SERVO_MOVE_DELAY_MS);

		pulse_width += pulse_step;

        if (pulse_width >= 2500) {
            pulse_width = 2500; // Limit pulse width to 2500 microseconds
            pulse_step = -250; // Decrement pulse width by 250 microseconds
        } else if (pulse_width <= 500) {
            pulse_width = 500; // Limit pulse width to 500 microseconds
            pulse_step = 250; // Increment pulse width by 250 microseconds
        }
	}

	return 0;
}
