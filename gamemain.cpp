
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
// �萔�E�\���̒�`
//
int finish;
int cutin_swich;
float gauge[3];


//
// �O���[�o���ϐ��錾
//

// �Q�[�����
GameInput gPad;

Image*     _image;
music*     _music;
FadeSound* _FadeSound;
DataSave* _Save;


// �V�[���؂�ւ��p
SceneBase* gScene;
SceneBase* gNewScene;

void ChangeScene(SceneBase* scene) {
	gNewScene = scene;		// ���̃V�[�����Z�b�g
}
// �J���[�}�X�N�p
int gColorMaskR = 0, gColorMaskG = 0, gColorMaskB = 0, gColorMaskA = 0;

// �w��̐F���J���[�}�X�N
void ColorMask(int colorR, int colorG, int colorB, int colorA) {
	gColorMaskR = colorR;
	gColorMaskG = colorG;
	gColorMaskB = colorB;
	gColorMaskA = colorA;
}

// �t�F�[�h�C���A�E�g�p
int gColorFadeStR, gColorFadeStG, gColorFadeStB, gColorFadeStA;
int gColorFadeEdR, gColorFadeEdG, gColorFadeEdB, gColorFadeEdA;
int gFadeFrames = 0, gFadeCnt = 0;

// �w��̐F�Ƀt�F�[�h�A�E�g�i�J���[�}�X�N�g�p, alpha=255�ɂ���j
void ColorFadeOut(int colorR, int colorG, int colorB, int frames) {
	// �t�F�[�h�J�n�l
	gColorFadeStR = gColorMaskR;
	gColorFadeStG = gColorMaskG;
	gColorFadeStB = gColorMaskB;
	gColorFadeStA = gColorMaskA;
	// �t�F�[�h���B�l
	gColorFadeEdR = colorR;
	gColorFadeEdG = colorG;
	gColorFadeEdB = colorB;
	gColorFadeEdA = 255;
	// �t�F�[�h�J�E���^
	gFadeFrames = frames;
	gFadeCnt = 0;
}

// ���݂̃J���[�}�X�N����t�F�[�h�C���i�J���[�}�X�N�g�p, alpha=0�ɂ���j
void ColorFadeIn(int frames) {
	// �t�F�[�h�J�n�l
	gColorFadeStR = gColorMaskR;
	gColorFadeStG = gColorMaskG;
	gColorFadeStB = gColorMaskB;
	gColorFadeStA = gColorMaskA;
	// �t�F�[�h���B�l
	gColorFadeEdR = gColorMaskR;
	gColorFadeEdG = gColorMaskG;
	gColorFadeEdB = gColorMaskB;
	gColorFadeEdA = 0;
	// �t�F�[�h�J�E���^
	gFadeFrames = frames;
	gFadeCnt = 0;
}

// �t�F�[�h�C���A�E�g�͏I���������H
// �߂�l: 1 = �t�F�[�h��, 0 = �t�F�[�h�I��(�������͊J�n�O)

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
	gScene = new SceneMovie();		// Scene�̎��̂����
	_Save = new DataSave();


	gNewScene = NULL;		// ���̃V�[��������������

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
	gPad.Input();    // �Q�[���p�b�h�̓���
}

void FrameProcess() {
	
		gScene->Process();
		// �J���[�}�X�N�̃t�F�[�h�C���A�E�g
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
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, gColorMaskA);	// ���������[�h
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
		// �V�[����؂�ւ��邩�H
		if(gNewScene != NULL) {
			delete gScene;		// ���̃V�[�����폜����
			gScene = gNewScene;	// �󂯎�����V�[�����|�C���^�Z�b�g
			gNewScene = NULL;	// ���̃V�[��������������
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