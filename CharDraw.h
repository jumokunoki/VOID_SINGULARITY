/*****************************************************************//**
 * \file   CharDraw.h
 * \brief  �����`��
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/
#pragma once
#include <iostream>
#include "relay_point.h"
#include "ScriptText.h"


class CharDraw
{
public:
	CharDraw();
	~CharDraw();

	void NameProcess(int num);//���O��ݒ肷��֐�
	void SetTutorial(int change);//�`���[�g���A���̃Z�b�g
	void Process(int change);
	void Draw(int clear);
	int SearchLetter(std::string text, int byte);//�����̃o�C�g���𒲂ׂ�֐�
	void Init();//�V�i���I�𗬂�����̏�����
	void AllInit();//�V�[���؂�ւ��̂��ׂĂ̏�����
	//�Q�b�^�[�Z�b�^�[
	void SetLine() { line = 0; }
	void SetScenario(int index) { scenario = index;}
	void SetTalkScene(int index) { talk_scene = index; }
	int  GetTalkScene() { return talk_scene; }
	int  GetScenario() { return scenario; }

	int  GetProcessStop() { return process_stop; }
	void SetProcessStop() { process_stop = 1; }

protected:
	int scenario;//�V�i���I�^�C�v�@1�F�V�i���I�@2�F�`���[�g���A��
	int count;
	int get_se;//se�̍Đ�
	int index;//�����̓ǂݍ���
	int line;//�ǂݍ���ł���s��
	int talk_scene;//���ڂ�text��ǂ�ł��邩

	int process_stop;//�v���C���[�̈ړ���s�ɂ���ϐ�

	int VoiceMem[2];//���D����{�C�X�̊i�[�ϐ�

	int read_stage_text[TALK_SCENE_MAX][100];//�V�i���I��ǂ񂾂炻�̔ԍ�����ɂ���

	std::string copy;//�e�L�X�g�̃R�s�[��
	char name[128];//���O���i�[����z��

	float x, y, direction;
};

