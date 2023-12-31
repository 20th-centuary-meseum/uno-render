// #define IMG const byte PROGMEM

#include "decode_img.hpp"
#include "../assets/assets.hpp"

#define HITBOX_CHAR 8
#define HITBOX_BULLET 5
#define SET_BIT_ZERO(bit, len) ((bit) >> (len) << (len))

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
    
    for (int i = 0; i < TILE_SIZE; i++)
    {
        byte buffer = TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] & ( 0b11111111 << (8 - shift_length));

        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] = buffer | (pgm_read_byte(&sprite_imgs[image_id][i * 2]) >> (shift_length));
        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] = pgm_read_byte(&sprite_imgs[image_id][i * 2]) << (8 - shift_length) | pgm_read_byte(&sprite_imgs[image_id][i * 2 + 1]) >> shift_length;

        buffer = TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 2] & (0b11111111 >> shift_length);
        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 2] = buffer | (pgm_read_byte(&sprite_imgs[image_id][i * 2 + 1]) << (8 - shift_length));
    }
}

void DecodeSpriteReverse(byte image_byte, short x_pos, short y_pos)
{
    short tmp_y = y_pos * MAX_X / 8;
    byte shift_length = x_pos % 8;

    for (byte i = 0; i < TILE_SIZE; i++)
    {
        byte buffer = TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] & ( 0b11111111 << (8 - shift_length));

        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] = buffer | ((~pgm_read_byte(&sprite_imgs[image_byte][i * 2]) & 0b11111111) >> shift_length);
        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] = (~pgm_read_byte(&sprite_imgs[image_byte][i * 2]) & 0b11111111) << (8 - shift_length) | (~pgm_read_byte(&sprite_imgs[image_byte][i * 2 + 1]) & 0b11111111) >> shift_length;

        buffer = TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 2] & (0b11111111 >> shift_length);
        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 2] = buffer | ((~pgm_read_byte(&sprite_imgs[image_byte][i * 2 + 1]) & 0b11111111) << (8 - shift_length));
    }

    if (shift_length == 0)
    {
        TV.screen[(y_pos - 1) * MAX_X / 8 + x_pos / 8] = 0b11111111;
        TV.screen[(y_pos - 1) * MAX_X / 8 + x_pos / 8 + 1] = 0b11111111;
        TV.screen[(y_pos + TILE_SIZE) * MAX_X / 8 + x_pos / 8] = 0b11111111;
        TV.screen[(y_pos + TILE_SIZE) * MAX_X / 8 + x_pos / 8 + 1] = 0b11111111;

        for (byte y = y_pos - 1; y <= y_pos + TILE_SIZE; y++)
        {
            TV.screen[y * MAX_X / 8 + (x_pos - 1) / 8] |= 0b00000001;
            TV.screen[y * MAX_X / 8 + (x_pos + 16) / 8] |= 0b10000000;
        }
    }
    else
    {
        TV.screen[(y_pos - 1) * MAX_X / 8 + x_pos / 8] |= 0b11111111 >> shift_length;
        TV.screen[(y_pos - 1) * MAX_X / 8 + x_pos / 8 + 1] |= 0b11111111;
        TV.screen[(y_pos - 1) * MAX_X / 8 + x_pos / 8 + 2] |= 0b11111111 << (8 - shift_length);

        TV.screen[(y_pos + TILE_SIZE) * MAX_X / 8 + x_pos / 8] |= 0b11111111 >> shift_length;
        TV.screen[(y_pos + TILE_SIZE) * MAX_X / 8 + x_pos / 8 + 1] |= 0b11111111;
        TV.screen[(y_pos + TILE_SIZE) * MAX_X / 8 + x_pos / 8 + 2] |= 0b11111111 << (8 - shift_length);

        for (byte y = y_pos - 1; y <= y_pos + TILE_SIZE; y++)
        {
            TV.screen[y * MAX_X / 8 + (x_pos -  1) / 8] |= 0b00000001 << (8 - shift_length);
            TV.screen[y * MAX_X / 8 + (x_pos + 16) / 8] |= 0b10000000 >> shift_length;
        }
    }
}

