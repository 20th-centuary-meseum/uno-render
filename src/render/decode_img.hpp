#ifndef DECODE_IMG_H
#define DECODE_IMG_H

#include "../../common.hpp"

void beginTV();
void clearTV();
void DecodeImg(byte image_byte, byte x_pos, byte y_pos);
byte ReadBits(byte x, byte low_range, byte high_range);
int pow2(int i);

#endif