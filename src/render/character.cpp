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

#include "./character.hpp"

Character::Character(byte _character_id, short _x, short _y) : Sprite(_character_id, _x, _y)
{
	state = 0;
	SET_CHAR_BIT(state, _character_id);
}

void Character::set_speed(byte px, byte frame)
{
	if (vx != 0)
	{
		vx = vx > 0 ? px : -px;
		x_frame = frame;
	}
	else if (vy != 0)
	{
		vy = vy > 0 ? px : -px;
		y_frame = frame;
	}
}

void Character::set_move_up(byte px, byte frame)
{
	vx = 0;
	x_frame = 0;
	vy = px;
	y_frame = frame;
	SET_DIR_BIT(state, DIR_UP);
}
void Character::set_move_right(byte px, byte frame)
{
	vx = px;
	x_frame = frame;
	vy = 0;
	y_frame = 0;
	SET_DIR_BIT(state, DIR_DOWN);
}
void Character::set_move_down(byte px, byte frame)
{
	vx = 0;
	x_frame = 0;
	vy = -px;
	y_frame = frame;
	SET_DIR_BIT(state, DIR_RIGHT);
}
void Character::set_move_left(byte px, byte frame)
{
	vx = -px;
	x_frame = frame;
	vy = 0;
	y_frame = 0;
	SET_DIR_BIT(state, DIR_LEFT);
}

void Character::attack()
{
	SET_ATK_BIT(state, true);
}

void Character::render()
{
	DecodeSprite(state, x, y);
}

void Character::next_frame()
{
	Sprite::next_frame();
	SET_FRAME_BIT(state, (Sprite::frame_cnt & 0b00000011));
}