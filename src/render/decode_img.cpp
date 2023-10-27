// #define IMG const byte PROGMEM

#include "decode_img.hpp"
#include "../assets/assets.hpp"

#define HITBOX_CHAR 8
#define HITBOX_BULLET 5

TVout TV;

void DecodeSprite(byte image_byte, short x_pos, short y_pos)
{
    if (x_pos < -15 || x_pos >= TILE_SIZE * MAP_WIDTH)
        return;
    if (y_pos < -15 || y_pos >= TILE_SIZE * MAP_HEIGHT)
        return;

    byte image_id = image_byte;

    // byte *sprite_imgs[image_id] = *(sprite_imgs + image_id);

    short tmp_y = y_pos * MAX_X / 8;
    byte shift_length = x_pos % 8;
    uint16_t y_minus = 0;
    uint16_t y_plus = 0;

    if (y_pos < 0)
        y_minus = -y_pos;
    if (y_pos > MAX_Y - 1)
        y_plus = y_pos - (MAX_Y - 1);

    if (x_pos < -8) // 2개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + i * MAX_X / 8] |= pgm_read_byte(&sprite_imgs[image_id][i * 2 + 1]) << -8 - x_pos;
        }
    }
    else if (x_pos < 0) // 1개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + i * MAX_X / 8] |= pgm_read_byte(&sprite_imgs[image_id][i * 2]) << -x_pos | pgm_read_byte(&sprite_imgs[image_id][i * 2 + 1]) >> (8 + x_pos);
            TV.screen[tmp_y + i * MAX_X / 8 + 1] |= pgm_read_byte(&sprite_imgs[image_id][i * 2 + 1]) << -x_pos;
        }
    }
    else if (x_pos + 8 >= MAX_X) // 2개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(&sprite_imgs[image_id][i * 2]) >> shift_length;
        }
    }
    else if (x_pos + 16 >= MAX_X) // 1개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(&sprite_imgs[image_id][i * 2]) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] |= pgm_read_byte(&sprite_imgs[image_id][i * 2]) << (8 - shift_length) | pgm_read_byte(&sprite_imgs[image_id][i * 2 + 1]) >> shift_length;
        }
    }
    else // 안 짤림.
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(&sprite_imgs[image_id][i * 2]) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] |= pgm_read_byte(&sprite_imgs[image_id][i * 2]) << (8 - shift_length) | pgm_read_byte(&sprite_imgs[image_id][i * 2 + 1]) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 2] |= pgm_read_byte(&sprite_imgs[image_id][i * 2 + 1]) << (8 - shift_length);
        }
    }
}
void DecodeBullet(short x_pos, short y_pos)
{
    if (x_pos < -15 || x_pos >= TILE_SIZE * MAP_WIDTH)
        return;
    if (y_pos < -15 || y_pos >= TILE_SIZE * MAP_HEIGHT)
        return;

    short tmp_y = y_pos * MAX_X / 8;
    byte shift_length = x_pos % 8;
    uint16_t y_minus = 0;
    uint16_t y_plus = 0;

    if (y_pos < 0)
        y_minus = -y_pos;
    if (y_pos > MAX_Y - 1)
        y_plus = y_pos - (MAX_Y - 1);

    if (x_pos < -8) // 2개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + i * MAX_X / 8] |= pgm_read_byte(&bullet_img[i * 2 + 1]) << -8 - x_pos;
        }
    }
    else if (x_pos < 0) // 1개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + i * MAX_X / 8] |= pgm_read_byte(&bullet_img[i * 2]) << -x_pos | pgm_read_byte(&bullet_img[i * 2 + 1]) >> (8 + x_pos);
            TV.screen[tmp_y + i * MAX_X / 8 + 1] |= pgm_read_byte(&bullet_img[i * 2 + 1]) << -x_pos;
        }
    }
    else if (x_pos + 8 >= MAX_X) // 2개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(&bullet_img[i * 2]) >> shift_length;
        }
    }
    else if (x_pos + 16 >= MAX_X) // 1개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(&bullet_img[i * 2]) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] |= pgm_read_byte(&bullet_img[i * 2]) << (8 - shift_length) | pgm_read_byte(&bullet_img[i * 2 + 1]) >> shift_length;
        }
    }
    else // 안 짤림.
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(&bullet_img[i * 2]) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] |= pgm_read_byte(&bullet_img[i * 2]) << (8 - shift_length) | pgm_read_byte(&bullet_img[i * 2 + 1]) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 2] |= pgm_read_byte(&bullet_img[i * 2 + 1]) << (8 - shift_length);
        }
    }
}

