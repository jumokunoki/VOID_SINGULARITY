/*****************************************************************//**
 * \file   Fade.cpp
 * \brief  �t�F�[�h
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/
#include "Fade.h"
#include "dxlib.h"
#include "mymath.h"

Fades::Fades() {

	Fade.scene_change = 0;
	Fade.type = 0;
	Fade._FadeIn = 255;
	Fade.FadeColor = 0;
	Fade.hang = 0;
	Fade.all_fade_count = 0;
	Fade.add_frame = 0;

	chara_fade.scene_change = 0;
	chara_fade.type = 0;
	chara_fade._FadeIn = 0;
	chara_fade.FadeColor = 0;
	chara_fade.hang = 1;
	chara_fade.all_fade_count = 0;
	chara_fade.add_frame = 0;

};

Fades::~Fades() {

};

void Fades::FadeSet(int in_out, int color_type, int frame, int type) {

	// in_out    0:in   1:out          color_type 0:black  1:white
	if(Fade.add_frame >= Fade.all_fade_count && Fade.type == 0) {
		Fade.add_frame = 0;
		Fade.type = type;
		switch(color_type) {
		case 0:
			Fade.FadeColor = GetColor(0, 0, 0);
			break;
		case 1:
			Fade.FadeColor = GetColor(255, 255, 255);
			break;
		}

		switch(in_out) {
		case 0:
			Fade.hang = -1;
			Fade.all_fade_count = frame;
			Fade._FadeIn = 255;
			break;
		case 1:
			Fade.hang = 1;
			Fade.all_fade_count = frame;
			Fade._FadeIn = 0;
			break;
		}
	}
};

void Fades::CharaFadeSet() {
	if (chara_fade.add_frame >= chara_fade.all_fade_count) {
		chara_fade.add_frame = 0;
		chara_fade.all_fade_count = 30;
		chara_fade._FadeIn = 0;
	}
}

void Fades::FadeProcess() {

	if (chara_fade.add_frame <= chara_fade.all_fade_count) {
		chara_fade.add_frame++;
		float add = (float)255 / (float)chara_fade.all_fade_count;
		chara_fade._FadeIn += add * chara_fade.hang;
	}
	else {
		chara_fade._FadeIn = 0;
	}

	if(Fade.add_frame <= Fade.all_fade_count) {
		Fade.add_frame++;
		float add = (float)255 / (float)Fade.all_fade_count;
		Fade._FadeIn += add * Fade.hang;
	}
	switch(Fade.type) {
	case 0: {
		//�������Ȃ�
		break;
	}
	case 1: {
		//�N���A�̏���
		if(Fade._FadeIn >= 255) {
			StopSoundMem(_image->Bgm[7]);
			if(Fade.add_frame++ >= Fade.all_fade_count * 2) {
				Fade.hang *= -1;
				Fade.add_frame = 0;
				Fade.scene_change = 1;
			}
		}
		break;
	}
	case 2: {
		if(Fade._FadeIn >= 255 ) {
			Fade._FadeIn = 0;
			//�Q�[���I�[�o�[�Ɉړ�
			Fade.scene_change = 2;
		}
		break;
	}
	case 3: {
		if(Fade._FadeIn >= 255) {
			Fade.hang *= -1;
			Fade.add_frame = 0;
			Fade.scene_change = 3;
		}
		else if (Fade.hang == -1) {
			if (Fade._FadeIn <= 0) {
				//�`���[�g���A���Ɉړ�
				Fade.scene_change = 4;
			}
		}
		break;
	}
	case 4: {
		break;
	}
	}

	if(Fade._FadeIn >= 255) {
		Fade._FadeIn = 255;
	}

	if(Fade._FadeIn <= 0) {
		Fade._FadeIn = 0;
	}
};

int  Fades::CheckFadeMove() {
	//�t�F�[�h���O���ȏォ�m�F���邽�߂̊֐�
	if(Fade.add_frame < (float)Fade.all_fade_count * (float)0.3f) {
		return 0;
	}
	return 1;
};

void Fades::PortalIn(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int GrHandle, int Color, int turn)
{
	// ��]�~�g�k�~���s�ړ�
	MATRIX mRot = MGetRotZ(angle);						// 2D��x,y����]������ɂ́A3D�Ȃ�Z����]�ɂȂ�
	MATRIX mScale = MGetScale(VGet(zoom, zoom, 1));		// Z�����̔{����1�̂܂�
	MATRIX mTrans = MGetTranslate(position);
	MATRIX m;
	m = MMult(mRot, mScale);
	m = MMult(m, mTrans);
	m = MMult(m, mView);

	// �`�悷��摜��4�̒��_���W
	VECTOR pos[4] = {
		// �ʏ�p�i���ォ��E���j
		VGet(-width / 2.0, -height / 2.0, 0),	// ����
		VGet(width / 2.0, -height / 2.0 ,0),	// �E��
		VGet(width / 2.0,  height / 2.0 ,0),	// �E��
		VGet(-width / 2.0,  height / 2.0 ,0),	// ����
	};

	// 4�̒��_���W�S�Ăɍs����|���ĕϊ�����
	for (int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}

	// �y�o�b�t�@��L���ɂ���
	SetUseZBufferFlag(TRUE);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, chara_fade._FadeIn);


	// �y�o�b�t�@�ɉ摜�Ɠ����傫���̃}�X�N����������
	DrawBoxToZBuffer(pos[0].x, pos[0].y, pos[2].x, pos[2].y, TRUE, DX_ZWRITE_MASK);

	// �y�o�b�t�@�ɉ摜�̌`�Ń}�X�N�𙊂�т�
	DrawExtendGraphToZBuffer(pos[0].x, pos[0].y,  pos[2].x, pos[2].y, GrHandle, DX_ZWRITE_CLEAR);

	// �摜�̑傫���̃{�b�N�X��`�悷��(�}�X�N������т���Ă���Ƃ��낵���h��Ԃ���Ȃ�)
	DrawBox(pos[0].x, pos[0].y, pos[2].x, pos[2].y, Color, TRUE);


	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	// �y�o�b�t�@�𖳌��ɂ���
	SetUseZBufferFlag(FALSE);
}

//void  Fades::PortalIn(int x, int y, int GrHandle, int Color)
//{
//	int w, h;
//
//	// �摜�̃T�C�Y���擾����
//	GetGraphSize(GrHandle, &w, &h);
//
//	// �y�o�b�t�@��L���ɂ���
//	SetUseZBufferFlag(TRUE);
//
//	// �y�o�b�t�@�ɉ摜�Ɠ����傫���̃}�X�N����������
//	DrawBoxToZBuffer(x, y, x + w, y + h, TRUE, DX_ZWRITE_MASK);
//
//	// �y�o�b�t�@�ɉ摜�̌`�Ń}�X�N�𙊂�т�
//	DrawGraphToZBuffer(x, y, GrHandle, DX_ZWRITE_CLEAR);
//
//	// �摜�̑傫���̃{�b�N�X��`�悷��(�}�X�N������т���Ă���Ƃ��낵���h��Ԃ���Ȃ�)
//	DrawBox(x, y, x + w, y + h, Color, TRUE);
//
//	// �y�o�b�t�@�𖳌��ɂ���
//	SetUseZBufferFlag(FALSE);
//}