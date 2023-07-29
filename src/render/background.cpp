#include "../../common.hpp"
#include "background.hpp"
#include "decode_img.hpp"

Background::Background() : map{
							   0,
						   }
{
}

void Background::set(byte X, byte Y, byte tile_id, byte tile_rot)
{
	// make tile byte with id and tile_rot
	byte tile_byte;
	tile_byte = tile_id << 2;
	tile_byte += tile_rot;
	//
	map[Y * MAP_HEIGHT + X] = tile_byte;
}

void Background::render()
{
	for (byte x = 0; x < MAP_WIDTH; x++)
	{
		for (byte y = 0; y < MAP_HEIGHT; y++)
		{
			DecodeImg(map[y * MAP_WIDTH + x], x * 16, y * 16);
		}
	}
}