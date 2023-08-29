#include "./bullet.hpp"
#define BULLET_PX 3
#define BULLET_FRAME 1

Bullet::Bullet(byte _x, byte _y, byte dir)
{
	x = _x;
	y = _y;

	switch (dir)
	{
	case DIR_UP:
		vx = 0;
		x_frame = 100;
		vy = BULLET_PX;
		y_frame = BULLET_FRAME;
		break;
	case DIR_RIGHT:
		vx = BULLET_PX;
		x_frame = BULLET_FRAME;
		vy = 0;
		y_frame = 100;
		break;
	case DIR_DOWN:
		vx = 0;
		x_frame = 100;
		vy = -BULLET_PX;
		y_frame = BULLET_FRAME;
		break;
	case DIR_LEFT:
		vx = -BULLET_PX;
		x_frame = BULLET_FRAME;
		vy = 0;
		y_frame = 100;
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