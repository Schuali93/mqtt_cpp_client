#include <iostream>
#include <thread>
#include "MqttClient.h"

const std::string SERVER_ADDRESS("tcp://homeassistant.local:1883");
const std::string CLIENT_ID("paho_cpp_async_publish");
const std::string TOPIC("test/topic");

const int QOS = 1;

int main() {
    MqttClient mqttClient(SERVER_ADDRESS, CLIENT_ID);

    try {
        mqttClient.connect("mqtt-user", "mqtt-user");
        mqttClient.subscribe(TOPIC, QOS);
        std::cout << "Connected and subscribed to topic: " << TOPIC << std::endl;
        // Start periodic publishing
        mqttClient.startPeriodicPublish(TOPIC, "Hello MQTT", QOS, 5);

        // Let it run for 30 seconds
        std::this_thread::sleep_for(std::chrono::seconds(30));

        // Stop periodic publishing
        mqttClient.stopPeriodicPublish();

        mqttClient.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}