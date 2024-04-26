/*****************************************************************//**
 * \file   ScriptText.h
 * \brief  シナリオ情報
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#pragma once
#include "dxlib.h"
#include <iostream>

#define TALK_SCENE_MAX 20
#define LINE_MAX 100

struct SCRIPT_CONTENTS {
	int  left_chara;//左のキャラ
	int  left_light;//左のキャラを明るくするかの変数
	int  left_chara_back;//左のキャラのバック
	int  right_chara;//右のキャラ
	int  right_light;//右のキャラを明るくするかの変数
	int  right_chara_back;//右のキャラのバック
	int  name;//どの名前を使うかの変数
	std::string voice;//ボイスの名前を入れる変数
	std::string text;//出力するtext
};

struct SCRIPT {
	SCRIPT_CONTENTS contents;
};

struct SCRIPT_OUTLINE {
	int next;//終わるかどうかを判断する変数
	int handle;//画像番号
};

struct TUTORIAL {
	SCRIPT_OUTLINE outline;
};


extern SCRIPT talk[TALK_SCENE_MAX][LINE_MAX]; //シナリオのデータが入った配列

extern TUTORIAL tutorial[TALK_SCENE_MAX][LINE_MAX]; //チュートリアルデータが入った配列