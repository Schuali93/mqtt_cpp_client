cmake_minimum_required(VERSION 3.14)
project(mqtt_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.10.5  # You can specify the version you want to use
)

FetchContent_MakeAvailable(json)

add_executable(mqtt_client main.cpp MqttClient.cpp SystemInfoPublisher.cpp)
target_link_libraries(mqtt_client PRIVATE paho-mqttpp3 paho-mqtt3as nlohmann_json::nlohmann_json)