#include <iostream>
#include <thread>
#include "MqttClient.h"

const std::string SERVER_ADDRESS("tcp://homeassistant.local:1883");
const std::string CLIENT_ID("paho_cpp_async_publish");
const std::string TOPIC("test/topic");

const int QOS = 0;

int main() {
    MqttClient mqttClient(SERVER_ADDRESS, CLIENT_ID);

    try {
        mqttClient.connect("mqtt-user", "mqtt-user");
        mqttClient.subscribe(TOPIC, QOS);
        mqttClient.publish(TOPIC, "Hello MQTT", QOS);
        std::this_thread::sleep_for(std::chrono::seconds(1));
        mqttClient.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}