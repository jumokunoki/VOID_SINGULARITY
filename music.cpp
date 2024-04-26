/*****************************************************************//**
 * \file   music.cpp
 * \brief  ‰¹Šy
 *
 * \author âV“¡ Œè‰H
 * \date   August 2023
 *********************************************************************/
#include "music.h"
#include "dxlib.h"
#include "gamemain.h"
#include "mymath.h"
music::music() {
	cool_voice = 0;
};

music::~music() {
	
};

void music::SetCoolVoice() {
	if (cool_voice <= 0) {
		cool_voice = 300;
	}
}
											 
void music::MusicProcess() {
	if (cool_voice > 0) {
		cool_voice--;
	}
};

void music::SetSeVolume(int se) {
	ChangeVolumeSoundMem(gauge[0], se);
};

void music::SetBgmVolume(int bgm) {
	ChangeVolumeSoundMem(gauge[1], bgm);
};

void music::SetVoiceVolume(int voice) {
	ChangeVolumeSoundMem(gauge[2], voice);
};

void music::MakeSe(int se) {
	PlaySoundMem(se, DX_PLAYTYPE_BACK);
}

void music::MakeBgm(int bgm) {
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP);
}

void music::MakeVoice(int voice_num, int max) {
	if (cool_voice <= 0) {
		int randam = rand() % max;
		for (int i = 0; i < 16; i++) {
			if (CheckVoiceAll() == 1) {
				PlaySoundMem(_image->chara_voice[voice_num + randam], DX_PLAYTYPE_BACK);
			}
		}
	}
}

void music::StopSe(int Se) {
	StopSoundMem(Se);
}

void music::StopBgm(int Bgm) {
	StopSoundMem(Bgm);
}

int music::CheckVoiceAll(){
	int check = 0;
	for (int i = 0; i < 16; i++) {
		if (CheckSoundMem(_image->chara_voice[i]) != 1) {
			check++;
		}
	}

	if (check >= 16) {
		return 1;
	}
	else {
		return 0;
	}
}