#ifndef DECODE_IMG_H
#define DECODE_IMG_H

#define IMG_ID_BOX 0

#include <TVout.h>
#include "../../common.hpp"

extern TVout TV;
void beginTV();
void clearTV();
void DecodeImg(byte image_byte, byte x_pos, byte y_pos);
void DecodeSprite(byte image_byte, short x_pos, short y_pos);
void DecodeItem(byte image_byte, byte x_pos, byte y_pos);
void DecodeUI(byte p1_health, byte p2_health, byte p1_item, byte p2_item);
byte did_crash_img(byte image_byte, short x_pos, short y_pos);
bool did_crash_character(byte character_x, byte character_y, byte bullet_x, byte bullet_y);

#endif
