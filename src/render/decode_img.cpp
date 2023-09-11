// #define IMG const byte PROGMEM

#include "decode_img.hpp"

#define HITBOX_CHAR 8
#define HITBOX_BULLET 5

TVout TV;

byte none[32] = {0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000};

byte box[32] = {0b00000000, 0b00000000,
                0b01111111, 0b11111110,
                0b01000000, 0b00000010,
                0b01000000, 0b00000010,
                0b01000000, 0b00000010,
                0b01000000, 0b00000010,
                0b01000000, 0b00000010,
                0b01000000, 0b00000010,
                0b01000000, 0b00000010,
                0b01000000, 0b00000010,
                0b01000000, 0b00000010,
                0b01000000, 0b00000010,
                0b01000000, 0b00000010,
                0b01000000, 0b00000010,
                0b01111111, 0b11111110,
                0b00000000, 0b00000000};
byte item[32] = {0b00000000, 0b00000000, // 17 (item1)
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000001, 0b00000000,
                 0b00000010, 0b10000000,
                 0b00000010, 0b10000000,
                 0b00001100, 0b01100000,
                 0b00010001, 0b00010000,
                 0b00001100, 0b01100000,
                 0b00000010, 0b10000000,
                 0b00000010, 0b10000000,
                 0b00000001, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000,
                 0b00000000, 0b00000000};

byte *
    images[] = {
        none,
        box,
        item,
};

