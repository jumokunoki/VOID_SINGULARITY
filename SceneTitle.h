/*****************************************************************//**
 * \file   SceneTitle.h
 * \brief  タイトル
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "gamemain.h"
#include "SceneBase.h"
#include "Option.h"
#include "DxLib.h"


class SceneTitle : public SceneBase
{

public:
	SceneTitle();			// コンストラクタ
	virtual ~SceneTitle();	// デストラクタ

	void SoundInit();       // 音の読み込み
	void ImageInit();       // 画像読み込み

	void SelectMove(int select ,int title,int wait , int extra);//明滅の処理
	virtual void	Process();	// 計算
	virtual void	Draw();		// 描画

protected:
#define EFFECT_CG_MAX 600
	int _cgBg;
	int effectcg[EFFECT_CG_MAX]; //背景
	int Se[4];
	int Bgm;
	int waitcount;

	char size[43];
	int effect_load_count;

	int effect_count;//パーティクルを動かすときの変数
	int character_handle;   //メイン主人公の描画ハンドル
	int title_handle;//タイトルロゴの画像ハンドル
	int controle_Handle;//操作画面の画像ハンドル
	int start_handle[3];//タイトル画面の画像ハンドル
	int command_handle[7][3];//選択画面のハンドル
	int select_count;//セレクトタイプが入る
	int select_handle_count[7];//
	int title_count;//ゲームスタート以外の画像描画の判定に使うが押されたときに1にする
	int extra_count;//スタッフロールやタイトルムービーで使うカウント
	int any_button;//any_startで使う変数
	float any_button_fade;//タイトル画面から選択画面に切り替えるときのフェード
	int copy_light_handle;//コピーライトのハンドル

	int handle_x, handle_y;//選択画面の画像の位置
	int select_x, select_y;//選択画面の画像の位置


	float FadeIn; //フェードに使う
	float FadeOut;//フェードに使う
	float flashing;//フェードに使う
	int   hang;//フェードに掛けて足したり引いたりするのに使う
	int   any_hang;//タイトル画面のフェード
	int   FadeCount;//フェードアウトをするときにフラグを1にする
	
	struct EFFECT {
		VECTOR pos;
		float direction;
	};

	ANIMCNT anim[2];

	MOTION hand;
	Option option;

};

