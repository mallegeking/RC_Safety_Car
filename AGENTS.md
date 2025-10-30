# Repository Guidelines

## Project Structure & Module Organization
Application sources live in `src/`, with `main.cpp` orchestrating HAL, control, sensors, and MQTT handlers. Board-specific abstractions sit in `lib/hal/`; keep new hardware logic there and expose interfaces through matching headers. Share configuration through `src/config.h`, and keep credentials in an untracked `src/secrets.h`. Static web assets are served from `data/`, while diagrams and references belong in `docs/`. Place new modules alongside related code and provide a header when the API is reused.

## Build, Test, and Development Commands
Use `pio run` for a full build of the default environment defined in `platformio.ini`. Flash hardware with `pio run -e <env> -t upload` after selecting the correct environment, and monitor serial logs via `pio device monitor -b 115200`. Run `pio run --target clean` if PlatformIO caches cause unexpected results. When tests are added, execute them with `pio test -e <env>` to exercise Unity-based suites.

## Coding Style & Naming Conventions
Match the current two-space indentation and same-line brace style shown in `src/main.cpp`. Prefer `snake_case` for functions and variables, and reserve `SCREAMING_SNAKE_CASE` for constants and macros (e.g., `MQTT_TOPIC_CMD`). Keep headers lightweight with `#pragma once` and place implementation details in `.cpp` files. Leverage HAL helpers (such as `hal_millis()` and `hal_yield()`) instead of raw Arduino calls when interacting with hardware, and document non-obvious safety logic with brief comments.

## Testing Guidelines
Create unit or component tests under a `test/` directory, mirroring the module under test (for example, `test_control`). Stub HAL interactions so tests stay hardware-independent, and assert safety-critical paths like emergency braking and watchdog behavior. Run `pio run` before submitting to confirm the code still builds, then `pio test -e <env>` for any environments you touched. Describe manual bench or track tests in the pull request when hardware validation is required.

## Commit & Pull Request Guidelines
The repository has no commit history yet, so adopt a consistent format from the start: short imperative subjects, optionally using Conventional Commit prefixes (`feat`, `fix`, `refactor`). Reference related issues in the body and call out configuration or wiring changes explicitly. Pull requests should include: what changed and why, which environment you built and tested, any relevant logs or screenshots, and reminders about secrets (`src/secrets.h` stays local).

## Security & Configuration Tips
Never commit real credentials; provide updates through `src/secrets.h.example` and keep the populated `src/secrets.h` git-ignored. Review `platformio.ini` and HAL changes for pin conflicts, ensuring safe defaults when sensors fail or MQTT disconnects. Validate any new MQTT topics stay within the existing namespace (`MQTT_TOPIC_*`) to avoid broker collisions, and sanitize remote commands before acting on them.
