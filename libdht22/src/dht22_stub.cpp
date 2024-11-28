//
// Created by Bradley on 11/24/24.
//
// This is a stub to be able to develop on systems that are not raspberry pi.
//
#include "devices/dht22.h"

#include <iostream>

namespace devices {
    dht22::dht22() {
    } // dht22

    dht22::~dht22() {
    } // ~dht22

    bool dht22::Create() {
        return true;
    } // Create

    bool dht22::Read_() {
        static auto start = std::chrono::steady_clock::now();
        std::chrono::seconds duration = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::steady_clock::now() - start);

        m_temperature = 2.0f + static_cast<float>(duration.count() % 90);
        m_humidity = 55.0f;

        return true;
    } // Read_

    bool dht22::Read(int count) {
        return Read_();
    } // Read
}; // devices