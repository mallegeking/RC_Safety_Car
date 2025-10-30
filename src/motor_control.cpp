#include "motor_control.h"
#include "hal_board.h"
#include "config.h"
#include <Arduino.h>

// TODO: fill these constants with your actual pin/channel mappings
static const int PWM_CH_FL = 0;
static const int PWM_CH_FR = 1;
static const int PWM_CH_RL = 2;
static const int PWM_CH_RR = 3;

// helper to constrain
static inline float clampf(float v, float a, float b) {
  if (v < a) return a;
  if (v > b) return b;
  return v;
}

void motor_init() {
  // TODO:
  // configure motor direction pins, enable pins, PWM channels on HAL
  Serial.println("[MOTOR] init - TODO: configure pins and PWM");
}

void setWheelSpeeds(float fl, float fr, float rl, float rr) {
  // clamp to allowed range and apply global scaling
  fl = clampf(fl, -1.0f, 1.0f);
  fr = clampf(fr, -1.0f, 1.0f);
  rl = clampf(rl, -1.0f, 1.0f);
  rr = clampf(rr, -1.0f, 1.0f);

  // Map to PWM via HAL
  hal_pwm_set(PWM_CH_FL, fl);
  hal_pwm_set(PWM_CH_FR, fr);
  hal_pwm_set(PWM_CH_RL, rl);
  hal_pwm_set(PWM_CH_RR, rr);
}

void setDrive(float throttle, float turn) {
  // simple differential mixing
  float left = throttle + turn;
  float right = throttle - turn;
  // normalize
  float maxv = fabs(left) > fabs(right) ? fabs(left) : fabs(right);
  if (maxv > 1.0f) {
    left /= maxv;
    right /= maxv;
  }
  // Apply same to both axles (FL, RL = left; FR, RR = right)
  setWheelSpeeds(left, right, left, right);
}

void stopMotors() {
  setWheelSpeeds(0,0,0,0);
}

void emergencyBrake() {
  // If your motor driver supports active braking, implement toggle direction pins appropriately.
  // Otherwise just stop motors.
  stopMotors();
}
