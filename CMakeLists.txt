cmake_minimum_required(VERSION 3.10)
project(typing_service)

set(CMAKE_CXX_STANDARD 17)

find_package(nlohmann_json REQUIRED)

add_executable(client src/client.cpp)

target_link_libraries(client nlohmann_json::nlohmann_json)
