#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include <stdint.h>

#define byte uint8_t
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

#define MAP_WIDTH 8
#define MAP_HEIGHT 6

#define TILE_SIZE 16

#define MIN_X 0
#define MIN_Y 0

#define MAX_X 128
#define MAX_Y 96

#if MAX_X != MAP_WIDTH * TILE_SIZE
#error Invalid MAX_X value.
#endif

#if MAX_Y != MAP_HEIGHT * TILE_SIZE
#error Invalid MAX_Y value.
#endif

#define DIR_UP 0	// y 증가, 정면
#define DIR_RIGHT 1 // x 증가, 우측면
#define DIR_DOWN 2	// y 감소, 후면
#define DIR_LEFT 3	// x 감소, 좌측면

#define BULLET_FRAME_LEFT 30
#define ATTACK_DELAY 10
#define BULLET_MAX_NUM 4

#if BULLET_FRAME_LEFT / ATTACK_DELAY > BULLET_MAX_NUM
#error Invalid BULLET_FRAME_LEFT value.
#endif

#endif