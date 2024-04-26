/*****************************************************************//**
 * \file   Fade.h
 * \brief  �t�F�[�h
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/
#pragma once
#include "gamemain.h"
class Fades
{
public:
	Fades();
	~Fades();
	void    FadeSet(int in_out, int color_type, int frame, int type);
	void     CharaFadeSet();
	void    FadeProcess();
	int     CheckFadeMove();
	void PortalIn(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int GrHandle, int Color, int turn);
	void    SetSceneChange(int index) { Fade.scene_change = index; }
	void    SetType(int index) { Fade.type = index; }
	int     GetType() { return Fade.type; }
	int     GetScene_Change() { return Fade.scene_change; }

	struct FADE {
		float _FadeIn;//�t�F�[�h�C��
		int FadeColor;//�t�F�[�h�{�b�N�X�̐F
		int hang;//�オ�艺����
		int all_fade_count;//���t���[����MAX�ɂ��邩
		int add_frame;//���t���[������
		int scene_change;
		int type;
	};

	FADE Fade;
	FADE chara_fade;

};

