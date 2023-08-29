#include "./character.hpp"

Character::Character(byte _character_id, short _x, short _y) : Sprite(_character_id, _x, _y)
{
	state = 0;
	atk_frame_cnt = 0;
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
	x_frame = 100;
	vy = px;
	y_frame = frame;
	SET_DIR_BIT(state, DIR_UP);
}
void Character::move_right(byte px, byte frame)
{
	vx = px;
	x_frame = frame;
	vy = 0;
	y_frame = 100;
	SET_DIR_BIT(state, DIR_RIGHT);
}
void Character::move_down(byte px, byte frame)
{
	vx = 0;
	x_frame = 100;
	vy = -px;
	y_frame = frame;
	SET_DIR_BIT(state, DIR_DOWN);
}
void Character::move_left(byte px, byte frame)
{
	vx = -px;
	x_frame = frame;
	vy = 0;
	y_frame = 100;
	SET_DIR_BIT(state, DIR_LEFT);
}

bool Character::attack()
{
	if (atk_frame_cnt > 0)
	{
		return false;
	}

	SET_ATK_BIT(state, true);
	atk_frame_cnt = 30;
	return true;
}

void Character::render()
{
	DecodeSprite(state, x, y);
}

void Character::next_frame() // 블록 충돌? , 투사체 충돌?
{
	byte next_x = x + vx;
	byte next_y = y + vy;

	// ,현 xy 인덱스 + vx * q + vy * k
	if (!(TV.screen[(next_y)*MAX_X / 8 + (next_x) / 8] ||
		  TV.screen[(next_y + 15) * MAX_X / 8 + (next_x) / 8] ||
		  TV.screen[(next_y)*MAX_X / 8 + (next_x) / 8 + 1] ||
		  TV.screen[(next_y + 15) * MAX_X / 8 + (next_x + 1) / 8]))
	{
		Sprite::next_frame();
	}

	if (atk_frame_cnt > 0)
	{
		atk_frame_cnt -= 1;
	}

	if (atk_frame_cnt < 25)
	{
		SET_ATK_BIT(state, false);
	}

	// 일정 프레임마다 모션변경
	// 상태, -> 투사체 충돌 결과 필요
	Sprite::next_frame();
	if (vx || vy && !(frame_cnt % 15))
	{
		SET_FRAME_BIT(state, (GET_FRAME_BIT(state) + 1) & 0b00000011);
	}
}