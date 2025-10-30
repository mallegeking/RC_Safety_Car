#pragma once

// -------------------- TODO: Edit these --------------------
// Board specifics: set in hal_board.cpp mapping
// ---------------------------------------------------------

// MQTT topics & IDs
#define MQTT_CLIENT_ID "rc_car_01"
#define MQTT_TOPIC_CMD "rc/car/1/cmd"
#define MQTT_TOPIC_TELEMETRY "rc/car/1/telemetry"
#define MQTT_TOPIC_ESTOP "rc/car/1/estop"

// Control params (tune during testing)
constexpr float CONTROL_LOOP_HZ = 25.0f;      // control frequency
constexpr float SENSOR_READ_HZ  = 25.0f;      // sensor read frequency
constexpr float REACTION_TIME_S  = 0.4f;      // reaction margin (s)
constexpr float A_DEC = 1.0f;                // conservative deceleration (m/s^2)

// Motor scale
constexpr float MAX_THROTTLE = 0.8f;  // clamp network throttle [0..1]

// Sensor config
#define SENSOR_MAX_RANGE_CM 120.0f

// Logging
#define TELEMETRY_PUBLISH_HZ 2

// ---------------------------------------------------------
