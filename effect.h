/*****************************************************************//**
 * \file   effect.h
 * \brief  �G�t�F�N�g
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/
#pragma once
#include <math.h>
#include "dxlib.h"
#include "gamemain.h"


class Effect
{
public:

	 Effect();
	~Effect();

protected:

	//int cgEffect[EFFECT_TYPE_MAX][EFFECT_SHEETS_MAX];
	int rifflect_cooltime;
	struct EFFECT
	{
		VECTOR pos;	//�G�t�F�N�g���Đ�������W
		int cx, cy;
		int Cnt;	//���t���[��������J�E���g
		int use;	//���̔z��v�f���g�p���Ă��邩
		int type;	//�G�t�F�N�g�̎��
		int speed;	//�G�t�F�N�g�̍Đ����x
		int sheets;	//�摜�̖���
		int direction;//�G�t�F�N�g�̊p�x
		int chara_type;//�G�t�F�N�g���g�����L�����̃^�C�v

		int angle_type;   //����ł�����̊p�x��ۑ�����
		
	};

	EFFECT effect[EFFECT_MAX];

public:
	void EffectInit();

	void SetEffect(int x, int y, int type, float direction, int aiming, int arrow, int portal, int size, int chara_type);//�g���Ƃ��Ɉʒu��^�C�v���Z�b�g����֐�
	//�Z�b�^�[�Q�b�^�[
	void EffectCoolTime(int index) { rifflect_cooltime = index; };
	int GetCoolTime() { return rifflect_cooltime; }
	//�p�x���Z�b�g����֐�
	VECTOR AngreProcess(int direction);

	//�G�t�F�N�g�̏���
	void CountEffect();
	void DoEffect();

	//�G�t�F�N�g�̕`��
	void Draw(MATRIX mview);
	void NormalDraw(MATRIX, VECTOR,float );
	void ShootDraw(MATRIX mview, int plx, int ply, int arrow, int aiming);

};


