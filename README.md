Welcome to the DHT22 library.  This is a library (and program to test it) that utilizes the DHT22 / DHT11 temperature
and humidity sensor.

## Original Author
The original author of this code was [Joshua Small](https://github.com/technion).  The repository is available here [github: lol_dht22](https://github.com/technion/lol_dht22)

The code was modified to put it into a shared library and include a test app to grab the data from the shared library.

## Devices
- DHT22 [Tested]
  - Maximum poll rate of 1 second  
- DHT11 [Untested]
  - Supposed to be compatible with the DHT22 but has a maximum poll rate of 1 second.

## Hookup / Wiring Notes
Some of the sensors bought online will require a resistor and some will not as some sellers include the resistor
already connected.  Verify what you purchase to determine if you require the use of a resistor.

## Building
```bash
$ cmake .
make
sudo make install
```

## Using the library

### Create
```c++
bool Create();
```
Class Initialization.

### Read
```c++
bool Read(int count=5);
```
> [!WARNING] This is a blocking call and will enfore a 2 second read interval on the sensor.

This will block until (one of)
- Sensor data was read successfully
- count attempts have been tried and have failed

### getTemperature
```c++
float getTemperature() const
```

### getHumidity
```c++
float getHumidity() const
```