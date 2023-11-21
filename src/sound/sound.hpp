#ifndef SOUND_H
#define SOUND_H

#define MUSIC_SHEET_LEN 42

#define MUSIC_SHEET_BGM 0

#include "notes.hpp"
#include "../render/decode_img.hpp"

const unsigned short music_sheet[][MUSIC_SHEET_LEN] PROGMEM = {
	{
		NOTE_E5,
		NOTE_E5,
		NOTE_NO,
		NOTE_E5,
		NOTE_NO,
		NOTE_C5,
		NOTE_NO,
		NOTE_E5,
		NOTE_G5,
		NOTE_NO,
		NOTE_NO,
		NOTE_NO,
		NOTE_G4,
		NOTE_NO,
		NOTE_NO,
		NOTE_NO,
		NOTE_C5,
		NOTE_NO,
		NOTE_NO,
		NOTE_G4,
		NOTE_NO,
		NOTE_NO,
		NOTE_E4,
		NOTE_NO,
		NOTE_NO,
		NOTE_A4,
		NOTE_NO,
		NOTE_B4,
		NOTE_NO,
		NOTE_B4,
		NOTE_C5,
		NOTE_G4,
		NOTE_E5,
		NOTE_G5,
		NOTE_A5,
		NOTE_NO,
		NOTE_F5,
		NOTE_G5,
		NOTE_E5,
		NOTE_C5,
		NOTE_D5,
		NOTE_B4,
	}
};

class SoundPlayer {
private:
	unsigned int total_ms_passed;
	byte music_sheed_id;
	byte cur_note_idx;
	unsigned long last;
	void play_current();
public:
	SoundPlayer(byte _music_sheed_id);
	~SoundPlayer();
	void update();
};

#endif