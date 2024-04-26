/*****************************************************************//**
 * \file   Option.cpp
 * \brief  オプション設定
 *
 * \author 齋藤 瑚羽
 * \date  August 2023
 *********************************************************************/

#include "Option.h"
#include "SceneTitle.h"
#include "dxlib.h"
#include "Pause.h"
#include "mymath.h"


Option::Option() {

	color_type = 0;
	
	gauge_handle_x = 1264;
	gauge_handle_y = 120;

	border.x = 577;
	border.y = 180;
	border.h = 50;
	gauge_unit.x = 640;
	gauge_unit.y = 231;
	gauge_unit.h = 20;
	
	for (int i = 0; i < 4; i++) {
		select_bar[i] = 0;
	}
	select_bar[0] = 1;
	FadeOut = 255;

	back = 0;

	select_count = 0;

	cutin_select = 0;
}

Option::~Option() {

}


void Option::SelectProcess(int count) {
	for (int i = 0; i < 4; i++) {
		select_bar[i] = 0;
	}
	switch (count) {
	case 0: {
		select_bar[0] = 1;
		break;
	}
	case 1: {
		select_bar[1] = 1;
		break;
	}
	case 2: {
		select_bar[2] = 1;
		break;
	}
	case 3: {
		select_bar[3] = 1;
		break;
	}
	}
}
void Option::Process() {

	if(gPad._gTrg[0] & PAD_INPUT_UP) {
		select_count--;
	}

	if(gPad._gTrg[0] & PAD_INPUT_DOWN) {
		select_count++;
	}

	if(select_count > 3) {
		select_count = 0;
	}

	if(select_count < 0) {
		select_count = 3;
	}

	SelectProcess(select_count);

	if(select_count < 3) {
		if(gPad._gKey[0] & PAD_INPUT_LEFT) {
			gauge[select_count] -= 2;
		}
		if(gPad._gKey[0] & PAD_INPUT_RIGHT) {
			gauge[select_count] += 2;
		}

		if(gauge[select_count] > 255) {
			gauge[select_count] = 255;
		}
		if(gauge[select_count] < 0) {
			gauge[select_count] = 0;
		}
	}

	if (select_count == 3 && gPad._gTrg[0] & PAD_INPUT_LEFT || gPad._gTrg[0] & PAD_INPUT_RIGHT) {
		cutin_select = 1 - cutin_select;
	}

	if (select_count == 3 && gPad._gTrg[0] & PAD_INPUT_4) {
		if (cutin_select != 1) {
			cutin_swich = 0;
		}
		else {
			cutin_swich = 1;
		}
	}

	if(cutin_swich == 0) {
		color_type = GetColor(255, 0, 0);
	}
	else {
		color_type = GetColor(0, 0, 255);
	}

}

void Option::Draw() {

	DrawGraph(0, 0, _image->GetOption_Bg(), true);


	for(int i = 0; i < 3; i++) {
		DrawExtendGraph(gauge_unit.x, gauge_unit.y + 110 * i, gauge_unit.x + gauge[i] * 3.1, gauge_unit.y + gauge_unit.h + 110 * i, _image->GetGauge_Handle(), true);//ゲージ本体
		DrawGraph((1920 - gauge_handle_x) / 2, border.y + 110 * i, _image->GetGauge_Border(i, select_bar[i]), true); //ゲージの枠
		DrawGraph(gauge_unit.x + gauge[i] * 3.1, gauge_unit.y - 10 + 110 * i , _image->GetGauge_Ber(), true);//ゲージについているバーの描画

		//ボリュームがオンかオフか
		if (gauge[i] > 0) {
			DrawGraph((1920 - gauge_handle_x) / 2 + 180, border.y  + 42 + 110 * i, _image->GetSound_Switch(0), true);
		}
		else {
			DrawGraph((1920 - gauge_handle_x) / 2 + 180, border.y + 42 + 110 * i, _image->GetSound_Switch(1), true);
		}
	}
	//カットインのオンオフ
	if (select_count == 3) {
		DrawGraph((1920 - gauge_handle_x) / 2, 550, _image->GetCutin_On_Handle(cutin_select + cutin_swich * 2), true);
		DrawGraph((1920 - gauge_handle_x) / 2 + 650, 550, _image->GetCutin_Off_Handle(cutin_select + cutin_swich * 2), true);
	}
	else {
		DrawGraph((1920 - gauge_handle_x) / 2, 550, _image->GetCutin_On_Handle(cutin_swich * 2 + 1), true);
		DrawGraph((1920 - gauge_handle_x) / 2 + 650, 550, _image->GetCutin_Off_Handle(cutin_swich * 2), true);
		
	}
}