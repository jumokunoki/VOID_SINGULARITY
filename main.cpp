
#include "DxLib.h"
#include "gamemain.h"
#include "main.h"
#include <time.h>
#include "relay_point.h"

void New_Variable();
void Gamemain();	// gamemain.cpp �Ɏ��̂��L�q

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{

	SetOutApplicationLogValidFlag(false);
	// ������ -------------------------------------------------------------------------
	// �c�w���C�u��������������
	SetGraphMode(SCREEN_W, SCREEN_H, SCREEN_DEPTH);	// ��ʂ̉𑜓x����1280�~�c720�A1�h�b�g������32�r�b�g�Ɏw�肷��
	ChangeWindowMode(true);							// �E�B���h�E���[�h�Ɏw�肷��
	if(DxLib_Init() == -1)
	{	// �G���[���N�����璼���ɏI��
		return -1;
	}
	SetDrawScreen(DX_SCREEN_BACK);		// �`����ʂ𗠉�ʂɃZ�b�g
	srand((unsigned)time(NULL));

	//�N���X�ǂݍ���
	New_Variable();

	// �Q�[�����C��
	Gamemain();

	

	// ��� ---------------------------------------------------------------------------
	DxLib_End();		// �c�w���C�u�����g�p�̏I������

	// �I��
	return 0;
}