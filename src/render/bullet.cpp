#include "./bullet.hpp"

Bullet::Bullet(byte _x, byte _y, byte dir)
{
	x = _x;
	y = _y;

	switch (dir)
	{
	case DIR_UP:
		vx = 0;
		x_frame = 100;
		vy = 3;
		y_frame = 1;
		break;
	case DIR_RIGHT:
		vx = 3;
		x_frame = 1;
		vy = 0;
		y_frame = 100;
		break;
	case DIR_DOWN:
		vx = 0;
		x_frame = 100;
		vy = -3;
		y_frame = 1;
		break;
	case DIR_LEFT:
		vx = -3;
		x_frame = 1;
		vy = 0;
		y_frame = 100;
		break;
	}

	face_id = 16;
	frame_left = 120;
}

void Bullet::next_frame()
{
	frame_left -= 1;
	Sprite::next_frame();
}