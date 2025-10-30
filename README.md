# RC Safety Car — Minimal Skeleton

This repository contains a minimal, portable skeleton for the RC Safety Car project.
It targets Arduino-compatible Wi-Fi/BLE boards (ESP32, Arduino Nano 33 IoT, RP2040+WiFi add-ons, etc.)

## Structure
- `src/` : application code (control, sensors, motor, mqtt)
- `lib/hal/` : hardware abstraction layer; adapt `hal_board.cpp` to your board
- `data/` : optional web UI files served by the device
- `docs/` : wiring diagrams and other documentation
- `platformio.ini` : PlatformIO build configuration

## Quick start
1. Install [VS Code] + [PlatformIO] extension.
2. Edit `platformio.ini` to set your board.
3. Copy `src/secrets.h.example` → `src/secrets.h` and fill Wi-Fi / MQTT credentials (do **not** commit).
4. Edit `lib/hal/hal_board.cpp` to set pin numbers and hardware specifics.
5. `pio run -e <env> -t upload` to compile & flash.
6. Monitor serial logs: `pio device monitor -b 115200`.

## Files to edit before first run
- `platformio.ini` — set board environment.
- `lib/hal/hal_board.cpp` — implement `hal_board_init()` pin mapping and low-level APIs.
- `src/config.h` — configure constants and topic names.
- `src/secrets.h` (create from `secrets.h.example`) — fill Wi-Fi & MQTT credentials.

## CI (GitHub Actions)
`ci.yml` (optional) is included to run builds automatically on push/pull requests. Useful to catch compile errors on multiple board targets.
