#include "../../common.hpp"
#include "background.hpp"
#include "decode_img.hpp"

Background::Background(byte map_seed) : map{
											0,
										}
{
	byte map_id = map_seed % 2;
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
			set(j, i, 1, bitRead(pgm_read_byte(background_map[map_id] + i), (MAP_WIDTH - j - 1)));
		}
	}
}

void Background::set(byte X, byte Y, byte tile_id)
{
	set(X, Y, tile_id, false);
}

void Background::set(byte X, byte Y, byte tile_id, bool invinsible)
{
	// 000000MMD D: 0 = 파괴 가능, 1 = 파괴불능.
	map[Y * MAP_WIDTH + X] = tile_id << 1;
	if (invinsible)
	{
		map[Y * MAP_WIDTH + X] |= 0b00000001;
	}
}

bool Background::is_invinsible(byte x, byte y)
{
	return map[y * MAP_WIDTH + x] & 0b00000001;
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