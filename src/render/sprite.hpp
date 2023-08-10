#ifndef SPRITE_H
#define SPRITE_H

#include "../../common.hpp"

class Sprite
{
public:
	Sprite(byte _face_id, byte _x, byte _y);
	byte x;
	byte y;
	byte face_id;
	void render();
};

#endif