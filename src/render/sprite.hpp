#ifndef SPRITE_H
#define SPRITE_H

#include "../../common.hpp"

class Sprite
{
public:
	Sprite(byte _face_id, short _x, short _y);
	static byte frame_cnt;
	static void start_next_frame();

	short x;
	short y;
	int8_t vx;
	int8_t vy;
	byte x_frame;
	byte y_frame;
	byte face_id;
	void render();
	void next_frame();
};

#endif