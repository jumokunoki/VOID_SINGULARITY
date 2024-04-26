// �Ǝ��`�惉�C�u����
#include "mydraw.h"

// �摜�̒��S�ŉ�]���ĕ`�悷��
void _MyDrawModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle, int turn) {
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
	if(turn != 0) {
		// ���]�p
		VECTOR posTurn[4] = {
			// ���]�p�i�E�ォ�獶���j
			VGet(width / 2.0, -height / 2.0 ,0),	// �E��
			VGet(-width / 2.0, -height / 2.0, 0),	// ����
			VGet(-width / 2.0,  height / 2.0 ,0),	// ����
			VGet(width / 2.0,  height / 2.0 ,0),	// �E��
		};
		for(int i = 0; i < 4; i++) {
			pos[i] = posTurn[i];
		}
	}

	// 4�̒��_���W�S�Ăɍs����|���ĕϊ�����
	for(int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}
	// �ϊ��������W�ŕ`�悷��
	DrawModiGraph(
		pos[0].x, pos[0].y,
		pos[1].x, pos[1].y,
		pos[2].x, pos[2].y,
		pos[3].x, pos[3].y,
		cgHandle, true);
}


void MyDrawModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle) {
	// ���E���]���Ȃ�
	_MyDrawModiGraph(mView, position, zoom, angle, width, height, cgHandle, 0);
}

void MyDrawTurnModiGraph(MATRIX mView, VECTOR position, float zoom, float angle, int width, int height, int cgHandle) {
	// ���E���]����
	_MyDrawModiGraph(mView, position, zoom, angle, width, height, cgHandle, 1);
}





// 4�_���w�肵�Ďl�p��`��
void MyDraw4PointBox(MATRIX mView, VECTOR pos[4], unsigned int Color, int FillFlag) {
	MATRIX m = mView;

	// 4�̒��_���W�S�Ăɍs����|���ĕϊ�����
	for(int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}

	// �h��Ԃ����H
	if(FillFlag == 0) {
		// �ϊ��������W�ŁA���Ŏl�p��`�悷��
		DrawLine(
			pos[0].x, pos[0].y,	// ����
			pos[1].x, pos[1].y,	// �E��
			Color);
		DrawLine(
			pos[1].x, pos[1].y,	// �E��
			pos[3].x, pos[3].y,	// �E��
			Color);
		DrawLine(
			pos[3].x, pos[3].y,	// �E��
			pos[2].x, pos[2].y,	// ����
			Color);
		DrawLine(
			pos[2].x, pos[2].y,	// ����
			pos[0].x, pos[0].y,	// ����
			Color);
	}
	else {
		// �ϊ��������W�ŁA�O�p�`�Q��`�悷��
		DrawTriangle(
			pos[0].x, pos[0].y,	// ����
			pos[1].x, pos[1].y,	// �E��
			pos[2].x, pos[2].y,	// ����
			Color, FillFlag);
		DrawTriangle(
			pos[1].x, pos[1].y,	// �E��
			pos[2].x, pos[2].y,	// ����
			pos[3].x, pos[3].y,	// �E��
			Color, FillFlag);
	}
}

// ��`��`��
void MyDrawBox(MATRIX mView, int x1, int y1, int x2, int y2, unsigned int Color, int FillFlag) {
	VECTOR pos[4] = {
		VGet(x1,		y1,		0),	// ����
		VGet(x2 - 1,	y1,		0),	// �E��
		VGet(x1,		y2 - 1,	0),	// ����
		VGet(x2 - 1,	y2 - 1,	0),	// �E��
	};
	MyDraw4PointBox(mView, pos, Color, FillFlag);
}


void MyDrawDeformationGraph(MATRIX mView, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4, float direction, int handle, int FillFlag) {
	VECTOR pos[4] = {
		VGet(x1,		y1,		0),	// ����
		VGet(x2 - 1,	y2,		0),	// �E��
		VGet(x3,		y3 - 1,	0),	// ����
		VGet(x4 - 1,	y4 - 1,	0),	// �E��
	};
	MATRIX mRot = MGetRotZ(direction);
	MATRIX m = mView;
	//m = MMult(m, mRot);

	// 4�̒��_���W�S�Ăɍs����|���ĕϊ�����
	for(int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}
	DrawModiGraph(pos[0].x, pos[0].y, pos[1].x, pos[1].y, pos[2].x, pos[2].y, pos[3].x, pos[3].y, handle, FillFlag);
}



void MyDrawExtendGraph(MATRIX mView, int x1, int y1, int x2, int y2, unsigned int handle, int FillFlag) {
	VECTOR pos[4] = {
		VGet(x1,		y1,		0),	// ����
		VGet(x2 - 1,	y1,		0),	// �E��
		VGet(x1,		y2 - 1,	0),	// ����
		VGet(x2 - 1,	y2 - 1,	0),	// �E��
	};
	MATRIX m = mView;
	for(int i = 0; i < 4; i++) {
		pos[i] = VTransform(pos[i], m);
	}
	DrawExtendGraph(pos[0].x, pos[0].y, pos[3].x, pos[3].y, handle, FillFlag);
}
void MyDrawRect(MATRIX mView, MYRECT_PLUS rc, unsigned int Color, int FillFlag){
	MyDrawBox(mView, rc.x, rc.y, rc.x+rc.w, rc.y+rc.h, Color, FillFlag);
}

void MyDrawLine(MATRIX mView, int x1, int y1, int x2, int y2, int Color ) {
	VECTOR pos[] = {
		VGet(x1,		y1,		0),	// 1
		VGet(x2 - 1,	y2,		0),	// 2
	};
	MATRIX m = mView;
	for(int i = 0; i < 2; i++) {
		pos[i] = VTransform(pos[i], m);
	}
	DrawLineAA(pos[0].x, pos[0].y, pos[1].x, pos[1].y, Color);
}
void MyDrawCircle(MATRIX mView, int x, int y, int r) {
	MATRIX m = mView;
	VECTOR pos;
	pos = VGet(x, y, 0);

	pos = VTransform(pos, m);

	DrawCircle(pos.x, pos.y, r, GetColor(0,168,0), TRUE);


}

// �ʒu�𑵂��ĕ������`��
// posBaseX = -1:������, 0:����, 1:�E����
void DrawPosString(int x, int y, int posBaseX, unsigned int color, const char* str) {
	int w = GetDrawStringWidth(str, strlen(str));	// �`�悷�镶���̉��T�C�Y�𓾂�
	if(posBaseX == 0) {
		// ���������Ȃ̂�x�ʒu�����ɔ������炷
		x -= w / 2;
	}
	else if(posBaseX > 0) {
		// �E�����Ȃ̂�x�ʒu�����ɂ��炷
		x -= w;
	}
	DrawString(x, y, str, color);
}
