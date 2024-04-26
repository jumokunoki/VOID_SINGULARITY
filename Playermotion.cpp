/*****************************************************************//**
 * \file   Playermotion.cpp
 * \brief  プレイヤーモーション
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#include "Player.h"

//プレイヤーのモーションをまとめたｃｐｐ

void Player::DoFrameCount(int stock) {
	SetMotSpeed();
	_gPlayer.motcnt++;

	if(_gPlayer.motcnt >= _gPlayer.motspeed) {
		_gPlayer.motaddnum++;
		_gPlayer.motcnt = 0;
	}
	//一定の値まで行ったらモーションを０にする
	if(_gPlayer.motspeed * _gPlayer.motaddnum > _gPlayer.motspeed * (_gPlayer.motsheet - 1)) {
		_gPlayer.motaddnum = 0;
		_gPlayer.motcnt = 0;
		//ループする番号の指定
		if(_gPlayer.motten == 3) {
			_gPlayer.motaddnum = 17;
		}
		else if( _gPlayer.motten == 4 || _gPlayer.motten == 5 || _gPlayer.motten == 6 ) {
			_gPlayer.motaddnum = 40;
		}
		//ジャンプ後はたちのモーション
		if(_gPlayer.motten == 2 ) {
			_gPlayer.motten = 0;
		}
	}

	//ｈｐが0になったらたちのモーションに変更
	if (_gPlayer.hp <= 0 && stock <= 0) {
		_gPlayer.motone = 0;
		_gPlayer.motten = 0;
	}
}
void Player::SetMotSpeed() {
	//モーションスピードを変えたいときはシートの番号を入れてモーションスピードを変える
	switch(_gPlayer.motten) {
	case 0:
		if (_gPlayer.motaddnum == 30) {
			if (_gPlayer.motcnt == 0) {
				_gPlayer.loop++;
			}
			if (_gPlayer.loop == 5) {
				_music->MakeVoice(STAND_VOICE, RANDAM_TWO);
				_gPlayer.loop = 0;
			}
		}
		break;
	case 1:
		break;
	case 2:
		if (_gPlayer.motaddnum == 13) {
			_gPlayer.falling_mot = 0;
		}
		if (_gPlayer.motaddnum == 16) {
			_gPlayer.motspeed = 6;
		}
		if(_gPlayer.motaddnum == 20) {
			if(CheckSoundMem(_image->Se[20]) != 1) {
				_music->MakeSe(_image->Se[20]);
			}
		}
		if(_gPlayer.motaddnum >= 21) {
			_gPlayer.motspeed = 4;
		}
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	}
}
void Player::ChengeFrameCount(int handred, int ten, int one, int oldmot) {
	//前のモーション番号と違ったらモーションを変更する
	if (oldmot != 0 + (ten * 10) + 0) {
		_gPlayer.motaddnum = 0;
		_gPlayer.motcnt = 0;
		_gPlayer.loop = 0;
		switch (handred) {
		case 0: {
			switch (ten) {
			case 0:
				//たち
				_gPlayer.motsheet = 31;
				_gPlayer.motspeed = 4;
				break;
			case 1:
				//歩き
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 2;
				break;
			case 2:
				//ジャンプ
				_gPlayer.motsheet = 24;
				_gPlayer.motspeed = 1;
				_gPlayer.motaddnum = 3;
				break;
			case 3:
				//通常弾
				_gPlayer.motsheet = 21;
				_gPlayer.motspeed = 3;
				break;
			case 4:
				//反射弾
				_gPlayer.motsheet = 60;
				_gPlayer.motspeed = 1;
				break;
			case 5:
				//貫通弾
				_gPlayer.motsheet = 60;
				_gPlayer.motspeed = 1;
				break;
			case 6:
				//黒武器
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 3;
				break;
			case 7:
				//歩き＋通常弾
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 2;
				break;
			case 8:
				//歩き＋反射弾
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 2;
				break;
			}
		}
		case 1: {
			switch (ten) {
			case 0:
				//たち
				_gPlayer.motsheet = 31;
				_gPlayer.motspeed = 4;
				break;
			case 1:
				//歩き
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 2;
				break;
			case 2:
				//ジャンプ
				_gPlayer.motsheet = 24;
				_gPlayer.motspeed = 1;
				_gPlayer.motaddnum = 3;

				break;
			case 3:
				//通常弾
				_gPlayer.motsheet = 21;
				_gPlayer.motspeed = 1;
				break;
			case 4:
				//反射弾
				_gPlayer.motsheet = 60;
				_gPlayer.motspeed = 1;
				break;
			case 5:
				//貫通弾
				_gPlayer.motsheet = 60;
				_gPlayer.motspeed = 1;
				break;
			case 6:
				//黒武器
				_gPlayer.motsheet = 60;
				_gPlayer.motspeed = 1;
				break;
			case 7:
				//歩き＋通常弾
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 2;
				break;
			case 8:
				//歩き＋反射弾
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 2;
				break;
			}
		}
		}
	}

	//歩きかつ銃を撃つモーションの時に止まったら銃を構えた状態から始める
	if (oldmot == 70 && ten * 10 == 30) {
		_gPlayer.motaddnum = 17;
	}
	else if (oldmot == 80 && ten * 10 == 40) {
		_gPlayer.motaddnum = 40;
	}

}