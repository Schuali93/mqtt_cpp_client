#ifndef MQTTCLIENT_H
#define MQTTCLIENT_H

#include <string>
#include <mqtt/async_client.h>

class MqttClient {
public:
    MqttClient(const std::string& serverAddress, const std::string& clientId);
    void connect(const std::string& username, const std::string& password);
    void subscribe(const std::string& topic, int qos);
    void publish(const std::string& topic, const std::string& payload, int qos);
    void disconnect();

private:
    class callback : public virtual mqtt::callback {
    public:
        void message_arrived(mqtt::const_message_ptr msg) override;
    };

    mqtt::async_client client;
    callback cb;
};

#endif // MQTTCLIENT_H