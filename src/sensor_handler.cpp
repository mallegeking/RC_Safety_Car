#include "sensor_handler.h"
#include "config.h"
#include "hal_board.h"
#include <Arduino.h>

// TODO: include VL53L1X library and implement address assignment
// e.g., Adafruit_VL53L1X or Pololu drivers

static SensorSnapshot latest_snapshot = { -1, -1, -1, 0 };

void sensors_init() {
  // TODO:
  // - Wire.begin(SDA, SCL) if needed
  // - Initialize each VL53L1X and set unique I2C addresses using XSHUT pins
  Serial.println("[SENSORS] init - TODO: configure I2C and sensors");
  latest_snapshot.timestamp_ms = hal_millis();
}

bool sensors_read(SensorSnapshot &out) {
  // TODO: perform actual sensor reads and apply small filters (median/EWMA)
  // Placeholder: return dummy values to ensure rest of system works
  unsigned long now = hal_millis();
  out.front_cm = 80.0f;       // TODO: replace with real measurement
  out.rear_left_cm = 150.0f;  // TODO
  out.rear_right_cm = 150.0f; // TODO
  out.timestamp_ms = now;

  // update latest (apply basic EWMA filter)
  const float alpha = 0.35f;
  if (latest_snapshot.timestamp_ms == 0) {
    latest_snapshot = out;
  } else {
    latest_snapshot.front_cm = alpha * out.front_cm + (1.0f - alpha) * latest_snapshot.front_cm;
    latest_snapshot.rear_left_cm = alpha * out.rear_left_cm + (1.0f - alpha) * latest_snapshot.rear_left_cm;
    latest_snapshot.rear_right_cm = alpha * out.rear_right_cm + (1.0f - alpha) * latest_snapshot.rear_right_cm;
    latest_snapshot.timestamp_ms = now;
  }
  return true;
}

SensorSnapshot sensors_get_latest() {
  return latest_snapshot;
}
