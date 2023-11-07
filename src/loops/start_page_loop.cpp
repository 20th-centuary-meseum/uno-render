#include "start_page_loop.hpp"
#include "../controller/controller.hpp"
#include "../assets/assets.hpp"
#include "../render/render.hpp"

void start_page_loop()
{
	while (!CON_START(con1 | con2))
	{
		DecodeFull(START_PAGE);
		update_controller();
	}
}