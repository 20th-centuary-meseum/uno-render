#include "sound.hpp"
#define ONE_BIT_MS 250

SoundPlayer::SoundPlayer(byte _music_sheed_id) {
	music_sheed_id = _music_sheed_id;
	total_ms_passed = 0;
	cur_note_idx = 0;
	play_current();
	unsigned long last = millis();
}
SoundPlayer::~SoundPlayer() {
	TV.noTone();
}


void SoundPlayer::update() {
	total_ms_passed += millis() - last;
	last = millis();

	if (total_ms_passed > ONE_BIT_MS) {
		total_ms_passed = 0;
		cur_note_idx = (cur_note_idx + 1) % MUSIC_SHEET_LEN;
		play_current();
	}
}

void SoundPlayer::play_current() {
	unsigned short note = pgm_read_word(&music_sheet[music_sheed_id][cur_note_idx]);
	if (note == NOTE_NO) TV.noTone();
	else TV.tone(note, ONE_BIT_MS);
}