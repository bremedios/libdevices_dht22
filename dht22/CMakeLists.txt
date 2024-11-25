cmake_minimum_required(VERSION 3.25)

project(dht22app)

set(CMAKE_CXX_STANDARD 20)

include_directories(../libdht22/include)

add_executable(dht22app main.cpp)

target_link_libraries(dht22app PRIVATE dht22)
