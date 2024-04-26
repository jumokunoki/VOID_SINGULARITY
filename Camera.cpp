//�@�J����

#include "camera.h"
#include "gamemain.h"
#include "mymath.h"
#include "main.h"

Camera::Camera() {
	_pos = VGet(SCREEN_W / 2, SCREEN_H / 2, 0);
	_lookat = VGet(SCREEN_W / 2, SCREEN_H / 2, 0);
	_scale = 1.0f;
	_rotate = 0.0f;
}
Camera::~Camera() {
	// �������Ȃ�
}

void	Camera::Process() {

	// �ʒu�����~�b�g�𒴂��Ȃ��悤�Ɂi��]�͉��������j
	float left, top, right, bottom;
	left = _rcLimit.x + _lookat.x / _scale;
	right = (_rcLimit.x + _rcLimit.w) - _lookat.x / _scale;
	top = _rcLimit.y + _lookat.y / _scale;
	bottom = (_rcLimit.y + _rcLimit.h) - _lookat.y / _scale;
	_pos.x = Clamp(left, right, _pos.x);
	_pos.y = Clamp(top, bottom, _pos.y);


	// View�s��̐���
	MATRIX m = MGetTranslate(VScale(_pos, -1));				// �J�����ʒu��*-1����
	m = MMult(m, MGetScale(VGet(_scale, _scale, 1)));		// Z�����̔{����1�̂܂�
	m = MMult(m, MGetRotZ(DegToRad(_rotate)));				// 2D��x,y����]������ɂ́A3D�Ȃ�Z����]�ɂȂ�
	m = MMult(m, MGetTranslate(_lookat));					// �����_�����炷
	_mView = m;
}