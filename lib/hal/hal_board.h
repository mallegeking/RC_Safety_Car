#pragma once
#include <stdint.h>

// Basic hardware abstraction layer API
// Implement these in hal_board.cpp for your specific board.

#ifdef __cplusplus
extern "C" {
#endif

// Initialize pins, I2C, PWM, ADC, etc.
void hal_board_init();

// Millisecond timestamp (wrap-safe)
uint32_t hal_millis();

// Delay ms
void hal_delay_ms(uint32_t ms);

// PWM API: duty [-1.0..1.0] maps to hardware PWM
void hal_pwm_set(int pwm_channel, float duty);

// Digital outputs for LED/buzzer
void hal_digital_write(int pin, int value);

// Read analog (0..4095 typical)
int hal_adc_read(int pin);

// Create / delete OS task if RTOS is available
bool hal_create_task(void (*task_func)(void*), const char* name, int stack_size, void* params, int priority, bool pinned_core);
void hal_yield();

#ifdef __cplusplus
}
#endif
