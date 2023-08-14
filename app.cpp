#include "src/render/render.hpp"

void start_app()
{
	beginTV();
	Sprite box(IMG_ID_BOX, 0, 0);
	Sprite box2(IMG_ID_BOX, 27, 27);
	box.vy = 1;
	box.y_frame = 1;

	box2.vx = 1;
	box2.x_frame = 1;

	Background background;
	background.set(2, 2, IMG_ID_BOX, 0);

	// background.render();
	box.render();
	box2.render();

	// while (true)
	// {
	// 	// clearTV();
	// 	Sprite::start_next_frame();
	// 	box.next_frame();
	// 	box2.next_frame();
	// 	if (box.y > 100)
	// 		box.y = 0;
	// 	if (box2.x > 100)
	// 		box2.x = 0;
	// 	delay(16);
	// }
}