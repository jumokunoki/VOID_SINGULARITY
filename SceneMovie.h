/*****************************************************************//**
 * \file   SceneMovie.h
 * \brief  ムービーシーン
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "SceneBase.h"
class SceneMovie : public SceneBase
{
public:
	SceneMovie();			// コンストラクタ
	virtual ~SceneMovie();	// デストラクタ
	void FadeProcess();
	virtual void	Process()override;	// 計算
	virtual void	Draw()override;		// 描画

protected:

	int movie_handle;//動画ハンドル
	int Logocount;   //画像の描画時間
	int logo_handle;//学院の画像を核のする変数
	int loading;

	float Fade;//フェードインアウトに使う変数

	float FadeOut;//フェードインアウトに使う変数
	float FadeLogo;//フェードインアウトに使う変数
	float FadeLoad;//ロードが終わった時に使う変数
	

};

