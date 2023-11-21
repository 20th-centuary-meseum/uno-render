#include "start_page_loop.hpp"
#include "../controller/controller.hpp"
#include "../assets/assets.hpp"
#include "../render/render.hpp"
#include "../sound/sound.hpp"

void start_page_loop()
{
	unsigned long last = millis();
	unsigned long current = millis();
	byte frame_cnt = 0;

	SoundPlayer sound_player(MUSIC_SHEET_BGM);

	bool show_text = true;

	while (!CON_START(con1 | con2))
	{
		unsigned long current = millis();
		if (last - current > FRAME_DELAY_MS)
		{
			if (frame_cnt > 30) {
				show_text = !show_text;
				frame_cnt = 0;
			}
			last = millis();
		}
		sound_player.update();
		DecodeFull(START_PAGE_A);
		update_controller();
	}
}