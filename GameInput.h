/*****************************************************************//**
 * \file   GameInput.h
 * \brief  プレイヤーの入力情報
 *
 * \author 奈良充樹
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
	GameInput();			// コンストラクタ
	virtual ~GameInput();	// デストラクタ

	int     CheckAllButton();
	int     CheckMoveButton();
	void    Input();

public:
	int _gKey[PLAYER_MAX];			// 1P:0,2P:1,3P:2,4P:3
	int _gTrg[PLAYER_MAX];		
	int _gRel[PLAYER_MAX];		

	struct PLAYERINFO {        // 内容は作成するゲームに応じて変更
		int _playerID;         // プレイヤーのゲーム通しての番号
		int _useID;            // プレイヤーが使っているキャラのID
		int _W_useID;          // プレイヤーが選択した武器
	};

	PLAYERINFO pin[PLAYER_MAX];
};
