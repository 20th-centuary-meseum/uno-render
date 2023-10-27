#include "game_loop.hpp"

#include "../render/render.hpp"
#include "../controller/controller.hpp"
#include "../utils/utils.hpp"
#include "../assets/assets.hpp"

byte game_loop(byte char1_id, byte char2_id)
{
	byte p1_score = 0, p2_score = 0;

	while (p1_score < 3 && p2_score < 3)
	{
		if (set_loop(char1_id, char2_id, p1_score, p2_score) == 1)
		{
			p1_score += 1;
		}
		else
		{
			p2_score += 1;
		}
	}

	return p1_score == 3 ? 1 : 2;
}

// return value 형식 => 1p 승리: return 1. 2p 승리: return 2
byte set_loop(byte char1_id, byte char2_id, byte p1_score, byte p2_score)
{
	Background background;

	for (byte i = 2; i < MAP_HEIGHT - 1; i++)
	{
		for (byte j = 2; j < MAP_WIDTH - 1; j++)
		{
			background.set(j, i, 1, 0);
		}
	}

	Character player1(char1_id, 1, 16);
	Bullets player1_bullets;
	player1.set_speed(0, 100);

	Character player2(char2_id, MAX_X - 16, MAX_Y - 16);
	Bullets player2_bullets;
	player2.set_speed(0, 100);

	Items items;

	unsigned long last = millis();
	unsigned long current = millis();

	while (true)
	{
		Rand::refresh();
		current = millis();
		if (current - last > FRAME_DELAY_MS)
		{
			last = millis();
			background.render();

			Sprite::start_next_frame();

			player1.next_frame(background.map);
			player2.next_frame(background.map);

			player1.render();
			player2.render();

			player1_bullets.next_frame(&player2, &player1, &items, &background);
			player2_bullets.next_frame(&player1, &player2, &items, &background);

			player1.get_item_if_crashed(items);
			player2.get_item_if_crashed(items);

			player1_bullets.render();
			player2_bullets.render();

			items.render();

			if (player1.hp <= 0)
			{
				return 2;
			}
			if (player2.hp <= 0)
			{
				return 1;
			}

			DecodeUI(player1.hp, player2.hp, player1.possess_item_id, player2.possess_item_id, p1_score, p2_score);
		}

		update_controller();
		if (CON_X(con1))
		{
			if (player1.attack())
			{
				player1_bullets.add_bullet(player1.x, player1.y, GET_DIR_BIT(player1.state));
			}
		}
		else if (CON_Y(con1))
		{
			player1.use_item();
		}

		if (CON_X(con2))
		{
			if (player2.attack())
			{
				player2_bullets.add_bullet(player2.x, player2.y, GET_DIR_BIT(player2.state));
			}
		}
		else if (CON_Y(con2))
		{
			player2.use_item();
		}

		player1.move_by_controller(con1);
		player2.move_by_controller(con2);
	}
}