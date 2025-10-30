#include <Arduino.h>
#include "hal_board.h"
#include "config.h"
#include "sensor_handler.h"
#include "control.h"
#include "mqtt_handler.h"

void setup() {
  Serial.begin(115200);
  hal_board_init();

  sensors_init();
  motor_init();
  mqtt_init();

  control_init();

  Serial.println("RC Safety Car skeleton boot complete.");
}

void loop() {
  // If RTOS tasks not available, we must call loop-based components here.
  // sensors_read and control_loop_iteration will be called here at approximate rates.
  static unsigned long last_sensor_ms = 0;
  static unsigned long last_control_ms = 0;
  unsigned long now = hal_millis();

  // sensor read at SENSOR_READ_HZ
  if (now - last_sensor_ms >= (unsigned long)(1000.0f / SENSOR_READ_HZ)) {
    SensorSnapshot snap;
    sensors_read(snap); // updates internal filtered copy
    last_sensor_ms = now;
  }

  // control loop fallback
  if (now - last_control_ms >= (unsigned long)(1000.0f / CONTROL_LOOP_HZ)) {
    control_loop_iteration();
    last_control_ms = now;
  }

  // MQTT loop (must be called frequently)
  mqtt_loop();

  // Yield to background / cooperative scheduling
  hal_yield();
}
