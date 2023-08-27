#include "src/render/render.hpp"

void start_app()
{
	beginTV();
	Character cat(0, 0, 0);
	cat.set_move_up(1, 3);

	while (true)
	{
		clearTV();
		Sprite::start_next_frame();
		cat.next_frame();
		cat.render();

		switch (GET_DIR_BIT(cat.state))
		{
		case DIR_UP:
			if (cat.y > MAX_Y - 16)
				cat.set_move_right(1, 3);
			break;
		case DIR_RIGHT:
			if (cat.x > MAX_X - 16)
				cat.set_move_down(1, 3);
			break;
		case DIR_DOWN:
			if (cat.y < MIN_Y + 16)
				cat.set_move_left(1, 3);
			break;
		case DIR_LEFT:
			if (cat.x < MIN_X + 16)
				cat.set_move_up(1, 3);
			break;

		default:
			break;
		}

		delay(32);
	}
}