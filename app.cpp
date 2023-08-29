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
	player1.set_speed(0, 100);

	Bullet *player1_bullet = 0;

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
			player1.render();

			if (player1_bullet)
			{
				player1_bullet->next_frame();
				if (player1_bullet->frame_left == 0)
				{
					delete player1_bullet;
					player1_bullet = 0;
				}
				player1_bullet->render();
			}
		}

		update_controller();

		if (CON_AT(con1))
		{
			bool atk_success = player1.attack();
			if (atk_success && !player1_bullet)
			{
				player1_bullet = new Bullet(player1.x, player1.y, GET_DIR_BIT(player1.state));
			}
		}

		if (CON_U(con1))
		{
			player1.move_up(1, 1);
		}
		else if (CON_D(con1))
		{
			player1.move_down(1, 1);
		}
		else if (CON_R(con1))
		{
			player1.move_right(1, 1);
		}
		else if (CON_L(con1))
		{
			player1.move_left(1, 1);
		}
		else
		{
			player1.set_speed(0, 100);
		}
	}
}