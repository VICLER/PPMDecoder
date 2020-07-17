#pragma once

#include "Arduino.h"

#define MAX_CHANNEL_NUM 8 // the maximum channel number
#define MIN_PULSE 1000	  // min valid impulse us
#define MAX_PULSE 2000	  // max valid impulse us

class PPM
{
public:
	void begin(uint8_t inputPort);
	uint16_t get(uint8_t channel);
	uint8_t getPWM(uint8_t channel);
	void increment_ovf_count();
	bool available();
	void process();
	
private:
	uint16_t _channels[MAX_CHANNEL_NUM];
	volatile uint32_t _ovf_count;
	uint32_t _micros_count;
	uint32_t _micros();
	bool _available;
};

extern PPM ppm;