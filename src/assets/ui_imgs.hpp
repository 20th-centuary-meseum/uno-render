#ifndef UI_IMGS
#define UI_IMGS

#define HEART_FULL 0
#define HEART_HALF 1

const byte ui_imgs[][8] PROGMEM = {

	// HEART_FULL
	{0b00000000,
	 0b01101100,
	 0b11111110,
	 0b11111110,
	 0b01111100,
	 0b00111000,
	 0b00010000,
	 0b00000000},

	// HEART_HALF
	{0b00000000,
	 0b01101100,
	 0b10010010,
	 0b10000010,
	 0b01111100,
	 0b00111000,
	 0b00010000,
	 0b00000000},
};

#endif