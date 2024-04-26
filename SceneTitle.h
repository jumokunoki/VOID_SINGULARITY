/*****************************************************************//**
 * \file   SceneTitle.h
 * \brief  �^�C�g��
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "gamemain.h"
#include "SceneBase.h"
#include "Option.h"
#include "DxLib.h"


class SceneTitle : public SceneBase
{

public:
	SceneTitle();			// �R���X�g���N�^
	virtual ~SceneTitle();	// �f�X�g���N�^

	void SoundInit();       // ���̓ǂݍ���
	void ImageInit();       // �摜�ǂݍ���

	void SelectMove(int select ,int title,int wait , int extra);//���ł̏���
	virtual void	Process();	// �v�Z
	virtual void	Draw();		// �`��

protected:
#define EFFECT_CG_MAX 600
	int _cgBg;
	int effectcg[EFFECT_CG_MAX]; //�w�i
	int Se[4];
	int Bgm;
	int waitcount;

	char size[43];
	int effect_load_count;

	int effect_count;//�p�[�e�B�N���𓮂����Ƃ��̕ϐ�
	int character_handle;   //���C����l���̕`��n���h��
	int title_handle;//�^�C�g�����S�̉摜�n���h��
	int controle_Handle;//�����ʂ̉摜�n���h��
	int start_handle[3];//�^�C�g����ʂ̉摜�n���h��
	int command_handle[7][3];//�I����ʂ̃n���h��
	int select_count;//�Z���N�g�^�C�v������
	int select_handle_count[7];//
	int title_count;//�Q�[���X�^�[�g�ȊO�̉摜�`��̔���Ɏg���������ꂽ�Ƃ���1�ɂ���
	int extra_count;//�X�^�b�t���[����^�C�g�����[�r�[�Ŏg���J�E���g
	int any_button;//any_start�Ŏg���ϐ�
	float any_button_fade;//�^�C�g����ʂ���I����ʂɐ؂�ւ���Ƃ��̃t�F�[�h
	int copy_light_handle;//�R�s�[���C�g�̃n���h��

	int handle_x, handle_y;//�I����ʂ̉摜�̈ʒu
	int select_x, select_y;//�I����ʂ̉摜�̈ʒu


	float FadeIn; //�t�F�[�h�Ɏg��
	float FadeOut;//�t�F�[�h�Ɏg��
	float flashing;//�t�F�[�h�Ɏg��
	int   hang;//�t�F�[�h�Ɋ|���đ�������������肷��̂Ɏg��
	int   any_hang;//�^�C�g����ʂ̃t�F�[�h
	int   FadeCount;//�t�F�[�h�A�E�g������Ƃ��Ƀt���O��1�ɂ���
	
	struct EFFECT {
		VECTOR pos;
		float direction;
	};

	ANIMCNT anim[2];

	MOTION hand;
	Option option;

};

