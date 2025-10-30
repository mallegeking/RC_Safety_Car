#pragma once
#include <stdint.h>

// Basic sensor data structure (distances in cm)
struct SensorSnapshot {
  float front_cm;
  float rear_left_cm;
  float rear_right_cm;
  unsigned long timestamp_ms;
};

// Initialize sensors (I2C, XSHUT sequencing for VL53L1X)
void sensors_init();

// Read sensors (blocking read, returns true when successful)
bool sensors_read(SensorSnapshot &out);

// Get last filtered snapshot (non-blocking)
SensorSnapshot sensors_get_latest();
