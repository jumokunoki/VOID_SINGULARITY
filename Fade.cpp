/*****************************************************************//**
 * \file   Fade.cpp
 * \brief  フェード
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#include "Fade.h"
#include "dxlib.h"
#include "mymath.h"

Fades::Fades() {

	Fade.scene_change = 0;
	Fade.type = 0;
	Fade._FadeIn = 255;
	Fade.FadeColor = 0;
	Fade.hang = 0;
	Fade.all_fade_count = 0;
	Fade.add_frame = 0;

	chara_fade.scene_change = 0;
	chara_fade.type = 0;
	chara_fade._FadeIn = 0;
	chara_fade.FadeColor = 0;
	chara_fade.hang = 1;
	chara_fade.all_fade_count = 0;
	chara_fade.add_frame = 0;

};

Fades::~Fades() {

};

void Fades::FadeSet(int in_out, int color_type, int frame, int type) {

	// in_out    0:in   1:out          color_type 0:black  1:white
	if(Fade.add_frame >= Fade.all_fade_count && Fade.type == 0) {
		Fade.add_frame = 0;
		Fade.type = type;
		switch(color_type) {
		case 0:
			Fade.FadeColor = GetColor(0, 0, 0);
			break;
		case 1:
			Fade.FadeColor = GetColor(255, 255, 255);
			break;
		}

		switch(in_out) {
		case 0:
			Fade.hang = -1;
			Fade.all_fade_count = frame;
			Fade._FadeIn = 255;
			break;
		case 1:
			Fade.hang = 1;
			Fade.all_fade_count = frame;
			Fade._FadeIn = 0;
			break;
		}
	}
};

void Fades::CharaFadeSet() {
	if (chara_fade.add_frame >= chara_fade.all_fade_count) {
		chara_fade.add_frame = 0;
		chara_fade.all_fade_count = 30;
		chara_fade._FadeIn = 0;
	}
}

void Fades::FadeProcess() {

	if (chara_fade.add_frame <= chara_fade.all_fade_count) {
		chara_fade.add_frame++;
		float add = (float)255 / (float)chara_fade.all_fade_count;
		chara_fade._FadeIn += add * chara_fade.hang;
	}
	else {
		chara_fade._FadeIn = 0;
	}

	if(Fade.add_frame <= Fade.all_fade_count) {
		Fade.add_frame++;
		float add = (float)255 / (float)Fade.all_fade_count;
		Fade._FadeIn += add * Fade.hang;
	}
	switch(Fade.type) {
	case 0: {
		//何もしない
		break;
	}
	case 1: {
		//クリアの処理
		if(Fade._FadeIn >= 255) {
			StopSoundMem(_image->Bgm[7]);
			if(Fade.add_frame++ >= Fade.all_fade_count * 2) {
				Fade.hang *= -1;
				Fade.add_frame = 0;
				Fade.scene_change = 1;
			}
		}
		break;
	}
	case 2: {
		if(Fade._FadeIn >= 255 ) {
			Fade._FadeIn = 0;
			//ゲームオーバーに移動
			Fade.scene_change = 2;
		}
		break;
	}
	case 3: {
		if(Fade._FadeIn >= 255) {
			Fade.hang *= -1;
			Fade.add_frame = 0;
			Fade.scene_change = 3;
		}
		else if (Fade.hang == -1) {
			if (Fade._FadeIn <= 0) {
				//チュートリアルに移動
				Fade.scene_change = 4;
			}
		}
		break;
	}
	case 4: {
		break;
	}
	}

	if(Fade._FadeIn >= 255) {
		Fade._FadeIn = 255;
	}

	if(Fade._FadeIn <= 0) {
		Fade._FadeIn = 0;
	}
};

int  Fades::CheckFadeMove() {
	//フェードが三割以上か確認するための関数
	if(Fade.add_frame < (float)Fade.all_fade_count * (float)0.3f) {
		return 0;
	}
	return 1;
};

void Fades::PortalIn(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int GrHandle, int Color, int turn)
{
	// 回転×拡縮×並行移動
	MATRIX mRot = MGetRotZ(angle);						// 2Dでx,yを回転させるには、3DならZ軸回転になる
	MATRIX mScale = MGetScale(VGet(zoom, zoom, 1));		// Z方向の倍率は1のまま
	MATRIX mTrans = MGetTranslate(position);
	MATRIX m;
	m = MMult(mRot, mScale);
	m = MMult(m, mTrans);
	m = MMult(m, mView);

	// 描画する画像の4つの頂点座標
	VECTOR pos[4] = {
		// 通常用（左上から右回り）
		VGet(-width / 2.0, -height / 2.0, 0),	// 左上
		VGet(width / 2.0, -height / 2.0 ,0),	// 右上
		VGet(width / 2.0,  height / 2.0 ,0),	// 右下
		VGet(-width / 2.0,  height / 2.0 ,0),	// 左下
	};

	// 4つの頂点座標全てに行列を掛けて変換する
	for (int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}

	// Ｚバッファを有効にする
	SetUseZBufferFlag(TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, chara_fade._FadeIn);


	// Ｚバッファに画像と同じ大きさのマスクを書き込む
	DrawBoxToZBuffer(pos[0].x, pos[0].y, pos[2].x, pos[2].y, TRUE, DX_ZWRITE_MASK);

	// Ｚバッファに画像の形でマスクを刳り貫く
	DrawExtendGraphToZBuffer(pos[0].x, pos[0].y,  pos[2].x, pos[2].y, GrHandle, DX_ZWRITE_CLEAR);

	// 画像の大きさのボックスを描画する(マスクが刳り貫かれているところしか塗りつぶされない)
	DrawBox(pos[0].x, pos[0].y, pos[2].x, pos[2].y, Color, TRUE);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// Ｚバッファを無効にする
	SetUseZBufferFlag(FALSE);
}

//void  Fades::PortalIn(int x, int y, int GrHandle, int Color)
//{
//	int w, h;
//
//	// 画像のサイズを取得する
//	GetGraphSize(GrHandle, &w, &h);
//
//	// Ｚバッファを有効にする
//	SetUseZBufferFlag(TRUE);
//
//	// Ｚバッファに画像と同じ大きさのマスクを書き込む
//	DrawBoxToZBuffer(x, y, x + w, y + h, TRUE, DX_ZWRITE_MASK);
//
//	// Ｚバッファに画像の形でマスクを刳り貫く
//	DrawGraphToZBuffer(x, y, GrHandle, DX_ZWRITE_CLEAR);
//
//	// 画像の大きさのボックスを描画する(マスクが刳り貫かれているところしか塗りつぶされない)
//	DrawBox(x, y, x + w, y + h, Color, TRUE);
//
//	// Ｚバッファを無効にする
//	SetUseZBufferFlag(FALSE);
//}