const byte sprites[][32] PROGMEM = {
    {0b01101000, 0b00010110, // 0
     0b01000100, 0b00100010,
     0b01100011, 0b11000110,
     0b10111111, 0b11111000,
     0b01110101, 0b10101011,
     0b00010101, 0b10101100,
     0b11111111, 0b11111011,
     0b00101111, 0b11111000,
     0b00110000, 0b00001100,
     0b10000001, 0b10000001,
     0b10000000, 0b10000001,
     0b10000000, 0b10000001,
     0b11100000, 0b00000111,
     0b00100000, 0b00000100,
     0b00100001, 0b10000100,
     0b00011110, 0b01111100},

    {0b01101111, 0b00010110, // 1
     0b01000100, 0b00100010,
     0b01100011, 0b11000110,
     0b10111111, 0b11111000,
     0b01110101, 0b10101011,
     0b00010101, 0b10101100,
     0b11111111, 0b11111011,
     0b00101111, 0b11111000,
     0b00110000, 0b00001100,
     0b10000001, 0b10000001,
     0b10000000, 0b10000001,
     0b10000000, 0b10000001,
     0b11100000, 0b00000111,
     0b00100000, 0b00000100,
     0b00100001, 0b10000100,
     0b00011110, 0b01111100},

    {0b01101111, 0b11110110, // 2
     0b01000100, 0b00100010,
     0b01100011, 0b11000110,
     0b10111111, 0b11111000,
     0b01110101, 0b10101011,
     0b00010101, 0b10101100,
     0b11111111, 0b11111011,
     0b00101111, 0b11111000,
     0b00110000, 0b00001100,
     0b10000001, 0b10000001,
     0b10000000, 0b10000001,
     0b10000000, 0b10000001,
     0b11100000, 0b00000111,
     0b00100000, 0b00000100,
     0b00100001, 0b10000100,
     0b00011110, 0b01111100},

    {0b01101111, 0b00010110, // 3
     0b01000100, 0b00100010,
     0b01100011, 0b11000110,
     0b10111111, 0b11111000,
     0b01110101, 0b10101011,
     0b00010101, 0b10101100,
     0b11111111, 0b11111011,
     0b00101111, 0b11111000,
     0b00110000, 0b00001100,
     0b10000001, 0b10000001,
     0b10000000, 0b10000001,
     0b10000000, 0b10000001,
     0b11100000, 0b00000111,
     0b00100000, 0b00000100,
     0b00100001, 0b10000100,
     0b00011110, 0b01111100},

    {0b00000000, 0b00000000, // 4
     0b01111111, 0b11111110,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01111111, 0b11111110,
     0b00000000, 0b00000000},

    {0b00000000, 0b00000000, // 5
     0b01111111, 0b11111110,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01111111, 0b11111110,
     0b00000000, 0b00000000},

    {0b00000000, 0b00000000, // 6
     0b01111111, 0b11111110,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01111111, 0b11111110,
     0b00000000, 0b00000000},

    {0b00000000, 0b00000000, // 7
     0b01111111, 0b11111110,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000000,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01111111, 0b11111110,
     0b00000000, 0b00000000},

    {0b00000101, 0b00000000, // 8
     0b00000100, 0b10000000,
     0b00111111, 0b11000000,
     0b01111100, 0b00010000,
     0b01111110, 0b00010000,
     0b01101100, 0b00000000,
     0b11101010, 0b00000000,
     0b11111110, 0b00010000,
     0b01111111, 0b11110010,
     0b00011100, 0b10001010,
     0b00010010, 0b10001011,
     0b00100010, 0b10001001,
     0b00100011, 0b10001111,
     0b00110000, 0b00111100,
     0b00001000, 0b01000000,
     0b00000111, 0b10000000},

    {0b11110101, 0b00000000, // 9
     0b00000100, 0b10000000,
     0b00111111, 0b11000000,
     0b01111100, 0b00010000,
     0b01111110, 0b00010000,
     0b01101100, 0b00000000,
     0b11101010, 0b00000000,
     0b11111110, 0b00010000,
     0b01111111, 0b11110010,
     0b00011100, 0b10001010,
     0b00010010, 0b10001011,
     0b00100010, 0b10001001,
     0b00100011, 0b10001111,
     0b00110000, 0b00111100,
     0b00001000, 0b01000000,
     0b00000111, 0b10000000},

    {0b11110101, 0b00000000, // 10
     0b11110100, 0b10000000,
     0b00111111, 0b11000000,
     0b01111100, 0b00010000,
     0b01111110, 0b00010000,
     0b01101100, 0b00000000,
     0b11101010, 0b00000000,
     0b11111110, 0b00010000,
     0b01111111, 0b11110010,
     0b00011100, 0b10001010,
     0b00010010, 0b10001011,
     0b00100010, 0b10001001,
     0b00100011, 0b10001111,
     0b00110000, 0b00111100,
     0b00001000, 0b01000000,
     0b00000111, 0b10000000},

    {0b11110101, 0b00000000, // 11
     0b00000100, 0b10000000,
     0b00111111, 0b11000000,
     0b01111100, 0b00010000,
     0b01111110, 0b00010000,
     0b01101100, 0b00000000,
     0b11101010, 0b00000000,
     0b11111110, 0b00010000,
     0b01111111, 0b11110010,
     0b00011100, 0b10001010,
     0b00010010, 0b10001011,
     0b00100010, 0b10001001,
     0b00100011, 0b10001111,
     0b00110000, 0b00111100,
     0b00001000, 0b01000000,
     0b00000111, 0b10000000},

    {0b00000000, 0b00000000, // 12
     0b01111111, 0b11111110,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01111111, 0b11111110,
     0b00000000, 0b00000000},

    {0b00000000, 0b00000000, // 13
     0b01111111, 0b11111110,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b11111110,
     0b00000000, 0b00000000},

    {0b00000000, 0b00000000, // 14
     0b01111111, 0b11111110,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b00000000, 0b00000000},

    {0b00000000, 0b00000000, // 15
     0b01111111, 0b11111110,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b00000010,
     0b01000000, 0b11111110,
     0b00000000, 0b00000000},

    {0b00000000, 0b00000000, // 16 (bullet)
     0b00000000, 0b00000000,
     0b00000000, 0b00000000,
     0b00000000, 0b00000000,
     0b00000000, 0b00000000,
     0b00000001, 0b10000000,
     0b00000011, 0b11000000,
     0b00000111, 0b11100000,
     0b00000111, 0b11100000,
     0b00000011, 0b11000000,
     0b00000001, 0b10000000,
     0b00000000, 0b00000000,
     0b00000000, 0b00000000,
     0b00000000, 0b00000000,
     0b00000000, 0b00000000,
     0b00000000, 0b00000000},

    {0b00000000, 0b00000000, // 17 (item1)
     0b00000000, 0b00000000,
     0b00000000, 0b00000000,
     0b00000001, 0b00000000,
     0b00000010, 0b10000000,
     0b00000010, 0b10000000,
     0b00001100, 0b01100000,
     0b00010001, 0b00010000,
     0b00001100, 0b01100000,
     0b00000010, 0b10000000,
     0b00000010, 0b10000000,
     0b00000001, 0b00000000,
     0b00000000, 0b00000000,
     0b00000000, 0b00000000,
     0b00000000, 0b00000000,
     0b00000000, 0b00000000}};

