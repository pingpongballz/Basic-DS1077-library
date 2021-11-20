#include "Arduino.h"
#include "DS1077.h"
#include "Wire.h"


byte address = 0xB0 >> 1;
byte mux_word[2] = { 0x18,0x00 };
byte div_word[2] = { 0x00,0x00 };

DS1077::DS1077(unsigned long base_freq, int CTRL0, int CTRL1)
{
	Wire.begin();
	
	_base_freq = base_freq;
	_CTRL0 = CTRL0;
	_CTRL1 = CTRL1;
	pinMode(_CTRL0, OUTPUT);
	pinMode(_CTRL1, OUTPUT);
}

unsigned long DS1077::set_freq(word N_scale, word P1_scale)
{
	if (P1_scale == 1 || P1_scale == 2 || P1_scale == 4 || P1_scale == 8)
	{
		int P1_scale_place = log10(P1_scale) / log10(2);
		set_N_divider(N_scale);
		set_P1_divider(P1_scale_place);
		return _base_freq / (N_scale * P1_scale);
	}

}

unsigned long DS1077::set_OUT0_div(byte P0_scale)
{
	if (P0_scale == 1 || P0_scale == 2 || P0_scale == 4 || P0_scale == 8)
	{
		byte P0_scale_place = log10(P0_scale) / log10(2);
		mux_word[0] = (mux_word[0] & 0b11111001) | P0_scale_place << 1;
		write_to(2, MUX, mux_word);
		return _base_freq / P0_scale;
	}

}


void DS1077::toggle_OUT0(bool condition)
{
	mux_word[0] = (mux_word[0] & 0b11000111) | 0b00011000;
	write_to(2, MUX, mux_word);
	if (condition)
	{
		digitalWrite(_CTRL0, 0);
	}
	else
	{
		digitalWrite(_CTRL0, 1);
	}
	
}

void DS1077::toggle_OUT1(bool condition)
{
	mux_word[0] = (mux_word[0] & 0b10111111);
	write_to(2, MUX, mux_word);
	if (condition)
	{
		digitalWrite(_CTRL1, 0);
	}
	else
	{
		digitalWrite(_CTRL1, 1);
	}
}



void DS1077::reset(void)
{

	mux_word[0] = 0x18;
	mux_word[1] = 0x00;
	div_word[0] = 0x00;
	div_word[1] = 0x00;
	write_to(2, DIV, div_word);
	write_to(2, MUX, mux_word);
}

unsigned long DS1077::set_closest_freq(uint32_t freq)
{
	unsigned long ratio = _base_freq / freq;
	unsigned long closest_freq;
	int P1_shift = 0;
	unsigned int P1 = 1;
	if (ratio >= 8200)
	{
		ratio = 8200;
	}
	else if (ratio <= 1)
	{
		ratio = 1;
	}
	while (!(ratio >= 1 && ratio <= 1025))
	{
		ratio = ratio >> 1;
		P1_shift++;
	}
	P1 = P1 << P1_shift;
	Serial.println(P1);
	set_freq(ratio, P1);
	closest_freq = _base_freq / (ratio * P1);
	
	return closest_freq;

}



void DS1077::write_to(int data_bytes, byte reg_addr, byte data[])
{
	Wire.beginTransmission(address);
	Wire.write(reg_addr);
	for (int i = 0; i < data_bytes; i++)
	{
		Wire.write(data[i]);
	}
	Wire.endTransmission();
}

void DS1077::set_N_divider(word divider)
{
	if (divider >= 2 && divider <= 1025)
	{
		mux_word[1] = mux_word[1] & 0b10111111;
		write_to(2, MUX, mux_word);
		divider -= 2;
		divider = divider << 6;
		byte firstbyte = highByte(divider);
		byte secondbyte = lowByte(divider);
		div_word[0] = firstbyte;
		div_word[1] = secondbyte;
		write_to(2, DIV, div_word);
	}
	else if (divider == 1)
	{
		mux_word[1] = mux_word[1] | 0b01000000;
		write_to(2, MUX, mux_word);
	}

}

void DS1077::set_P1_divider(word divider)
{
	if (divider >= 1 && divider <= 4)
	{
		divider = divider << 7;
		mux_word[0] = (mux_word[0] & 0b11111110) | highByte(divider);
		mux_word[1] = (mux_word[0] & 0b01111111) | lowByte(divider);
		write_to(2, MUX, mux_word);
	}
	
}

