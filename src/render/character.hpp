#ifndef CHARACTER_H
#define CHARACTER_H

#define DIR_UP 0	// y 증가, 정면
#define DIR_RIGHT 1 // x 증가, 우측면
#define DIR_DOWN 2	// y 감소, 후면
#define DIR_LEFT 3	// x 감소, 좌측면

#include "../../common.hpp"
#include "./sprite.hpp"
#include "./decode_img.hpp"

class Character : public Sprite
{
public:
	Character(byte _character_id, short _x, short _y);
	byte state;

	void set_speed(byte px, byte frame);
	void set_move_up(byte px, byte frame);	  // (px per frame)
	void set_move_right(byte px, byte frame); // (px per frame)
	void set_move_down(byte px, byte frame);  // (px per frame)
	void set_move_left(byte px, byte frame);  // (px per frame)
	void attack();

	void render();
	void next_frame();
};

#endif