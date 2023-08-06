#ifndef SPRITE_H
#define SPRITE_H

#include "../../common.hpp"

class Sprite
{
public:
	Sprite(byte X, byte Y);
	byte x;
	byte y;
	byte face_id;
	void render();
};

#endif