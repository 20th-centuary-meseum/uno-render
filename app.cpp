#include "src/render/render.hpp"
#include "src/controller/controller.hpp"

#define FRAME_DELAY_MS 32

void start_app()
{
	beginTV();
	init_controller();

	Background backround;

	backround.set(7, 0, 1, 0);
	backround.set(3, 2, 1, 0);
	backround.set(4, 2, 1, 0);
	backround.set(5, 2, 1, 0);
	backround.set(3, 3, 1, 0);
	backround.set(4, 3, 1, 0);
	backround.set(5, 3, 1, 0);

	Character player1(0, 64, 0);
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

			player1.next_frame(backround.map);
			player2.next_frame(backround.map);

			player1.render();
			player2.render();

			player1_bullets.next_frame();
			player2_bullets.next_frame();

			player1_bullets.render();
			player2_bullets.render();

			for (byte i = 0; i < BULLET_MAX_NUM; i++)
			{
				byte crash_bit = did_crash_img(player1_bullets.bullets[i]->face_id, player1_bullets.bullets[i]->x, player1_bullets.bullets[i]->y);
				if (crash_bit)
				{
					if (crash_bit == 0b0000001)
					{
						// up-left
						backround.set((player1_bullets.bullets[i]->x / TILE_SIZE), (player1_bullets.bullets[i]->y / TILE_SIZE + 1), 0, 0);
					}
					else if (crash_bit == 0b0000011)
					{
						// up-right
						backround.set((player1_bullets.bullets[i]->x / TILE_SIZE + 1), (player1_bullets.bullets[i]->y / TILE_SIZE + 1), 0, 0);
					}
					else if (crash_bit == 0b0000101)
					{
						// down-left
						backround.set((player1_bullets.bullets[i]->x / TILE_SIZE), (player1_bullets.bullets[i]->y / TILE_SIZE), 0, 0);
					}
					else if (crash_bit == 0b0000111)
					{
						// down-right
						backround.set((player1_bullets.bullets[i]->x / TILE_SIZE + 1), (player1_bullets.bullets[i]->y / TILE_SIZE), 0, 0);
					}

					// delete player1_bullets.bullets[i];
					// player1_bullets.bullets[i] = 0;
				}
			}
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