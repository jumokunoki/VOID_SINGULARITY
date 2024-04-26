/*****************************************************************//**
 * \file   Option.h
 * \brief  オプション設定
 *
 * \author 齋藤 瑚羽
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "dxlib.h"
#include "gamemain.h"

class Option
{
public:
	Option();			// コンストラクタ
	virtual ~Option();	// デストラクタ
	virtual void	Process();	// 計算
	void SelectProcess(int select_count);//音量するバーの選択
	virtual void	Draw();		// 描画

protected:


	int back;         //タイトルに戻るために使う

	int select_count;
	int select_bar[4];
	int cutin_select;

	float FadeOut;//フェードアウトカウント

	int color_type;

	struct BAR {
		int x, y, w, h;
	};
	BAR border;
	BAR gauge_unit;

	int gauge_handle_x;
	int gauge_handle_y;

};

