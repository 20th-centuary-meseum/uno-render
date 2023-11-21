#include "select_characer_loop.hpp"
#include "../controller/controller.hpp"
#include "../render/render.hpp"
#include "../assets/assets.hpp"
#include "../sound/sound.hpp"

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
	SoundPlayer sound_player(MUSIC_SHEET_BGM);

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

	byte blink = 0;

	DecodeFull(SELECT_CHAR);

	while (!char1_selected)
	{
		current = millis();
		if (current - last < 60)
		{
			if (char1_selected || blink < 20)
				DecodeSpriteReverse(char1_id << 5, coords[0][0], coords[0][1]);
			else
				DecodeSpriteBorder(char1_id << 5, coords[0][0], coords[0][1]);

			DecodeSpriteBorder(char2_id << 5, coords[0][0] + 64, coords[0][1]);

			for (byte i = 0; i < 5; i++)
			{
				if (i == char1_id)
					DecodeSpriteReverse(i << 5, coords[i + 1][0], coords[i + 1][1]);
				else
					DecodeSpriteBorder(i << 5, coords[i + 1][0], coords[i + 1][1]);

				DecodeSpriteBorder(i << 5, coords[i + 1][0] + 64, coords[i + 1][1]);
			}
			last = millis();
			blink = (blink + 1) % 40;
		}
		if (CON_SELECT(con1))
		{
			char1_selected = true;
		}

		con1_last = con1;
		update_controller();

		if (!char1_selected)
			char1_id = changed_char_id(char1_id, con1, con1_last);
		sound_player.update();
	}

	while (!char2_selected)
	{
		current = millis();
		if (current - last < 60)
		{
			if (char2_selected || blink < 20)
				DecodeSpriteReverse(char2_id << 5, coords[0][0] + 64, coords[0][1]);
			else
				DecodeSpriteBorder(char2_id << 5, coords[0][0] + 64, coords[0][1]);

			for (byte i = 0; i < 5; i++)
			{
				if (i == char1_id)
					DecodeSpriteReverse(i << 5, coords[i + 1][0], coords[i + 1][1]);
				else
					DecodeSpriteBorder(i << 5, coords[i + 1][0], coords[i + 1][1]);

				if (i == char2_id)
					DecodeSpriteReverse(i << 5, coords[i + 1][0] + 64, coords[i + 1][1]);
				else
					DecodeSpriteBorder(i << 5, coords[i + 1][0] + 64, coords[i + 1][1]);
			}

			last = millis();
			blink = (blink + 1) % 40;
		}

		if (CON_SELECT(con2) && char2_id != char1_id)
		{
			char2_selected = true;
		}

		con2_last = con2;
		update_controller();

		if (!char2_selected)
			char2_id = changed_char_id(char2_id, con2, con2_last);

		sound_player.update();
	}

	delay(1000);

	return char1_id << 4 | char2_id;
}