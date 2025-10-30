# GEMINI Project Context: RC Safety Car

## Project Overview

This is a C++ project for an RC (Remote Controlled) "Safety Car," designed to run on an Arduino-compatible microcontroller with Wi-Fi capabilities (such as an ESP32). The project is built using the PlatformIO ecosystem.

The car's primary functions are managed through a modular structure:
- **Control System:** A main control loop runs at a configurable frequency (`CONTROL_LOOP_HZ` in `src/config.h`).
- **Motor Control:** Handles the car's throttle.
- **Sensor Handling:** Reads data from sensors, likely for obstacle detection (e.g., VL53L1X time-of-flight sensor).
- **MQTT Communication:** The car is controlled and monitored remotely via MQTT. It subscribes to a command topic (`rc/car/1/cmd`) and an emergency stop topic (`rc/car/1/estop`). It publishes telemetry data to `rc/car/1/telemetry`.
- **Hardware Abstraction:** A Hardware Abstraction Layer (HAL) in `lib/hal/` allows the application code to be portable across different microcontrollers. The specific pin mappings and hardware initializations must be implemented in `lib/hal/hal_board.cpp`.
- **Web UI:** The `data/` directory contains `index.html`, suggesting the device can serve a web page, likely for status display or simple controls.

## Building and Running

This project uses the **PlatformIO** extension in VS Code.

1.  **Prerequisites:**
    *   Visual Studio Code with the PlatformIO IDE extension installed.
    *   A copy of the project.

2.  **Initial Setup:**
    *   **Board Configuration:** Edit `platformio.ini` to set the `board` variable under the `[env:generic_board]` section to match your target hardware (e.g., `board = esp32dev`).
    *   **Hardware Pins:** Edit `lib/hal/hal_board.cpp` to define the correct pin numbers for your board's wiring (e.g., motor PWM, sensor I2C, LEDs).
    *   **Project Configuration:** Review and adjust constants in `src/config.h` (e.g., MQTT topics, control loop frequencies).
    *   **Secrets:** Create a new file `src/secrets.h` (by copying `src/secrets.h.example`, though this file is currently missing). Add your Wi-Fi and MQTT broker credentials to this file. **This file should not be committed to version control.**

3.  **Build & Upload:**
    *   To build the project, run the following PlatformIO command:
        ```bash
        pio run -e generic_board
        ```
    *   To build and upload the firmware to the connected device:
        ```bash
        pio run -e generic_board -t upload
        ```
        *(Replace `generic_board` with your specific environment name from `platformio.ini` if you change it)*

4.  **Monitor:**
    *   To view serial output from the device:
        ```bash
        pio device monitor -b 115200
        ```

## Development Conventions

*   **CI:** A GitHub Actions workflow is defined in `.github/workflows/ci.yml`. It automatically builds the firmware for the `esp32dev` board on every push and pull request to catch compilation errors.
*   **Hardware Abstraction:** All direct hardware interactions (pin control, I2C, PWM) should be implemented in `lib/hal/hal_board.cpp` by fulfilling the API defined in `lib/hal/hal_board.h`. The main application code in `src/` should only use the `hal_*` functions.
*   **Configuration:**
    *   **Compile-time constants** (e.g., control parameters, MQTT topics) are centralized in `src/config.h`.
    *   **Secrets** (Wi-Fi/MQTT credentials) must be stored in `src/secrets.h` and are git-ignored.
*   **Dependencies:** C++ library dependencies are managed by PlatformIO in the `platformio.ini` file under `lib_deps`. Key libraries include:
    *   `PubSubClient` for MQTT.
    *   `Adafruit VL53L1X` for the time-of-flight distance sensor.
    *   `Adafruit NeoPixel` for addressable LEDs.
