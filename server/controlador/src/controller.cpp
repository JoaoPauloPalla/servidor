#include <controller.h>

Controller::Controller() {
    scanTime = 5;
    temperature = 0.0;
    maxTemperature = 0.0;
    minTemperature = 0.0;
    temperatureSetpoint = 0.0;
    temperatureHysteresis = 0.0;
    isFreezerActive = false;

    sensor = new Adafruit_MLX90614();
    buffer = xQueueCreate(60, 256);
    mqttClient = new MqttClient();

}

Controller::~Controller() {
    delete mqttClient;
    delete sensor;
}

void Controller::runTasks() {
    delay(3000);
    // Initialize mqtt client
    // mqttClient->init();

    // Initialize sensor
    if (sensor->begin()) {
        Serial.println("Sensor initialized");
    }else {
        Serial.println("Sensor not initialized");
    }

    // Initialize temperature control
    xTaskCreatePinnedToCore(Controller::taskMQTT, "taskMQTT", 8192, (void *)this, 0, NULL, 0);
    xTaskCreatePinnedToCore(Controller::taskTemperatureControl, "taskTemperatureControl", 4096, (void *)this, 0, NULL, 1);
}

void Controller::taskMQTT(void *args) {
    Serial.println("Task taskMQTT created");
    Controller *controller = (Controller *)args;
    controller->mqttClient->init();
    JsonDocument data;
    char payload[1024];

    while (true) {
        if (xQueueReceive(controller->buffer, &data,  pdMS_TO_TICKS( 10*controller->scanTime )) == true ) {
            // Serial.println("Data received: " + data.as<String>());
            serializeJson(data, payload);
            if (controller->mqttClient->connected()) {
                if (controller->mqttClient->publish("temp", payload) ){
                    // Serial.println("Data published");
                }else{
                    Serial.println("Data not published");
                }
            }else{
                Serial.println("Mqtt not connected");
            }
        }
    }
}

void Controller::taskTemperatureControl(void *args) {
    Serial.println("Task taskTemperatureControl created");
    Controller *controller = (Controller *)args;

    float freezerTemperature = 0;
    float temperature = 0;

    while (true) {
        freezerTemperature = round(controller->sensor->readAmbientTempC()*100)/100;
        temperature = round(controller->sensor->readObjectTempC()*100)/100;   
        vTaskDelay(2000);

        controller->data["controllerId"] = 0;
        controller->data["recipeId"] = 0;
        controller->data["timestamp"] = __TIMESTAMP__;
        controller->data["freezerTemperature"] = freezerTemperature;
        controller->data["temperature"] = temperature;
        controller->data["setpointTemperature"] = controller->temperatureSetpoint;
        controller->data["isFreezerActive"] = false;
        
        if ( xQueueSend(controller->buffer, &controller->data, pdMS_TO_TICKS(0)) ){
            // Serial.println("Data sent to buffer.");
         }
        else{
            Serial.println("Data not sent to buffer.");
        }

        vTaskDelay(controller->scanTime*1000);
    }
}

void Controller::callback(char *topic, byte *payload, unsigned int length){
    
    String msg; 
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       msg += c;
    }
    Serial.print("[MQTT] Mensagem recebida: ");
    Serial.println(msg); 

}