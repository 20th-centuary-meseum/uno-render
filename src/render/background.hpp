#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../../common.hpp"

const byte background_map[][MAP_HEIGHT] PROGMEM = {
	{0b00000000,
	 0b00011000,
	 0b01011010,
	 0b01000010,
	 0b01011010,
	 0b00011000},

	{0b00000000,
	 0b00001000,
	 0b01100000,
	 0b01000010,
	 0b00000110,
	 0b00010000},
};

class Background
{
public:
	byte map[MAP_WIDTH * MAP_HEIGHT];
	Background();
	void set(byte X, byte Y, byte tile_id);
	void set(byte X, byte Y, byte tile_id, bool invinsible);
	void render();
	void generate_map();
};

#endif