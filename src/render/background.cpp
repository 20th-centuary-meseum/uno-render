#include "../../common.hpp"
#include "background.hpp"
#include "decode_img.hpp"

Background::Background() : map{
							   0,
						   }
{
}

void Background::set(byte X, byte Y, byte tile_id)
{
	set(X, Y, tile_id, false);
}

void Background::set(byte X, byte Y, byte tile_id, bool invinsible)
{
	// 000000MMD D: 0 = 파괴 가능, 1 = 파괴불능.
	map[Y * MAP_WIDTH + X] = tile_id << 1 + invinsible;
}

void Background::generate_map()
{
	for (byte i = 1; i < MAP_HEIGHT; i++)
	{
		for (byte j = 0; j < MAP_WIDTH; j++)
		{
			if (i == 1 && j == 0)
			{
				continue;
			}
			if (i == MAP_HEIGHT - 1 && j == MAP_WIDTH - 1)
			{
				continue;
			}
			set(j, i, 1, bitRead(background_map[0][i], j));
		}
	}
}

void Background::render()
{
	for (byte x = 0; x < MAP_WIDTH; x++)
	{
		for (byte y = 0; y < MAP_HEIGHT; y++)
		{
			DecodeTile(map[y * MAP_WIDTH + x], x * 16, y * 16);
		}
	}
}