/*****************************************************************//**
 * \file   Gimmick.h
 * \brief  ギミック、アイテム
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "Character.h"
#include "mymath.h"
#include "DxLib.h"
#include "MapData.h"

// ギミックの大きさ
const int GIM_W = 120;
const int GIM_H = 120;
const int DOOR_W = 100;
const int DOOR_H = 400;

// ギミックの量
const int GIMMAX = 200;
const int ABMAX  = 60;
const int TBMAX  = 50;
const int HCMAX  = 30;
const int AMBMAX = 20;
const int SLMAX  = 20;
const int DOOR_MAX = 20;

// GimMax内のパーティション
const int PARTI_AB = 0;
const int PARTI_TB = ABMAX;
const int PARTI_HC = PARTI_TB + TBMAX;
const int PARTI_AMB = PARTI_HC + HCMAX;
const int PARTI_SL = PARTI_AMB + AMBMAX;
const int PARTI_DOOR = PARTI_SL + SLMAX;

const int SAVE_MAX = 15;

class Gimmick
{
public:
	Gimmick();
	virtual ~Gimmick();

	void GimInit();
	void GeneGimmick(int type, int x, int y, int TreContent); // TreContentで宝箱の時、中身選択、レバーの時、初期状態の選択（0、1）
	void GeneLeverDoor(int LX, int LY, int DX, int DY);
	void Save(int Floor_Num); // 一回しか取れないギミックをフロアを越えて、戻ってきても元の場所に置けるように情報をセーブ
	void Load(int Floor_Num); // 保持していたデータをもとに元の位置に再現する
	void MotProcess();
	int Process(HITSLIDE hit);
	void Draw(MATRIX view);

	void RectReset(int index) { GimHit[index] = Gim_NONE; }
	int GetPosGimX(int index) { return GimHit[index].x; }
	int GetPosGimY(int index) { return GimHit[index].y; }
	int GetGimType(int index) { return GimHit[index].type; }
	MYRECT_PLUS GetGimRect(int index) { return GimHit[index]; }
	int Getstate(int index) { return _state[index]; }
	void SetPossible(bool set, int index) { _Possible[index] = set; }
	bool GetPossible(int index) { return _Possible[index]; }

protected:

	MYRECT_PLUS GimHit[GIMMAX];
	int direction[GIMMAX];
	MYRECT_PLUS Gim_NONE = { 0,0,0,0,0,0,0 };

	struct Gim_Save {
		MYRECT_PLUS info[SAVE_MAX];
		int state[SAVE_MAX];
	};

	Gim_Save _G_save[FLOOR_MAX];

	int got[GIMMAX];


	bool _ExistGim[GIMMAX];   // ギミックの存在自体のオンオフ
    bool _Possible[GIMMAX];   // ギミックの稼働可能か
	int  _state[GIMMAX];      // ギミックの状態の管理・・・トレジャーで特に使用


	struct MOTION {
		int motaddcount;
		int motcount;
		int motspeed;
		int motseet;
	};
	float Fade;
	int hang;
	MOTION _door;
};

