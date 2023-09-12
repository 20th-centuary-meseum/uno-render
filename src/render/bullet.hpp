#ifndef BULLET_H
#define BULLET_H

#include "./decode_img.hpp"
#include "./sprite.hpp"
#include "./character.hpp"
#include "./background.hpp"
#include "./items.hpp"
#include "../../common.hpp"

class Bullet : public Sprite // 10 byte
{
public:
	Bullet(byte _x, byte _y, byte dir);
	byte frame_left;
	void next_frame();
	bool did_crash_background(byte *map);
	bool did_crash_player(Character *character);
};

class Bullets // 9 byte
{
public:
	byte next_bullet_idx;
	Bullets();
	Bullet *bullets[BULLET_MAX_NUM];
	void add_bullet(byte x, byte y, byte dir);
	void delete_bullet(byte idx);
	void next_frame(Character *player, Items *items, Background *background);
	void render();
};

#endif