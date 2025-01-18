#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "MqttClient.h"
#include <nlohmann/json.hpp>

const std::string SERVER_ADDRESS("tcp://homeassistant.local:1883");
const std::string CLIENT_ID("paho_cpp_async_publish");
const std::string TOPIC("test/topic");

const int QOS = 0;

std::string getCurrentTime() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_time);

    std::ostringstream oss;
    oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

int main() {
    MqttClient mqttClient(SERVER_ADDRESS, CLIENT_ID);

    try {
        mqttClient.connect("mqtt-user", "mqtt-user");
        mqttClient.subscribe(TOPIC, QOS);

        // Create a JSON payload
        nlohmann::json payload;
        payload["message"] = "Hello MQTT";
        payload["timestamp"] = getCurrentTime();

        // Start periodic publishing with JSON payload
        mqttClient.startPeriodicPublish(TOPIC, payload, QOS, 5);

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