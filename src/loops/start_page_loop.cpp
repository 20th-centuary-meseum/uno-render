#include "start_page_loop.hpp"
#include "../controller/controller.hpp"
#include "../assets/assets.hpp"
#include "../render/render.hpp"

void start_page_loop()
{
	unsigned long last = millis();
	unsigned long current = millis();

	bool show_text = true;

	while (!CON_START(con1 | con2))
	{
		unsigned long current = millis();
		if (last - current > 1000)
		{
			show_text = !show_text;
			last = millis();
		}

		DecodeFull(show_text ? START_PAGE_A : START_PAGE_B);
		update_controller();
	}
}