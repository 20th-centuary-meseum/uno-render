#include <TVout.h>
#include "decode_img.hpp"
#include "../../common.hpp"

TVout TV;

byte sprite[32] = {
    0b00000000,
    0b00000000,
    0b01111111,
    0b11111110,
    0b01000000,
    0b11111110,
    0b01000000,
    0b01111110,
    0b01000000,
    0b00111110,
    0b01000000,
    0b00011110,
    0b01000000,
    0b00001110,
    0b01000000,
    0b00000010,
    0b01000000,
    0b00000010,
    0b01000000,
    0b00000010,
    0b01000000,
    0b00000010,
    0b01000000,
    0b00000010,
    0b01000000,
    0b00000010,
    0b01000000,
    0b00000010,
    0b01111111,
    0b11111110,
    0b00000000,
    0b00000000,
};
byte *images[] = {sprite};

void DecodeSprite(byte image_byte, byte x_pos, byte y_pos)
{
  byte image_id = image_byte *= 2;
  byte image_rot = bitRead(image_byte, 0) + 2 * bitRead(image_byte, 0);

  byte *image_binary = *(images + image_id);

  int tmp_y = y_pos * TILE_SIZE * MAP_WIDTH / 8;

  for (int i = 0; i < TILE_SIZE; i++)
  {
    byte tmp = x_pos % 8;
    TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8] |= *(image_binary + i * 2) >> tmp;
    TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8 + 1] |= *(image_binary + i * 2) << (8 - tmp) | *(image_binary + i * 2 + 1) >> tmp;
    TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8 + 2] |= *(image_binary + i * 2 + 1) << (8 - tmp);
  }
}

void DecodeImg(byte image_byte, byte x_pos, byte y_pos)
{
  byte image_id = image_byte *= 2;
  byte image_rot = bitRead(image_byte, 0) + 2 * bitRead(image_byte, 0);

  byte *image_binary = *(images + image_id);

  int tmp_y = y_pos * TILE_SIZE * MAP_WIDTH / 8;

  for (int i = 0; i < TILE_SIZE; i++)
  {
    TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8] = *(image_binary + i * 2);
    TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8 + 1] = *(image_binary + i * 2 + 1);
  }
}
void beginTV() { TV.begin(_NTSC, 128, 96); }

void clearTV() { TV.clear_screen(); }
