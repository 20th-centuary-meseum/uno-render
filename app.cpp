#include "src/render/render.hpp"
#include "src/controller/controller.hpp"

#define FRAME_DELAY_MS 32

void start_app()
{
	beginTV();
	init_controller();

	Background backround;
	backround.set(0, 2, 1, 0);

	Character player1(0, 64, 48);
	Bullets player1_bullets;
	player1.set_speed(0, 100);

	Character player2(0, 0, 0);
	Bullets player2_bullets;
	player2.set_speed(0, 100);

	unsigned long last = millis();
	unsigned long current = millis();

	while (true)
	{
		current = millis();
		if (current - last > FRAME_DELAY_MS)
		{
			last = millis();
			backround.render();

			Sprite::start_next_frame();

			player1.next_frame();
			player2.next_frame();

			player1.render();
			player2.render();

			player1_bullets.next_frame();
			player2_bullets.next_frame();

			// if (player1_bullets.bullets_crashed)
			// {
			// 	for (byte i = 0; i < BULLET_MAX_NUM; i++)
			// 	{
			// 		if (bitRead(player1_bullets.bullets_crashed, i))
			// 		{
			// 			delete player1_bullets.bullets[i];
			// 			player1_bullets.bullets[i] = 0;
			// 		}
			// 	}
			// }

			player1_bullets.render();
			player2_bullets.render();
		}

		update_controller();

		if (CON_AT(con1))
		{
			if (player1.attack())
			{
				player1_bullets.add_bullet(player1.x, player1.y, GET_DIR_BIT(player1.state));
			}
		}

		if (CON_AT(con2))
		{
			if (player2.attack())
			{
				player2_bullets.add_bullet(player2.x, player2.y, GET_DIR_BIT(player2.state));
			}
		}

		player1.move_by_controller(con1);
		player2.move_by_controller(con2);
	}
}