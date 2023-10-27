#include "app.hpp"

#include "src/controller/controller.hpp"
#include "src/render/render.hpp"
#include "common.hpp"
#include "src/loops/loops.hpp"

void start_app()
{
	beginTV();
	init_controller();

	byte scene = SCENE_START;
	byte args = true;

	while (true)
	{
		// game_loop(0, 0);
		if (args)
		{
			start_page_loop();
		}
		args = select_character_loop();
		args = game_loop(args >> 4, args & 0b00001111);
		args = end_loop(args);
	}
}