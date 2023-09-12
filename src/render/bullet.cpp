#include "./bullet.hpp"
#include "../utils/utils.hpp"

#define HITBOX_CHAR 8
#define HITBOX_BULLET 5

#define BULLET_PX 3
#define BULLET_FRAME 1

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
	frame_left = BULLET_FRAME_LEFT;
}

void Bullet::next_frame()
{
	frame_left -= 1;
	Sprite::next_frame();
}

bool Bullet::did_crash_background(byte *map)
{
	byte x_start = x + 5;
	byte y_start = y + 5;

	if (vy > 0)
	{
		return map[(y + vy + 15) / TILE_SIZE * MAP_WIDTH + x / TILE_SIZE] | map[(y + vy + 15) / TILE_SIZE * MAP_WIDTH + (x + 15) / TILE_SIZE];
	}
	else if (vx > 0)
	{
		return map[y / TILE_SIZE * MAP_WIDTH + (x + vx + 15) / TILE_SIZE] | map[(y + 15) / TILE_SIZE * MAP_WIDTH + (x + vx + 15) / TILE_SIZE];
	}
	else if (vy < 0)
	{
		return map[(y + vy) / TILE_SIZE * MAP_WIDTH + x / TILE_SIZE] | map[(y + vy) / TILE_SIZE * MAP_WIDTH + (x + 15) / TILE_SIZE];
	}
	else if (vx < 0)
	{
		return map[y / TILE_SIZE * MAP_WIDTH + (x + vx) / TILE_SIZE] | map[(y + 15) / TILE_SIZE * MAP_WIDTH + (x + vx) / TILE_SIZE];
	}
}

bool Bullet::did_crash_player(Character *character)
{
	byte x_dist = character->x - x;
	byte y_dist = character->y - y;

	return POW(x_dist) + POW(y_dist) < POW(HITBOX_BULLET + HITBOX_CHAR);
}

// -----------------------------------------------------
Bullets::Bullets() : bullets{
						 0,
					 }
{
	next_bullet_idx = 0;
}

void Bullets::add_bullet(byte x, byte y, byte dir)
{
	if (bullets[next_bullet_idx] != 0)
		return;

	bullets[next_bullet_idx] = new Bullet(x, y, dir);
	next_bullet_idx = next_bullet_idx >= BULLET_MAX_NUM - 1 ? 0 : next_bullet_idx + 1;
}

void Bullets::next_frame()
{
	byte i;
	for (i = 0; i < BULLET_MAX_NUM; i++)
	{
		if (bullets[i])
		{
			bullets[i]->next_frame();
			if (bullets[i]->frame_left <= 0)
			{
				delete bullets[i];
				bullets[i] = 0;
			}
			else if (!bullets[i]->is_x_in() || !bullets[i]->is_y_in())
			{
				bullets[i]->frame_left = 0;
			}
		}
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