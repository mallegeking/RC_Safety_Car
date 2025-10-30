#pragma once

// Initialize motor control (PWM channels, direction pins, etc.)
void motor_init();

// Set individual wheel outputs in [-1.0 .. 1.0] (FL, FR, RL, RR)
// -1.0 : full reverse, 0 : stop, +1.0 : full forward
void setWheelSpeeds(float fl, float fr, float rl, float rr);

// Convenience mixing: throttle [-1..1], turn [-1..1]
void setDrive(float throttle, float turn);

// Stop motors (coast)
void stopMotors();

// Emergency brake (active braking, if supported)
void emergencyBrake();
