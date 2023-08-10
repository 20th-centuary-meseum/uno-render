#include "src/render/render.hpp"

void start_app()
{
	beginTV();
	clearTV();

	Sprite knight(IMG_ID_BOX, 30, 40);

	Background background;
	background.set(2, 2, IMG_ID_BOX, 0);
	background.render();
	knight.render();
}