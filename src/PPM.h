#pragma once

#include "Arduino.h"

#define MAX_CHANNELS 8 // the maximum channel number
#define MIN_PULSE 1000	  // min valid impulse us
#define MAX_PULSE 2000	  // max valid impulse us

class PPM
{
public:
	void begin(uint8_t inputPort, uint8_t max_channels);
	uint16_t get(uint8_t channel);
	uint8_t getPWM(uint8_t channel);
	uint16_t getServo_us(uint8_t channel);
	void increment_ovf_count();
	bool available();
	void process();
	
private:
	uint16_t _channels[MAX_CHANNELS];
	volatile uint32_t _ovf_count;
	uint8_t _max_channels;
	uint32_t _micros_count;
	uint32_t _micros();
	bool _available;
};

extern PPM ppm;