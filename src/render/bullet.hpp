#ifndef BULLET_H
#define BULLET_H

#include "./sprite.hpp"
#include "../../common.hpp"

class Bullet : public Sprite
{
public:
	Bullet(byte _x, byte _y, byte dir);

	byte team;
	byte frame_left;
	void next_frame();
};

#endif