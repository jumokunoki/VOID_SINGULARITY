/*****************************************************************//**
 * \file   FadeSound.cpp
 * \brief  �T�E���h�̃t�F�[�h
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/
#include "FadeSound.h"
FadeSound::FadeSound() {

};

FadeSound::~FadeSound() {

};

void FadeSound::SetFadeBgm(int* bgm, int old_gauge, int set_count,int in_out) {
	//�����̉����t�F�[�h�C���A�E�g�ł���悤�ɂ��邽�߂ɍ�����N���X
	//�t�F�[�h�C���A�E�g�̐ݒ�
	SOUND change_sound;
	change_sound.change = bgm;
	change_sound.old = old_gauge;
	change_sound.count = 0;
	change_sound.max_count = set_count;
	switch (in_out) {
	case 1:
		change_sound.now = 0;
		change_sound.hang = in_out;
		break;
	case -1:
		change_sound.now = old_gauge;
		change_sound.hang = in_out;
		break;
	}
	change_sound.use = true;
	//---------------------------------
	change_volume.push_back(change_sound);

};

void FadeSound::FadeBgmProcess() {
	//use�������瓮����
	for (auto&  volume: change_volume) {
		if (volume.use != 0) {
			float add_volume = (float)volume.old / volume.max_count;
			volume.now += add_volume * volume.hang;
			ChangeVolumeSoundMem(volume.now,*volume.change);
			volume.count++;
		}
		if (volume.count >= volume.max_count) {
			if (volume.hang < 0) {
				StopSoundMem(*volume.change);
			}
			ChangeVolumeSoundMem(volume.old, *volume.change);
			volume.use = false;
		}
	}
};