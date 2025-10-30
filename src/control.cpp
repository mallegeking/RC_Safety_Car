#include "control.h"
#include "motor_control.h"
#include "sensor_handler.h"
#include "mqtt_handler.h"
#include "config.h"
#include "hal_board.h"
#include <Arduino.h>

enum CarState { STATE_IDLE, STATE_MANUAL, STATE_ASSISTED, STATE_AEB, STATE_ESTOP };
static CarState current_state = STATE_IDLE;

// Network-controlled targets
static float network_throttle = 0.0f; // [-1..1]
static float network_turn = 0.0f;     // [-1..1]
static unsigned long last_command_ts = 0;

static unsigned long last_control_ts = 0;
static unsigned long control_period_ms = (unsigned long)(1000.0f / CONTROL_LOOP_HZ);

// safety thresholds (tune)
static const float buffer_cm = 10.0f;
static const float d_stop_cm = 15.0f; // immediate stop threshold

void control_compute_and_apply() {
  SensorSnapshot s = sensors_get_latest();

  // estimate speed v from last throttle — TODO: replace with encoder-based velocity
  float v_est = fabs(network_throttle) * 0.8f; // m/s crude mapping; tune later

  // safe distance computation (meters->cm)
  float d_safe_cm = v_est * REACTION_TIME_S * 100.0f + (v_est * v_est) / (2.0f * A_DEC) * 100.0f + buffer_cm;

  // check front AEB
  float front = s.front_cm;
  if (front > 0 && front <= d_stop_cm) {
    current_state = STATE_AEB;
    emergencyBrake();
    mqtt_publish_telemetry("{\"event\":\"AEB\",\"front_cm\":15}");
    return;
  } else if (front > 0 && front <= d_safe_cm) {
    // slow proportionally
    float t = (front - d_stop_cm) / (d_safe_cm - d_stop_cm);
    float target_throttle = network_throttle * t;
    setDrive(target_throttle, network_turn);
    return;
  }

  // link-loss detection: if no command for >500ms -> idle
  unsigned long now = hal_millis();
  if (now - last_command_ts > 500) {
    current_state = STATE_IDLE;
    stopMotors();
    return;
  }

  // normal manual/assisted control path
  current_state = STATE_MANUAL;
  // clamp throttle to max
  float thr = network_throttle;
  if (thr > MAX_THROTTLE) thr = MAX_THROTTLE;
  if (thr < -MAX_THROTTLE) thr = -MAX_THROTTLE;

  setDrive(thr, network_turn);
}

void control_task_entry(void* pv) {
  (void)pv;
  while (1) {
    control_compute_and_apply();
    hal_delay_ms(control_period_ms);
  }
}

void control_init() {
  motor_init();
  // Try to create RTOS task, otherwise you'll call control_loop_iteration() in main loop.
  bool created = hal_create_task(control_task_entry, "CONTROL", 4096, NULL, 3, true);
  if (!created) {
    Serial.println("[CONTROL] No RTOS task created. Use loop() fallback.");
  }
}

void control_loop_iteration() {
  control_compute_and_apply();
}

void control_request_estop(bool on) {
  if (on) {
    current_state = STATE_ESTOP;
    emergencyBrake();
  } else {
    current_state = STATE_IDLE;
  }
}

const char* control_get_state() {
  switch (current_state) {
    case STATE_IDLE: return "IDLE";
    case STATE_MANUAL: return "MANUAL";
    case STATE_ASSISTED: return "ASSISTED";
    case STATE_AEB: return "AEB";
    case STATE_ESTOP: return "ESTOP";
    default: return "UNKNOWN";
  }
}
