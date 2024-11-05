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

    ESP_LOGI("Controller", "Creating tasks");
    delay(5000);

    // Initialize sensor
    if (sensor->begin()) {
        ESP_LOGI("Controller", "Temperature sensor initialized");
    }else {
        ESP_LOGE("Controller", "Sensor not initialized");
    }

    // Initialize temperature control
    xTaskCreatePinnedToCore(Controller::taskMQTT, "taskMQTT", 8192, (void *)this, 0, NULL, 0);
    xTaskCreatePinnedToCore(Controller::taskTemperatureControl, "taskTemperatureControl", 4096, (void *)this, 0, NULL, 1);
}

void Controller::taskMQTT(void *args) {
    ESP_LOGI("Controller", "[TaskMQTT] Task taskMQTT created");
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
                    ESP_LOGI("Controller", "[TaskMQTT] Data published");
                }else{
                    ESP_LOGE("Controller", "[TaskMQTT] Data not published");
                }
            }else{
                ESP_LOGE("Controller", "[TaskMQTT] Mqtt not connected");
                controller->mqttClient->init();
            }
        }
    }
}

void Controller::taskTemperatureControl(void *args) {
    ESP_LOGI("Controller", "[taskTemperatureControl] Task taskTemperatureControl created");
    Controller *controller = (Controller *)args;

    float freezerTemperature = 0;
    float temperature = 0;
    
    while (true) {
        freezerTemperature = round(controller->sensor->readAmbientTempC()*100)/100;
        temperature = round(controller->sensor->readObjectTempC()*100)/100;   
        vTaskDelay(2000);

        if (temperature > 0 && freezerTemperature > 0) {
            
            controller->data["controllerId"] = 0;
            controller->data["recipeId"] = 0;
            controller->data["timestamp"] = __TIMESTAMP__;
            controller->data["freezerTemperature"] = freezerTemperature;
            controller->data["temperature"] = temperature;
            controller->data["setpointTemperature"] = controller->temperatureSetpoint;
            controller->data["isFreezerActive"] = false;
            
            if ( xQueueSend(controller->buffer, &controller->data, pdMS_TO_TICKS(0)) ){
                ESP_LOGI("Controller", "[taskTemperatureControl] Data sent to buffer.");
            }
            else{
                ESP_LOGE("Controller", "[taskTemperatureControl] Data not sent to buffer.");
            }

        }

        vTaskDelay(controller->scanTime*1000);
    }
}
