//�@�J����

#pragma once
#include "DxLib.h"		// VECTOR��MATRIX���`�Ƃ��Ďg�����߁A.h�ɓ���Ă���
#include "mymath.h"

class Camera {
public:
	Camera();
	~Camera();

	void	Process();
	float GetScale() { return _scale; }

	void SetrcLimit(MYRECT rc) { _rcLimit = rc; }
	void SetPos(VECTOR pos) { _pos = pos; }
	void  Setscale(float scale) { _scale = scale; }

	MATRIX	GetViewMatrix() { return _mView; }

protected:
	
	MATRIX	_mView;		// View�s��
	VECTOR	_pos;		// �J�����̈ʒu�Bworld���W��
	VECTOR	_lookat;	// �J�����̒����_�B��ʂ̂����𒆐S�ɁA�g��/��]������
	float	_scale;		// �J�����̊g�嗦
	float	_rotate;	// �J�����̉�]�idegree)

	MYRECT	_rcLimit;	// world���W�Ń��~�b�g�ݒ�


};


