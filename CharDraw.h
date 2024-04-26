/*****************************************************************//**
 * \file   CharDraw.h
 * \brief  文字描画
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#pragma once
#include <iostream>
#include "relay_point.h"
#include "ScriptText.h"


class CharDraw
{
public:
	CharDraw();
	~CharDraw();

	void NameProcess(int num);//名前を設定する関数
	void SetTutorial(int change);//チュートリアルのセット
	void Process(int change);
	void Draw(int clear);
	int SearchLetter(std::string text, int byte);//文字のバイト数を調べる関数
	void Init();//シナリオを流した後の初期化
	void AllInit();//シーン切り替えのすべての初期化
	//ゲッターセッター
	void SetLine() { line = 0; }
	void SetScenario(int index) { scenario = index;}
	void SetTalkScene(int index) { talk_scene = index; }
	int  GetTalkScene() { return talk_scene; }
	int  GetScenario() { return scenario; }

	int  GetProcessStop() { return process_stop; }
	void SetProcessStop() { process_stop = 1; }

protected:
	int scenario;//シナリオタイプ　1：シナリオ　2：チュートリアル
	int count;
	int get_se;//seの再生
	int index;//文字の読み込み
	int line;//読み込んでいる行数
	int talk_scene;//何個目のtextを読んでいるか

	int process_stop;//プレイヤーの移動を不可にする変数

	int VoiceMem[2];//声優さんボイスの格納変数

	int read_stage_text[TALK_SCENE_MAX][100];//シナリオを読んだらその番号を一にする

	std::string copy;//テキストのコピー先
	char name[128];//名前を格納する配列

	float x, y, direction;
};

