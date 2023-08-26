#ifndef CHARACTER_H
#define CHARACTER_H

/*
		 CHR A DR FR
   state 000 0 00 00

   CHR : 캐릭터 종류
   A   : 공격 여부
   DR  : 방향
   FR  : 세부 모션 프레임
*/

#define SET_CHAR_BIT(state, char_id) state = (state & 0b00011111) | char_id << 5
#define GET_CHAR_BIT(state) state >> 5

#define SET_ATK_BIT(state, atk) state = (state & 0b11101111) | atk << 4
#define GET_ATK_BIT(state) (state & 0b00010000) >> 4

#define DIR_UP 0	// y 증가, 정면
#define DIR_RIGHT 1 // x 증가, 우측면
#define DIR_DOWN 2	// y 감소, 후면
#define DIR_LEFT 3	// x 감소, 좌측면

#define SET_DIR_BIT(state, dir) state = (state & 0b11110011) | dir << 2
#define GET_DIR_BIT(state) (state & 0b00001100) >> 2

#define FRAME_NUM 4
#define SET_FRAME_BIT(state, frame) state = (state & 0b11111100) | frame
#define GET_FRAME_BIT(state) state = (state & 0b00000011)

#include "../../common.hpp"
#include "./sprite.hpp"
#include "./decode_img.hpp"

class Character : public Sprite
{
public:
	Character(byte _character_id, short _x, short _y);
	byte state;

	void set_speed(byte px, byte frame);

	void move_up(byte px, byte frame);	  // (px per frame)
	void move_right(byte px, byte frame); // (px per frame)
	void move_down(byte px, byte frame);  // (px per frame)
	void move_left(byte px, byte frame);  // (px per frame)

	void attack();

	void render();
	void next_frame();
};

#endif