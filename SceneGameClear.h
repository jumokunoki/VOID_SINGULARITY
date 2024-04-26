/*****************************************************************//**
 * \file   SceneGameClear.h
 * \brief  �Q�[���N���A
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/
#pragma once
#include "SceneBase.h"
#include "dxlib.h"
#include "gamemain.h"
class SceneGameClear : public SceneBase
{
public:
	 SceneGameClear();
	~SceneGameClear();

	void Process();
	int  CheckVoiceAll();//�{�C�X������Ă��邩���m�F����
	void StopProcess();//�X�g�b�v�ɂȂ��Ă��邩�{�C�X������Ă��邩���m�F����
	void Flow_Process(int count);//�S�̂̓���
	void Draw();
protected:
	float _Fade[5];//�摜�̃t�F�[�h�Ŏg���ϐ�
	int    hang[5];//�t�F�[�h�̊|���Z�Ŏg���ϐ�
	int flow_count;//�N���A��ʂ̗��ꐧ�䂷�����
	int handle_count;//�摜�ԍ�������ϐ�
	int movie_flag;//���悪�Đ����ꂽ�����m�F����t���O
	int voice[4];//�{�C�X���i�[����ϐ�
	int voice_num;//�{�C�X�𗬂�����+1
	int stop;//�{�C�X������Ă���Ԃ͏������~�߂�
	int stop_order;//�{�C�X������Ă��邩���m�F����ϐ�
};

