#include "./character.hpp"

#define CHARACTER_PX 2
#define CHARACTER_FRAME 1
#define CHARACTER_MAX_HP 10

Character::Character(byte _character_id, short _x, short _y) : Sprite(_character_id, _x, _y)
{
	state = 0;
	atk_frame_cnt = 0;
	SET_CHAR_BIT(state, _character_id);
	hp = CHARACTER_MAX_HP - 5; // 음수, 최대 체력 이상 예외처리 필수!
	possess_item_id = 0;
	using_item_id = 0;
	using_item_frame_cnt = 0; // frame update, 모션 타이머 조작할 때 같이 줄이자!
	atk_dmg = 1;
}

Character *test()
{
	return new Character(0, 0, 0);
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

void Character::move_by_controller(byte controller)
{
	if (CON_U(controller))
	{
		vx = 0;
		x_frame = 100;
		vy = CHARACTER_PX;
		y_frame = CHARACTER_FRAME;
		SET_DIR_BIT(state, DIR_UP);
	}
	else if (CON_R(controller))
	{
		vx = CHARACTER_PX;
		x_frame = CHARACTER_FRAME;
		vy = 0;
		y_frame = 100;
		SET_DIR_BIT(state, DIR_RIGHT);
	}
	else if (CON_D(controller))
	{
		vx = 0;
		x_frame = 100;
		vy = -CHARACTER_PX;
		y_frame = CHARACTER_FRAME;
		SET_DIR_BIT(state, DIR_DOWN);
	}
	else if (CON_L(controller))
	{
		vx = -CHARACTER_PX;
		x_frame = CHARACTER_FRAME;
		vy = 0;
		y_frame = 100;
		SET_DIR_BIT(state, DIR_LEFT);
	}
	else
	{
		vx = 0;
		x_frame = 100;
		vy = 0;
		y_frame = 100;
	}
}

bool Character::attack()
{
	if (atk_frame_cnt > 0)
	{
		return false;
	}

	SET_ATK_BIT(state, true);
	atk_frame_cnt = ATTACK_DELAY;
	return true;
}

void Character::get_item_if_crashed(Items &items)
{
	if (possess_item_id != 0)
		return;

	for (byte i = 0; i < MAX_POSSESS_ITEM; i++)
	{
		if (abs(items[i]->x - x) < 8 && abs(items[i]->y - y) < 8)
		{
			possess_item_id = items[i]->face_id;
			items.delete_item(i);
		}
	}
}

void Character::use_item()
{
	if (using_item_id)
		return;

	switch (possess_item_id)
	{
	case ITEM_HEAL:
		using_item_frame_cnt = 60;
		hp += 2;
		if (hp > 10)
			hp = 10;
		break;
	case ITEM_SHLD:

		break;
	case ITEM_DASH:

		break;
	case ITEM_SPED:
		using_item_frame_cnt = 120;
		// 재광이형
		break;
	case ITEM_DAMG:
		using_item_frame_cnt = 120;
		atk_dmg = 2;
		break;

	default:
		break;
	}
	using_item_id = possess_item_id;
	possess_item_id = 0;
}

void Character::render()
{
	DecodeSprite(state, x, y);
	if (using_item_id)
	{
		DecodeSpriteItem(using_item_id, x, y - 12);
	}
}

void Character::next_frame(byte *map) // 블록 충돌? , 투사체 충돌?
{
	bool did_crash = false;
	if (using_item_id == ITEM_SPED)
	{
		vx *= 2;
		vy *= 2;
	}

	switch (GET_DIR_BIT(state))
	{
	case DIR_UP:
		did_crash = map[(y + vy + 15) / TILE_SIZE * MAP_WIDTH + x / TILE_SIZE] | map[(y + vy + 15) / TILE_SIZE * MAP_WIDTH + (x + 15) / TILE_SIZE];
		break;
	case DIR_RIGHT:
		did_crash = map[y / TILE_SIZE * MAP_WIDTH + (x + vx + 15) / TILE_SIZE] | map[(y + 15) / TILE_SIZE * MAP_WIDTH + (x + vx + 15) / TILE_SIZE];
		break;
	case DIR_DOWN:
		did_crash = map[(y + vy) / TILE_SIZE * MAP_WIDTH + x / TILE_SIZE] | map[(y + vy) / TILE_SIZE * MAP_WIDTH + (x + 15) / TILE_SIZE];
		break;
	case DIR_LEFT:
		did_crash = map[y / TILE_SIZE * MAP_WIDTH + (x + vx) / TILE_SIZE] | map[(y + 15) / TILE_SIZE * MAP_WIDTH + (x + vx) / TILE_SIZE];
		break;
	}
	if (!did_crash)
	{
		Sprite::next_frame();
	}

	if (atk_frame_cnt > 0)
	{
		atk_frame_cnt -= 1;
	}

	if (atk_frame_cnt < ATTACK_DELAY - 5)
	{
		SET_ATK_BIT(state, false);
	}

	// 일정 프레임마다 모션변경
	// 상태, -> 투사체 충돌 결과 필요
	if (vx || vy)
	{
		if (!(frame_cnt % 6))
			SET_FRAME_BIT(state, (GET_FRAME_BIT(state) + 1) & 0b00000011);
	}
	else
	{
		SET_FRAME_BIT(state, 0);
	}

	if (using_item_id)
	{
		using_item_frame_cnt -= 1;
		if (using_item_frame_cnt == 0)
		{
			using_item_id = 0;
			atk_dmg = 1;
		}
	}
}

void Character::damage(byte atk)
{
	hp -= atk;
	if (hp < 0)
		hp = 0;
	return;
}