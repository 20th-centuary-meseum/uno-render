#ifndef BULLET_H
#define BULLET_H

#include "./decode_img.hpp"
#include "./sprite.hpp"
#include "./character.hpp"
#include "./background.hpp"
#include "./items.hpp"
#include "../../common.hpp"

#define BULLET_MAX_NUM 3

class Bullet : public Sprite // 10 byte
{
	static byte BULLET_PX;
	static byte BULLET_FRAME;

public:
	Bullet(byte _x, byte _y, byte dir);
	static void activate_hyper();
	static void deactivate_hyper();

	byte frame_left;
	void next_frame();
	byte did_crash_background(byte *map);
	bool did_crash_player(Character *character);
	void render();
};

class Bullets // 9 byte
{
public:
	static byte BULLET_FRAME_LEFT;
	static byte ATTACK_DELAY;

	byte next_bullet_idx;
	Bullets();
	static void activate_hyper();
	static void deactivate_hyper();

	Bullet *bullets[BULLET_MAX_NUM];
	void add_bullet(byte x, byte y, byte dir);
	void delete_bullet(byte idx);
	void next_frame(Character *player_vict, Character *player_owner, Items *items, Background *background);
	void render();
};

#endif