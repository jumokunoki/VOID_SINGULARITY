/*****************************************************************//**
 * \file   GameInput.cpp
 * \brief  プレイヤーの入力情報
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

// 以前からの流用品（必要とあらば変更、複数人数分は不要）
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
	// キーの入力、トリガ入力を得る
	int keyold[PLAYER_MAX];
	keyold[PLAYER_ONE] = _gKey[PLAYER_ONE];


	_gKey[PLAYER_ONE] = GetJoypadInputState(DX_INPUT_KEY_PAD1);		// キー入力を取得

	for(int i = 0; i < PLAYER_MAX; i++) {
		_gTrg[i] = (_gKey[i] ^ keyold[i]) & _gKey[i];          // キーのトリガ情報生成（押した瞬間しか反応しないキー情報）
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