/*****************************************************************//**
 * \file   Gimmick.h
 * \brief  �M�~�b�N�A�A�C�e��
 *
 * \author �ޗǏ[���A�V�� ��H
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "Character.h"
#include "mymath.h"
#include "DxLib.h"
#include "MapData.h"

// �M�~�b�N�̑傫��
const int GIM_W = 120;
const int GIM_H = 120;
const int DOOR_W = 100;
const int DOOR_H = 400;

// �M�~�b�N�̗�
const int GIMMAX = 200;
const int ABMAX  = 60;
const int TBMAX  = 50;
const int HCMAX  = 30;
const int AMBMAX = 20;
const int SLMAX  = 20;
const int DOOR_MAX = 20;

// GimMax���̃p�[�e�B�V����
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
	void GeneGimmick(int type, int x, int y, int TreContent); // TreContent�ŕ󔠂̎��A���g�I���A���o�[�̎��A������Ԃ̑I���i0�A1�j
	void GeneLeverDoor(int LX, int LY, int DX, int DY);
	void Save(int Floor_Num); // ��񂵂����Ȃ��M�~�b�N���t���A���z���āA�߂��Ă��Ă����̏ꏊ�ɒu����悤�ɏ����Z�[�u
	void Load(int Floor_Num); // �ێ����Ă����f�[�^�����ƂɌ��̈ʒu�ɍČ�����
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


	bool _ExistGim[GIMMAX];   // �M�~�b�N�̑��ݎ��̂̃I���I�t
    bool _Possible[GIMMAX];   // �M�~�b�N�̉ғ��\��
	int  _state[GIMMAX];      // �M�~�b�N�̏�Ԃ̊Ǘ��E�E�E�g���W���[�œ��Ɏg�p


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

