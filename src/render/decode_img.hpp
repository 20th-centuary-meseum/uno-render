#ifndef DECODE_IMG_H
#define DECODE_IMG_H

#define IMG_ID_BOX 0

#include "../../common.hpp"

void beginTV();
void clearTV();
void DecodeImg(byte image_byte, byte x_pos, byte y_pos);

#endif
