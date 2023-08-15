#include "src/render/render.hpp"

void start_app()
{
	beginTV();
	Sprite box3(IMG_ID_BOX, -11, 48);

	Background background;
	background.set(2, 2, IMG_ID_BOX, 0);
	box3.vx = -1;
	box3.x_frame = 3;

	box3.vy = -1;
	box3.y_frame = 3;

	while (true)
	{
		clearTV();
		Sprite::start_next_frame();
		box3.next_frame();
		box3.render();
		if (box3.y < -15)
		{
			box3.vy = 1;
		}
		else if (box3.y > 96)
		{
			box3.vy = -1;
		}

		if (box3.x < -15)
		{
			box3.vx = 1;
		}
		else if (box3.x > 128)
		{
			box3.vx = -1;
		}
		delay(16);
	}
}