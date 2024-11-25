cmake_minimum_required(VERSION 3.25)

project(dht22app)

include_directories(libdht22/include)
add_subdirectory(libdht22)

add_executable(dht22app dht22/main.cpp)

if(EXISTS "/usr/local/lib/libwiringPi.so")
    target_link_libraries(dht22app PRIVATE dht22 wiringPi)
else()
    target_link_libraries(dht22app PRIVATE dht22)
endif()

