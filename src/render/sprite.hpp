#ifndef SPRITE_H
#define SPRITE_H

#include "../../common.hpp"

class Sprite
{
public:
	Sprite(byte _face_id, byte _x, byte _y);
	static byte frame_cnt;
	static void start_next_frame();

	byte x;
	byte y;
	byte vx;
	byte vy;
	byte x_frame;
	byte y_frame;
	byte face_id;
	void render();
	void next_frame();
};

#endif