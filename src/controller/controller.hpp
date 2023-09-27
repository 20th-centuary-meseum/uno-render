#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../../common.hpp"
/*
 Pin state binary
	E AB AT URLD
 0b 0 00 0  0000

 E:  Empty. Not used.
 A:  A Button.
 B:  B Button.
 AT: Attack Button.

 U: Up Button.
 R: Right Button.
 L: Left Button.
 D: Down Button.
*/

#define A_BIT 6
#define B_BIT 5

#define AT_BIT 4

#define U_BIT 3
#define R_BIT 2
#define D_BIT 1
#define L_BIT 0

#define CON_A(con_state) bitRead(con_state, A_BIT)
#define CON_B(con_state) bitRead(con_state, B_BIT)

#define CON_AT(con_state) bitRead(con_state, AT_BIT)

#define CON_U(con_state) bitRead(con_state, U_BIT)
#define CON_R(con_state) bitRead(con_state, R_BIT)
#define CON_D(con_state) bitRead(con_state, D_BIT)
#define CON_L(con_state) bitRead(con_state, L_BIT)

#define CON1_A_PIN 6
#define CON1_B_PIN 8

#define CON1_AT_PIN 10

#define CON1_U_PIN 3
#define CON1_R_PIN 4
#define CON1_D_PIN 2
#define CON1_L_PIN 5

#define CON2_A_PIN 16
#define CON2_B_PIN 17

#define CON2_AT_PIN 14

#define CON2_U_PIN 15
#define CON2_R_PIN 17
#define CON2_D_PIN 16
#define CON2_L_PIN 18

extern byte con1;
extern byte con2;

void init_controller();
void update_controller();

#endif