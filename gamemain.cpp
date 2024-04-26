
#include "DxLib.h"
#include "gamemain.h"
#include "main.h"
#include "SceneBase.h"
#include "SceneTest.h"
#include "SceneTitle.h"
#include "SceneMovie.h"
#include "SceneGameOver.h"
#include "SceneGameClear.h"


//
// 定数・構造体定義
//
int finish;
int cutin_swich;
float gauge[3];


//
// グローバル変数宣言
//

// ゲーム情報
GameInput gPad;

Image*     _image;
music*     _music;
FadeSound* _FadeSound;
DataSave* _Save;


// シーン切り替え用
SceneBase* gScene;
SceneBase* gNewScene;

void ChangeScene(SceneBase* scene) {
	gNewScene = scene;		// 次のシーンをセット
}
// カラーマスク用
int gColorMaskR = 0, gColorMaskG = 0, gColorMaskB = 0, gColorMaskA = 0;

// 指定の色をカラーマスク
void ColorMask(int colorR, int colorG, int colorB, int colorA) {
	gColorMaskR = colorR;
	gColorMaskG = colorG;
	gColorMaskB = colorB;
	gColorMaskA = colorA;
}

// フェードインアウト用
int gColorFadeStR, gColorFadeStG, gColorFadeStB, gColorFadeStA;
int gColorFadeEdR, gColorFadeEdG, gColorFadeEdB, gColorFadeEdA;
int gFadeFrames = 0, gFadeCnt = 0;

// 指定の色にフェードアウト（カラーマスク使用, alpha=255にする）
void ColorFadeOut(int colorR, int colorG, int colorB, int frames) {
	// フェード開始値
	gColorFadeStR = gColorMaskR;
	gColorFadeStG = gColorMaskG;
	gColorFadeStB = gColorMaskB;
	gColorFadeStA = gColorMaskA;
	// フェード到達値
	gColorFadeEdR = colorR;
	gColorFadeEdG = colorG;
	gColorFadeEdB = colorB;
	gColorFadeEdA = 255;
	// フェードカウンタ
	gFadeFrames = frames;
	gFadeCnt = 0;
}

// 現在のカラーマスクからフェードイン（カラーマスク使用, alpha=0にする）
void ColorFadeIn(int frames) {
	// フェード開始値
	gColorFadeStR = gColorMaskR;
	gColorFadeStG = gColorMaskG;
	gColorFadeStB = gColorMaskB;
	gColorFadeStA = gColorMaskA;
	// フェード到達値
	gColorFadeEdR = gColorMaskR;
	gColorFadeEdG = gColorMaskG;
	gColorFadeEdB = gColorMaskB;
	gColorFadeEdA = 0;
	// フェードカウンタ
	gFadeFrames = frames;
	gFadeCnt = 0;
}

// フェードインアウトは終了したか？
// 戻り値: 1 = フェード中, 0 = フェード終了(もしくは開始前)

int IsColorFade() {
	if (gFadeCnt < gFadeFrames) {
		return 1;
	}
	return 0;
}

void AppInit() {
	_image = new Image();
	_music = new music();
	_FadeSound = new FadeSound();
	gScene = new SceneMovie();		// Sceneの実体を作る
	_Save = new DataSave();


	gNewScene = NULL;		// 次のシーンを初期化する

	cutin_swich = 0;
	finish = 0;


	gauge[0] = 160;
	gauge[1] = 200;
	gauge[2] = 255;


}

void AppRelease() {
	delete gScene;
	delete _image;
	delete _music;
	delete _FadeSound;
}

void FrameInput() {
	gPad.Input();    // ゲームパッドの入力
}

void FrameProcess() {
	
		gScene->Process();
		// カラーマスクのフェードインアウト
		if (IsColorFade() != 0) {
			gFadeCnt++;
			gColorMaskR = EasingLinear(gFadeCnt, gColorFadeStR, gColorFadeEdR, gFadeFrames);
			gColorMaskG = EasingLinear(gFadeCnt, gColorFadeStG, gColorFadeEdG, gFadeFrames);
			gColorMaskB = EasingLinear(gFadeCnt, gColorFadeStB, gColorFadeEdB, gFadeFrames);
			gColorMaskA = EasingLinear(gFadeCnt, gColorFadeStA, gColorFadeEdA, gFadeFrames);
		}
	
}

void FrameDraw() {
	ClearDrawScreen();

	if (gNewScene == NULL) {
		gScene->Draw();
	}
	if (gColorMaskA > 0) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, gColorMaskA);	// 半透明モード
		DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(gColorMaskR, gColorMaskG, gColorMaskB), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, gColorMaskA);
	}

	ScreenFlip();
}

void Gamemain() {

	AppInit();

	while(ProcessMessage() == 0) {

#ifdef _DEBUG
		if(CheckHitKey(KEY_INPUT_ESCAPE) == 1) {
			break;
		}
#endif
		// シーンを切り替えるか？
		if(gNewScene != NULL) {
			delete gScene;		// 今のシーンを削除する
			gScene = gNewScene;	// 受け取ったシーンをポインタセット
			gNewScene = NULL;	// 次のシーンを初期化する
		}

		FrameInput();
		FrameProcess();
		FrameDraw();

	

		if(finish != 0) {
			break;
		}
	}

	AppRelease();
}