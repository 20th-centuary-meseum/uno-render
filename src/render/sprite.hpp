#ifndef SPRITE_H
#define SPRITE_H

#include "../../common.hpp"

class Sprite // 9 byte
{
public:
	Sprite();
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
	bool is_x_in();
	bool is_y_in();
	void next_frame();
};

#endif