#include <mqttClient.h>

MqttClient::MqttClient():PubSubClient() {
    broker = "192.168.1.8";
    broker_port = 1883;
    id = "esp";
    user = "esp";
    password = "password";
    topic = "data";
    config_topic = "config";    

    wifiClient = new WiFiClient();
    ip = IPAddress(192, 168, 1, 10);
    gateway = IPAddress(192, 168, 1, 254);
    subnet = IPAddress(255, 255, 255, 0);
    ssid = "Joao 2.4G";
    wifiPassword = "1234567@a";
}

MqttClient::~MqttClient() {
    if(wifiClient != nullptr ) delete wifiClient;
}

void MqttClient::init( ) {

    Serial.println("Connecting to WiFi..");
    if (!WiFi.config(ip, gateway, subnet)) {
        Serial.println("Connection failed to configure");
    }
    WiFi.begin(ssid, wifiPassword);
    while(WiFi.status() != WL_CONNECTED){
        Serial.println("Connecting to WiFi..");
        delay(1000);
    }
    Serial.println(WiFi.localIP());

    this->setServer(this->broker, this->broker_port);
    this->setCallback(callback);
    this->setClient(*wifiClient);
    if (this->connect(this->user, this->user, this->password)) {
        Serial.println("MQTT connected");
    } else {
        Serial.println("MQTT not connected");
    } 

    this->subscribe(this->config_topic, 0);
    this->loop();

}

void MqttClient::sendData(JsonDocument doc) {
    String payload;
    serializeJson(doc, payload);
    this->publish(topic, payload.c_str());
}

void MqttClient::callback(char *topic, byte *payload, unsigned int length) {
    
    /* Rotina de configuração/callback a ser definida  */
    JsonDocument doc;
    deserializeJson(doc, payload, length);
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