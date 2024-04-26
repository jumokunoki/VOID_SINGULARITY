#pragma once
#include "SceneBase.h"
#include "GameInput.h"
#include "music.h"
#include "Image.h"
#include "FadeSound.h"
#include "DataSave.h"


extern GameInput gPad;
extern Image* _image;
extern music* _music;
extern FadeSound* _FadeSound;
extern DataSave* _Save;


extern int finish;
extern float gauge[3];
extern int cutin_swich;

struct ANIMCNT{
	int count;
	int use;
	int num;
};

struct MOTION {
	int motaddcount;
	int motcount;
	int motspeed;
	int motseet;
	int got;
};

struct ALPHA {
	float fade;
	int   hang;
};

void ChangeScene(SceneBase* scene);

void ColorMask(int colorR, int colorG, int colorB, int colorA);		// カラーマスクの指定

// 指定の色にフェードアウト（カラーマスク使用, alpha=255にする）
void ColorFadeOut(int colorR, int colorG, int colorB, int frames);

// 現在のカラーマスクからフェードイン（カラーマスク使用, alpha=0にする）
void ColorFadeIn(int frames);

// フェードインアウトは終了したか？
// 戻り値: 1 = フェード中, 0 = フェード終了(もしくは開始前)
int IsColorFade();

void Gamemain();