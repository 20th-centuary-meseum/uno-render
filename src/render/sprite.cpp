#include "sprite.hpp"
#include "decode_img.hpp"

Sprite::Sprite(byte X, byte Y)
{
	x = X;
	y = Y;
}

void Sprite::render() { DecodeImg(face_id * 4, x, y); }