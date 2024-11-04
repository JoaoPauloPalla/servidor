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
    // WiFiClient* wifiClient;
    MqttClient* mqttClient;
    QueueHandle_t buffer;
    JsonDocument data;

    // const char* mqttServer;
    // int mqttPort;
    // const char* mqttUser;
    // const char* mqttPassword;
    // const char* mqttTopicConfig;
    // const char* mqttTopicTemperature;
    // PubSubClient* mqttClient;
    // static void mqttCallback(char* topic, uint8_t* payload, unsigned int length);

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
    static void callback(char *, byte *, unsigned int );

};