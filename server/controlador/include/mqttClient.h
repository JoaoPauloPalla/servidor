#pragma once

#include <Arduino.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>

class MqttClient : public PubSubClient {
    public:
        IPAddress ip;
        IPAddress gateway;
        IPAddress subnet;
        const char* ssid;
        const char* wifiPassword;
        int broker_port;
        const char* broker;
        const char* topic;
        const char* config_topic;
        const char* id;
        const char* user;
        const char* password;
        WiFiClient* wifiClient;

        MqttClient( );
        ~MqttClient();

        void init();
        void sendData(JsonDocument);
        static void callback(char *, byte *, unsigned int);
};
