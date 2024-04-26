/*****************************************************************//**
 * \file   MapData.h
 * \brief  マップデータ
 *
 * \author 奈良充樹
 * \date  August 2023
 *********************************************************************/

#pragma once
#include "DxLib.h"		// VECTORやMATRIXを定義として使うため、.hに入れておく

const int FLOOR_MAX = 17;

class MapData
{
public:
	MapData();			// コンストラクタ
	virtual ~MapData();	// デストラクタ

	// 当たり判定関連
	int		CheckHitMapChip(int x, int y);	// 指定位置のチップが当たり判定ありか？
	int		CheckHitChip(int chip_no);		// 指定のチップIDが当たり判定ありか？

	struct HITSLIDE {
		int	hit;				// 当たっていれば1、当たっていないければ0
		int	slide_x, slide_y;	// 当たっている場合、ずらすべき値
	};
	HITSLIDE IsHitBox(int box_x, int box_y, int box_w, int box_h, int move_x, int move_y);	// 指定のboxがmove_x,move_yに移動していた場合、マップチップに当たるか？
	int IsHitPointBox(float x, float y);
	int IsHitCircleMap(int circle_x, int circle_y, int circle_r);
	int IsHitC4Point(int circle_x, int circle_y, int circle_r);

	void SetMapData();

	int  GetFloorNum() { return _FloorNum;  }
	void SetFloorNum(int Floor) { _FloorNum = Floor; }
	void AddFloorNum() { _FloorNum++; }
	void SubFloorNum() { _FloorNum--; }

	// マップチップ関連
#define	CHIPSIZE_W	(60)
#define	CHIPSIZE_H	(60)
// マップデータ
#define	MAPSIZE_W	(64)
#define	MAPSIZE_H	(36)

	// worldのサイズを取得(pixel単位)
	int	GetWorldSizeW() { return MAPSIZE_W * CHIPSIZE_W ; }
	int	GetWorldSizeH() { return MAPSIZE_H * CHIPSIZE_H ; }
	int GetChipSizeW() { return CHIPSIZE_W; }
	int GetChipSizeH() { return CHIPSIZE_H; }

protected:
	int _gMapData[MAPSIZE_W * MAPSIZE_H];
	int _FloorNum;

};


