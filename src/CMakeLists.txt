cmake_minimum_required(VERSION 3.1)
project(mqtt_client)

add_executable(mqtt_client main.cpp MqttClient.cpp)
target_link_libraries(mqtt_client paho-mqttpp3 paho-mqtt3as)