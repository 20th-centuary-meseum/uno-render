#include "./utils.hpp"

unsigned int Rand::seed = 0;
byte Rand::refresh()
{
    seed = micros();
}
byte Rand::get() // range = 0~255
{
    byte result;
    result = seed;
    seed = seed >> 8;

    return result;
}