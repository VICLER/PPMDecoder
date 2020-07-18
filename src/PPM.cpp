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

#include "PPM.h"

PPM ppm;

static void ISR_PPM(void)
{
	ppm.process();
}

ISR(TIMER2_OVF_vect)
{
	ppm.increment_ovf_count();
}

void PPM::begin(uint8_t inputPort, uint8_t max_channels = MAX_CHANNELS)
{
	pinMode(inputPort, INPUT);
	attachInterrupt(digitalPinToInterrupt(inputPort), ISR_PPM, FALLING);
	_max_channels = max_channels; 
	for (uint8_t i = 0; i < MAX_CHANNELS; i++)
		_channels[i] = 0;

	_ovf_count = 0;
	_micros_count = 0;

	TCCR2B = (TCCR2B & 0b11111000) | (1 << CS21); 	// 8 prescaler
	TIMSK2 |= 0b00000001;				 		   // enable TIMER2 overflow interrupt
	TCCR2A &= 0b11111100;
	TCCR2B &= 0b11110111;
}

uint32_t PPM::_micros()
{
	uint8_t SREG_old = SREG;
	cli();
	uint8_t tcnt2 = TCNT2;
	bool flag_save = bitRead(TIFR2, 0);
	if (flag_save)
	{
		tcnt2 = TCNT2;
		_ovf_count++;
		TIFR2 |= 0b00000001;
	}
	_micros_count = (_ovf_count << 8) | tcnt2 ;
	SREG = SREG_old;
#if (F_CPU == 16000000)
	return _micros_count >> 1;
#elif (F_CPU == 8000000)
	return _micros_count;
#endif
}

void PPM::increment_ovf_count()
{
	_ovf_count++;
}

void PPM::process()
{
	static uint8_t _channel_index = _max_channels;
	static uint32_t _lastTime = 0, _currentTime = 0;

	_currentTime = _micros();
	int16_t pulse_us = _currentTime - _lastTime;
	_lastTime = _currentTime;

	if (pulse_us > 3000 && pulse_us < 12000) // sync
	{
		_channel_index = 0;
		_available = true;
		return;
	}
	else if (pulse_us > 12000)
		_available = false;

	if (_channel_index < _max_channels)
		_channels[_channel_index++] = constrain(pulse_us, MIN_PULSE, MAX_PULSE);
}

uint16_t PPM::get(uint8_t channel)
{
	return (_channels[channel - 1]);
}

uint8_t PPM::getPWM(uint8_t channel)
{
	return (_channels[channel - 1] - MIN_PULSE) * 0.255f;
}

uint16_t PPM::getServo_us(uint8_t channel){
	return ( (_channels[channel - 1] - 706.89655) * 1.856 ); // range 0 -> 180 using WriteMicroseconds
}

bool PPM::available()
{
	return _available;
}