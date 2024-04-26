/*****************************************************************//**
 * \file   Fade.h
 * \brief  フェード
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#pragma once
#include "gamemain.h"
class Fades
{
public:
	Fades();
	~Fades();
	void    FadeSet(int in_out, int color_type, int frame, int type);
	void     CharaFadeSet();
	void    FadeProcess();
	int     CheckFadeMove();
	void PortalIn(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int GrHandle, int Color, int turn);
	void    SetSceneChange(int index) { Fade.scene_change = index; }
	void    SetType(int index) { Fade.type = index; }
	int     GetType() { return Fade.type; }
	int     GetScene_Change() { return Fade.scene_change; }

	struct FADE {
		float _FadeIn;//フェードイン
		int FadeColor;//フェードボックスの色
		int hang;//上がり下がり
		int all_fade_count;//何フレームでMAXにするか
		int add_frame;//枚フレーム足す
		int scene_change;
		int type;
	};

	FADE Fade;
	FADE chara_fade;

};

