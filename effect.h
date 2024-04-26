/*****************************************************************//**
 * \file   effect.h
 * \brief  エフェクト
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#pragma once
#include <math.h>
#include "dxlib.h"
#include "gamemain.h"


class Effect
{
public:

	 Effect();
	~Effect();

protected:

	//int cgEffect[EFFECT_TYPE_MAX][EFFECT_SHEETS_MAX];
	int rifflect_cooltime;
	struct EFFECT
	{
		VECTOR pos;	//エフェクトを再生する座標
		int cx, cy;
		int Cnt;	//毎フレーム数えるカウント
		int use;	//この配列要素を使用しているか
		int type;	//エフェクトの種類
		int speed;	//エフェクトの再生速度
		int sheets;	//画像の枚数
		int direction;//エフェクトの角度
		int chara_type;//エフェクトを使ったキャラのタイプ

		int angle_type;   //球を打った後の角度を保存する
		
	};

	EFFECT effect[EFFECT_MAX];

public:
	void EffectInit();

	void SetEffect(int x, int y, int type, float direction, int aiming, int arrow, int portal, int size, int chara_type);//使うときに位置やタイプをセットする関数
	//セッターゲッター
	void EffectCoolTime(int index) { rifflect_cooltime = index; };
	int GetCoolTime() { return rifflect_cooltime; }
	//角度をセットする関数
	VECTOR AngreProcess(int direction);

	//エフェクトの処理
	void CountEffect();
	void DoEffect();

	//エフェクトの描画
	void Draw(MATRIX mview);
	void NormalDraw(MATRIX, VECTOR,float );
	void ShootDraw(MATRIX mview, int plx, int ply, int arrow, int aiming);

};


