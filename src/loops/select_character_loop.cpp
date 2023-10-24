#include "select_characer_loop.hpp"
#include "../controller/controller.hpp"
#include "../render/render.hpp"
#include "../assets/assets.hpp"

#define X_START 5
#define Y_START 54

// 0  2  4
//   1  3
byte changed_char_id(byte cur_id, byte con, byte con_last)
{
	if (!CON_U(con) && CON_U(con_last))
	{
		if (cur_id == 0 || cur_id == 2)
			cur_id += 1;
		else if (cur_id == 4)
			cur_id = 3;
	}
	else if (!CON_R(con) && CON_R(con_last))
	{
		if (cur_id < 3)
			cur_id += 2;
	}
	else if (!CON_D(con) && CON_D(con_last))
	{
		if (cur_id % 2)
			cur_id -= 1;
	}
	else if (!CON_L(con) && CON_L(con_last))
	{
		if (cur_id > 1)
			cur_id -= 2;
	}

	return cur_id;
}

// return value 형식 => 첫 4비트: char1 id, 다음 4비트: char2 id
byte select_character_loop()
{
	byte char1_id = 0;
	bool char1_selected = false;
	byte con1_last = 0;

	byte char2_id = 0;
	bool char2_selected = false;
	byte con2_last = 0;

	byte coords[][2] = {
		{24, 24},
		{X_START, Y_START},
		{X_START + 9, Y_START + 19},
		{X_START + 19, Y_START},
		{X_START + 28, Y_START + 19},
		{X_START + 38, Y_START},
	};
	unsigned long last = millis();
	unsigned long current = millis();

	DecodeFull(SELECT_CHAR);

	DecodeSprite(0 << 5, coords[1][0], coords[1][1]);
	DecodeSprite(0 << 5, coords[1][0] + 64, coords[1][1]);

	DecodeSprite(1 << 5, coords[2][0], coords[2][1]);
	DecodeSprite(1 << 5, coords[2][0] + 64, coords[2][1]);

	DecodeSprite(2 << 5, coords[3][0], coords[3][1]);
	DecodeSprite(2 << 5, coords[3][0] + 64, coords[3][1]);

	DecodeSprite(3 << 5, coords[4][0], coords[4][1]);
	DecodeSprite(3 << 5, coords[4][0] + 64, coords[4][1]);

	DecodeSprite(4 << 5, coords[5][0], coords[5][1]);
	DecodeSprite(4 << 5, coords[5][0] + 64, coords[5][1]);

	while (!char1_selected || !char2_selected)
	{
		current = millis();
		if (current - last > 64)
		{
			DecodeFull(SELECT_CHAR);

			DecodeSprite(char1_id << 5, coords[0][0], coords[0][1]);
			DecodeSprite(char2_id << 5, coords[0][0] + 64, coords[0][1]);

			DecodeSprite(char1_id << 5, coords[char1_id + 1][0], coords[char1_id + 1][1]);
			DecodeSprite(char2_id << 5, coords[char2_id + 1][0] + 64, coords[char2_id + 1][1]);

			char1_id = changed_char_id(char1_id, con1, con1_last);
			char2_id = changed_char_id(char2_id, con2, con2_last);

			con1_last = con1;
			con2_last = con2;
		}
		if (CON_SELECT(con1))
		{
			char1_selected = true;
		}
		if (CON_SELECT(con2))
		{
			char2_selected = true;
		}

		update_controller();
	}

	return char1_id << 4 | char2_id;
}