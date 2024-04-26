
#include "DxLib.h"
#include "gamemain.h"
#include "main.h"
#include <time.h>
#include "relay_point.h"

void New_Variable();
void Gamemain();	// gamemain.cpp に実体を記述

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	SetOutApplicationLogValidFlag(false);
	// 初期化 -------------------------------------------------------------------------
	// ＤＸライブラリ初期化処理
	SetGraphMode(SCREEN_W, SCREEN_H, SCREEN_DEPTH);	// 画面の解像度を横1280×縦720、1ドットあたり32ビットに指定する
	ChangeWindowMode(true);							// ウィンドウモードに指定する
	if(DxLib_Init() == -1)
	{	// エラーが起きたら直ちに終了
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// 描画先画面を裏画面にセット
	srand((unsigned)time(NULL));

	//クラス読み込み
	New_Variable();

	// ゲームメイン
	Gamemain();

	

	// 解放 ---------------------------------------------------------------------------
	DxLib_End();		// ＤＸライブラリ使用の終了処理

	// 終了
	return 0;
}