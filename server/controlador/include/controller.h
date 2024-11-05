# pragma once

#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_MLX90614.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <mqttClient.h>

class Controller
{
public:
    Controller();
    ~Controller();

    IPAddress ip;
    IPAddress gateway;
    IPAddress subnet;
    const char* ssid;
    const char* password;
    MqttClient* mqttClient;
    QueueHandle_t buffer;
    JsonDocument data;

    int scanTime;
    float temperature;
    float maxTemperature;
    float minTemperature;
    float temperatureSetpoint;
    float temperatureHysteresis;
    bool isFreezerActive;
    Adafruit_MLX90614* sensor;

    void runTasks();
    static void taskTemperatureControl(void* args); 
    static void taskMQTT(void* args);
    void controlTemperature( float mesuredTemperature);

};