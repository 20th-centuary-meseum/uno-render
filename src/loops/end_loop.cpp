#include "end_loop.hpp"

#include "../../common.hpp"
#include "../assets/assets.hpp"
#include "../controller/controller.hpp"
#include "../render/render.hpp"

byte end_loop(byte character_won)
{
	unsigned long last = millis();
	unsigned long current = millis();

	short frame_cnt = 0;
	byte full_img_id = character_won == 1 ? WIN_1P : WIN_2P;

	// 10초 동안 버튼 안누르면 시작화면, 버튼 누르면 캐릭터 선택 화면
	while (frame_cnt < 300)
	{
		current = millis();
		if (current - last > FRAME_DELAY_MS)
		{
			last = millis();
			frame_cnt++;

			DecodeFull(full_img_id);

			// 바로 엔딩화면 스킵을 막기 위한 딜레이
			if (CON_START(con1 | con2))
			{
				return 0;
			}
		}

		update_controller();
	}
	return 1;
}