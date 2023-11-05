#include "./bullet.hpp"
#include "../utils/utils.hpp"

#define HITBOX_CHAR 8
#define HITBOX_BULLET 5

#define NO_BACKGROUND 255

static byte Bullet::BULLET_PX = 3;
static byte Bullet::BULLET_FRAME = 1;

Bullet::Bullet(byte _x, byte _y, byte dir)
{
	switch (dir)
	{
	case DIR_UP:
		vx = 0;
		x_frame = 100;
		vy = BULLET_PX;
		y_frame = BULLET_FRAME;
		x = _x;
		y = _y + 11;
		break;
	case DIR_RIGHT:
		vx = BULLET_PX;
		x_frame = BULLET_FRAME;
		vy = 0;
		y_frame = 100;
		x = _x + 11;
		y = _y;
		break;
	case DIR_DOWN:
		vx = 0;
		x_frame = 100;
		vy = -BULLET_PX;
		y_frame = BULLET_FRAME;
		x = _x;
		y = _y - 11;
		break;
	case DIR_LEFT:
		vx = -BULLET_PX;
		x_frame = BULLET_FRAME;
		vy = 0;
		y_frame = 100;
		x = _x - 11;
		y = _y;
		break;
	}

	face_id = 16;
	frame_left = Bullets::BULLET_FRAME_LEFT;
}

static void Bullet::activate_hyper()
{
	BULLET_PX = 5;
}
static void Bullet::deactivate_hyper()
{
	BULLET_PX = 3;
}

void Bullet::next_frame()
{
	frame_left -= 1;
	Sprite::next_frame();
}

void Bullet::render()
{
	DecodeBullet(x, y);
}

// return 값 설명
// byte 0b 0000 0000
//         x좌표 y좌표
// 어차피 MAP x, y는 최대 8, 즉 3비트.
// 그러므로 x << 4 + y해서 리턴한다.
// 만약 충돌이 없을 경우 모두 1, 즉 255를 리턴한다.

byte Bullet::did_crash_background(byte *map)
{
	byte x_center = (x + 8) / TILE_SIZE;
	byte y_center = (y + 8) / TILE_SIZE;

	// // 모서리 4개 확인.
	if (map[x_center + y_center * MAP_WIDTH])
		return (x_center << 4) + y_center;
	return NO_BACKGROUND;
}

bool Bullet::did_crash_player(Character *character)
{
	int8_t x_dist = character->x - x; // +3은 x, y좌표가 중심이 아니기 때문에
	int8_t y_dist = character->y - y; // 각각의 좌표에 반지름 8, 5를 더하고 뺀 값으로 보정해준 것임.

	return x_dist * x_dist + y_dist * y_dist < 169;
}

// -----------------------------------------------------
static byte Bullets::BULLET_FRAME_LEFT = 30;
static byte Bullets::ATTACK_DELAY = 30;

Bullets::Bullets() : bullets{
						 0,
					 }
{
	next_bullet_idx = 0;
}

static void Bullets::activate_hyper()
{
	ATTACK_DELAY = 20;
}
static void Bullets::deactivate_hyper()
{
	ATTACK_DELAY = 30;
}

void Bullets::add_bullet(byte x, byte y, byte dir)
{
	if (bullets[next_bullet_idx] != 0)
		return;

	bullets[next_bullet_idx] = new Bullet(x, y, dir);
	next_bullet_idx = next_bullet_idx >= BULLET_MAX_NUM - 1 ? 0 : next_bullet_idx + 1;
}
void Bullets::delete_bullet(byte idx)
{
	delete bullets[idx];
	bullets[idx] = nullptr;
}

void Bullets::next_frame(Character *player_vict, Character *player_owner, Items *items, Background *background)
{
	byte i;
	for (i = 0; i < BULLET_MAX_NUM; i++)
	{
		if (bullets[i] == nullptr)
			continue;

		if (bullets[i]->frame_left <= 0)
		{
			delete_bullet(i);
			continue;
		}

		if (!bullets[i]->is_x_in() || !bullets[i]->is_y_in())
		{
			delete_bullet(i);
			continue;
		}

		if (bullets[i]->did_crash_player(player_vict))
		{
			player_vict->damage(player_owner->atk_dmg);
			bullets[i]->frame_cnt = 100;
			delete_bullet(i);
			continue;
		}

		byte map_crash_xy = bullets[i]->did_crash_background(background->map);
		if (map_crash_xy != NO_BACKGROUND)
		{
			byte tile_x = map_crash_xy >> 4;
			byte tile_y = map_crash_xy & 0b00001111;
			if (!background->is_invinsible(tile_x, tile_y))
			{
				background->set(tile_x, tile_y, 0);
				items->add_item(tile_x, tile_y);
			}
			delete_bullet(i);
			continue;
		}

		bullets[i]->next_frame();
	}
}

void Bullets::render()
{
	byte i;
	for (i = 0; i < BULLET_MAX_NUM; i++)
	{
		if (bullets[i])
		{
			bullets[i]->render();
		}
	}
}