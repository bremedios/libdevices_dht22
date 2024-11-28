cmake_minimum_required(VERSION 3.25)

project(devices_dht22)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

include_directories(include)

set(PUBLIC_HEADER include/devices/dht22.h)

set(HEADER_FILES include/devices/dht22.h)

#  We compile against the stub if wiringPi is not available.
if(EXISTS "/usr/local/include/wiringPi.h")
    set(SOURCE_FILES src/dht22.cpp)
else()
    set(SOURCE_FILES src/dht22_stub.cpp)
endif()

add_library(devices_dht22 SHARED ${SOURCE_FILES} ${HEADER_FILES})

if(EXISTS "/usr/local/lib/libwiringPi.so")
    target_link_libraries(devices_dht22 PRIVATE wiringPi)
endif()

install(TARGETS devices_dht22 DESTINATION lib)
install(FILES include/devices/dht22.h DESTINATION include/devices)