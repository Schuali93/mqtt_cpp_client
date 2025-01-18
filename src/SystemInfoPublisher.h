/*
 * SystemInfoPublisher.h
 * 
 * Declaration of the SystemInfoPublisher class for reading computer-specific values
 * and publishing them to an MQTT broker using the MqttClient class.
 * 
 * Author: schuali93
 * Date: 18.01.25
 */

#ifndef SYSTEMINFOPUBLISHER_H
#define SYSTEMINFOPUBLISHER_H

#include "MqttClient.h"

class SystemInfoPublisher : public MqttClient {
public:
    /**
     * Constructor to initialize the SystemInfoPublisher with server address and client ID.
     * @param serverAddress The address of the MQTT server.
     * @param clientId The client ID for the MQTT client.
     */
    SystemInfoPublisher(const std::string& serverAddress, const std::string& clientId);

    /**
     * Starts publishing system information periodically.
     * @param topic The topic to publish to.
     * @param interval The interval in seconds between each publish.
     */
    void startPublishing(const std::string& topic, int interval) override;

private:
    /**
     * Reads the current system information and returns it as a JSON object.
     * @return A JSON object containing the system information.
     */
    nlohmann::json readSystemInfo();

    int getFanSpeed();

};

#endif // SYSTEMINFOPUBLISHER_H