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

#endif