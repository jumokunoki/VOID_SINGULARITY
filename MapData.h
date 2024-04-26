/*****************************************************************//**
 * \file   MapData.h
 * \brief  �}�b�v�f�[�^
 *
 * \author �ޗǏ[��
 * \date  August 2023
 *********************************************************************/

#pragma once
#include "DxLib.h"		// VECTOR��MATRIX���`�Ƃ��Ďg�����߁A.h�ɓ���Ă���

const int FLOOR_MAX = 17;

class MapData
{
public:
	MapData();			// �R���X�g���N�^
	virtual ~MapData();	// �f�X�g���N�^

	// �����蔻��֘A
	int		CheckHitMapChip(int x, int y);	// �w��ʒu�̃`�b�v�������蔻�肠�肩�H
	int		CheckHitChip(int chip_no);		// �w��̃`�b�vID�������蔻�肠�肩�H

	struct HITSLIDE {
		int	hit;				// �������Ă����1�A�������Ă��Ȃ������0
		int	slide_x, slide_y;	// �������Ă���ꍇ�A���炷�ׂ��l
	};
	HITSLIDE IsHitBox(int box_x, int box_y, int box_w, int box_h, int move_x, int move_y);	// �w���box��move_x,move_y�Ɉړ����Ă����ꍇ�A�}�b�v�`�b�v�ɓ����邩�H
	int IsHitPointBox(float x, float y);
	int IsHitCircleMap(int circle_x, int circle_y, int circle_r);
	int IsHitC4Point(int circle_x, int circle_y, int circle_r);

	void SetMapData();

	int  GetFloorNum() { return _FloorNum;  }
	void SetFloorNum(int Floor) { _FloorNum = Floor; }
	void AddFloorNum() { _FloorNum++; }
	void SubFloorNum() { _FloorNum--; }

	// �}�b�v�`�b�v�֘A
#define	CHIPSIZE_W	(60)
#define	CHIPSIZE_H	(60)
// �}�b�v�f�[�^
#define	MAPSIZE_W	(64)
#define	MAPSIZE_H	(36)

	// world�̃T�C�Y���擾(pixel�P��)
	int	GetWorldSizeW() { return MAPSIZE_W * CHIPSIZE_W ; }
	int	GetWorldSizeH() { return MAPSIZE_H * CHIPSIZE_H ; }
	int GetChipSizeW() { return CHIPSIZE_W; }
	int GetChipSizeH() { return CHIPSIZE_H; }

protected:
	int _gMapData[MAPSIZE_W * MAPSIZE_H];
	int _FloorNum;

};


