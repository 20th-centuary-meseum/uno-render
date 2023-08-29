#ifndef BULLET_H
#define BULLET_H

#include "./sprite.hpp"
#include "../../common.hpp"

class Bullet : public Sprite // 10 byte
{
public:
	Bullet(byte _x, byte _y, byte dir);
	byte frame_left;
	void next_frame();
};

class Bullets // 9 byte
{
public:
	byte next_bullet_idx;
	Bullets();
	Bullet *bullets[BULLET_MAX_NUM];
	void add_bullet(byte x, byte y, byte dir);
	void next_frame();
	void render();
};

#endif