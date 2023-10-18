#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../../common.hpp"

#define A_BIT 8
#define B_BIT 0
#define X_BIT 9
#define Y_BIT 1

#define U_BIT 5
#define R_BIT 7
#define D_BIT 4
#define L_BIT 6

#define SELECT_BIT 2
#define START_BIT 3
#define LB_BIT 10
#define RB_BIT 11

#define CON_A(con_state) bitRead(con_state, A_BIT)
#define CON_B(con_state) bitRead(con_state, B_BIT)

#define CON_X(con_state) bitRead(con_state, X_BIT)
#define CON_Y(con_state) bitRead(con_state, Y_BIT)

#define CON_U(con_state) bitRead(con_state, U_BIT)
#define CON_R(con_state) bitRead(con_state, R_BIT)
#define CON_D(con_state) bitRead(con_state, D_BIT)
#define CON_L(con_state) bitRead(con_state, L_BIT)

#define CON_SELECT(con_state) bitRead(con_state, SELECT_BIT)
#define CON_START(con_state) bitRead(con_state, START_BIT)
#define CON_LB(con_state) bitRead(con_state, LB_BIT)
#define CON_RB(con_state) bitRead(con_state, RB_BIT)

#define POWER_1 3
#define DATA_CLOCK_1 14
#define DATA_LATCH_1 15
#define DATA_SERIAL_1 16

#define POWER_2 5
#define DATA_CLOCK_2 4
#define DATA_LATCH_2 3
#define DATA_SERIAL_2 2

extern uint16_t con1;
extern uint16_t con2;

void init_controller();
void update_controller();

#endif