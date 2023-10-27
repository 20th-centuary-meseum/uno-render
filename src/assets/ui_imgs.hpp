#ifndef UI_IMGS
#define UI_IMGS

#define HEART_FULL 0
#define HEART_HALF 1

#define SCORE_START_L 2
#define SCORE_START_R 6

#define SCORE_FRAME_L 10
#define SCORE_FRAME_M1 11
#define SCORE_FRAME_M2 12
#define SCORE_FRAME_R 13

const byte ui_imgs[][8] PROGMEM = {

	// HEART_FULL 0
	{0b00000000,
	 0b01101100,
	 0b11111110,
	 0b11111110,
	 0b01111100,
	 0b00111000,
	 0b00010000,
	 0b00000000},

	// HEART_HALF 1
	{0b00000000,
	 0b01101100,
	 0b10010010,
	 0b10000010,
	 0b01111100,
	 0b00111000,
	 0b00010000,
	 0b00000000},

	// SCORE_ZERO ( SCORE_START_L 2)
	{0b01110000,
	 0b01010000,
	 0b01010000,
	 0b01110000,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000},
	// SCORE_ONE
	{0b00100000,
	 0b00100000,
	 0b00100000,
	 0b00100000,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000},
	// SCORE_TWO
	{0b01110000,
	 0b00010000,
	 0b01100000,
	 0b01110000,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000},
	// SCORE_THREE
	{0b01110000,
	 0b00110000,
	 0b00010000,
	 0b01110000,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000},
	// SCORE_ZERO ( SCORE_START_R 6)
	{0b00001110,
	 0b00001010,
	 0b00001010,
	 0b00001110,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000},
	// SCORE_ONE
	{0b00000100,
	 0b00000100,
	 0b00000100,
	 0b00000100,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000},
	// SCORE_TWO
	{0b00001110,
	 0b00000010,
	 0b00001100,
	 0b00001110,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000},
	// SCORE_THREE
	{0b00001110,
	 0b00000110,
	 0b00000010,
	 0b00001110,
	 0b00000000,
	 0b00000000,
	 0b00000000,
	 0b00000000},
	// SCORE_FRAME_L 10
	{0b00000111,
	 0b00000100,
	 0b00000100,
	 0b00000100,
	 0b00000100,
	 0b00000100,
	 0b00000100,
	 0b00000111},

	// SCORE_FRAME_M1 11
	{0b11111111,
	 0b00000000,
	 0b00000001,
	 0b00000000,
	 0b00000001,
	 0b00000000,
	 0b00000001,
	 0b11111110},

	// SCORE_FRAME_M2 12
	{0b01111111,
	 0b10000000,
	 0b00000000,
	 0b10000000,
	 0b00000000,
	 0b10000000,
	 0b00000000,
	 0b11111111},

	// SCORE_FRAME_R 13
	{0b11100000,
	 0b00100000,
	 0b00100000,
	 0b00100000,
	 0b00100000,
	 0b00100000,
	 0b00100000,
	 0b11100000}};

#endif