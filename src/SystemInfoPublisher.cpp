/*
 * SystemInfoPublisher.cpp
 * 
 * Implementation of the SystemInfoPublisher class for reading computer-specific values
 * and publishing them to an MQTT broker using the MqttClient class.
 * 
 * Author: schuali93
 * Date: 18.01.25
 */

#include "SystemInfoPublisher.h"
#include <chrono>
#include <thread>
#include <sys/sysinfo.h>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <array>

SystemInfoPublisher::SystemInfoPublisher(const std::string& serverAddress, const std::string& clientId)
    : MqttClient(serverAddress, clientId) {}

void SystemInfoPublisher::startPublishing(const std::string& topic, int interval) {
    running = true;
    publishThread = std::thread([this, topic, interval]() {
        while (running) {
            nlohmann::json payload = readSystemInfo();
            publish(topic, payload, 0);
            std::this_thread::sleep_for(std::chrono::seconds(interval));
        }
    });
}

nlohmann::json SystemInfoPublisher::readSystemInfo() {
    struct sysinfo sysInfo;
    sysinfo(&sysInfo);

    nlohmann::json info;
    info["uptime"] = sysInfo.uptime;
    info["totalram"] = sysInfo.totalram;
    info["freeram"] = sysInfo.freeram;
    info["procs"] = sysInfo.procs;
    info["cpu_temp"] = getCpuTemp(); // Add fan speed to the JSON object

    return info;
}

double SystemInfoPublisher::getCpuTemp() {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen("sensors | grep 'temp' | awk '{print $2}'", "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    std::istringstream iss(result);
    double cpuTemp;
    iss >> cpuTemp;
    return cpuTemp;
}