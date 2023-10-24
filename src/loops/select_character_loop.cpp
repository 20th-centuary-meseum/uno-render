#include "select_characer_loop.hpp"
#include "../controller/controller.hpp"
#include "../render/render.hpp"
#include "../assets/assets.hpp"

// return value 형식 => 첫 4비트: char1 id, 다음 4비트: char2 id
byte select_character_loop()
{
	byte char1_id = 0;
	bool char1_selected = false;

	byte char2_id = 0;
	bool char2_selected = false;

	while (!char1_selected || !char2_selected)
	{
		if (CON_SELECT(con1))
		{
			char1_selected = true;
		}
		if (CON_SELECT(con2))
		{
			char2_selected = true;
		}
		update_controller();
		DecodeFull(SELECT_CHAR);
	}

	return char1_id << 4 | char2_id;
}