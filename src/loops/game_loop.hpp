#ifndef GAME_LOOP_H
#define GAME_LOOP_H

#include "../../common.hpp"

byte ready_loop();
byte set_loop(byte char1_id, byte char2_id, byte p1_score, byte p2_score);
byte game_loop(byte char1_id, byte char2_id);

#endif