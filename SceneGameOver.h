/*****************************************************************//**
 * \file   SceneGameOver.h
 * \brief  �Q�[���I�[�o�[
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/
#pragma once
#include "gamemain.h"
#include "SceneBase.h"
#include "SceneTitle.h"
class SceneGameOver : public SceneBase
{
public:
	SceneGameOver();
	~SceneGameOver();

	virtual void Process();
	virtual void Draw();

protected:
	int gameover_handle[31];//�Q�[���I�[�o�[�̉摜���i�[����ϐ�
	int chara_serif;//�L�����̃Z���t�摜���i�[����ϐ�
	int voice;//�����_���Ń{�C�X���i�[����ϐ�

	MOTION over;//�A�j���[�V�����Ŏg���\����
};

