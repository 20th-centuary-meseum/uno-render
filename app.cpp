#include "src/render/render.hpp"
#include "src/controller/controller.hpp"

#define FRAME_DELAY_MS 32

void start_app()
{
	beginTV();
	init_controller();

	Character player(0, 0, 0);
	player.set_speed(0, 100);

	unsigned long last = millis();
	unsigned long current = millis();

	while (true)
	{
		current = millis();
		if (current - last > FRAME_DELAY_MS)
		{
			last = millis();
			clearTV();
			Sprite::start_next_frame();
			player.next_frame();

			player.render();

			if (player.y < MIN_Y || player.y > MAX_Y)
			{
				player.y = (MIN_Y + MAX_Y) / 2;
			}
		}

		update_controller();

		if (CON_U(con1))
		{
			player.move_up(1, 1);
		}
		else if (CON_D(con1))
		{
			player.move_down(1, 1);
		}
		else
		{
			player.set_speed(0, 100);
		}
	}
}