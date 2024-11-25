#include <iostream>

#include "devices/dht22.h"

int main (int argc, char**argv) {

	devices::dht22 dht22;

	if (!dht22.Create()) {
		std::cerr << "dht22::Create() failed:" << std::endl;
		return -1;
	}

	if (!dht22.Read()) {
		std::cerr << "dht22::Read() failed: " << std::endl;
		return -1;
	}

	std::cout << "Temperature: " << dht22.getTemperature() << std::endl;
	std::cout << "Humidity:    " << dht22.getHumidity() << std::endl;

	return 0;
} // main
