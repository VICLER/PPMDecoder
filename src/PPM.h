/* Arduino library for decoding PPM receiver signal
 *
 * Copyright (c) 2020 Victor Glekler
 *
 * MIT License
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
/**
 * @file PPM.h
 * @brief Base class for PPM Decoder
 * @author Victor Glekler
 * Contact: victor.glekler@gmail.com
 * https://github.com/VICLER
*/

#pragma once

#include "Arduino.h"

#define MAX_CHANNELS 8 	  // the maximum channel number
#define MIN_PULSE 1000	 // min valid impulse us
#define MAX_PULSE 2000	// max valid impulse us

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