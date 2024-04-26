/*****************************************************************//**
 * \file   Option.h
 * \brief  �I�v�V�����ݒ�
 *
 * \author �V�� ��H
 * \date   July 2022
 *********************************************************************/

#pragma once
#include "dxlib.h"
#include "gamemain.h"

class Option
{
public:
	Option();			// �R���X�g���N�^
	virtual ~Option();	// �f�X�g���N�^
	virtual void	Process();	// �v�Z
	void SelectProcess(int select_count);//���ʂ���o�[�̑I��
	virtual void	Draw();		// �`��

protected:


	int back;         //�^�C�g���ɖ߂邽�߂Ɏg��

	int select_count;
	int select_bar[4];
	int cutin_select;

	float FadeOut;//�t�F�[�h�A�E�g�J�E���g

	int color_type;

	struct BAR {
		int x, y, w, h;
	};
	BAR border;
	BAR gauge_unit;

	int gauge_handle_x;
	int gauge_handle_y;

};

