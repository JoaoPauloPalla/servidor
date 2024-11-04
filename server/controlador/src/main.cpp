#include <Arduino.h>
#include <controller.h>
#include <WiFi.h>

WiFiClient espClient;
Controller* controller;


void setup() {
  Serial.begin(9600);

  controller = new Controller();
  controller->runTasks();
}

void loop() {

  // while(true)
  // { 
  //   freezerTemperature = round(controller->sensor->readAmbientTempC()*100)/100;
  //   temperature = round(controller->sensor->readObjectTempC()*100)/100;   

  //   doc["controllerId"] = 0;
  //   doc["recipeId"] = 0;
  //   doc["timestamp"] = __TIMESTAMP__;
  //   doc["freezerTemperature"] = freezerTemperature;
  //   doc["temperature"] = temperature;
  //   doc["setpointTemperature"] = controller->temperatureSetpoint;
  //   doc["isFreezerActive"] = false;
  //   serializeJson(doc, payload);       

  //   Serial.println(payload);

  //   if ( xQueueSend(controller->buffer, &payload, pdMS_TO_TICKS(0)) ){
  //       Serial.println("Data sent to buffer.");
  //   }else{
  //       Serial.println("Data not sent to buffer");
  //   }

  // }
    delay(1000);
}
