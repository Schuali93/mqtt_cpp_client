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

class MqttClient {
public:
    /**
     * Constructor to initialize the MQTT client with server address and client ID.
     * @param serverAddress The address of the MQTT server.
     * @param clientId The client ID for the MQTT client.
     */
    MqttClient(const std::string& serverAddress, const std::string& clientId);

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
     * @param payload The message payload.
     * @param qos The Quality of Service level.
     */
    void publish(const std::string& topic, const std::string& payload, int qos);

    /**
     * Disconnects from the MQTT server.
     */
    void disconnect();

    /**
     * Starts a thread to periodically publish messages to a topic.
     * @param topic The topic to publish to.
     * @param payload The message payload.
     * @param qos The Quality of Service level.
     * @param interval The interval in seconds between each publish.
     */
    void startPeriodicPublish(const std::string& topic, const std::string& payload, int qos, int interval);

    /**
     * Stops the periodic publishing thread.
     */
    void stopPeriodicPublish();

private:
    /**
     * The function that runs in a separate thread to periodically publish messages.
     * @param topic The topic to publish to.
     * @param payload The message payload.
     * @param qos The Quality of Service level.
     * @param interval The interval in seconds between each publish.
     */
    void periodicPublish(const std::string& topic, const std::string& payload, int qos, int interval);

    class callback : public virtual mqtt::callback {
    public:
        /**
         * Callback function to handle message arrival.
         * @param msg The arrived message.
         */
        void message_arrived(mqtt::const_message_ptr msg) override;
    };

    mqtt::async_client client; ///< The MQTT asynchronous client.
    callback cb; ///< The callback handler for the MQTT client.
    std::thread publishThread; ///< The thread for periodic publishing.
    std::atomic<bool> running; ///< Atomic flag to control the periodic publishing thread.
};

#endif // MQTTCLIENT_H