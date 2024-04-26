/*****************************************************************//**
 * \file   GameInput.cpp
 * \brief  �v���C���[�̓��͏��
 *
 * \author �ޗǏ[���A�V�� ��H
 * \date   August 2023
 *********************************************************************/

// �ȑO����̗��p�i�i�K�v�Ƃ���ΕύX�A�����l�����͕s�v�j
#include "GameInput.h"
#include "gamemain.h"
#include "DxLib.h"

GameInput::GameInput() {
	for(int i = 0; i < PLAYER_MAX; i++) {
		_gKey[i] = 0;
		_gTrg[i] = 0;
		_gRel[i] = 0;
		pin[i]._useID = 0;
		pin[i]._playerID = 0 + i;
		for(int j = 0; j < 3; j++) {
			pin[i]._W_useID = 0;
		}
	}
}

GameInput::~GameInput() {
}

void GameInput::Input() {
	// �L�[�̓��́A�g���K���͂𓾂�
	int keyold[PLAYER_MAX];
	keyold[PLAYER_ONE] = _gKey[PLAYER_ONE];


	_gKey[PLAYER_ONE] = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// �L�[���͂��擾

	for(int i = 0; i < PLAYER_MAX; i++) {
		_gTrg[i] = (_gKey[i] ^ keyold[i]) & _gKey[i];          // �L�[�̃g���K��񐶐��i�������u�Ԃ����������Ȃ��L�[���j
		_gRel[i] = (_gKey[i] ^ keyold[i]) & ~_gKey[i];
	}
}

int GameInput::CheckAllButton() {

	int all_button = 16; 

	for (int padnum = 0; padnum < PLAYER_MAX; padnum++) {
		for (int i = 0; i < 13; i++) {
			if (_gTrg[padnum] & all_button) {
				return 1;
			}
			all_button += all_button;
		}
	}
	return 0;
};


int GameInput::CheckMoveButton() {

	int move_button = 2;

	for (int padnum = 0; padnum < PLAYER_MAX; padnum++) {
		for (int i = 0; i < 2; i++) {
			if (_gKey[padnum] & move_button) {
				return 1;
			}
			move_button += move_button;
		}
	}
	return 0;
};