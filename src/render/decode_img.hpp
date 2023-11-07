#ifndef DECODE_IMG_H
#define DECODE_IMG_H

#define IMG_ID_BOX 0

#include <TVout.h>
#include "../../common.hpp"

extern TVout TV;
void beginTV();
void clearTV();
void DecodeTile(byte image_byte, byte x_pos, byte y_pos);
void DecodeSprite(byte image_byte, short x_pos, short y_pos);
void DecodeSpriteReverse(byte image_byte, short x_pos, short y_pos);
void DecodeBullet(short x_pos, short y_pos);
void DecodeItem(byte image_id, byte x_pos, byte y_pos);
void DecodeSpriteItem(byte image_id, short x_pos, short y_pos);
void DecodeUI(byte p1_health, byte p2_health, byte p1_item, byte p2_item, byte p1_score, byte p2_score, short frame_left);
void DecodeFull(byte image_id);

#endif
