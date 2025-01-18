#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "SystemInfoPublisher.h"
#include <nlohmann/json.hpp>

const std::string SERVER_ADDRESS("tcp://homeassistant.local:1883");
const std::string CLIENT_ID("paho_cpp_async_publish");
const std::string TOPIC("system/info");

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
    SystemInfoPublisher systemInfoPublisher(SERVER_ADDRESS, CLIENT_ID);

    try {
        systemInfoPublisher.connect("mqtt-user", "mqtt-user");
        systemInfoPublisher.subscribe(TOPIC, QOS);

        // Start publishing system information every 5 seconds
        systemInfoPublisher.startPublishing(TOPIC, 5);

        while (true)
        {
            if (std::cin.get() != EOF) 
            {
                std::cout << "Exiting..." << std::endl;
                break;
            }
        }
        // Stop publishing system information
        systemInfoPublisher.stopPublishing();

        systemInfoPublisher.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}