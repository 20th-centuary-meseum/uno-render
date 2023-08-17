#include "src/render/render.hpp"

void start_app()
{
	beginTV();
	Character cat(0, 0, 0);

	while (true)
	{
		clearTV();
		Sprite::start_next_frame();

		cat.next_frame();
		cat.render();

		delay(16);
	}
}