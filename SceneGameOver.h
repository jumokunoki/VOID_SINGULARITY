/*****************************************************************//**
 * \file   SceneGameOver.h
 * \brief  ゲームオーバー
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#pragma once
#include "gamemain.h"
#include "SceneBase.h"
#include "SceneTitle.h"
class SceneGameOver : public SceneBase
{
public:
	SceneGameOver();
	~SceneGameOver();

	virtual void Process();
	virtual void Draw();

protected:
	int gameover_handle[31];//ゲームオーバーの画像を格納する変数
	int chara_serif;//キャラのセリフ画像を格納する変数
	int voice;//ランダムでボイスを格納する変数

	MOTION over;//アニメーションで使う構造体
};

