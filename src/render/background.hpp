#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../../common.hpp"

#define MAP_LEN 2

const byte background_map[][MAP_HEIGHT] PROGMEM = {
	{0b00000000,
	 0b00000000,
	 0b01011010,
	 0b01000010,
	 0b01011010,
	 0b00000000},

	{0b00000000,
	 0b00011000,
	 0b01010010,
	 0b01000010,
	 0b01001010,
	 0b00011000},

	{0b00000000,
	 0b00001000,
	 0b01100000,
	 0b01100110,
	 0b00000110,
	 0b00010000},
};

class Background
{

private:
	byte generate_obstacle(byte x, byte y, byte seed, byte tild_id, byte step);
	byte generate_map(byte tild_id);
	byte cnt_open_paths(byte x, byte y, byte* check);
public:
	byte map[MAP_WIDTH * MAP_HEIGHT];
	Background();
	byte get(byte x, byte y);
	void set(byte x, byte y, byte tile_id);
	void set(byte x, byte y, byte tile_id, bool invinsible);
	bool is_invinsible(byte x, byte y);
	void render();
};

#endif