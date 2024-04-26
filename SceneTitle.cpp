/*****************************************************************//**
 * \file   SceneTitle.cpp
 * \brief  タイトル
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#include "SceneTitle.h"
#include "DxLib.h"
#include "gamemain.h"
#include "SceneTest.h"
#include "SceneMovie.h"
#include "Option.h"
#include "main.h"
#include <math.h>


SceneTitle::SceneTitle() {

	effect_load_count = 0;

	flashing = 0;
	hang = 1;

	hand.motcount = 0;
	hand.motaddcount = 13;
	hand.motspeed = 4;
	hand.motseet  = 91*2;

	
	ImageInit();
	SoundInit();

	_music->MakeBgm(Bgm);
	_music->MakeBgm(Se[3]);

	GetGraphSize(command_handle[0][0], &select_x, &select_y);

	GetGraphSize(controle_Handle, &handle_x, &handle_y);

	select_count = 0;
	extra_count = 0;
	any_button = 0;
	any_button_fade = 255;
	any_hang = -1;
	FadeIn = 255;
	FadeOut = 0;

	FadeCount = 0;
	for(int i = 0; i < 2; i++) {
		anim[i].count = 0;
	}

	for(int i = 0; i < 7; i++) {
		select_handle_count[i] = 0;
	}
	select_handle_count[0] = 1;

	anim[0].use = 1;
	anim[1].use = 0;

	
	title_count = 0;


	effect_count = 0;
	waitcount = 0;

}

SceneTitle::~SceneTitle() {
	for(int i = 0; i < EFFECT_CG_MAX; i++) {
		DeleteGraph(effectcg[i]);
	}
	DeleteGraph(character_handle);
	DeleteGraph(controle_Handle);

	DeleteSoundMem(Bgm);
	for(int i = 0; i < 4; i++) {
		DeleteSoundMem(Se[i]);
	}
}


void SceneTitle::SelectMove(int select, int title, int wait, int extra) {
	for (int i = 0; i < 7; i++) {
		select_handle_count[i] = 0;
	}
	switch (title) {
	case 0:
		switch (select) {
		case 0:
			select_handle_count[0] = 1;
			break;
		case 1:
			select_handle_count[1] = 1;
			break;
		case 2:
			select_handle_count[2] = 1;
			break;
		case 3:
			select_handle_count[3] = 1;
			break;
		case 4:
			select_handle_count[4] = 1;
			break;
		case 5:
			select_handle_count[5] = 1;
			break;
		case 6:
			select_handle_count[6] = 1;
			break;
		}
		break;
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	{
		switch (select) {
		case 0:
			select_handle_count[0] = 2;
			break;
		case 1:
			select_handle_count[1] = 2;
			break;
		case 2:
			select_handle_count[2] = 2;
			break;
		case 3:
			select_handle_count[3] = 2;
			break;
		case 4:
			select_handle_count[4] = 2;
			break;
		case 5:
			select_handle_count[5] = 2;
			break;
		case 6:
			select_handle_count[6] = 2;
			break;
		}
		break;
	}
	}
	if (wait >= 20) {
		int waitcount = wait % 10;
		switch (waitcount) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		{
			switch (select) {
			case 0:
				select_handle_count[0] = 1;
				break;
			case 1:
				select_handle_count[1] = 1;
				break;
			case 2:
				select_handle_count[2] = 1;
				break;
			case 3:
				select_handle_count[3] = 1;
				break;
			case 4:
				select_handle_count[4] = 1;
				break;
			case 5:
				select_handle_count[5] = 1;
				break;
			case 6:
				select_handle_count[6] = 1;
				break;
			}
		}

		}
	}

};

void SceneTitle::Process() {
	
	if(GetMovieStateToGraph(_image->GetStaff_Roll()) != 1) {

		_music->SetBgmVolume(Bgm);
		if(CheckSoundMem(Bgm) == 0 && GetMovieStateToGraph(_image->GetStaff_Roll()) != 1) {
			_music->MakeBgm(Bgm);
			_music->MakeBgm(Se[3]);
			SeekMovieToGraph(_image->GetStaff_Roll(), 0);
		}
		for(int i = 0; i < 4; i++) {
			_music->SetSeVolume(Se[i]);
		}

		

		effect_count++;

		if(FadeIn >= 0) {
			FadeIn -= 4.25;
		}
		else {
			for(int i = 0; i < 2; i++) {
				if(anim[i].use != 0) {
					if((effect_count % 2) == 0) {
						anim[i].count++;
					}
				}
			}
		}

		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 2; j++) {
				if(i == j) { continue; }

				if(anim[i].count >= 300 * 2 - 1) {
					anim[i].count = 0;
					anim[i].use = 0;
				}

				if(anim[i].count >= 180 * 2 - 1) {
					if(anim[j].use == 0) {
						anim[j].use = 1;
					}
				}
			}
		}

		flashing += ((float)225 / 60) * hang;
		if (flashing >= 255) {
			hang = -1;
		}
		else if (flashing <= 0) {
			hang = 1;
		}
		

		//↑共通処理
		//---------------------------------------------------
		if(any_button == 0) {
			if(waitcount <= 0) {
				if(gPad.CheckAllButton() == 1) {
					_music->MakeSe(Se[1]);
					waitcount = 60;
				}
			}
			if(waitcount > 0) {
				waitcount--;
				any_button_fade += 4.25 * any_hang;
				if(waitcount <= 0) {
					any_button = 1;
					any_hang *= -1;
					flashing = 0;
				}
			}
		}
		//---------------------------------------------------------------------
		else {
			if(any_button_fade <= 255) {
				any_button_fade += 4.25 * any_hang;
				
			}
			else {

				if(FadeCount != 0) {
					if(FadeOut <= 255) {
						FadeOut += 4.25;
					}
					else if(FadeOut >= 255) {
						StopSoundMem(Se[3]);
						StopSoundMem(Bgm);
						SceneBase* gScene = new SceneTest;
						ChangeScene(gScene);
					}
				}

				if(title_count == 0 || extra_count == 1) {

					if(gPad._gTrg[0] & PAD_INPUT_UP) {
						_music->MakeSe(Se[0]);
						select_count--;
						flashing = 255;
					}
					if(gPad._gTrg[0] & PAD_INPUT_DOWN) {
						_music->MakeSe(Se[0]);
						select_count++;
						flashing = 255;
					}
				}

				if(extra_count != 1) {
					if(select_count > 4) {
						select_count = 0;
					}
					if(select_count < 0) {
						select_count = 4;
					}
				}
				else {
					if(select_count > 6) {
						select_count = 5;
					}
					if(select_count < 5) {
						select_count = 6;
					}
				}


				if(title_count == 0) {
					if(gPad._gTrg[0] & PAD_INPUT_4) {
						_music->MakeSe(Se[1]);
						waitcount = 50;
						switch(select_count) {
						case 0:
							title_count = 1;
							break;
						case 1:
							title_count = 2;
							break;
						case 2:
							title_count = 3;
							break;
						case 3:
							title_count = 4;
							break;
						case 4:
							title_count = 5;
							break;
						case 5:
							title_count = 6;
							break;
						case 6:
							title_count = 7;
							break;
						}
					}
				}

				SelectMove(select_count, title_count, waitcount, extra_count);

				if(title_count != 0) {
					waitcount--;
					if(waitcount < 0) {
						switch(title_count) {
						case 1:
							FadeCount = 1;
							break;
						case 2:
							option.Process();
							break;
						case 3:
							break;
						case 4:
							extra_count = 1;
							title_count = 0;
							select_count = 5;
							flashing = 255;
							break;
						case 5:
							finish = 1;
							break;
						case 6: {
							StopSoundMem(Se[3]);
							StopSoundMem(Bgm);
							SceneBase* gScene = new SceneMovie;
							ChangeScene(gScene);
							break;
						}
						case 7:
							if(GetMovieStateToGraph(_image->GetStaff_Roll()) != 1) {
								_music->StopBgm(Bgm);
								SeekMovieToGraph(_image->GetStaff_Roll(), 0);
								PlayMovieToGraph(_image->GetStaff_Roll());
							}
							title_count = 0;
							break;
						}
					}
				}

				hand.motcount++;
				if (hand.motcount >= hand.motspeed) {
					hand.motcount = 0;
					hand.motaddcount++;
				}
				if (hand.motaddcount * hand.motspeed > (hand.motseet - 1) * hand.motspeed) {
					hand.motcount = 0;
					hand.motaddcount = 0;
				}


				if(title_count != 0 || extra_count == 1) {
					if(gPad._gTrg[0] & PAD_INPUT_3) {
						_music->MakeSe(Se[2]);
						title_count = 0;
						if(extra_count != 0) {
							extra_count = 0;
						}
					}
				}
			}
		}
	}
	else {
		if(gPad._gTrg[0] & PAD_INPUT_4) {
			PauseMovieToGraph(_image->GetStaff_Roll());
		}
	}
	
}
//クレジット　
void SceneTitle::Draw() {
	
	if (GetASyncLoadNum() <= 5) {
		if(GetMovieStateToGraph(_image->GetStaff_Roll()) != 1) {

			DrawGraph(0, 0, _cgBg, true);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, any_button_fade);

			if(any_button == 0) {
				DrawGraph((SCREEN_W - 1000) / 2, (SCREEN_H - 375) / 2 - 200, title_handle, true);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, flashing);
				DrawGraph((SCREEN_W - select_x) / 2+50, (SCREEN_H - select_y) / 2 + 200, start_handle[1], true);
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, any_button_fade);
				if(waitcount > 0) {
					if(waitcount % 10 >= 5 || waitcount <= 20) {
						DrawGraph((SCREEN_W - select_x) / 2 + 50, (SCREEN_H - select_y) / 2 + 200, start_handle[2], true);
					}
				}
				DrawGraph((SCREEN_W - select_x) / 2+50, (SCREEN_H - select_y) / 2 + 200, start_handle[0], true);
			}
			else {

				//メインキャラクター
				DrawGraph(60, 0, character_handle, true);
				//タイトルロゴ
				DrawGraph(790, 50, title_handle, true);


				if(extra_count != 1) {
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 430 + 10 , command_handle[0][select_handle_count[0]], true);
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 550 +  5 , command_handle[1][select_handle_count[1]], true);
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 670 - 10 , command_handle[2][select_handle_count[2]], true);
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 790 - 25 , command_handle[3][select_handle_count[3]], true);
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 910 - 30 , command_handle[4][select_handle_count[4]], true);
				}
				else {
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 430 + 30 - 20, command_handle[5][select_handle_count[5]], true);
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 550 + 25 - 20, command_handle[6][select_handle_count[6]], true);
				}

				DrawGraph((SCREEN_W - select_x) / 2 + 590, 1030 + 10, copy_light_handle, true);

				if (hand.motaddcount < 91) {
					DrawGraph(0, 0, _image->GetHand_Effect(hand.motaddcount), true);
				}

				SetDrawBlendMode(DX_BLENDMODE_ALPHA, flashing);
				switch (select_count) {
				case 0:
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 430 + 10 , command_handle[0][2], true);
					break;
				case 1:
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 550 +  5 , command_handle[1][2], true);
					break;
				case 2:
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 670 - 10 , command_handle[2][2], true);
					break;
				case 3:
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 790 - 25 , command_handle[3][2], true);
					break;
				case 4:
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 910 - 30 , command_handle[4][2], true);
					break;
				case 5:
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 430 + 10, command_handle[5][2], true);
					break;
				case 6:
					DrawGraph((SCREEN_W - select_x) / 2 + 320, 550 +  5, command_handle[6][2], true);
					break;
				}

				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, flashing);

			//---------------------------------------------------------------------	
			}
			
			for(int i = 0; i < 2; i++) {
				DrawGraph(0, 0, _image->GetEffectCg(anim[i].count), true);
			}

			if(title_count != 0) {
				if(waitcount < 0) {
					if(title_count == 2) {
						option.Draw();
					}
					else if(title_count == 3) {
						DrawGraph((SCREEN_W - handle_x) / 2, (SCREEN_H - handle_y) / 2, controle_Handle, true);
					}
				}
			}

			//エフェクト
			
			//フェード処理
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, FadeOut);
			if(FadeCount == 0) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, FadeIn);
			}
			DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		else {
			DrawGraph(0, 0, _image->GetStaff_Roll(), true);
		}

	}
	else {
		DrawGraph(0, 0, _image->GetLoading_Bg(), true);
		DrawGraph(1920 - 328, 1080 - 349, _image->GetLoading_Chara(), true);
	}

}

