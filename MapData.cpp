/*****************************************************************//**
 * \file   MapData.cpp
 * \brief  マップデータ
 *
 * \author 奈良充樹
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

	// マップデータをクラスメンバにコピーする
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

// 指定のチップIDが当たり判定ありか？
int	MapData::CheckHitChip(int chip_no)
{
	// 当たるIDかどうかをチェック
	int idtable[] =
	{
		2, 4, 7, 8,
		9, 10, 11, 12, 13, 14, 15, 16,
		20, 21, 22,102,
		-1		// 最後
	};
	int i = 0;
	while(idtable[i] != -1)
	{
		if(chip_no == idtable[i])
		{
			// 当たった
			return chip_no;
		}
		i++;
	}

	// 当たっていない
	return 0;
}

// マップチップとの当たり判定
// 引数：
//   x,y = マップチップの位置(x,y) チップ単位
// 戻値：
//   0 : 当たり判定を行わない
//   0以外 : 当たり判定を行う（チップ番号を返す）
int MapData::CheckHitMapChip(int x, int y)
{
	// マップチップ位置はマップデータからはみ出ているか？
	if(0 <= x && x < MAPSIZE_W && 0 <= y && y < MAPSIZE_H)
	{	// はみでていない

		// マップチップIDが0以外は当たり判定を行う
		// 現在、レイヤーは考慮されていない
		int chip_no = _gMapData[y * MAPSIZE_W + x];
		return CheckHitChip(chip_no);
	}

	// 当たっていない
	return 0;
}


// 指定のboxがmove_x,move_yに移動していた場合、マップチップに当たるか？
// boxはpixel単位
// move_x, move_yはpixel単位
MapData::HITSLIDE MapData::IsHitBox(int box_x, int box_y, int box_w, int box_h, int move_x, int move_y) {
	HITSLIDE hitSlide;
	hitSlide.hit = 0;
	hitSlide.slide_x = 0;
	hitSlide.slide_y = 0;

	int x, y;
	// 矩形を作成する
	int l, t, r, b;		// 左上(left,top) - 右下(right,bottom)
	l = box_x;
	t = box_y;
	r = box_x + box_w;
	b = box_y + box_h;

	// boxの左上座標～右下座標にあたるマップチップと、当たり判定を行う
	for(y = t / CHIPSIZE_H; y <= b / CHIPSIZE_H; y++)
	{
		for(x = l / CHIPSIZE_W; x <= r / CHIPSIZE_W; x++)
		{
			// (x,y)は、マップチップの座標（チップ単位）
			// この位置のチップは当たるか？
			int chip_no = CheckHitMapChip(x, y);
			if(chip_no != 0)
			{	// このチップと当たった。
				// X,Yの移動方向を見て、その反対方向に補正する
				if(move_x < 0)
				{	// 左に動いていたので、右に補正
					hitSlide.slide_x = x * CHIPSIZE_W + CHIPSIZE_W - (box_x);
				}
				if(move_x > 0)
				{	// 右に動いていたので、左に補正
					hitSlide.slide_x = x * CHIPSIZE_W - 1 - (box_x + box_w);
				}
				if(move_y > 0)
				{	// 下に動いていたので、上に補正
					hitSlide.slide_y = y * CHIPSIZE_H - 1 - (box_y + box_h);
				}
				if(move_y < 0)
				{	// 上に動いていたので、下に補正
					hitSlide.slide_y = y * CHIPSIZE_H + CHIPSIZE_H - (box_y);
				}
				// 当たったので戻る
				hitSlide.hit = 1;
				return hitSlide;
			}
		}
	}

	// 当たらなかった
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
	// 最初4点とれればいいかなと思ってましたが、(扱いにくい)ファジーな判定なので増やすかも
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