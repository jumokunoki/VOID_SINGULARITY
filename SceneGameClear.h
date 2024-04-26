/*****************************************************************//**
 * \file   SceneGameClear.h
 * \brief  ゲームクリア
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#pragma once
#include "SceneBase.h"
#include "dxlib.h"
#include "gamemain.h"
class SceneGameClear : public SceneBase
{
public:
	 SceneGameClear();
	~SceneGameClear();

	void Process();
	int  CheckVoiceAll();//ボイスが流れているかを確認する
	void StopProcess();//ストップになっているかつボイスが流れているかを確認する
	void Flow_Process(int count);//全体の動き
	void Draw();
protected:
	float _Fade[5];//画像のフェードで使う変数
	int    hang[5];//フェードの掛け算で使う変数
	int flow_count;//クリア画面の流れ制御するもの
	int handle_count;//画像番号を入れる変数
	int movie_flag;//動画が再生されたかを確認するフラグ
	int voice[4];//ボイスを格納する変数
	int voice_num;//ボイスを流したら+1
	int stop;//ボイスが流れている間は処理を止める
	int stop_order;//ボイスが流れているかを確認する変数
};

