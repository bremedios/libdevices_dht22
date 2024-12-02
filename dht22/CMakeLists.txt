cmake_minimum_required(VERSION 3.25)

project(dht22app VERSION 0.01)

set(CMAKE_CXX_STANDARD 20)

include_directories(../libdht22/include)

add_executable(dht22app main.cpp)

if(EXISTS "/usr/local/lib/libwiringPi.so")
    target_link_libraries(dht22app PRIVATE devices_dht22 wiringPi)
else()
    target_link_libraries(dht22app PRIVATE devices_dht22)
endif()

install(PROGRAMS dht22app DESTINATION bin)
