/*****************************************************************//**
 * \file   Cutin.h
 * \brief  �J�b�g�C��
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/
#pragma once
#include "gamemain.h"


#define CUTIN_MAX 1
#define CUTIN_TYPE_MAX 2
#define CUTIN_SHEETS_MAX 32
#define CUTIN_TYPE_TRUST 0
#define CUTIN_TYPE_BLACK 1

class Cutin
{
public:

	Cutin();
	~Cutin();
	void SetCutin(int type);//�J�b�g�C���̃^�C�v���Z�b�g
	int Process();
	void Draw();

protected:




	struct CUTIN
	{
		int x, y;   //���W
		int Cnt;	//���t���[��������J�E���g
		int type;	//�G�t�F�N�g�̎��
		int speed;	//�G�t�F�N�g�̍Đ����x
		int sheets;	//�摜�̖���
	};

	CUTIN cutin[CUTIN_MAX];

};

