#include "sprite.hpp"
#include "decode_img.hpp"

Sprite::Sprite(byte _face_id, byte _x, byte _y)
{
	x = _x;
	y = _y;
	face_id = _face_id;
}

void Sprite::render() { DecodeImg(face_id * 4, x, y); }