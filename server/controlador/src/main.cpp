#include <Arduino.h>
#include <controller.h>
#include <WiFi.h>
#include "esp_log.h"

WiFiClient espClient;
Controller* controller;


void setup() {
  Serial.begin(9600);
  esp_log_level_set("*", ESP_LOG_INFO);
  ESP_LOGI("Main", "Initializing controller");
  controller = new Controller();
  controller->runTasks();
}

void loop() {
    delay(1000);
}
