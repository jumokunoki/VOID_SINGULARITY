/*****************************************************************//**
 * \file   MapData.cpp
 * \brief  �}�b�v�f�[�^
 *
 * \author �ޗǏ[��
 * \date   August 2023
 *********************************************************************/

#include "DxLib.h"
#include "main.h"
#include "gamemain.h"
#include "MapData.h"
#include "mymath.h"
#include "mydraw.h"
#include "MapInfo.h"


MapData::MapData() {

	_FloorNum = _Save->GetStage();

	// �}�b�v�f�[�^���N���X�����o�ɃR�s�[����
	int x, y;
	for(y = 0; y < MAPSIZE_H; y++) {
		for(x = 0; x < MAPSIZE_W; x++) {
			_gMapData[y * MAPSIZE_W + x] = mapdata[_FloorNum][y * MAPSIZE_W + x];
		}
	}
}

MapData::~MapData() {
	
}

void MapData::SetMapData() {
	int x, y;
	for(y = 0; y < MAPSIZE_H; y++) {
		for(x = 0; x < MAPSIZE_W; x++) {
			_gMapData[y * MAPSIZE_W + x] = mapdata[_FloorNum][y * MAPSIZE_W + x];
		}
	}
}

// �w��̃`�b�vID�������蔻�肠�肩�H
int	MapData::CheckHitChip(int chip_no)
{
	// ������ID���ǂ������`�F�b�N
	int idtable[] =
	{
		2, 4, 7, 8,
		9, 10, 11, 12, 13, 14, 15, 16,
		20, 21, 22,102,
		-1		// �Ō�
	};
	int i = 0;
	while(idtable[i] != -1)
	{
		if(chip_no == idtable[i])
		{
			// ��������
			return chip_no;
		}
		i++;
	}

	// �������Ă��Ȃ�
	return 0;
}

// �}�b�v�`�b�v�Ƃ̓����蔻��
// �����F
//   x,y = �}�b�v�`�b�v�̈ʒu(x,y) �`�b�v�P��
// �ߒl�F
//   0 : �����蔻����s��Ȃ�
//   0�ȊO : �����蔻����s���i�`�b�v�ԍ���Ԃ��j
int MapData::CheckHitMapChip(int x, int y)
{
	// �}�b�v�`�b�v�ʒu�̓}�b�v�f�[�^����͂ݏo�Ă��邩�H
	if(0 <= x && x < MAPSIZE_W && 0 <= y && y < MAPSIZE_H)
	{	// �݂͂łĂ��Ȃ�

		// �}�b�v�`�b�vID��0�ȊO�͓����蔻����s��
		// ���݁A���C���[�͍l������Ă��Ȃ�
		int chip_no = _gMapData[y * MAPSIZE_W + x];
		return CheckHitChip(chip_no);
	}

	// �������Ă��Ȃ�
	return 0;
}


// �w���box��move_x,move_y�Ɉړ����Ă����ꍇ�A�}�b�v�`�b�v�ɓ����邩�H
// box��pixel�P��
// move_x, move_y��pixel�P��
MapData::HITSLIDE MapData::IsHitBox(int box_x, int box_y, int box_w, int box_h, int move_x, int move_y) {
	HITSLIDE hitSlide;
	hitSlide.hit = 0;
	hitSlide.slide_x = 0;
	hitSlide.slide_y = 0;

	int x, y;
	// ��`���쐬����
	int l, t, r, b;		// ����(left,top) - �E��(right,bottom)
	l = box_x;
	t = box_y;
	r = box_x + box_w;
	b = box_y + box_h;

	// box�̍�����W�`�E�����W�ɂ�����}�b�v�`�b�v�ƁA�����蔻����s��
	for(y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++)
	{
		for(x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++)
		{
			// (x,y)�́A�}�b�v�`�b�v�̍��W�i�`�b�v�P�ʁj
			// ���̈ʒu�̃`�b�v�͓����邩�H
			int chip_no = CheckHitMapChip(x, y);
			if(chip_no != 0)
			{	// ���̃`�b�v�Ɠ��������B
				// X,Y�̈ړ����������āA���̔��Ε����ɕ␳����
				if(move_x < 0)
				{	// ���ɓ����Ă����̂ŁA�E�ɕ␳
					hitSlide.slide_x = x * CHIPSIZE_W + CHIPSIZE_W - (box_x);
				}
				if(move_x > 0)
				{	// �E�ɓ����Ă����̂ŁA���ɕ␳
					hitSlide.slide_x = x * CHIPSIZE_W - 1 - (box_x + box_w);
				}
				if(move_y > 0)
				{	// ���ɓ����Ă����̂ŁA��ɕ␳
					hitSlide.slide_y = y * CHIPSIZE_H - 1 - (box_y + box_h);
				}
				if(move_y < 0)
				{	// ��ɓ����Ă����̂ŁA���ɕ␳
					hitSlide.slide_y = y * CHIPSIZE_H + CHIPSIZE_H - (box_y);
				}
				// ���������̂Ŗ߂�
				hitSlide.hit = 1;
				return hitSlide;
			}
		}
	}

	// ������Ȃ�����
	return hitSlide;
}

int MapData::IsHitPointBox(float x, float y) {
	int hit = 0;
	int cx, cy;
	cx = x / CHIPSIZE_W;
	cy = y / CHIPSIZE_H;

	int chip_no = CheckHitMapChip(cx, cy);

	if(chip_no != 0) {
		hit = chip_no;
	}

	return hit;

}

int MapData::IsHitCircleMap(int circle_x, int circle_y, int circle_r) {

	int chip_no = 0;
	int x, y;
	float rad,deg;

	for(deg = 0; deg <= 360; deg++) {
		rad = DegToRad(deg);
		x = (circle_x + circle_r * cos(rad)) / CHIPSIZE_W;
		y = (circle_y + circle_r * sin(rad)) / CHIPSIZE_H;

		chip_no = CheckHitMapChip(x, y);
		if(chip_no != 0) {
			return chip_no;
		}
	}
	return chip_no;
}

int MapData::IsHitC4Point(int circle_x, int circle_y, int circle_r) {
	// �ŏ�4�_�Ƃ��΂������ȂƎv���Ă܂������A(�����ɂ���)�t�@�W�[�Ȕ���Ȃ̂ő��₷����
	int hit = 0;
	int x, y;
	float rad, deg;

	for(deg = 0; deg <= 270; deg += 90) {
		rad = DegToRad(deg);
		x = (circle_x + circle_r * cos(rad)) / CHIPSIZE_W;
		y = (circle_y + circle_r * sin(rad)) / CHIPSIZE_H;

		int chip_no = CheckHitMapChip(x, y);
		if(chip_no != 0) {
			return (deg)/90;
		}
	}
}