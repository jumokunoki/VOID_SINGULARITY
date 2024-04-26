/*****************************************************************//**
 * \file   GameInput.h
 * \brief  �v���C���[�̓��͏��
 *
 * \author �ޗǏ[��
 * \date   August 2023
 *********************************************************************/

#pragma once
#define PLAYER_MAX       4
#define PLAYER_ONE       0
#define PLAYER_TWO       1
#define PLAYER_THREE     2
#define PLAYER_FOUR      3

class GameInput
{
public:
	GameInput();			// �R���X�g���N�^
	virtual ~GameInput();	// �f�X�g���N�^

	int     CheckAllButton();
	int     CheckMoveButton();
	void    Input();

public:
	int _gKey[PLAYER_MAX];			// 1P:0,2P:1,3P:2,4P:3
	int _gTrg[PLAYER_MAX];		
	int _gRel[PLAYER_MAX];		

	struct PLAYERINFO {        // ���e�͍쐬����Q�[���ɉ����ĕύX
		int _playerID;         // �v���C���[�̃Q�[���ʂ��Ă̔ԍ�
		int _useID;            // �v���C���[���g���Ă���L������ID
		int _W_useID;          // �v���C���[���I����������
	};

	PLAYERINFO pin[PLAYER_MAX];
};