const byte ui_images[][8] PROGMEM = {{0b00000000,
                                      0b01101100,
                                      0b11111110,
                                      0b11111110,
                                      0b01111100,
                                      0b00111000,
                                      0b00010000,
                                      0b00000000}};

bool did_crash_character(byte character_x, byte character_y, byte bullet_x, byte bullet_y)
{
    // const HITBOX_CHAR = 8, HITBOX_BULLET = 5
    short x_dist = character_x - bullet_x;
    short y_dist = character_y - bullet_y;
    if ((x_dist) * (x_dist) + (y_dist) * (y_dist) <= (HITBOX_CHAR + HITBOX_BULLET) * (HITBOX_CHAR + HITBOX_BULLET))
        return true;
    else
        return false;
}

// return 값 설명
// byte 0b00000 0  0  0
//              UD RL FLAG
// FLAG => 충돌 참 / 거짓
// UD => 위쪽 / 아래쪽
// RL => 오른쪽 / 왼쪽
byte did_crash_img(byte image_byte, short x_pos, short y_pos)
{
    byte image_id = image_byte;

    short tmp_y = y_pos * MAX_X / 8;
    byte shift_length = x_pos % 8;
    uint16_t y_minus = 0;
    uint16_t y_plus = 0;

    if (y_pos % 16 == 0)
    {
        for (int i = 0; i < TILE_SIZE; i++)
        {
            if (TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] & (pgm_read_byte(&sprites[image_id][i * 2]) >> shift_length))
            {
                return 1 | ((1) << 2);
            }
            else if (TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] & (pgm_read_byte(&sprites[image_id][i * 2]) << (8 - shift_length) | pgm_read_byte(&sprites[image_id][i * 2 + 1]) >> shift_length))
            {
                return 1 | ((1) << 2) | ((shift_length <= 3) << 1);
            }
            else if (TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 2] & (pgm_read_byte(&sprites[image_id][i * 2 + 1]) << (8 - shift_length)))
            {
                return 1 | ((1) << 2) | 2;
            }
        }
    }
    else
    {
        for (int i = 0; i < TILE_SIZE; i++)
        {
            if (TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] & (pgm_read_byte(&sprites[image_id][i * 2]) >> shift_length))
            {
                return 1 | ((i < 16 - y_pos % 16) << 2);
            }
            else if (TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] & (pgm_read_byte(&sprites[image_id][i * 2]) << (8 - shift_length) | pgm_read_byte(&sprites[image_id][i * 2 + 1]) >> shift_length))
            {
                return 1 | ((i < 16 - y_pos % 16) << 2) | ((shift_length <= 3) << 1);
            }
            else if (TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 2] & (pgm_read_byte(&sprites[image_id][i * 2 + 1]) << (8 - shift_length)))
            {
                return 1 | ((i < 16 - y_pos % 16) << 2) | 2;
            }
        }
    }
    return false;
}

