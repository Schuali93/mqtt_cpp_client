/*
 * MqttClient.h
 * 
 * Declaration of the MqttClient class for connecting, subscribing, publishing,
 * and periodically publishing messages to an MQTT broker.
 * 
 * Author: schuali93
 * Date: 18.01.25
 */

#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <string>
#include <thread>
#include <atomic>
#include <mqtt/async_client.h>
#include <nlohmann/json.hpp>

class MqttClient {
public:
    /**
     * Constructor to initialize the MQTT client with server address and client ID.
     * @param serverAddress The address of the MQTT server.
     * @param clientId The client ID for the MQTT client.
     */
    MqttClient(const std::string& serverAddress, const std::string& clientId);

    virtual ~MqttClient() {}; // Add virtual destructor

    /**
     * Connects to the MQTT server with the provided username and password.
     * @param username The username for authentication.
     * @param password The password for authentication.
     */
    void connect(const std::string& username, const std::string& password);

    /**
     * Subscribes to a topic with the specified Quality of Service (QoS) level.
     * @param topic The topic to subscribe to.
     * @param qos The Quality of Service level.
     */
    void subscribe(const std::string& topic, int qos);

    /**
     * Publishes a message to a topic with the specified payload and QoS level.
     * @param topic The topic to publish to.
     * @param payload The message payload in JSON format.
     * @param qos The Quality of Service level.
     */
    void publish(const std::string& topic, const nlohmann::json& payload, int qos);

    /**
     * Disconnects from the MQTT server.
     */
    void disconnect();

    virtual void startPublishing(const std::string& topic, int interval);

    /**
     * Stops the periodic publishing thread.
     */
    void stopPublishing();

protected:

    class callback : public virtual mqtt::callback {
    public:
        /**
         * Callback function to handle message arrival.
         * @param msg The arrived message.
         */
        void message_arrived(mqtt::const_message_ptr msg) override;
    };

    mqtt::async_client client;
    std::thread publishThread;
    std::atomic<bool> running;
    callback cb;
};

#endif // MQTTCLIENT_H