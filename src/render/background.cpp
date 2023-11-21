#include "../../common.hpp"
#include "background.hpp"
#include "decode_img.hpp"
#include "../utils/utils.hpp"

Background::Background() : map{
											0,
										}
{
	while (true) 
	{
		byte tile_id = 1;
		generate_map(tile_id);
		delay(300);
		render();
		byte check[MAP_WIDTH * MAP_HEIGHT] = {0, };
		if (cnt_open_paths(0, 1, check)) {
			for (byte i = 1; i < MAP_HEIGHT; i++)
			{
				for (byte j = 0; j < MAP_WIDTH; j++)
				{
					if ((i == 1 && j == 0) || (i == MAP_HEIGHT - 1) && (j == MAP_WIDTH - 1))
					{
						continue;
					}
					if (get(j, i) == 0) set(j, i, tile_id, 0);
				}
			}
			break;
		}
		for (byte i = 0; i < MAP_HEIGHT; i++)
		{
			for (byte j = 0; j < MAP_WIDTH; j++)
			{
				set(j, i, 0, 0);
			}
		}
	}
}

byte Background::cnt_open_paths(byte x, byte y, byte* check)
{
	if (check[y * MAP_WIDTH + x]) return 0;
	if (get(x, y)) return 0;
	if (x < 0 || x >= MAP_WIDTH || y < 1 || y >= MAP_HEIGHT) return 0;
	if (x == MAP_WIDTH - 1 && y == MAP_HEIGHT - 1) return 1;

	check[y * MAP_WIDTH + x] = 1;

	return cnt_open_paths(x + 1, y, check) + 
	cnt_open_paths(x - 1, y, check) + 
	cnt_open_paths(x, y + 1, check) + 
	cnt_open_paths(x, y - 1, check);
}

byte Background::generate_map(byte tild_id)
{
	byte cnt = 0;
	while (cnt <= 7) {
		Rand::refresh();
		Rand::get();
		byte map_seed = Rand::get();
		for (byte i = 1; i < MAP_HEIGHT; i++)
		{
			for (byte j = 0; j < MAP_WIDTH / 2; j++)
			{
				if (i == 1 && j == 0)
				{
					continue;
				}
				if (bitRead(map_seed, i) && bitRead(map_seed, j)) 
				{
					cnt += generate_obstacle(j, i, map_seed, tild_id, 0);
					if (cnt > 7) break;
				}
			}
			if (cnt > 7) break;
		}
	}

	for (byte i = 1; i < MAP_HEIGHT; i++)
	{
		for (byte j = 0; j < MAP_WIDTH / 2; j++)
		{
			map[(MAP_HEIGHT - i) * MAP_WIDTH + (MAP_WIDTH - j - 1)] = get(j, i);
		}
	}
}

byte Background::generate_obstacle(byte x, byte y, byte seed, byte tile_id, byte step)
{
	if (x < 0 || x >= MAP_WIDTH / 2 || y < 1 || y >= MAP_HEIGHT) return;
	if ((x == 0 && y == 0) || step >= 1) return;

	if (bitRead(seed, x+4) || bitRead(seed, y+4) || step == 0) {
		if (get(x, y)) {
			return 0;
		}

		set(x, y, (seed % 3 + 1), true);

		return 1 +
			generate_obstacle(x + 1, y, seed, tile_id, step + 1) +
			generate_obstacle(x, y + 1, seed, tile_id, step + 1) +
			generate_obstacle(x - 1, y, seed, tile_id, step + 1) +
			generate_obstacle(x, y - 1, seed, tile_id, step + 1);
	}
}

byte Background::get(byte x, byte y)
{
	return map[y * MAP_WIDTH + x];
}

void Background::set(byte x, byte y, byte tile_id)
{
	set(x, y, tile_id, false);
}

void Background::set(byte x, byte y, byte tile_id, bool invinsible)
{
	// 000000MMD D: 0 = 파괴 가능, 1 = 파괴불능.
	map[y * MAP_WIDTH + x] = tile_id << 1;
	if (invinsible)
	{
		map[y * MAP_WIDTH + x] |= 0b00000001;
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