// シーンの枠組みの基

#pragma once
#include "DxLib.h"

class SceneBase
{
public:
	SceneBase();			// コンストラクタ
	virtual ~SceneBase();	// デストラクタ

	virtual void	Process();	// 計算
	virtual void	Draw();		// 描画
};

