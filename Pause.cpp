/*****************************************************************//**
 * \file   Pause.cpp
 * \brief  ポーズ
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
 //通常∞　貫通20　反射50　黒10　白ポ10　黒ポ10
#include "Pause.h"
#include "dxlib.h"
#include "gamemain.h"
#include "mymath.h"
#include "SceneTest.h"
#include "main.h"
#include "SceneTitle.h"

Pause::Pause() {

	num_size_big_x = 35;
	num_size_big_y = 40;
	num_size_min_x = 17;
	num_size_min_y = 26;

	for (int i = 0; i < BOX_MAX; i++) {
		box[i].x = 800;
		box[i].y = 240;
		box[i].w = 60 * 6;
		box[i].h = 60 * 2;
		brend_box[i] = 0;
		time[i] = 0.0f;
		brend_box_time[i] = 0;
		gauge_time[i] = 0;
		bullet_parcent[i] = 0;
		
	}

	for (int i = 0; i < SELECT_BOX_MAX; i++) {
		select_box_time[i] = 0;
		select_brend_box = 0;
		select_box[i].x = 800 + 300 * i;
		select_box[i].y = 900;
		select_box[i].w = 60 * 4;
		select_box[i].h = 60 * 2;

		select_handle_count[i] = 0;
	}

	for (int i = 0; i < 2; i++) {
		instructions_handle_count[i] = 0;
	}

	brend = 0;

	screen_count = 0;

	select_count = 0;

	instructions = 0;

	use = 0;

	old_count = 0;

	waitcount = 0;

	instructions_count = 0;

	flashing = 255;
	hang = -1;

}

Pause::~Pause() {

}

void Pause::PauseInit() {
	//ポーズを消した時の初期化
	
	for(int i = 0; i < BOX_MAX; i++) {
		box[i].x = 800;
		box[i].y = 240;
		box[i].w = 60 * 6;
		box[i].h = 60 * 2;
		brend_box[i] = 0;
		time[i] = 0;
		bullet_parcent[i] = 0;
		gauge_time[i] = 0;
		
		brend_box_time[i] = 0;
	}
	
	
	for(int i = 0; i < SELECT_BOX_MAX; i++) {
		select_box_time[i] = 0;
		select_brend_box = 0;
		select_box[i].x = 800 + 300 * i;
		select_box[i].y = 900;
		select_box[i].w = 60 * 4;
		select_box[i].h = 60 * 2;
	}

	brend = 0;

	screen_count = 0;

	select_count = 0;

	instructions = 0;

	use = 0;

	flashing = 255;

}

void Pause::Process(int* pause, int hp, int hp_stock, int normal, int riflect, int trust, int wpo, int bpo, int hp_max, int max_normal, int max_riflect, int max_trust, int max_wpo, int max_bpo) {
	//ポーズ画面の処理
	
	if (*pause == 0) {
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		brend = 0;
	}

        //------------------------------------------------------------

	if (*pause == 1) {

		screen_count++;

		//------------------------------------------------------------


		old_count = screen_count;

		old_count -= 20;
		if (old_count >= 0) {
			if (brend <= 255) {
				brend += 4.250;
			}
		}

		old_count -= 30;//キャラ描写空の合間

		for (int i = 0; i < BOX_MAX; i++) {
			//文字のフェードイン
			if (old_count - 10 * i >= 0) {
				if (brend_box[i] <= 255) {
					brend_box[i] += 25.50;
					if (time[i] < 10) { time[i]++; }

				}
			}
			//ゲージのいーじんぐの処理
			if (old_count - 10 - 10 * i >= 0) {
				if (gauge_time[i] < 30) { gauge_time[i]++; }
				switch (i) {
				case 0: {
					GaugeProcess(hp + (hp_stock * 100), hp_max, i, gauge_time[i]);//hp
					break;
				}
				case 1: {
					GaugeProcess(normal, max_normal, i, gauge_time[i]);//normal
					break;
				}
				case 2: {
					GaugeProcess(riflect, max_riflect, i, gauge_time[i]);//riflect
					break;
				}
				case 3: {
					GaugeProcess(trust, max_trust, i, gauge_time[i]);//trust
					break;
				}
				case 4: {
					GaugeProcess(max_wpo, max_wpo, i, gauge_time[i]);//wpo
					break;
				}
				case 5: {
					GaugeProcess(max_bpo, max_bpo, i, gauge_time[i]);//bpo
					break;
				}
				}
			}
		}

		old_count -= 50 + 20;//キャラ描写空の合間

		for (int i = 0; i < SELECT_BOX_MAX; i++) {
			if (old_count - 20 >= 0) {
				if (select_brend_box <= 255) {
					select_brend_box += 11.25;
				}
			}
		}
		old_count -= 40;//キャラ描写空の合間

		//ここから動かせるようになる
		if (old_count >= 0) {
			use = 1;
		}

		//----------------------------------------
		if (use == 0) {
			if (gPad._gTrg[0] & PAD_INPUT_4) {
				screen_count += 180;
			}
		}


		if (use == 1) {
			if (instructions == 0) {

				flashing += ((float)225 / 60) * hang;
				if (flashing >= 255) {
					hang = -1;
				}
				else if (flashing <= 0) {
					hang = 1;
				}

				if (gPad._gTrg[0] & PAD_INPUT_LEFT) {
					_music->MakeSe(_image->Se[21]);
					flashing = 255;
					select_count--;
				}
				if (gPad._gTrg[0] & PAD_INPUT_RIGHT) {
					_music->MakeSe(_image->Se[21]);
					flashing = 255;
					select_count++;
				}
				if (select_count < 0) {
					select_count = 2;
				}
				else if (select_count > 2) {
					select_count = 0;
				}

				if (instructions == 0) {
					if (gPad._gTrg[0] & PAD_INPUT_4) {
						_music->MakeSe(_image->Se[22]);
						if (select_count == 0) {
							instructions = 1;
						}
						else if (select_count == 1) {
							instructions = 2;
						}
						else if (select_count == 2) {
							instructions = 3;
						}
						waitcount = 20;
					}
				}
			}
		}


		//--------------------------------------------
		//ゲームメインに戻ったときに初期化をする
		if (instructions == 0 && use == 1) {
			if (gPad._gTrg[0] & PAD_INPUT_3) {
				*pause = 0;
				PauseInit();
			}
		}
		//-------------------------------------------------123
		//ポーズのセレクト画面に戻す
		if (instructions != 0) {
			if (waitcount < 0) {
				if (gPad._gTrg[0] & PAD_INPUT_3) {
					_music->MakeSe(_image->Se[23]);
					instructions = 0;
				}
			}
			else {
				waitcount--;
			}
		}
		//------------------------------------------------　2
		if (instructions == 2) {//設定画面を描画と処理
			if (waitcount < 0) {
				option.Process();
			}
		}
		//-----------------------------------------------　3
		//タイトルに戻る処理
		if (instructions == 3) {
			if (waitcount < 0) {
				if (gPad._gTrg[0] & PAD_INPUT_LEFT) {
					_music->MakeSe(_image->Se[21]);
					instructions_count --;
				}
				if (gPad._gTrg[0] & PAD_INPUT_RIGHT) {
					_music->MakeSe(_image->Se[21]);
					instructions_count++;
				}
			}

			if (instructions_count > 1) {
				instructions_count = 0;
			}
			else if (instructions_count < 0) {
				instructions_count = 1;
			}

		}

		SelectMove(select_count, instructions, instructions_count);

		
		if (instructions == 3) {
			if (waitcount < 0) {
				if (gPad._gTrg[0] & PAD_INPUT_4) {
					_music->MakeSe(_image->Se[22]);
					if (instructions_count == 0) {
						instructions_handle_count[0] = 2;
						for (int i = 0; i < 8; i++) {
							if (CheckSoundMem(_image->Bgm[i]) == 1) {
								StopSoundMem(_image->Bgm[i]);
							}
						}
						_Fade->SetSceneChange(0);
						_Fade->SetType(0);
						_image->SetLoadComplet(0);
						_FadeSound->change_volume.clear();
						_Save->SaveInit();
						ClearDrawScreen();
						SceneBase* gScene = new SceneTitle;
						ChangeScene(gScene);
					}
					else {
						instructions = 0;
						instructions_handle_count[1] = 2;
					}
				}
			}
		}
	}
}

void Pause::SelectMove(int select, int instructions,int instructions_count) {
	//点滅の処理
	for (int i = 0; i < 3; i++) {
		select_handle_count[i] = 0;
	}
	for (int i = 0; i < 2; i++) {
		instructions_handle_count[i] = 0;
	}
	switch (instructions) {
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
		}
		break;
	case 1:
	case 2:
	case 3:
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
		}
		switch (instructions_count) {
		case 0:
			instructions_handle_count[0] = 1;
			break;
		case 1:
			instructions_handle_count[1] = 1;
			break;
		}
		break;
	}
	}
}

//ゲージのイージング処理
void Pause::GaugeProcess(int now_bullet_nam, int max_bullet_nam, int i, float time) {
	int flame = 30;
	int percent = (now_bullet_nam * 100) / max_bullet_nam;
	int percent_over = ((now_bullet_nam - max_bullet_nam )* 100) / max_bullet_nam;

	bullet_parcent[i] = EasingOutExpo(time, 0, percent, flame );
}

void Pause::Draw(int pause) {
	if (pause == 1) {
		DrawGraph(0, 0, _image->GetPause_Handle(), true);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, brend);
		DrawGraph(230, 60, _image->GetName_Handle(), true);
		DrawGraph(300, 150, _image->GetCharaHandle(), true);
		DrawGraph(775, 90, _image->GetPurpose_Handle(), true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		for (int i = 0; i < BOX_MAX; i++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, brend_box[i]);
			//--------------------
			//HPと武器のハンドルの表示
			if (i < 3) {
				DrawGraph(box[i].x, box[i].y + ((box[i].h + 90) * (i % 3)), _image->GetBox_Handle(i), true);
				DrawCircleGauge(box[i].x + 358, box[i].y + 100 + ((box[i].h + 90) * (i % 3)), bullet_parcent[i], _image->GetParcent_Gauge());//+358は画像の左上からゲージの位置までの横の長さ　+100は画像の左上からゲージの位置までの縦のながさ
			}
			else if (3 <= i) {
				DrawGraph(box[i].x + box[i].w + 150, box[i].y + ((box[i].h + 90) * (i % 3)), _image->GetBox_Handle(i), true);
				DrawCircleGauge(box[i].x + box[i].w + 358 + 150, box[i].y + 100 + ((box[i].h + 90) * (i % 3)), bullet_parcent[i], _image->GetParcent_Gauge());//+150は画像の隙間の横の長さ　+100は画像の隙間の縦の長さ
			}

			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

		}
		//選択画面の描画
		for (int i = 0; i < SELECT_BOX_MAX; i++) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, select_brend_box);

			for (int i = 0; i < 3; i++) {
				DrawGraph(select_box[i].x, select_box[i].y, _image->GetSelect_Box_Handle(i,select_handle_count[i]), true);
			}



			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		//選択画面の明滅
		if (use == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, flashing);
			switch (select_count) {
			case 0:
				DrawGraph(select_box[0].x, select_box[0].y, _image->GetSelect_Box_Handle(0,2), true);
				break;
			case 1:
				DrawGraph(select_box[1].x, select_box[1].y, _image->GetSelect_Box_Handle(1,2), true);
				break;
			case 2:
				DrawGraph(select_box[2].x, select_box[2].y, _image->GetSelect_Box_Handle(2,2), true);
				break;
			}
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, flashing);
		}
	}
}

void Pause::BulletDraw(int pause, int hp, int hp_stock ,int normal, int riflect, int trust, int wpo, int bpo,int hp_max ,int max_normal, int max_riflect, int max_trust, int max_wpo, int max_bpo){
	if(pause == 1) {
		//銃弾の表示

			for(int i = 0; i < BOX_MAX; i++) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, brend_box[i]);
				if(brend_box[i] >= 255) {
					if(brend_box_time[i] < 30) {
						brend_box_time[i]++;
					}
				}
				if(i == 0) {
					BalletNumDraw(box[i].x + 105, box[i].y + 98 + ((box[i].h + 90) * (i % 3)), hp + ( hp_stock * 100));
					BalletNumDraw(box[i].x + 222 , box[i].y + 98 + ((box[i].h + 90) * (i % 3)), hp_max);
					  ParcentDraw(box[i].x + 354, box[i].y + 87 + ((box[i].h + 90) * (i % 3)), hp + (hp_stock * 100), hp_max, brend_box_time[i]);
				}
				if(i == 1) {
					BalletNumDraw(box[i].x + 150, box[i].y + 120 + ((box[i].h + 90) * (i % 3)), normal);
					BalletNumDraw(box[i].x + 240, box[i].y + 120 + ((box[i].h + 90) * (i % 3)), max_normal);
					  ParcentDraw(box[i].x + 354, box[i].y + 87 + ((box[i].h + 90) * (i % 3)), normal, max_normal, brend_box_time[i]);
				}
				if(i == 2) {
					BalletNumDraw(box[i].x + 150, box[i].y + 120 + ((box[i].h + 90) * (i % 3)), riflect);
					BalletNumDraw(box[i].x + 240, box[i].y + 120 + ((box[i].h + 90) * (i % 3)), max_riflect);
					  ParcentDraw(box[i].x + 354, box[i].y + 87 + ((box[i].h + 90) * (i % 3)), riflect, max_riflect, brend_box_time[i]);
				}
				if(i == 3) {
					BalletNumDraw(box[i].x + box[i].w + 150 + 150 , box[i].y + 120 + ((box[i].h + 90) * (i % 3)), trust);
					BalletNumDraw(box[i].x + box[i].w + 240 + 150, box[i].y + 120 + ((box[i].h + 90) * (i % 3)), max_trust);
				      ParcentDraw(box[i].x + box[i].w + 150  + 354, box[i].y + 87 + ((box[i].h + 90) * (i % 3)), trust, max_trust, brend_box_time[i]);
				}
				if(i == 4) {
					DrawGraph(box[i].x + box[i].w + 150 + 150 - 17.5, box[i].y + 120 + ((box[i].h + 90) * (i % 3)), _image->GetInf_W(), true);
					DrawGraph(box[i].x + box[i].w + 150 + 240 - 17.5, box[i].y + 120 + ((box[i].h + 90) * (i % 3)), _image->GetInf_W(), true);
					  ParcentDraw(box[i].x + box[i].w + 150  +354, box[i].y + 87 + ((box[i].h + 90) * (i % 3)), wpo, max_wpo, brend_box_time[i]);
				}
				if(i == 5) {
					DrawGraph(box[i].x + box[i].w + 150 + 150 - 17.5, box[i].y + 120 + ((box[i].h + 90) * (i % 3)), _image->GetInf_W(), true);
					DrawGraph(box[i].x + box[i].w + 150 + 240 - 17.5, box[i].y + 120 + ((box[i].h + 90) * (i % 3)), _image->GetInf_W(), true);
					ParcentDraw(box[i].x + box[i].w + 150 + 354, box[i].y + 87 + ((box[i].h + 90) * (i % 3)), bpo, max_bpo, brend_box_time[i]);
				}
			}
		
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void Pause::OptionDraw(int pause) {
	
	if(pause == 1) {
		if(waitcount < 0) {
			if(instructions == 1) {
				//操作説明画面の描画
				DrawGraph( 0, 0, _image->GetControle_Handle(), true);
			}
			else if(instructions == 2) {
				//設定画面を描画
				option.Draw();
			}
			else if(instructions == 3) {
				if(waitcount < 0) {
					//タイトル画面のyesnoの描画
					DrawGraph(0, 0, _image->GetEnd_Bg(), true);
					DrawGraph((1920 - 372 - 300) / 2, (1080 - 71) / 2, _image->GetYes_Handle(instructions_handle_count[0]), true);
					DrawGraph((1920 - 372 + 300) / 2, (1080 - 71) / 2, _image->GetNo_Handle(instructions_handle_count[1]), true);
				}
			}
		}
	}
}

void Pause::BalletNumDraw(int x, int y, int bullet_num) {
	//銃弾の表示
	int bullet = bullet_num;
	if(bullet_num <= 0) { bullet = 0; }
	int one = bullet % 10;
	int ten = (bullet / 10) % 10;
	int handred = (bullet / 100) % 10;
	int thousand = (bullet / 1000) % 10;

	int w = num_size_big_x;//フォントの横の長さ

	DrawGraph(x, y, _image->GetNumber_Big(one), true);
	DrawGraph(x - w + 7, y, _image->GetNumber_Big(ten), true);
	if(handred > 0) {
		DrawGraph(x - w * 2 + 14, y, _image->GetNumber_Big(handred), true);
	}
	if(thousand > 0) {
		DrawGraph(x - w * 3 + 21, y, _image->GetNumber_Big(thousand), true);
	}
}

void Pause::ParcentDraw(int x, int y, int now_bullet, int max_bullet, int time) {
	//銃弾の割合の描画
	int flame = 30;
	int num = now_bullet * 100 / max_bullet;

    int parcent = EasingOutExpo(time, 0, num, flame);

	if(time == flame) {
		if(now_bullet > 0) {
			parcent = parcent + 1;
		}
	}

	if(now_bullet <= 0) {
		parcent = 0;
	}

	int one = parcent % 10;
	int ten = (parcent / 10) % 10;
	int handred = (parcent / 100) % 10;

	int w = num_size_min_x;
	if(handred > 0) {
		DrawGraph(x, y, _image->GetNumber_Min(one), true);
		DrawGraph(x - w, y, _image->GetNumber_Min(ten), true);

		DrawGraph(x - w * 2, y, _image->GetNumber_Min(handred), true);

		DrawGraph(x + w, y, _image->GetParcent_Handle(), true);
	}
	
	else {
		int gap = -7;
		DrawGraph(x + gap, y, _image->GetNumber_Min(one), true);
		DrawGraph(x + gap - w, y, _image->GetNumber_Min(ten), true);
		DrawGraph(x + gap + w, y, _image->GetParcent_Handle(), true);
	}

}