void DecodeSprite(byte image_byte, short x_pos, short y_pos)
{
    if (x_pos < -15 || x_pos >= TILE_SIZE * MAP_WIDTH)
        return;
    if (y_pos < -15 || y_pos >= TILE_SIZE * MAP_HEIGHT)
        return;

    byte image_id = image_byte;

    // byte *sprites[image_id] = *(sprites + image_id);

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
            TV.screen[tmp_y + i * MAX_X / 8] |= pgm_read_byte(&sprites[image_id][i * 2 + 1]) << -8 - x_pos;
        }
    }
    else if (x_pos < 0) // 1개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + i * MAX_X / 8] |= pgm_read_byte(&sprites[image_id][i * 2]) << -x_pos | pgm_read_byte(&sprites[image_id][i * 2 + 1]) >> (8 + x_pos);
            TV.screen[tmp_y + i * MAX_X / 8 + 1] |= pgm_read_byte(&sprites[image_id][i * 2 + 1]) << -x_pos;
        }
    }
    else if (x_pos + 8 >= MAX_X) // 2개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(&sprites[image_id][i * 2]) >> shift_length;
        }
    }
    else if (x_pos + 16 >= MAX_X) // 1개 짤림
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(&sprites[image_id][i * 2]) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] |= pgm_read_byte(&sprites[image_id][i * 2]) << (8 - shift_length) | pgm_read_byte(&sprites[image_id][i * 2 + 1]) >> shift_length;
        }
    }
    else // 안 짤림.
    {
        for (int i = y_minus; i < TILE_SIZE - y_plus; i++)
        {
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= pgm_read_byte(&sprites[image_id][i * 2]) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] |= pgm_read_byte(&sprites[image_id][i * 2]) << (8 - shift_length) | pgm_read_byte(&sprites[image_id][i * 2 + 1]) >> shift_length;
            TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 2] |= pgm_read_byte(&sprites[image_id][i * 2 + 1]) << (8 - shift_length);
        }
    }
}

void DecodeImg(byte image_byte, byte x_pos, byte y_pos)
{
    byte image_id = image_byte >> 2;
    byte image_rot = bitRead(image_byte, 0) + 2 * bitRead(image_byte, 0);

    byte *image_address = *(images + image_id);

    int tmp_y = y_pos * MAX_X / 8;

    for (int i = 0; i < TILE_SIZE; i++)
    {
        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] = *(image_address + i * 2);
        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] = *(image_address + i * 2 + 1);
    }
}

void DecodeItem(byte image_byte, byte x_pos, byte y_pos)
{
    byte image_id = image_byte >> 2;
    byte image_rot = bitRead(image_byte, 0) + 2 * bitRead(image_byte, 0);

    byte *image_address = *(images + image_id);

    int tmp_y = y_pos * MAX_X / 8;

    for (int i = 0; i < TILE_SIZE; i++)
    {
        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8] |= *(image_address + i * 2);
        TV.screen[tmp_y + x_pos / 8 + i * MAX_X / 8 + 1] |= *(image_address + i * 2 + 1);
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
    byte *heart_ptr = ui_images[0];
    // health render
    for (int y = 0; y < (p1_health) / 5 + 1; y++) // p1

    {
        if (p1_health >= (y + 1) * 5)
        {
            decode_mini_img(0, y, heart_ptr);
            decode_mini_img(1, y, heart_ptr);
            decode_mini_img(2, y, heart_ptr);
            decode_mini_img(3, y, heart_ptr);
            decode_mini_img(4, y, heart_ptr);
        }
        else
        {
            for (int x = 0; x < p1_health % 5; x++)
            {
                decode_mini_img(x, y, heart_ptr);
            }
        }
    }

    for (int y = 0; y < (p2_health) / 5 + 1; y++) // p2
    {
        if (p2_health >= (y + 1) * 5)
        {
            decode_mini_img(15, y, heart_ptr);
            decode_mini_img(14, y, heart_ptr);
            decode_mini_img(13, y, heart_ptr);
            decode_mini_img(12, y, heart_ptr);
            decode_mini_img(11, y, heart_ptr);
        }
        else
        {
            for (int x = 0; x < p2_health % 5; x++)
            {
                decode_mini_img(15 - x, y, heart_ptr);
            }
        }
    }
    /*
    item decode code
    */
}

void beginTV()
{
    TV.begin(_NTSC, 128, 96);
}

void clearTV()
{
    TV.clear_screen();
}