#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include <stdint.h>

#define byte uint8_t
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)
#define bitSetHigh(value, bit) value = ((value) | (0x01 << (bit)))
#define bitSetLow(value, bit) value = ((value) & ~(0x01 << (bit)))

#define MAP_WIDTH 8
#define MAP_HEIGHT 6

#define TILE_SIZE 16

#define MIN_X 0
#define MIN_Y 16

#define MAX_X 128
#define MAX_Y 96

#define DIR_UP 0	// y 증가, 정면
#define DIR_RIGHT 1 // x 증가, 우측면
#define DIR_DOWN 2	// y 감소, 후면
#define DIR_LEFT 3	// x 감소, 좌측면

#define BULLET_FRAME_LEFT 30
#define ATTACK_DELAY 30
#define BULLET_MAX_NUM 4

#define ITEM_HEAL 1
#define ITEM_SHLD 2
#define ITEM_DASH 3
#define ITEM_SPED 4
#define ITEM_DAMG 5

#if BULLET_FRAME_LEFT / ATTACK_DELAY > BULLET_MAX_NUM
#error Invalid BULLET_FRAME_LEFT value.
#endif

#define FRAME_DELAY_MS 32

#define SCENE_START 0
#define SCENE_SELECT_CHARACTER 1
#define SCENE_GAME_PLAY 2
#define SCENE_END 3

#endif