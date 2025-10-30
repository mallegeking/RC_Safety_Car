#include "hal_board.h"
#include <Arduino.h>

/*
 * Default HAL implementation using Arduino functions.
 * Edit TODOs to reflect board-specific pin choices and hardware PWM mapping.
 */

// TODO: map hardware PWM channels if needed
void hal_board_init() {
  // TODO: Initialize I2C: Wire.begin(SDA_pin, SCL_pin);
  // TODO: pinMode for E-STOP input, LED, BUZZER
  // Example:
  // pinMode(2, OUTPUT); // status LED
}

uint32_t hal_millis() {
  return millis();
}

void hal_delay_ms(uint32_t ms) {
  delay(ms);
}

void hal_pwm_set(int pwm_channel, float duty) {
  // duty in [-1.0 .. 1.0] -> convert to 0..255 or LEDC resolution
  // TODO: implement hardware PWM mapping for your board
  int out = (int)((duty + 1.0f) * 127.5f); // placeholder [-1..1] -> [0..255]
  // analogWrite(pwm_pin_of_channel(pwm_channel), out);
  (void)out;
}

void hal_digital_write(int pin, int value) {
  digitalWrite(pin, value ? HIGH : LOW);
}

int hal_adc_read(int pin) {
  return analogRead(pin);
}

bool hal_create_task(void (*task_func)(void*), const char* name, int stack_size, void* params, int priority, bool pinned_core) {
  // Try to create FreeRTOS task if available on platform — otherwise fallback to false.
  #if defined(ESP32)
    TaskHandle_t handle;
    BaseType_t result = xTaskCreatePinnedToCore(task_func, name, stack_size, params, priority, &handle, pinned_core ? 1 : 0);
    return (result == pdPASS);
  #else
    // No RTOS available; caller must run tasks cooperatively from loop()
    (void)task_func; (void)name; (void)stack_size; (void)params; (void)priority; (void)pinned_core;
    return false;
  #endif
}

void hal_yield() {
  yield();
}
