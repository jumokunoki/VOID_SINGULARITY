/*****************************************************************//**
 * \file   ScriptText.h
 * \brief  �V�i���I���
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/
#pragma once
#include "dxlib.h"
#include <iostream>

#define TALK_SCENE_MAX 20
#define LINE_MAX 100

struct SCRIPT_CONTENTS {
	int  left_chara;//���̃L����
	int  left_light;//���̃L�����𖾂邭���邩�̕ϐ�
	int  left_chara_back;//���̃L�����̃o�b�N
	int  right_chara;//�E�̃L����
	int  right_light;//�E�̃L�����𖾂邭���邩�̕ϐ�
	int  right_chara_back;//�E�̃L�����̃o�b�N
	int  name;//�ǂ̖��O���g�����̕ϐ�
	std::string voice;//�{�C�X�̖��O������ϐ�
	std::string text;//�o�͂���text
};

struct SCRIPT {
	SCRIPT_CONTENTS contents;
};

struct SCRIPT_OUTLINE {
	int next;//�I��邩�ǂ����𔻒f����ϐ�
	int handle;//�摜�ԍ�
};

struct TUTORIAL {
	SCRIPT_OUTLINE outline;
};


extern SCRIPT talk[TALK_SCENE_MAX][LINE_MAX]; //�V�i���I�̃f�[�^���������z��

extern TUTORIAL tutorial[TALK_SCENE_MAX][LINE_MAX]; //�`���[�g���A���f�[�^���������z��