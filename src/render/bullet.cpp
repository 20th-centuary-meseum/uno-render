#include "./bullet.hpp"
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

bool Bullet::did_crash()
{
	return (
		TV.get_pixel(x + 7, y + 5) ||
		TV.get_pixel(x + 6, y + 6) ||
		TV.get_pixel(x + 5, y + 7) ||

		TV.get_pixel(x + 5, y + 8) ||
		TV.get_pixel(x + 6, y + 9) ||
		TV.get_pixel(x + 7, y + 10) ||

		TV.get_pixel(x + 8, y + 10) ||
		TV.get_pixel(x + 9, y + 9) ||
		TV.get_pixel(x + 10, y + 8) ||

		TV.get_pixel(x + 10, y + 7) ||
		TV.get_pixel(x + 9, y + 6) ||
		TV.get_pixel(x + 8, y + 5));
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
			if (bullets[i]->frame_left == 0)
			{
				delete bullets[i];
				bullets[i] = 0;
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