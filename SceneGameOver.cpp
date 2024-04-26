/*****************************************************************//**
 * \file   SceneGameOver.h
 * \brief  ÉQÅ[ÉÄÉIÅ[ÉoÅ[
 *
 * \author ‚Vì° åËâH
 * \date   August 2023
 *********************************************************************/
#include "SceneGameOver.h"
#include "SceneTest.h"
#include "stdio.h"
#include "dxlib.h"

SceneGameOver::SceneGameOver() {
	LoadDivGraph("res/gameover/GAME_OVER_1_00000_sheet.png", 30, 10, 3, 1000, 200, gameover_handle);
	chara_serif = 0;
	voice       = 0;
	int randam = rand() % 2;
	switch(randam) {
	case 0: {
		chara_serif = LoadGraph("res/gameover/GameOver_Font_1.png");
		voice = LoadSoundMem("res/voice/gameover_voice/dead_sirius.wav");
		break;
	}
	case 1: {
		chara_serif = LoadGraph("res/gameover/GameOver_Font_2.png");
		voice = LoadSoundMem("res/voice/gameover_voice/dead_rana.wav");
		break;
	}
	}

	PlaySoundMem(voice, DX_PLAYTYPE_BACK);
	SetVolumeMusicMem(gauge[2], voice);


	over.motspeed    = 4;
	over.motseet     = 30;
	over.motcount    = 0;
	over.motaddcount = 0;

};

SceneGameOver::~SceneGameOver() {
	for(int i = 0; i < 31; i++) {
		DeleteGraph(gameover_handle[i]);
	}
};

void SceneGameOver::Process() {

		over.motcount++;

		if(over.motcount >= over.motspeed) {
			over.motcount = 0;
			over.motaddcount++;
		}

		if(over.motaddcount * over.motspeed > (over.motseet - 1) * over.motspeed) {
			over.motcount = 0;
			over.motaddcount = 0;
		}

		if(CheckSoundMem(voice) == 0) {
			if(gPad._gTrg[0] & PAD_INPUT_4) {
				SceneBase* gScene = new SceneTest();
				ChangeScene(gScene);
			}
		}
	
};

void SceneGameOver::Draw() {

	DrawGraph((1920 - 1000) / 2, (1080 - 200) / 2, gameover_handle[over.motaddcount], true);
	DrawGraph(0, 0, chara_serif, true);

};