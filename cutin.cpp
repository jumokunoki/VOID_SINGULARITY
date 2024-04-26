/*****************************************************************//**
 * \file   cutin.cpp
 * \brief  �J�b�g�C��
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Cutin.h"
#include "dxlib.h"

Cutin::Cutin() {
	for(int i = 0; i < CUTIN_MAX; i++) {
		cutin[i].x = 0;
		cutin[i].y = 0;
		cutin[i].Cnt = 0;
		cutin[i].type = -1;
		cutin[i].speed = 2;
		cutin[i].sheets = 31;
	}
};

Cutin::~Cutin() {
	
};

void Cutin::SetCutin(int type) {
	//�J�b�g�C�����I���ɂȂ�����^�C�v�ɂ���Đ؂�ւ��鏈��
	for(int i = 0; i < CUTIN_MAX; i++) {
		if(cutin[i].type == -1) {
			cutin[i].x = 0;
			cutin[i].y = 0;
			switch(type) {
			case 1:
				cutin[i].type = CUTIN_TYPE_TRUST;
				cutin[i].speed = 2;
				cutin[i].sheets = 31;
				break;
			case 2:
				cutin[i].type = CUTIN_TYPE_BLACK;
				cutin[i].speed = 2;
				cutin[i].sheets = 31;
				break;
			}
		}
	}
};

int Cutin::Process() {
	//�J�b�g�C���̍Đ�
	int re = 0;
	for(int i = 0; i < CUTIN_MAX; i++) {
		if(cutin[i].type != -1) {
			cutin[i].Cnt++;
			if(cutin[i].Cnt > cutin[i].speed * cutin[i].sheets - 1) {
				cutin[i].Cnt = 0;
				cutin[i].type = -1;
				re = 1;
				break;
			}
		}
	}
	return re;
};

void Cutin::Draw() {
	//�J�b�g�C���̕`��
	for(int i = 0; i < CUTIN_MAX; i++) {
		if(cutin[i].type != -1) {
			DrawGraph(cutin[i].x, cutin[i].y, _image->GetCgCutin(cutin[i].type,(cutin[i].Cnt / cutin[i].speed) % cutin[i].sheets), true);
		}
	}
};