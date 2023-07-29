#ifndef APP_H
#define APP_H

#include "common.hpp"

// uint16_t palette[2];
// byte sprite[78];
// byte images_size;
// byte *images[1];
// int deb_lines;
// int deb_y;

void start_app();
void DecodeImg(byte image_byte, byte x_pos, byte y_pos);
byte ReadBits(byte x, byte low_range, byte high_range);
int pow2(int i);

class Background
{
public:
	byte map[MAP_WIDTH * MAP_HEIGHT];
	Background();
	void set(byte X, byte Y, byte tile_id, byte tile_rot); // fin!!
	void render();
};

class Sprite
{
public:
	Sprite(byte X, byte Y);
	byte x;
	byte y;
	byte face_id;
	void render();
};

#endif