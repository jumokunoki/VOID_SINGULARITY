/*****************************************************************//**
 * \file   Player.cpp
 * \brief  プレイヤーの挙動
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#include "player.h"
#include "gamemain.h"
#include "mydraw.h"
#include "DxLib.h"
#include "PlayerBullet.h"
#include "EnemyBullet.h"

Player::Player() {

	_gPlayer.type = CHARA_TYPE_PLAYER;
	_gPlayer.x = 120;
	_gPlayer.y = 1450;
	_gPlayer.arrow = 0;
	_gPlayer.useGravity = 1;
	_gPlayer.w = 300;
	_gPlayer.h = 300;
	_gPlayer.hit.x = _gPlayer.x + 135;
	_gPlayer.hit.y = _gPlayer.y + 85;
	_gPlayer.hit.w = PLAYER_W;
	_gPlayer.hit.h = PLAYER_H;

	_gPlayer.hp = _Save->GetNowHp();
	_gPlayer.maxhp = _Save->GetMaxHp();
	_gPlayer.arrow = 1;
	_gPlayer.aiming = 0;
	_gPlayer.isAim = 0;
	_gPlayer.gravity = 0;	// 重力による加速値
	_gPlayer.stand = 0;		// 床フラグ。着地していたら1

	_gPlayer.motaddnum = 0;
	_gPlayer.motcnt = 0;
	_gPlayer.mothandred = 1;
	_gPlayer.motten = 0;
	_gPlayer.motone = 0;
	_gPlayer.motsheet = 31;
	_gPlayer.motspeed = 4;
	_gPlayer.falling_mot = 1;
	_gPlayer.oldmot = 0;
	_gPlayer.loop = 0;

	b_select.BWPselect = 0;
	b_select.bulletType = 0;
	// 以下ストーリー中解放
    _Re_release  = _Save->GetRereas(0);
	_Tr_release  = _Save->GetRereas(1);

	_S_damjudge = false;
	_invijudge = false;
	_invincible_time = 0;

	_hitslideX = 0;
	_hitslideY = 0;

	jampcount = 0;
	waitcount = 0;

	_gPlayer.Portal_invincibility = 0;
	_gPlayer.Portal_delete = 0;

	port.x = 0;
	port.y = 0;
	port.count = 20;
	port.max_count = 20;

	_start_point = VGet(0, 0, 0);
	_terminal = VGet(0, 0, 0);
}


Player::~Player() {

}

void Player::PosHitSynchro() {
	// 移動後の当たり判定座標の更新（プレイヤー座標が移動したら差し入れる）
	_gPlayer.hit.x = _gPlayer.x + 135;
	_gPlayer.hit.y = _gPlayer.y + 85;
}


void Player::Gravity() {
	// 重力処理
	_gPlayer.gravity += 1.0;			
	_gPlayer.y += _gPlayer.gravity;
	_gPlayer.stand = 0;
	PosHitSynchro();
}

void Player::DetectGravity(int Gjudge) {
	// 上下の当たり判定
	if(Gjudge != 0) {
		// 当たった。当たったのは床か？（重力値はプラスだったか？）
		if(_gPlayer.gravity > 0)
		{
			_gPlayer.stand = 1;	// 床に当たったのでフラグセット
			_gPlayer.falling_mot = 1;
			
		}
		_gPlayer.gravity = 0;		// 重力による加速値をリセット
	}
	
	if (_gPlayer.stand != 1 && _gPlayer.falling_mot == 1) {
		if (_gPlayer.gravity >= 0) {
			//落下中は途中からのジャンプモーションの切り替え
			_gPlayer.motten = 2;
			_gPlayer.oldmot = _gPlayer.motten * 10;
			_gPlayer.motsheet = 24;
			_gPlayer.motspeed = 2;
			_gPlayer.motaddnum = 14;
			_gPlayer.falling_mot = 0;
		}
	}

}

void Player::PotInvProcess() {
	if (_gPlayer.Portal_invincibility > 0) {
		_gPlayer.Portal_invincibility--;
	}
};

void Player::MoveProcess() {
	// プレイヤーの移動プロセス
	if(_gPlayer.motten != 2 &&_gPlayer.motten != 5 && _gPlayer.motten != 6) {
		_gPlayer.motten = 0;
	}

	if (GetHp() > 0) {

		_gPlayer.Rspeed = 0;

		if ((gPad._gKey[0] & PAD_INPUT_6) == 0 || b_select.bulletType < 2) {
			if (gPad._gKey[0] & PAD_INPUT_LEFT) {
				_gPlayer.Rspeed = -10;
				_gPlayer.x += _gPlayer.Rspeed;
				PosHitSynchro();
				_gPlayer.arrow = -1;
				_gPlayer.mothandred = 0;
				if (_gPlayer.motten != 2 && _gPlayer.stand == 1) {
					_gPlayer.motten = 1;
				}
				if (CheckSoundMem(_image->Se[16]) != 1) {
					_music->MakeSe(_image->Se[16]);
				}
			}
			if (gPad._gKey[0] & PAD_INPUT_RIGHT) {
				_gPlayer.Rspeed = 10;
				_gPlayer.x += _gPlayer.Rspeed;
				PosHitSynchro();
				_gPlayer.arrow = 1;
				_gPlayer.mothandred = 1;
				if (_gPlayer.motten != 2 && _gPlayer.stand == 1) {
					_gPlayer.motten = 1;
				}
				if (CheckSoundMem(_image->Se[16]) != 1) {
					_music->MakeSe(_image->Se[16]);
				}
			}

			if (_gPlayer.motten != 2) {
				if (gPad._gTrg[0] & PAD_INPUT_3) {
					if (_gPlayer.stand == 1) {
						jampcount = 1;
						waitcount = 9;
						_gPlayer.motten = 2;
					}
				}
			}
			else if (_gPlayer.motten == 2 && 18 <= _gPlayer.motaddnum) {//20は屈伸するシートナンバー
				if (gPad._gTrg[0] & PAD_INPUT_3) {
					if (_gPlayer.stand == 1) {
						_gPlayer.motaddnum = 4;
						_gPlayer.motcnt = 0;
						jampcount = 1;
						waitcount = 9;
						_gPlayer.motten = 2;
						_gPlayer.motspeed = 1;
						_music->MakeVoice(JUMP_VOICE, RANDAM_TWO);
					}
				}
			}

			if (jampcount == 1) {
				waitcount--;
				if (waitcount < 0) {
					if (_gPlayer.gravity >= 0) {
						_gPlayer.gravity = -25;
						_gPlayer.motspeed = 6;
						jampcount = 0;
						waitcount = 0;
						_music->MakeSe(_image->Se[19]);
						_music->MakeVoice(JUMP_VOICE, RANDAM_TWO);
						PosHitSynchro();
					}
				}
			}

		}
	}

	if(_hitslideX < 0) {
		_hitslideX++;
		PosHitSynchro();
	}
	if(_hitslideX > 0) {
		_hitslideX--;
		PosHitSynchro();
	}
	if(_hitslideY < 0) {
		_hitslideY++;
		PosHitSynchro();
	}
	if(_hitslideY > 0) {
		_hitslideY--;
		PosHitSynchro();
	}

	if(_gPlayer.motten != 1) {
		_music->StopSe(_image->Se[16]);
	}
}

void Player::HitObj(HITSLIDE HitObj,MYRECT_PLUS enemy) {
	// ステージに存在する敵やアイテムギミックに触れたときの挙動
	_hitslideX = HitObj.slide_x;
	_hitslideY = HitObj.slide_y;

	if(HitObj.hit != 0) {
		// 体力減少処理とノックバック数値変更
		switch(HitObj.hit) {
		case CHARA_TYPE_ENEMY1:
		case CHARA_TYPE_ENEMY2:
		case CHARA_TYPE_ENEMY3:
		case CHARA_TYPE_ENEMY4:
		case CHARA_TYPE_ENEMY5:
		case CHARA_TYPE_ENEMY6:
		case CHARA_TYPE_ENEMY7:
		case CHARA_TYPE_ENEMY8:
		case CHARA_TYPE_ENEMY9:
		case OBJ_TYPE_DOOR:
		{
			_gPlayer.x += _hitslideX;
			_gPlayer.y += _hitslideY;
			if(enemy.y < _gPlayer.hit.y + PLAYER_H) {
				if(_gPlayer.gravity > 0)
				{
					_gPlayer.stand = 1;	// 床に当たったのでフラグセット
				}
				_gPlayer.gravity = 0;		// 重力による加速値をリセット
			}

			break;
		}
		case Black_Hole:
		case Fix_Black_Hole:
		{
			
			if (_gPlayer.Portal_invincibility <= 30) {
			_gPlayer.x = _hitslideX;
			_gPlayer.y = _hitslideY;
			}
			if (HitObj.hit == Black_Hole) {
				_gPlayer.Portal_delete = 1;
			}

			break;
		}
		}
	}
}

void Player::AimProcess(int remRF, int remTR, int remBR, int remPW, int remPB, int direy) {
	// プレイヤーの照準指定
	// 武器セレクト
	if (gPad._gTrg[0] & PAD_INPUT_2) {
		if (remRF != 0 || remTR != 0 || remPW != 0 || remBR != 0 || remPB != 0) {
			_music->MakeSe(_image->Se[18]);
			b_select.bulletType++;
		}
	}
	//武器セレクトの初期化
	if (gPad._gTrg[0] & PAD_INPUT_5) {
		if (remRF != 0 || remTR != 0 || remPW != 0 || remBR != 0 || remPB != 0) {
			_music->MakeSe(_image->Se[18]);
			switch (b_select.bulletType) {
			case 0:
			case 1:
			case 2:
				b_select.bulletType = 3;
				break;
			case 3:
				b_select.bulletType = 0;
				break;
			}
		}
	}

	// 反射弾の時
	if (b_select.bulletType == 1) {
		if (_Re_release == 0 || remRF <= 0 && remPW <= 0) {
			b_select.bulletType++;
		}
		else if (remRF <= 0 && remPW != 0) {
			b_select.BWPselect = 1;
		}
		else if (remRF != 0 && remPW <= 0) {
			b_select.BWPselect = 0;
		}
	}
	// 貫通弾の時
	if (b_select.bulletType == 2) {
		if (_Tr_release == 0 || remTR <= 0 && remPW <= 0) {
			b_select.bulletType++;
		}
		else if (remTR <= 0 && remPW != 0) {
			b_select.BWPselect = 1;
		}
		else if (remTR != 0 && remPW <= 0) {
			b_select.BWPselect = 0;
		}
	}
	// 黒弾の時
	if (b_select.bulletType == 3) {
		if (remBR <= 0 && remPB <= 0) {
			b_select.bulletType = 0;
		}
		else if (remBR <= 0 && remPB != 0) {
			b_select.BWPselect = 2;
		}
		else if (remBR != 0 && remPB <= 0) {
			b_select.BWPselect = 0;
		}
	}
	// 黒弾の次は最初に戻る
	if (3 < b_select.bulletType) {
		b_select.bulletType = 0;
	}


	switch (b_select.bulletType) {
	case 0:
		if (gPad._gKey[0] & PAD_INPUT_8 || gPad._gKey[0] & PAD_INPUT_6) {
			_gPlayer.motten = 3;
			if (gPad._gKey[0] & PAD_INPUT_LEFT) {
				_gPlayer.motten = 7;
				_gPlayer.Rspeed = +2;
				_gPlayer.x += _gPlayer.Rspeed;
			}
			else if (gPad._gKey[0] & PAD_INPUT_RIGHT) {
				_gPlayer.motten = 7;
				_gPlayer.Rspeed = -2;
				_gPlayer.x += _gPlayer.Rspeed;
			}
		}
		break;
	case 1:
		if (gPad._gKey[0] & PAD_INPUT_8 || gPad._gKey[0] & PAD_INPUT_6) {
			_gPlayer.motten = 4;
			if (gPad._gKey[0] & PAD_INPUT_LEFT) {
				_gPlayer.motten = 8;
				_gPlayer.Rspeed = +5;
				_gPlayer.x += _gPlayer.Rspeed;
			}
			else if (gPad._gKey[0] & PAD_INPUT_RIGHT) {
				_gPlayer.motten = 8;
				_gPlayer.Rspeed = -5;
				_gPlayer.x += _gPlayer.Rspeed;
			}
		}
		break;
	case 2:
		if (gPad._gTrg[0] & PAD_INPUT_8 ){
			if (direy >= 60) {
				_gPlayer.motten = 5;
			}
		}
		if(gPad._gKey[0] & PAD_INPUT_6) {
			_gPlayer.motten = 5;
		}
		break;
	case 3:
		if (gPad._gTrg[0] & PAD_INPUT_8){
			if (direy >= 20) {
				_gPlayer.motten = 6;
			}
		}
		if(gPad._gKey[0] & PAD_INPUT_6) {
			_gPlayer.motten = 6;
		}
		break;
	}


	// 弾の属性（ポータル弾）セレクト

	b_select.BWPselect = 0;

	if (gPad._gKey[0] & PAD_INPUT_6) {
		switch (b_select.bulletType) {
		case 0:
		case 1:
		case 2: {
				b_select.BWPselect = 1;
				break;
		}
		case 3: {
				b_select.BWPselect = 2;
				break;
		}
		}
	}


	// エイム（方向指定）
	_gPlayer.isAim = 0;

	if (gPad._gKey[0] & PAD_INPUT_7) {
		if (gPad.CheckMoveButton() == 0) {
			switch (b_select.bulletType) {
			case 0:
				_gPlayer.motten = 3;
				break;
			case 1:
				_gPlayer.motten = 4;
				break;
			case 2:
				_gPlayer.motten = 5;
				break;
			case 3:
				_gPlayer.motten = 6;
				break;
			}
		}
	}
	if (gPad._gKey[0] & PAD_INPUT_7) {
		_gPlayer.isAim = 1;

	}
	if (_gPlayer.isAim == 1) {
		if (_gPlayer.aiming == 2 && gPad._gKey[0] & PAD_INPUT_UP) {
			_gPlayer.aiming = 1;
		}
		else if (_gPlayer.aiming == 1 && gPad._gKey[0] & PAD_INPUT_DOWN) {
			_gPlayer.aiming = 2;
		}
		else if (_gPlayer.aiming == 0) {
			_gPlayer.aiming = 1;
		}
	}
	else {
		_gPlayer.aiming = 0;
		if (gPad._gKey[0] & PAD_INPUT_UP) {
			_gPlayer.aiming = 3;
			if (gPad._gKey[0] & PAD_INPUT_7) {
				_gPlayer.isAim = 1;
			}
		}
		if (gPad._gKey[0] & PAD_INPUT_DOWN) {
			_gPlayer.aiming = 4;
			if (gPad._gKey[0] & PAD_INPUT_7) {
				_gPlayer.isAim = 1;
			}
		}
	}

	switch (_gPlayer.aiming) {
	case 0:
		_gPlayer.motone = 0;
		break;
	case 1:
		_gPlayer.motone = 1;
		break;
	case 2:
		_gPlayer.motone = 3;
		break;
	case 3:
		_gPlayer.motone = 2;
		break;
	case 4:
		_gPlayer.motone = 4;
		break;
	}

	if (_gPlayer.motten < 3) {
		_gPlayer.motone = 0;
	}
	if (_gPlayer.motten == 3 || _gPlayer.motten == 4 || _gPlayer.motten == 7 || _gPlayer.motten == 8) {
		if (_gPlayer.motone == 4) {
			_gPlayer.motone = 3;
		}
	}


}

void Player::EffectDraw(MATRIX mview) {
	_effect->ShootDraw(mview, _gPlayer.x, _gPlayer.y, _gPlayer.arrow, _gPlayer.aiming);
}

void Player::DamageProcess(int hit) {
	// 弾に当たった時のダメージ判定
	if (_invijudge != true) {
		switch (hit) {
		case E_BULLET_1: {
			_gPlayer.hp -= 10;
			_S_damjudge = true;
			_invijudge = true;
			_music->MakeVoice(DAMEGE_VOICE, RANDAM_THREE);
			break;
		}
		case E_BULLET_2: {
			_gPlayer.hp -= 10;
			_S_damjudge = true;
			_invijudge = true;
			_music->MakeVoice(DAMEGE_VOICE, RANDAM_THREE);
			break;
		}
		case E_BULLET_3: {
			_gPlayer.hp -= 10;
			_S_damjudge = true;
			_invijudge = true;
			_music->MakeVoice(DAMEGE_VOICE, RANDAM_THREE);
			break;
		}
		case E_BULLET_4: {
			_gPlayer.hp -= 20;
			_S_damjudge = true;
			_invijudge = true;
			_music->MakeVoice(DAMEGE_VOICE, RANDAM_THREE);
			break;
		}
		case E_BULLET_5: {
			_gPlayer.hp -= 20;
			_S_damjudge = true;
			_invijudge = true;
			_music->MakeVoice(DAMEGE_VOICE, RANDAM_THREE);
			break;
		}
		case E_BULLET_6: {
			_gPlayer.hp -= 30;
			_S_damjudge = true;
			_invijudge = true;
			_music->MakeVoice(DAMEGE_VOICE, RANDAM_THREE);
			break;
		}
		case E_BULLET_7: {
			_gPlayer.hp -= 20;
			_S_damjudge = true;
			_invijudge = true;
			_music->MakeVoice(DAMEGE_VOICE, RANDAM_THREE);
			break;
		}
		case E_BULLET_8: {
			_gPlayer.hp -= 30;
			_S_damjudge = true;
			_invijudge = true;
			_music->MakeVoice(DAMEGE_VOICE, RANDAM_THREE);
			break;
		}
		case E_BULLET_9: {
			_gPlayer.hp -= 50;
			_S_damjudge = true;
			_invijudge = true;
			_music->MakeVoice(DAMEGE_VOICE, RANDAM_THREE);
			break;
		}
		case E_BULLET_10: {
			_gPlayer.hp -= 70;
			_S_damjudge = true;
			_invijudge = true;
			_music->MakeVoice(DAMEGE_VOICE, RANDAM_THREE);
			break;
		}
		}
	}
}

void Player::AddIT() {
	// 無敵時間のカウント
	if(_invijudge == true) {
		_invincible_time++;
		if(_invincible_time >= 60) {
			_invijudge = false;
			_invincible_time = 0;
		}
	}
}

void Player::PortalMoveSet(int PorX, int PorY) {
	port.x = PorX;
	port.y = PorY;
	port.count = 0;
};

void Player::PortalMoveProcess() {
	if (port.count < port.max_count) {
		port.count++;
		_gPlayer.x = EasingLinear(port.count, _gPlayer.x, port.x - 67, port.max_count);
		_gPlayer.y = EasingLinear(port.count, _gPlayer.y, port.y - 75, port.max_count);
	}
};

void Player::Draw(MATRIX mView) {
	// プレイヤーの描画
	VECTOR PL = VGet(_gPlayer.x + 150, _gPlayer.y + 150, 0);

	if (_gPlayer.motten == 1 && _gPlayer.mothandred == 0) {
		PL = VGet(_gPlayer.x + 185, _gPlayer.y + 150, 0);
		if (_invincible_time % 10 < 7) {
			MyDrawModiGraph(mView, PL, 1.f, 0.f, _gPlayer.w, _gPlayer.h, _image->Get_cgPlayer(_gPlayer.mothandred * 100 + _gPlayer.motten * 10 + _gPlayer.motone, _gPlayer.motaddnum));
		}
	}
	else {
		if (_invincible_time % 10 < 7) {
			MyDrawModiGraph(mView, PL, 1.f, 0.f, _gPlayer.w, _gPlayer.h, _image->Get_cgPlayer(_gPlayer.mothandred * 100 + _gPlayer.motten * 10 + _gPlayer.motone, _gPlayer.motaddnum));
		}
	}

	_Fade->PortalIn(mView, PL, 1.f, 0.f, _gPlayer.w, _gPlayer.h, _image->Get_cgPlayer(_gPlayer.mothandred * 100 + _gPlayer.motten * 10 + _gPlayer.motone, _gPlayer.motaddnum), GetColor(0, 0, 0), 0);


	if (_gPlayer.motten > 2) {
		if (gPad._gKey[0] & PAD_INPUT_7) {
			float dir = 0.f;
			int greean = GetColor(0, 255, 0);
			switch (b_select.bulletType) {
			case 0:
			case 1: {
				switch (_gPlayer.arrow) {//右
				case 1: {
					switch (_gPlayer.aiming) {
					case 0: {//横
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 80 * cos(0);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 80 * sin(0);
						dir = DegToRad(0);
						break;
					}
					case 1: {//斜め上
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 20 + 80 * cos(Rad6);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) - 5 + 80 * sin(Rad6);
						dir = Rad6;
						break;
					}
					case 2: {//斜め下
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 25 + 80 * cos(Rad1);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 5 + 80 * sin(Rad1);
						dir = Rad1;
						break;
					}
					case 3: {//上
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) - 80 + 80 * cos(270);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) - 80 + 80 * sin(270);
						dir = DegToRad(270);
						break;
					}
					case 4: {//下
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 45 + 80 * cos(90);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 80 * sin(90);
						dir = DegToRad(90);
						break;
					}
					}
					break;
				}
				case -1: {
					switch (_gPlayer.aiming) {
					case 0: {//横
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) - 20 + 80 * cos(180);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 30 + 80 * sin(180);
						dir = DegToRad(180);
						break;
					}
					case 1: {//斜め上
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 25 + 80 * cos(Rad4);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) - 25 + 80 * sin(Rad4);
						dir = Rad4;
						break;
					}
					case 2: {//斜め下
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 25 + 80 * cos(Rad3);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) - 10 + 80 * sin(Rad3);
						dir = Rad3;
						break;
					}
					case 3: {//上
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) - 28 + 80 * cos(270);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) - 90 + 80 * sin(270);
						dir = DegToRad(270);
						break;
					}
					case 4: {//下
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 45 + 80 * cos(90);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 80 * sin(90);
						dir = DegToRad(90);
						break;
					}
					}
				}
				}
				break;
			}
			case 2:
			case 3: {
				switch (_gPlayer.arrow) {//右
				case 1: {
					switch (_gPlayer.aiming) {
					case 0: {//横
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 80 * cos(0);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 60 + 80 * sin(0);
						dir = DegToRad(0);
						break;
					}
					case 1: {//斜め上
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) - 10 + 80 * cos(Rad6);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 40 + 80 * sin(Rad6);
						dir = Rad6;
						break;
					}
					case 2: {//斜め下
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) - 10 + 80 * cos(Rad1);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 75 + 80 * sin(Rad1);
						dir = Rad1;
						break;
					}
					case 3: {//上
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) - 140 + 80 * cos(270);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) - 45 + 80 * sin(270);
						dir = DegToRad(270);
						break;
					}
					case 4: {//下
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 20 + 80 * cos(90);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 60 + 80 * sin(90);
						dir = DegToRad(90);
						break;
					}
					}
					break;
				}
				case -1: {
					switch (_gPlayer.aiming) {
					case 0: {//横
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 80 * cos(180);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 100 + 80 * sin(180);
						dir = DegToRad(180);
						break;
					}
					case 1: {//斜め上
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 60 + 80 * cos(Rad4);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 25 + 80 * sin(Rad4);
						dir = Rad4;
						break;
					}
					case 2: {//斜め下
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 65 + 80 * cos(Rad3);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 55 + 80 * sin(Rad3);
						dir = Rad3;
						break;
					}
					case 3: {//上
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 20 + 80 * cos(270);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) - 50 + 80 * sin(270);
						dir = DegToRad(270);
						break;
					}
					case 4: {//下
						_start_point.x = (_gPlayer.x + BULLET_SHOT_POINT) + 100 + 80 * cos(90);
						_start_point.y = (_gPlayer.y + BULLET_SHOT_POINT) + 60 + 80 * sin(90);
						dir = DegToRad(90);
						break;
					}
					}
					break;
				}
				}
			}
			}
			if ((gPad._gKey[0] & PAD_INPUT_7) != 0) {
				MyDrawLine(mView, _start_point.x, _start_point.y, _terminal.x, _terminal.y, greean);
			}
		}
	}
}
	
