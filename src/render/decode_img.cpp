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

void DecodeSprite(byte image_byte, short x_pos, short y_pos)
{
    byte image_id = image_byte *= 2;
    byte image_rot = bitRead(image_byte, 0) + 2 * bitRead(image_byte, 0);

    byte *image_binary = *(images + image_id);

    short tmp_y = y_pos * TILE_SIZE * MAP_WIDTH / 8;
    byte shift_length = x_pos % 8;
  
  uint16_t y_minus = 0;
  uint16_t y_plus = 0;
  if (y_pos<0) y_minus = -y_pos;
  if (y_pos>MAP_HEIGHT*TILE_SIZE -1) y_plus = y_pos - (MAP_HEIGHT*TILE_SIZE -1); 


    if (x_pos < -16 || x_pos >= TILE_SIZE * MAP_WIDTH)
        return;

    if (x_pos < -8) // 2개 짤림
    {
        for (int i = 0 + y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8 + 2] |= *(image_binary + i * 2 + 1) << (8 - shift_length);
        }
    }
    else if (x_pos < 0) // 1개 짤림
    {
        for (int i = 0 + y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8 + 1] |= *(image_binary + i * 2) << (8 - shift_length) | *(image_binary + i * 2 + 1) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8 + 2] |= *(image_binary + i * 2 + 1) << (8 - shift_length);
        }
    }
    else if (x_pos + 8 >= TILE_SIZE * MAP_WIDTH) // 2개 짤림
    {
        for (int i = 0 + y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8] |= *(image_binary + i * 2) >> shift_length;
        }
    }
    else if (x_pos + 16 >= TILE_SIZE * MAP_WIDTH) // 1개 짤림
    {
        for (int i = 0 + y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8] |= *(image_binary + i * 2) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8 + 1] |= *(image_binary + i * 2) << (8 - shift_length) | *(image_binary + i * 2 + 1) >> shift_length;
        }
    }
    else // 안 짤림.
    {
        for (int i = 0 + y_minus; i < TILE_SIZE - y_plus - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8] = *(image_binary + i * 2) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8 + 1] = *(image_binary + i * 2) << (8-shift_length) + *(image_binary + i * 2 + 1) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * TILE_SIZE * MAP_WIDTH / 8 + 2] = *(image_binary + i * 2 + 1) << (8-shift_length);
        }
    }

  // byte x, y;

  // for (y = y_pos >= 0 ? 0 : -y_pos; y < TILE_SIZE && y + y_pos < TILE_SIZE * MAP_HEIGHT; y++)
  // {
  //   for (x = x_pos >= 0 ? 0 : -x_pos; x < TILE_SIZE && x + x_pos < TILE_SIZE * MAP_WIDTH; x++)
  //   {
  //     TV.set_pixel(x_pos + x, y_pos + y, (image_binary[y * 2 + x / 8]) & (1 << 7 - x % 8));
  //   }
  // }
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
