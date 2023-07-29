#include <TVout.h>
#include "app.hpp"
#include "common.hpp"

TVout TV;

uint16_t palette[2] = {0x0000, 0x0001};
//                    {Black , White }

byte sprite[] = {0x00,					 // L1 0~255 8비트, 16x16 이미지
				 0x00,					 // L2
				 0x17, 0x14,			 // 3째줄 0 0 0 0 0 0 0 1 1 1 1
				 0x37, 0x11, 0x02, 0x11, // 4째줄 0 0 0 0 0 0 0 1 ! ! 1
				 0x17, 0x14,
				 0x34, 0x14, 0x02, 0x14,
				 0x34, 0x11, 0x08, 0x11,
				 0x34, 0x11, 0x08, 0x11, // L8
				 0x74, 0x11, 0x01, 0x12, 0x02, 0x12, 0x01, 0x11,
				 0x74, 0x11, 0x01, 0x11, 0x01, 0x12, 0x01, 0x15, // L10
				 0x94, 0x11, 0x01, 0x11, 0x01, 0x12, 0x01, 0x11, 0x03, 0x11,
				 0x53, 0x13, 0x05, 0x11, 0x03, 0x11,
				 0x73, 0x11, 0x01, 0x11, 0x05, 0x11, 0x03, 0x11,
				 0x53, 0x13, 0x05, 0x11, 0x03, 0x11,
				 0x54, 0x11, 0x02, 0x16, 0x01, 0x12,
				 0x34, 0x14, 0x02, 0x15};

byte images_size = 1;
byte *images[] = {sprite};
byte images_sizes[] = {78};

int deb_lines = 0;
int deb_y = 0;

void DecodeImg(byte image_byte, byte x_pos, byte y_pos)
{
	byte image_id = image_byte *= 2;
	byte image_rot = bitRead(image_byte, 0) + 2 * bitRead(image_byte, 0);

	byte cnt = 0;
	byte num_lines;
	byte start_pos;
	byte tmp_x = 0;
	byte tmp_y = 0;

	byte i = 0;

	byte *image = images[image_id];
	byte image_size = images_sizes[image_id];

	while (cnt != image_size)
	{
		num_lines = ReadBits(*(image + cnt), 4, 7); // 7 6 5 4 3 2 1 0
		start_pos = ReadBits(*(image + cnt), 0, 3);
		cnt += 1;

		for (int i = 0; i < num_lines; i++)
		{
			TV.draw_row(
				y_pos + tmp_y,												// y_start
				start_pos + x_pos + tmp_x,									// x_start
				start_pos + x_pos + tmp_x + ReadBits(*(image + cnt), 0, 3), // x_end <-- x_start + length
				*(palette + ReadBits(*(image + cnt), 4, 7))					// color
			);

			tmp_x += ReadBits(*(image + cnt), 0, 3);
			cnt += 1;
		}
		tmp_x = 0;
		tmp_y += 1;
	}
}

byte ReadBits(byte x, byte low_range, byte high_range)
{
	byte result;
	for (int i = 0; i <= high_range - low_range; i++)
	{
		result += bitRead(x, low_range + i) * pow2(i); // bitRead is Arduino only
	}
	return result;
}

int pow2(int i)
{
	int result = 1;

	for (int j = 0; j < i; j++)
		result *= 2;

	return result;
}

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

Sprite::Sprite(byte X, byte Y)
{
	x = X;
	y = Y;
}

void Sprite::render() { DecodeImg(face_id * 4, x, y); }

////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////
void start_app()
{
	TV.begin(_NTSC, 128, 96);
	TV.clear_screen();
	Sprite knight(30, 40);

	Background background;
	background.set(2, 2, 0, 0);
	background.render();
	knight.render();
}