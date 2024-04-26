/*****************************************************************//**
 * \file   SceneMovie.cpp
 * \brief  ムービーシーン
 *
 * \author 齋藤 瑚羽
 * \date  August 2023
 *********************************************************************/

#include "SceneMovie.h"
#include "dxlib.h"
#include "gamemain.h"
#include "SceneTitle.h"
#include "main.h"


SceneMovie::SceneMovie() {




	movie_handle = LoadGraph("res/opening.mp4");

	loading = LoadGraph("res/skip.png");

	logo_handle = LoadGraph("res/AMGlogo.png");




	SetUseASyncLoadFlag(TRUE);
	_image->TitleLoad();
	SetUseASyncLoadFlag(FALSE);

	Fade = 0;
	FadeLogo = 0;

	Logocount = 0;
	FadeOut = 0;
	FadeLoad = 0;

	

};

SceneMovie::~SceneMovie() {
	DeleteGraph(movie_handle);
	DeleteGraph(loading);
	DeleteGraph(logo_handle);
};

void SceneMovie::FadeProcess() {
	float* ptr = nullptr;
	int count = 0;
	int hang = 0;
	if (Logocount < 245) {
		Logocount++;
		for (int i = 0; i < 5; i++) {
			if (Logocount >= (60 * i) + 1) {
				count = i;
			}
		}

		switch (count) {
		case 0: {
			ptr = &FadeLogo;
			hang = 1;
			break;
		}
		case 2: {
			ptr = &FadeLogo;
			hang = -1;
			break;
		}
		case 3: {
			ptr = &FadeOut;
			hang = 1;
			break;
		}
		}
	}

	if (ptr != nullptr) {
		*ptr += (float)255 / 60 * hang;
		if (*ptr <= 0) {
			if (GetMovieStateToGraph(movie_handle) == 0) {
				PlayMovieToGraph(movie_handle);
			}
		}
	}

};

void SceneMovie::Process() {

	FadeProcess();

	if (GetASyncLoadNum() <= 0) {
		if (GetMovieStateToGraph(movie_handle) == 1) {
			if (FadeLoad < 255) {
				FadeLoad += (float)255 / 60;
			}
			else {
				if (gPad._gTrg[0] & PAD_INPUT_12) {
					PauseMovieToGraph(movie_handle);
				}
			}
		}
	}
	

	if (GetMovieStateToGraph(movie_handle) == 0 && FadeLogo <= 0) {
		if (FadeOut > 0) {
			FadeOut -= 4.25;
			FadeLoad -= 4.25;
		}
		else if (FadeOut <= 0) {
			_image->SetLoadComplet(0);
			SceneBase* gScene = new SceneTitle;
			ChangeScene(gScene);
		}
	}

	_image->LoadingProcess();

};

void SceneMovie::Draw() {
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, FadeLogo);
	DrawGraph(0, 0, logo_handle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, FadeOut); 
	DrawGraph(0, 0, movie_handle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, FadeLoad);

	if (GetASyncLoadNum() <= 0 ) {
		DrawGraph(0, 0, loading, true);
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
};