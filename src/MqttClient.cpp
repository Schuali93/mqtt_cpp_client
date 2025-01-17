#include "MqttClient.h"
#include <iostream>

MqttClient::MqttClient(const std::string& serverAddress, const std::string& clientId)
    : client(serverAddress, clientId), cb() {
    client.set_callback(cb);
}

void MqttClient::connect(const std::string& username, const std::string& password) {
    mqtt::connect_options connOpts;
    connOpts.set_clean_session(true);
    connOpts.set_user_name(username);
    connOpts.set_password(password);

    try {
        std::cout << "Connecting to the MQTT server..." << std::endl;
        client.connect(connOpts)->wait();
        std::cout << "Connected." << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << std::endl;
        throw;
    }
}

void MqttClient::subscribe(const std::string& topic, int qos) {
    try {
        std::cout << "Subscribing to topic: " << topic << std::endl;
        client.subscribe(topic, qos)->wait();
        std::cout << "Subscribed." << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << std::endl;
        throw;
    }
}

void MqttClient::publish(const std::string& topic, const std::string& payload, int qos) {
    try {
        std::cout << "Publishing message: " << payload << std::endl;
        client.publish(topic, payload.c_str(), payload.size(), qos, false)->wait();
        std::cout << "Message published." << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << std::endl;
        throw;
    }
}

void MqttClient::disconnect() {
    try {
        std::cout << "Disconnecting from the MQTT server..." << std::endl;
        client.disconnect()->wait();
        std::cout << "Disconnected." << std::endl;
    }
    catch (const mqtt::exception& exc) {
        std::cerr << exc.what() << std::endl;
        throw;
    }
}

void MqttClient::callback::message_arrived(mqtt::const_message_ptr msg) {
    std::cout << "Message arrived: " << msg->to_string() << std::endl;
}