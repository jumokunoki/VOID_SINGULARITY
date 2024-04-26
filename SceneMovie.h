/*****************************************************************//**
 * \file   SceneMovie.h
 * \brief  ���[�r�[�V�[��
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "SceneBase.h"
class SceneMovie : public SceneBase
{
public:
	SceneMovie();			// �R���X�g���N�^
	virtual ~SceneMovie();	// �f�X�g���N�^
	void FadeProcess();
	virtual void	Process()override;	// �v�Z
	virtual void	Draw()override;		// �`��

protected:

	int movie_handle;//����n���h��
	int Logocount;   //�摜�̕`�掞��
	int logo_handle;//�w�@�̉摜���j�̂���ϐ�
	int loading;

	float Fade;//�t�F�[�h�C���A�E�g�Ɏg���ϐ�

	float FadeOut;//�t�F�[�h�C���A�E�g�Ɏg���ϐ�
	float FadeLogo;//�t�F�[�h�C���A�E�g�Ɏg���ϐ�
	float FadeLoad;//���[�h���I��������Ɏg���ϐ�
	

};

