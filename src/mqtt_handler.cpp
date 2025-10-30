#include "mqtt_handler.h"
#include "config.h"
#include <Arduino.h>

// Libraries are specified in platformio.ini; implementations vary per board
// TODO: include your MQTT library and implement connect/subscribe/publish

// Example skeleton using PubSubClient or similar
static bool mqtt_connected = false;

void mqtt_init() {
  // TODO:
  // - initialize network (Wi-Fi) via hal-specific function or in main
  // - configure MQTT client (server, port) and callbacks
  // - subscribe to MQTT_TOPIC_CMD and MQTT_TOPIC_ESTOP
  Serial.println("[MQTT] init - TODO: configure network and broker");
}

void mqtt_loop() {
  // TODO: poll client, handle reconnects
  (void)mqtt_connected;
}

void mqtt_publish_telemetry(const char* json) {
  // TODO: publish telemetry with QoS 0/1 as desired
  Serial.printf("[MQTT] telemetry: %s\n", json);
}

void mqtt_publish_estop(bool estop) {
  // TODO: publish retained estop message
  Serial.printf("[MQTT] publish estop: %d\n", estop ? 1 : 0);
}