void DecodeTile(byte image_byte, byte x_pos, byte y_pos)
{
    byte image_id = image_byte >> 2;
    byte image_rot = bitRead(image_byte, 0) + 2 * bitRead(image_byte, 0);

    byte *image_address = *(tile_imgs + image_id);

    int tmp_y = y_pos * MAX_X / 8;

    for (int i = 0; i < TILE_SIZE; i++)
    {
        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] = pgm_read_byte(image_address + i * 2);
        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] = pgm_read_byte(image_address + i * 2 + 1);
    }
}

void DecodeItem(byte image_id, byte x_pos, byte y_pos)
{
    byte *image_address = *(item_imgs + image_id - 1);

    int tmp_y = y_pos * MAX_X / 8;

    for (int i = 0; i < TILE_SIZE; i++)
    {
        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(image_address + i * 2);
        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] |= pgm_read_byte(image_address + i * 2 + 1);
    }
}

void DecodeSpriteItem(byte image_id, short x_pos, short y_pos)
{
    // ----------------------------------------------------------------------- 시간 부족하면 지워도 괜찮다.
    if (x_pos < -15 || x_pos >= TILE_SIZE * MAP_WIDTH)
        return;
    if (y_pos < -15 || y_pos >= TILE_SIZE * MAP_HEIGHT) // 이슈 생기면 ㄴ
        return;

    // byte *sprite_imgs[image_id] = *(sprite_imgs + image_id);

    short tmp_y = y_pos * MAX_X / 8;
    byte shift_length = x_pos % 8;
    uint16_t y_minus = 0;
    uint16_t y_plus = 0;

    if (y_pos < 16)
        y_minus = -(y_pos - 16);
    if (y_pos > MAX_Y - 1)
        y_plus = y_pos - (MAX_Y - 1);

    if (x_pos < -8) // 2개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + i * MAX_X / 8] |= pgm_read_byte(&item_imgs[image_id - 1][i * 2 + 1]) << -8 - x_pos;
        }
    }
    else if (x_pos < 0) // 1개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + i * MAX_X / 8] |= pgm_read_byte(&item_imgs[image_id - 1][i * 2]) << -x_pos | pgm_read_byte(&item_imgs[image_id - 1][i * 2 + 1]) >> (8 + x_pos);
            TV.screen[tmp_y + i * MAX_X / 8 + 1] |= pgm_read_byte(&item_imgs[image_id - 1][i * 2 + 1]) << -x_pos;
        }
    }
    else if (x_pos + 8 >= MAX_X) // 2개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(&item_imgs[image_id - 1][i * 2]) >> shift_length;
        }
    }
    else if (x_pos + 16 >= MAX_X) // 1개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(&item_imgs[image_id - 1][i * 2]) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] |= pgm_read_byte(&item_imgs[image_id - 1][i * 2]) << (8 - shift_length) | pgm_read_byte(&item_imgs[image_id - 1][i * 2 + 1]) >> shift_length;
        }
    }
    else // 안 짤림.
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(&item_imgs[image_id - 1][i * 2]) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] |= pgm_read_byte(&item_imgs[image_id - 1][i * 2]) << (8 - shift_length) | pgm_read_byte(&item_imgs[image_id - 1][i * 2 + 1]) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 2] |= pgm_read_byte(&item_imgs[image_id - 1][i * 2 + 1]) << (8 - shift_length);
        }
    }
}

void decode_mini_img(byte x, byte y, byte *mini_img) // 8x8 이미지 렌더
{
    for (int i = 0; i < 8; i++)
    {
        TV.screen[x + (i + y * 8) * MAX_X / 8] = pgm_read_byte(mini_img + i);
    }
}

void DecodeUI(byte p1_health, byte p2_health, byte p1_item, byte p2_item)
{
    byte *heart_full_img = ui_imgs[HEART_FULL];
    byte *heart_half_img = ui_imgs[HEART_HALF];

    // health render
    for (byte x = 0; x < p1_health / 2; x++)
    {
        decode_mini_img(x, 0, heart_full_img);
    }

    if (p1_health % 2)
    {
        decode_mini_img(p1_health / 2, 0, heart_half_img);
    }

    for (byte x = 15; x > 15 - p2_health / 2; x--)
    {
        decode_mini_img(x, 0, heart_full_img);
    }

    if (p2_health % 2)
    {
        decode_mini_img(15 - p2_health / 2, 0, heart_half_img);
    }

    if (p1_item)
        DecodeItem(p1_item, 40, 0);
    if (p2_item)
        DecodeItem(p2_item, 72, 0);
}

void DecodeFull(byte image_id)
{
    for (short i = 0; i < 1536; i++)
    {
        TV.screen[i] = pgm_read_byte(&full_imgs[image_id][i]);
    }
}

void beginTV()
{
    TV.begin(_NTSC, 128, 96);
}

void clearTV()
{
    TV.clear_screen();
}