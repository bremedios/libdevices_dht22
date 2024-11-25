cmake_minimum_required(VERSION 3.25)

project(dht22)

set(CMAKE_CXX_STANDARD 20)

option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

include_directories(include)

set(PUBLIC_HEADER include/devices/dht22.h)

set(HEADER_FILES include/devices/dht22.h)
set(SOURCE_FILES src/dht22.cpp)
#set(SOURCE_FILES src/dht22_stub.cpp)

add_library(dht22 SHARED ${SOURCE_FILES} ${HEADER_FILES})

install(TARGETS dht22 DESTINATION lib)
install(FILES include/devices/dht22.h DESTINATION include/devices)
