#include "src/render/render.hpp"

void start_app()
{
	beginTV();
	Sprite box(IMG_ID_BOX, -9, 0);
	Sprite box1(IMG_ID_BOX, -4, 16);
	Sprite box2(IMG_ID_BOX, 115, 32);
	Sprite box3(IMG_ID_BOX, 120, 48);

	Background background;
	background.set(2, 2, IMG_ID_BOX, 0);

	box.render();
	box1.render();
	box2.render();
	box3.render();

	box3.vx = 1;
	box3.x_frame = 10;

	while (true)
	{
		clearTV();
		Sprite::start_next_frame();
		box3.next_frame();
		box3.render();
		if (box3.x > 200)
			box3.x = 0;
		delay(16);
	}
}