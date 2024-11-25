//
// Created by Bradley on 11/24/24.
//
// This is a stub to be able to develop on systems that are not raspberry pi.
//
#include "devices/dht22.h"

namespace devices {
    dht22::dht22() {
    } // dht22

    dht22::~dht22() {
    } // ~dht22

    bool dht22::Create() {
        return true;
    } // Create

    bool dht22::Read_() {
        m_temperature = 15.0f;
        m_humidity = 55.0f;

        return true;
    } // Read_

    bool dht22::Read(int count) {
        return Read_();
    } // Read
}; // devices
