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
byte did_crash_img(byte image_byte, short x_pos, short y_pos);

#endif
