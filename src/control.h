#pragma once
#include "sensor_handler.h"

// Start control subsystem (creates tasks if RTOS available)
void control_init();

// Call regularly if RTOS not available (fallback)
void control_loop_iteration();

// Request software E-Stop
void control_request_estop(bool on);

// Get current state textual (for telemetry)
const char* control_get_state();
