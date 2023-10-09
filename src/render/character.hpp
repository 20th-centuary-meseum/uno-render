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

#define SET_DIR_BIT(state, dir) state = (state & 0b11110011) | dir << 2
#define GET_DIR_BIT(state) (state & 0b00001100) >> 2

#define FRAME_NUM 4
#define SET_FRAME_BIT(state, frame) state = (state & 0b11111100) | frame
#define GET_FRAME_BIT(state) state = (state & 0b00000011)

#define MAX_POSSESS_ITEM 2

#include "../../common.hpp"
#include "./sprite.hpp"
#include "./decode_img.hpp"
#include "../controller/controller.hpp"
#include "./items.hpp"

class Character : public Sprite // 12 byte
{
public:
	Character(byte _character_id, short _x, short _y);
	byte state;
	byte hp;
	byte atk_frame_cnt;
	byte possess_item_id;
	byte using_item_id;
	byte using_item_frame_cnt;
	byte atk_dmg;

	void set_speed(byte px, byte frame);

	void move_by_controller(byte controller);

	bool attack();

	void get_item_if_crashed(Items &items);
	void use_item();

	void render();
	void next_frame(byte *map);

	void damage(byte atk);
};

#endif