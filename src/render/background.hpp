#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../../common.hpp"

class Background
{
public:
	byte map[MAP_WIDTH * MAP_HEIGHT];
	Background();
	void set(byte X, byte Y, byte tile_id, byte tile_rot); // fin!!
	void render();
};

#endif