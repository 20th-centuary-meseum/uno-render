#ifndef TILE_IMGS_H
#define TILE_IMGS_H

const byte tile_imgs[][32] PROGMEM = {
	{0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000},
	{0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000},

	// 나무1
	{0b00000111, 0b00000000,
	 0b01111100, 0b11111100,
	 0b00100000, 0b00000110,
	 0b00100000, 0b00000100,
	 0b00100000, 0b00001100,
	 0b00100000, 0b00000000,
	 0b00010000, 0b00001100,
	 0b00010000, 0b00001010,
	 0b01100000, 0b00000010,
	 0b01000000, 0b00000011,
	 0b01000000, 0b00000110,
	 0b11000101, 0b10011100,
	 0b01111101, 0b10010100,
	 0b00000001, 0b11110000,
	 0b00000001, 0b10000000,
	 0b00000011, 0b11000000},

	// 파도1
	{0b00000001, 0b11110000,
	 0b00000011, 0b00011000,
	 0b00001100, 0b00000100,
	 0b00001000, 0b00000010,
	 0b00010001, 0b11000001,
	 0b00110011, 0b00110001,
	 0b00100110, 0b00001001,
	 0b01101100, 0b00000100,
	 0b01001000, 0b00100011,
	 0b11010000, 0b01000000,
	 0b10010000, 0b10000000,
	 0b10010000, 0b10000000,
	 0b00000000, 0b01000000,
	 0b00010000, 0b00100000,
	 0b10000000, 0b00010000,
	 0b01111111, 0b11111110},

	// 산1
	{0b00000000, 0b01000000,
	 0b00000000, 0b10100000,
	 0b00000001, 0b00010000,
	 0b00000010, 0b00001000,
	 0b00000100, 0b00000100,
	 0b00001000, 0b11000010,
	 0b00000000, 0b00100001,
	 0b00010000, 0b00010000,
	 0b00101000, 0b00001000,
	 0b01000100, 0b00000000,
	 0b10000010, 0b00000010,
	 0b00000010, 0b00000100,
	 0b00000000, 0b00000001,
	 0b00000000, 0b00000000,
	 0b10000000, 0b00011111,
	 0b01111111, 0b10000000},

	// empty
	{0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000,
	 0b00000000, 0b00000000},

	// 나무2
	{0b00000111, 0b00000000,
	 0b01111111, 0b11111100,
	 0b00111111, 0b11111110,
	 0b00111111, 0b11111100,
	 0b00111111, 0b11111100,
	 0b00111111, 0b11110000,
	 0b00011111, 0b11111100,
	 0b00011111, 0b11111110,
	 0b01111111, 0b11111110,
	 0b01111111, 0b11111111,
	 0b01111100, 0b00111110,
	 0b11111101, 0b10111100,
	 0b01111101, 0b10110100,
	 0b00000001, 0b10110000,
	 0b00000001, 0b10000000,
	 0b00000011, 0b11000000},

	// 파도2
	{0b00000001, 0b11110000,
	 0b00000011, 0b11111000,
	 0b00001111, 0b11111100,
	 0b00001111, 0b11111110,
	 0b00011110, 0b00111111,
	 0b00111100, 0b11001111,
	 0b00111001, 0b11110111,
	 0b01110011, 0b11111011,
	 0b01110111, 0b11011100,
	 0b11101111, 0b10100000,
	 0b11101111, 0b01000000,
	 0b11101111, 0b01000000,
	 0b01111111, 0b10100000,
	 0b01101111, 0b11010000,
	 0b11111111, 0b11101000,
	 0b01111000, 0b01111110},

	// 산2
	{0b00000000, 0b01000000,
	 0b00000000, 0b11100000,
	 0b00000001, 0b11110000,
	 0b00000011, 0b11111000,
	 0b00000111, 0b11111100,
	 0b00001111, 0b00111110,
	 0b00001111, 0b11011111,
	 0b00010111, 0b11101111,
	 0b00111011, 0b11110111,
	 0b01111101, 0b11111001,
	 0b11111110, 0b11111110,
	 0b11111111, 0b11111100,
	 0b11111111, 0b11111101,
	 0b11111111, 0b11111111,
	 0b11111111, 0b11111111,
	 0b01111111, 0b10000000},

};

#endif