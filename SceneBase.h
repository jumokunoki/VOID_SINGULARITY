// �V�[���̘g�g�݂̊�

#pragma once
#include "DxLib.h"

class SceneBase
{
public:
	SceneBase();			// �R���X�g���N�^
	virtual ~SceneBase();	// �f�X�g���N�^

	virtual void	Process();	// �v�Z
	virtual void	Draw();		// �`��
};

