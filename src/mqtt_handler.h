#pragma once

#include <stdint.h>

// Initialize MQTT subsystem. Non-blocking.
void mqtt_init();

// Must be called regularly in loop or background task.
void mqtt_loop();

// Convenience publish telemetry (JSON string)
void mqtt_publish_telemetry(const char* json);

// Request soft E-Stop via MQTT (publish retain)
void mqtt_publish_estop(bool estop);
