#include <Arduino.h>
#include "controller.hpp"

uint16_t con1 = 0;
uint16_t con2 = 0;

void init_controller()
{
	pinMode(POWER_1, OUTPUT);
	digitalWrite(POWER_1, OUTPUT);
	pinMode(POWER_2, OUTPUT);
	digitalWrite(POWER_1, OUTPUT);

	// Set DATA_CLOCK normally HIGH
	pinMode(DATA_CLOCK_1, OUTPUT);
	digitalWrite(DATA_CLOCK_1, HIGH);
	pinMode(DATA_CLOCK_2, OUTPUT);
	digitalWrite(DATA_CLOCK_2, HIGH);

	// Set DATA_LATCH normally LOW
	pinMode(DATA_LATCH_1, OUTPUT);
	digitalWrite(DATA_LATCH_1, LOW);
	pinMode(DATA_LATCH_2, OUTPUT);
	digitalWrite(DATA_LATCH_2, LOW);

	// Set DATA_SERIAL normally HIGH
	pinMode(DATA_SERIAL_1, OUTPUT);
	digitalWrite(DATA_SERIAL_1, HIGH);
	pinMode(DATA_SERIAL_1, INPUT);
	pinMode(DATA_SERIAL_2, OUTPUT);
	digitalWrite(DATA_SERIAL_2, HIGH);
	pinMode(DATA_SERIAL_2, INPUT);
}

void update_controller()
{
	// Latch for 12us
	digitalWrite(DATA_LATCH_1, HIGH);
	delayMicroseconds(12);
	digitalWrite(DATA_LATCH_1, LOW);
	delayMicroseconds(6);

	// Retrieve button presses from shift register by pulling the clock high for 6us
	con1 = 0;
	for (int i = 0; i < 16; i++)
	{
		digitalWrite(DATA_CLOCK_1, LOW);
		delayMicroseconds(6);
		if (i <= 11)
		{
			con1 |= (!digitalRead(DATA_SERIAL_1)) << i;
		}
		digitalWrite(DATA_CLOCK_1, HIGH);
		delayMicroseconds(6);
	}

	// Latch for 12us
	digitalWrite(DATA_LATCH_2, HIGH);
	delayMicroseconds(12);
	digitalWrite(DATA_LATCH_2, LOW);
	delayMicroseconds(6);

	// Retrieve button presses from shift register by pulling the clock high for 6us
	con2 = 0;
	for (int i = 0; i < 16; i++)
	{
		digitalWrite(DATA_CLOCK_2, LOW);
		delayMicroseconds(6);
		if (i <= 11)
		{
			con2 |= (!digitalRead(DATA_SERIAL_2)) << i;
		}
		digitalWrite(DATA_CLOCK_2, HIGH);
		delayMicroseconds(6);
	}
}