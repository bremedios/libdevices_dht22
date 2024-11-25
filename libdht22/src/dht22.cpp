//
//  Originated from lol_dht22 program
//
#include <iostream>
#include <thread>
#include <cstring>

#include <unistd.h>

#include <wiringPi.h>

#include "devices/dht22.h"

#define MAXTIMINGS 85

static uint8_t sizecvt(const int read)
{
    /* digitalRead() and friends from wiringpi are defined as returning a value
       < 256. However, they are returned as int() types. This is a safety function */

    if (read > 255 || read < 0)
    {
        std::cerr << "sizecvt: Invalid data from wiringPi library" << std::endl;
    }

    return (uint8_t)read;
} // sizecvt

namespace devices {
    dht22::dht22() {
    } // dht22

    dht22::~dht22() {
    } // ~dht22

    bool dht22::Create() {
	    m_nextRead = std::chrono::steady_clock::now() + std::chrono::milliseconds(m_readPeriod);

        if (0 > wiringPiSetup()) {
            std::cerr << "dht22::Create: wiringPiSetup failed" << std::endl;

	        return false;
	    }
  
        if (setuid(getuid()) < 0)
        {
            std::cerr << "dht22::Create: setuid() failed" << std::endl;
            return false;
        }

        return true;
    } // Create

    bool dht22::Read_() {
        uint8_t laststate = HIGH;
        uint8_t counter = 0;
        uint8_t j = 0, i;

	    memset(m_dat, 0, sizeof(m_dat));

	    //  We need to sleep to ensure that we are not reading too
	    //  frequently.
	    for (;;) {

            auto now = std::chrono::steady_clock::now();

	        if (now > m_nextRead) {
                    break;
	        }

	        std::this_thread::sleep_for(m_nextRead - now);
        }
  
	    // pull pin down for 18 milliseconds
	    pinMode(m_pin, OUTPUT);
	    digitalWrite(m_pin, HIGH);
        delay(500);
        digitalWrite(m_pin, LOW);
        delay(20);
        // prepare to read the pin
        pinMode(m_pin, INPUT);

        // detect change and read data
        for ( i=0; i< MAXTIMINGS; i++) {
            counter = 0;
            while (sizecvt(digitalRead(m_pin)) == laststate) {
                counter++;
                delayMicroseconds(2);
                if (counter == 255) {
                    break;
                }
            }
            laststate = sizecvt(digitalRead(m_pin));

            if (counter == 255)
               break;

            // ignore first 3 transitions
            if ((i >= 4) && (i%2 == 0)) {
                // shove each bit into the storage bytes
                m_dat[j/8] <<= 1;
                if (counter > 16)
                  m_dat[j/8] |= 1;
                j++;
            }
        }

	    m_nextRead = std::chrono::steady_clock::now() + std::chrono::milliseconds(m_readPeriod);

        // check we read 40 bits (8bit x 5 ) + verify checksum in the last byte
        // print it out if data is good
        if ((j >= 40) && 
            (m_dat[4] == ((m_dat[0] + m_dat[1] + m_dat[2] + m_dat[3]) & 0xFF)) ) {
            float t, h;
            h = (float)m_dat[0] * 256 + (float)m_dat[1];
            h /= 10;
            t = (float)(m_dat[2] & 0x7F)* 256 + (float)m_dat[3];
            t /= 10.0;
            if ((m_dat[2] & 0x80) != 0)
                t *= -1;

	        m_temperature =t;
	        m_humidity=h;

            return true;
        }
        else
        {
            return false;
        }
    } // Read_

    bool dht22::Read(int count) {
	    int attempt = 0;

        for (int i = 0; i < count; ++i) {
            if (Read_())
                return true;
        }

	    return false;
    } // Read
}; // devices
