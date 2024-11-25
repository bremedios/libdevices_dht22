//
//  Originally from lol_dht22/dht22.c
//
#include <chrono>

namespace devices {
    class dht22 {
    public:
        dht22();
	~dht22();

	bool Create();
	bool Read(int count=5);

	float getTemperature() const { return m_temperature; }
	float getHumidity() const { return m_humidity; }
    private:
	bool Read_();

	std::chrono::steady_clock::time_point m_nextRead;
	float                                 m_temperature=0.0f;
	float                                 m_humidity=0.0f;
	int                                   m_pin=7;
	int                                   m_dat[5]={0};
	int                                   m_readPeriod=2000;

    }; // dht22
}; // devices
