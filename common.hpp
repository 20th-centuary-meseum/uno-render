#ifndef COMMON_H
#define COMMON_H

#include <Arduino.h>
#include <stdint.h>

#define byte uint8_t
#define bitRead(value, bit) (((value) >> (bit)) & 0x01)

#define MAP_WIDTH 8
#define MAP_HEIGHT 6

#define TILE_SIZE 16

#endif