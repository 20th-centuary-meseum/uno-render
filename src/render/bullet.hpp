#ifndef BULLET_H
#define BULLET_H

#include "./decode_img.hpp"
#include "./sprite.hpp"
#include "../../common.hpp"

class Bullet : public Sprite // 10 byte
{
public:
	Bullet(byte _x, byte _y, byte dir);
	byte frame_left;
	void next_frame();
	bool did_crash();
};

class Bullets // 9 byte
{
public:
	byte next_bullet_idx;
	Bullets();
	Bullet *bullets[BULLET_MAX_NUM];
	byte bullets_crashed;
	void add_bullet(byte x, byte y, byte dir);
	void next_frame();
	void render();
};

#endif