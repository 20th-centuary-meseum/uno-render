#include "src/render/render.hpp"

void start_app()
{
	beginTV();
	clearTV();

	Sprite knight(30, 40);

	Background background;
	background.set(2, 2, 0, 0);
	background.render();
	knight.render();
}