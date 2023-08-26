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

void Character::move_up(byte px, byte frame)
{
	vx = 0;
	x_frame = 0;
	vy = px;
	y_frame = frame;
	SET_DIR_BIT(state, DIR_UP);
}
void Character::move_right(byte px, byte frame)
{
	vx = px;
	x_frame = frame;
	vy = 0;
	y_frame = 0;
	SET_DIR_BIT(state, DIR_RIGHT);
}
void Character::move_down(byte px, byte frame)
{
	vx = 0;
	x_frame = 0;
	vy = -px;
	y_frame = frame;
	SET_DIR_BIT(state, DIR_DOWN);
}
void Character::move_left(byte px, byte frame)
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
	if (vx || vy && !(frame_cnt % 15))
	{
		SET_FRAME_BIT(state, (GET_FRAME_BIT(state) + 1) & 0b00000011);
	}
}