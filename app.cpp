#include "src/render/render.hpp"
#include "src/controller/controller.hpp"
#include "src/utils/utils.hpp"

#define FRAME_DELAY_MS 32

void start_app()
{
	beginTV();
	init_controller();

	Background background;

	for (byte i = 2; i < MAP_HEIGHT - 1; i++)
	{
		for (byte j = 2; j < MAP_WIDTH - 1; j++)
		{
			background.set(j, i, 1, 0);
		}
	}

	Character player1(0, 1, 16);
	Bullets player1_bullets;
	player1.set_speed(0, 100);

	Character player2(1, MAX_X - 16, MAX_Y - 16);
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

			player1_bullets.next_frame(&player2, &items, &background);
			player2_bullets.next_frame(&player1, &items, &background);

			player1.get_item_if_crashed(items);
			player2.get_item_if_crashed(items);

			player1_bullets.render();
			player2_bullets.render();

			items.render();

			DecodeUI(player1.hp, player2.hp, player1.possess_item_id, player2.possess_item_id);
		}

		update_controller();

		// if (CON_A(con1))
		// {
		// 	if (player1.attack())
		// 	{
		// 		player1_bullets.add_bullet(player1.x, player1.y, GET_DIR_BIT(player1.state));
		// 	}
		// } else
		if (CON_AT(con1))
		{
			player1.use_item();
		}

		if (CON_AT(con2))
		{
			if (player2.attack())
			{
				player2_bullets.add_bullet(player2.x, player2.y, GET_DIR_BIT(player2.state));
			}
		}
		else if (CON_A(con2))
		{
			// player2.use_item();
		}

		player1.move_by_controller(con1);
		player2.move_by_controller(con2);
	}
}