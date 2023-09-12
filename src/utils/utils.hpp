#ifndef UTILLS_H
#define UTILLS_H

#include "../../common.hpp"

#define POW(n) (n) * (n)

class Rand
{
public:
    static unsigned int seed;
    static byte get();
    static byte refresh();
};

#endif