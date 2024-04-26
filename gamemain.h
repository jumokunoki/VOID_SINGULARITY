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

void ColorMask(int colorR, int colorG, int colorB, int colorA);		// �J���[�}�X�N�̎w��

// �w��̐F�Ƀt�F�[�h�A�E�g�i�J���[�}�X�N�g�p, alpha=255�ɂ���j
void ColorFadeOut(int colorR, int colorG, int colorB, int frames);

// ���݂̃J���[�}�X�N����t�F�[�h�C���i�J���[�}�X�N�g�p, alpha=0�ɂ���j
void ColorFadeIn(int frames);

// �t�F�[�h�C���A�E�g�͏I���������H
// �߂�l: 1 = �t�F�[�h��, 0 = �t�F�[�h�I��(�������͊J�n�O)
int IsColorFade();

void Gamemain();