void DecodeSpriteBorder(byte image_byte, short x_pos, short y_pos)
{
    byte shift_length = x_pos % 8;

    if (shift_length == 0)
    {
        TV.screen[(y_pos - 1) * MAX_X / 8 + x_pos / 8] = 0;
        TV.screen[(y_pos - 1) * MAX_X / 8 + x_pos / 8 + 1] = 0;

        TV.screen[(y_pos + TILE_SIZE) * MAX_X / 8 + x_pos / 8] = 0;
        TV.screen[(y_pos + TILE_SIZE) * MAX_X / 8 + x_pos / 8 + 1] = 0;

        for (byte y = y_pos - 1; y <= y_pos + TILE_SIZE; y++)
        {
            TV.screen[y * MAX_X / 8 + (x_pos -  1) / 8] &= (0b11111110);
            TV.screen[y * MAX_X / 8 + (x_pos + 16) / 8] &= (0b01111111);
        }
    }
    else
    {
        byte buffer = TV.screen[(y_pos - 1) * MAX_X / 8 + x_pos / 8];

        TV.screen[(y_pos - 1) * MAX_X / 8 + x_pos / 8] = buffer >> (8 - shift_length) << (8 - shift_length);
        TV.screen[(y_pos - 1) * MAX_X / 8 + x_pos / 8 + 1] = 0;

        buffer = TV.screen[(y_pos - 1) * MAX_X / 8 + x_pos / 8 + 2];
        TV.screen[(y_pos - 1) * MAX_X / 8 + x_pos / 8 + 2] = buffer << shift_length >> shift_length;

        buffer = TV.screen[(y_pos + TILE_SIZE) * MAX_X / 8 + x_pos / 8];
        TV.screen[(y_pos + TILE_SIZE) * MAX_X / 8 + x_pos / 8] = buffer >> (8 - shift_length) << (8 - shift_length);
        TV.screen[(y_pos + TILE_SIZE) * MAX_X / 8 + x_pos / 8 + 1] = 0;
        
        buffer = TV.screen[(y_pos + TILE_SIZE) * MAX_X / 8 + x_pos / 8 + 2];
        TV.screen[(y_pos + TILE_SIZE) * MAX_X / 8 + x_pos / 8 + 2] = buffer << shift_length >> shift_length;

        for (byte y = y_pos - 1; y <= y_pos + TILE_SIZE; y++)
        {
            TV.screen[y * MAX_X / 8 + (x_pos -  1) / 8] &= 0b11111110 << (8 - shift_length);
            TV.screen[y * MAX_X / 8 + (x_pos + 16) / 8] &= 0b01111111 >> shift_length;
        }
    }

    DecodeSprite(image_byte, x_pos, y_pos);
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
    byte *image_address = *(tile_imgs + image_byte);

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

void decode_heart_img(byte x, byte *mini_img) // 8x8 이미지 렌더
{
    for (int i = 0; i < 8; i++)
    {
        TV.screen[x + (i + 4) * MAX_X / 8] = pgm_read_byte(mini_img + i);
    }
}

void DecodeUI(byte p1_health, byte p2_health, byte p1_item, byte p2_item, byte p1_score, byte p2_score, short frame_left)
{
    byte *heart_full_img = ui_imgs[HEART_FULL];
    byte *heart_half_img = ui_imgs[HEART_HALF];
    byte i;

    // health render
    for (i = 0; i < p1_health / 2; i++)
    {
        decode_heart_img(i, heart_full_img);
    }
    if (p1_health % 2)
    {
        decode_heart_img(p1_health / 2, heart_half_img);
    }

    for (i = 15; i > 15 - p2_health / 2; i--)
    {
        decode_heart_img(i, heart_full_img);
    }
    if (p2_health % 2)
    {
        decode_heart_img(15 - p2_health / 2, heart_half_img);
    }

    // item render
    if (p1_item)
    {
        for (i = 4; i < 16; i++)
        {
            TV.screen[5 + i * MAX_X / 8] |= pgm_read_byte(item_imgs[p1_item - 1] + i * 2);
            TV.screen[5 + i * MAX_X / 8 + 1] |= pgm_read_byte(item_imgs[p1_item - 1] + i * 2 + 1);
        }
    }
    if (p2_item)
    {
        for (i = 4; i < 16; i++)
        {
            TV.screen[9 + i * MAX_X / 8] |= pgm_read_byte(item_imgs[p2_item - 1] + i * 2);
            TV.screen[9 + i * MAX_X / 8 + 1] |= pgm_read_byte(item_imgs[p2_item - 1] + i * 2 + 1);
        }
    }

    // score render
    for (i = 0; i < 8; i++)
    {
        TV.screen[6 + (i + 4) * MAX_X / 8] |= pgm_read_byte(ui_imgs[SCORE_FRAME_L] + i);
        TV.screen[7 + (i + 4) * MAX_X / 8] |= pgm_read_byte(ui_imgs[SCORE_FRAME_M1] + i);
        TV.screen[8 + (i + 4) * MAX_X / 8] |= pgm_read_byte(ui_imgs[SCORE_FRAME_M2] + i);
        TV.screen[9 + (i + 4) * MAX_X / 8] |= pgm_read_byte(ui_imgs[SCORE_FRAME_R] + i);

        TV.screen[7 + (i + 6) * MAX_X / 8] |= pgm_read_byte(ui_imgs[SCORE_START_L + p1_score] + i);
        TV.screen[8 + (i + 6) * MAX_X / 8] |= pgm_read_byte(ui_imgs[SCORE_START_R + p2_score] + i);
    }

    if (frame_left >= 0)
    {
        // timer render
        byte x_start = 4;
        byte length = 119 * (frame_left / 1800.0);
        byte y_start = 13 * MAX_X / 8;
        byte y_end = 14 * MAX_X / 8;
        byte tmp = 0;

        for (i = 4; i < 8; i++)
        {
            if (i >= x_start + length)
                break;
            tmp |= 0b10000000 >> i;
        }
        TV.screen[y_start] = tmp;
        TV.screen[y_end] = tmp;

        if (length > 4)
        {
            for (i = 8; i <= length - 4; i += 8)
            {
                TV.screen[y_start + i / 8] = 0b11111111;
                TV.screen[y_end + i / 8] = 0b11111111;
            }

            tmp = 0;
            for (i = 0; i < (length - 4) % 8; i++)
            {
                tmp |= 0b10000000 >> i;
            }
            TV.screen[y_start + (x_start + length) / 8] = tmp;
            TV.screen[y_end + (x_start + length) / 8] = tmp;
        }
    }
}

void DecodeFull(byte image_id)
{
    for (short i = 0; i < 768; i++)
    {
        TV.screen[i * 2] = pgm_read_byte(&full_imgs[image_id][i * 2]);
        TV.screen[i * 2 + 1] = pgm_read_byte(&full_imgs[image_id][i * 2 + 1]);
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