/*****************************************************************//**
 * \file   Cutin.h
 * \brief  カットイン
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#pragma once
#include "gamemain.h"


#define CUTIN_MAX 1
#define CUTIN_TYPE_MAX 2
#define CUTIN_SHEETS_MAX 32
#define CUTIN_TYPE_TRUST 0
#define CUTIN_TYPE_BLACK 1

class Cutin
{
public:

	Cutin();
	~Cutin();
	void SetCutin(int type);//カットインのタイプをセット
	int Process();
	void Draw();

protected:




	struct CUTIN
	{
		int x, y;   //座標
		int Cnt;	//毎フレーム数えるカウント
		int type;	//エフェクトの種類
		int speed;	//エフェクトの再生速度
		int sheets;	//画像の枚数
	};

	CUTIN cutin[CUTIN_MAX];

};

