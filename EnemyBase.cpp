/*****************************************************************//**
 * \file   EnemyBase.cpp
 * \brief  エネミー関連の基
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#include "enemybase.h"
#include "DxLib.h"
#include "mydraw.h"


EnemyBase::EnemyBase() {
	
	for(int i = 0; i < 5; i++) {
		_contlCnt[i] = 0;
	}
	
	tui.motaddcount = 0;
	tui.motcount    = 0;
	tui.motspeed    = 2;
	tui.motseet     = 10;

	jet.motaddcount = 0;
	jet.motcount = 0;
	jet.motspeed = 4;
	jet.motseet = 30;

	boss_effect.fade = 0;
	boss_effect.hang = 1;

	for (int i = 0; i < ENEMY_MAX; i++) {
		_enemy[i].type = CHARA_TYPE_NONE;
		_enemy[i].pos = VGet(0, 0, 0);
		_enemy[i].graph = { 0,0,0,0 };
		_enemy[i].hit = _none;
		_enemy[i].search = _none;
		_enemy[i].cx = 0;
		_enemy[i].cy = 0;
		_enemy[i].hp = 0;
		_enemy[i].maxhp = 0;
		_enemy[i].base_point = 0;
		_enemy[i].init_pointY = 0;

		_enemy[i].isuse = false;
		_enemy[i].action_control = 0;
		_enemy[i].action_cnt = 0;
		_enemy[i].isAim = false;
		_enemy[i].direction = 0.0f;
		_enemy[i].angle = 0.0f;
		_enemy[i].arrow = 0;  // プレイヤーと同じく1or-1
		_enemy[i].aiming = 0;
		_enemy[i].movespeed = 0;
		_enemy[i].isWhite = false;
		_enemy[i].isBlack = false;

		_enemy[i].bomber_se = 0;
		_enemy[i].bomber_count = 0;
		_enemy[i].detection_sound = 0;
	}

	// ボス用のパラメータ
	_variable.search = _none;
	_variable.boss_hit[0] = _none;
	_variable.boss_hit[1] = _none;
	_variable.boss_hit[2] = _none;
	_variable.angle[0] = 0.0f;
	_variable.angle[1] = 0.0f;
	_variable.isdetectB = false;
	_variable.isguideB = false;
	_variable.issnipeB = false;
	_variable.easingcnt = 0;
	_variable.turncnt = 0;
	_variable.targetX = 0.0f;
	_variable.targetY = 0.0f;
}


EnemyBase::~EnemyBase() {
	
}

void EnemyBase::CharaInit(int index) {
// 初期化
	_enemy[index].type = CHARA_TYPE_NONE;
	_enemy[index].pos = VGet(0, 0, 0);
	_enemy[index].graph = { 0,0,0,0 };
	_enemy[index].hit = _none;
	_enemy[index].search = _none;
	_enemy[index].cx = 0;
	_enemy[index].cy = 0;
	_enemy[index].hp = 0;
	_enemy[index].maxhp = 0;
	_enemy[index].base_point = 0;
	_enemy[index].init_pointY = 0;

	_enemy[index].bomber_se = 0;
	_enemy[index].bomber_count = 0;
	_enemy[index].detection_sound = 0;

	_enemy[index].isuse = false;    // 他の処理で消せなかった時の保険
	_enemy[index].action_control = 0;
	_enemy[index].action_cnt = 0;
	_enemy[index].isAim = false;
	_enemy[index].direction = 0.0f;
	_enemy[index].angle = 0.0f;
	_enemy[index].arrow = 0;  // プレイヤーと同じく1or-1
	_enemy[index].aiming = 0;
	_enemy[index].movespeed = 0;
	_enemy[index].isWhite = false;
	_enemy[index].isBlack = false;
}

void EnemyBase::BossInit() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (_enemy[i].type == CHARA_TYPE_ENEMY7) {
			CharaInit(i);
			break;
		}
	}
	_variable.search = _none;
	_variable.boss_hit[0] = _none;
	_variable.boss_hit[1] = _none;
	_variable.boss_hit[2] = _none;
	_variable.angle[0] = 0.0f;
	_variable.angle[1] = 0.0f;
	_variable.isdetectB = false;
	_variable.isguideB = false;
	_variable.issnipeB = false;
}


void EnemyBase::AllInit() {
		// ステージ遷移ごとの初期化
	for(int i = 0; i < ENEMY_MAX; i++) {
		CharaInit(i);
	}
}

void EnemyBase::AllAddBlack() {
// プレイヤーが反物質カプセルをとった時の処理
	for(int i = 0; i < ENEMY_MAX; i++) {
		if(_enemy[i].isuse != false) {
			_enemy[i].isBlack = true;
		}
	}
}

int EnemyBase::GetBWstate(int index) {
// エネミーが白黒どちらの状態か
	int state = 0;
	if (_enemy[index].isWhite == true) {
		state = 1;
	}
	else if (_enemy[index].isBlack == true) {
		state = 2;
	}
	else {
		state = 0;
	}

	return state;
}

void EnemyBase::PosSynchro(int index) {
  // posを基準とした座標合わせ
	_enemy[index].graph.x = _enemy[index].pos.x;
	_enemy[index].graph.y = _enemy[index].pos.y;
	_enemy[index].graph.w = _enemy[index].pos.x + GRAPH_W;
	_enemy[index].graph.h = _enemy[index].pos.y + GRAPH_H;

	switch(_enemy[index].hit.type) {
	case CHARA_TYPE_ENEMY1:
	case CHARA_TYPE_ENEMY3:
	case CHARA_TYPE_ENEMY5:	{
		_enemy[index].hit.x = _enemy[index].pos.x + E1_HIT_X;
		_enemy[index].hit.y = _enemy[index].pos.y;
		_enemy[index].hit.w = ENEMY_W;
		_enemy[index].hit.h = ENEMY_H;
		_enemy[index].cx = _enemy[index].pos.x + GRAPH_W / 2;
		_enemy[index].cy = _enemy[index].pos.y + GRAPH_H / 2;
		break;
	}
	case CHARA_TYPE_ENEMY2: 
	case CHARA_TYPE_ENEMY4:
	case CHARA_TYPE_ENEMY6: {
		_enemy[index].hit.x = _enemy[index].pos.x + ENEMY_TWO_W / 2;
		_enemy[index].hit.y = _enemy[index].pos.y + ENEMY_TWO_H / 2;
		_enemy[index].hit.w = ENEMY_TWO_W;
		_enemy[index].hit.h = ENEMY_TWO_H;
        _enemy[index].cx = _enemy[index].pos.x + GRAPH_W / 2;
		_enemy[index].cy = _enemy[index].pos.y + GRAPH_H / 2;  
		break;
	}
	case CHARA_TYPE_ENEMY7: {
		switch(_enemy[index].arrow) {
		case 1: {
			_enemy[index].hit.x = _enemy[index].pos.x + 220;
			_enemy[index].hit.y = _enemy[index].pos.y + 220;
			_enemy[index].hit.w = E3_HIT_W;
			_enemy[index].hit.h = E3_HIT_H;
			_variable.boss_hit[0].x = _enemy[index].pos.x + 400;
			_variable.boss_hit[0].y = _enemy[index].pos.y + 75;
			_variable.boss_hit[1].x = _enemy[index].pos.x - 225;
			_variable.boss_hit[1].y = _enemy[index].pos.y + 330;
			_variable.boss_hit[2].x = _enemy[index].pos.x - 190;
			_variable.boss_hit[2].y = _enemy[index].pos.y + 120;
			_enemy[index].cx = _enemy[index].pos.x + BOSS_GRAPH_WH / 2;
			_enemy[index].cy = _enemy[index].pos.y + BOSS_GRAPH_WH / 2;
			break;
		}
		case -1: {
			_enemy[index].hit.x = _enemy[index].pos.x - 220;
			_enemy[index].hit.y = _enemy[index].pos.y + 220;
		    _enemy[index].hit.w = E3_HIT_W;
		    _enemy[index].hit.h = E3_HIT_H;
			_variable.boss_hit[0].x = _enemy[index].pos.x - 110;
			_variable.boss_hit[0].y = _enemy[index].pos.y + 65;
			_variable.boss_hit[1].x = _enemy[index].pos.x + 285;
			_variable.boss_hit[1].y = _enemy[index].pos.y + 335;
			_variable.boss_hit[2].x = _enemy[index].pos.x + 220;
			_variable.boss_hit[2].y = _enemy[index].pos.y + 110;
		    _enemy[index].cx = _enemy[index].pos.x + BOSS_GRAPH_WH / 2;
		    _enemy[index].cy = _enemy[index].pos.y + BOSS_GRAPH_WH / 2;
		break;
	}
	}
		break;
	}
	}
	switch(_enemy[index].search.type) {
	case SEARCH_AREA1: {
		_enemy[index].search.x = _enemy[index].pos.x - 200;
		_enemy[index].search.y = _enemy[index].pos.y - 150;
		_enemy[index].search.w = 600;
		_enemy[index].search.h = 500;
		break;
	}
	case SEARCH_AREA2: {
		if (_enemy[index].type != CHARA_TYPE_ENEMY7) {
			_enemy[index].search.x = (_enemy[index].pos.x - 90) - 400 * cos(_enemy[index].direction);
			_enemy[index].search.y = (_enemy[index].pos.y - 90) - 400 * sin(_enemy[index].direction);
			_enemy[index].search.w = 400;
			_enemy[index].search.h = 400;
		}
		if (_enemy[index].type == CHARA_TYPE_ENEMY7) {

			_enemy[index].search.x = (_enemy[index].pos.x + 50) - 600 * cos(_variable.angle[0]);
			_enemy[index].search.y = (_enemy[index].pos.y + 50) - 600 * sin(_variable.angle[0]);
			_enemy[index].search.w = 400;
			_enemy[index].search.h = 400;
			
			if (_enemy[index].isWhite == true) {
				_enemy[index].search.x = (_enemy[index].pos.x + 50) - 600 * cos(_variable.angle[0]);
				_enemy[index].search.y = (_enemy[index].pos.y + 50) - 600 * sin(_variable.angle[0]);
				_enemy[index].search.w = 600;
				_enemy[index].search.h = 600;
			}
			if (_enemy[index].isBlack == true) {
				_enemy[index].search.x = (_enemy[index].pos.x + 50) - 600 * cos(_variable.angle[0]);
				_enemy[index].search.y = (_enemy[index].pos.y + 50) - 600 * sin(_variable.angle[0]);
				_enemy[index].search.w = 200;
				_enemy[index].search.h = 200;
			}

		}
		break;
	}
	}
}

int EnemyBase::HitProcess(MYCIRCLE_PLUS hit, int index,int hp) {
// プレイヤーの弾が当たった時の処理
	int judge = 0;
	if (_enemy[index].isuse != false) {
		if (_enemy[index].hp <= 0) {
			_enemy[index].hit = _none;
			_enemy[index].search = _none;
			if (_enemy[index].type == CHARA_TYPE_ENEMY7) {
				_variable.search = _none;
			}
			_enemy[index].action_control = 0;
			if (_enemy[index].type != CHARA_TYPE_ENEMY7) {
				_effect->SetEffect(_enemy[index].cx, _enemy[index].cy, EFFECT_TYPE_BOMBER, 0, 0, 0, 0, 1, EFFECT_ENEMY);
			}
			else {
				_effect->SetEffect(_enemy[index].cx, _enemy[index].cy, EFFECT_TYPE_BOMBER, 0, 0, 0, 0, 3, EFFECT_ENEMY);
				//シーン切り替え用
				if (_Fade->GetType() == 0 && hp > 0) {
					_Fade->FadeSet(1, 1, 180, 1);
					_FadeSound->SetFadeBgm(&_image->Bgm[7], gauge[1], 180, -1);
				}
			}
			_music->MakeSe(_image->Se[9]);
			_enemy[index].isuse = false; // 対消滅の処理がこの後なので他の情報を消さずに置いておく	
		}
		if (hit.hit == 1) {
			_effect->SetEffect(hit.x + P_BULLET_W / 2, hit.y + P_BULLET_H / 2, EFFECT_TYPE_NORMAL_WALL, 0, 0, 0, 0, 1, EFFECT_PLAYER);
			_enemy[index].hp--;
			judge = 1;

		}
	}
	return judge;
}

void EnemyBase::AnnihilationEffect(int index) {
	if(_enemy[index].bomber_se == 1) {
		_enemy[index].bomber_count--;
		if(_enemy[index].bomber_count <= 0) {
			_music->MakeSe(_image->Se[9]);
			_effect->SetEffect(_enemy[index].cx, _enemy[index].cy, EFFECT_TYPE_BOMBER, 0, 0, 0, 0,1, EFFECT_ENEMY);
			_enemy[index].bomber_se = 0;
			_enemy[index].bomber_count = 0;
		}
	}
}
// キャラの追加
int EnemyBase::AddEnemy(int type, int x, int y, int arrow) {
// エネミーの追加
	int Add = -1;
	for(int i = 0; i < ENEMY_MAX; i++) {
		if(_enemy[i].type == CHARA_TYPE_NONE) {
			// キャラを[i]に追加。キャラタイプによって初期化情報が変わる
			_enemy[i].type = type;
			_enemy[i].pos = VGet(x, y, 0);
			_enemy[i].graph = { x, y, x + GRAPH_W, y + GRAPH_H };
			_enemy[i].cx = x + GRAPH_W / 2;
			_enemy[i].cy = y + GRAPH_H / 2;

			_enemy[i].arrow = arrow;
			_enemy[i].direction = 0.0f;
			_enemy[i].angle = 0.0f;
		    _enemy[i].isuse = true;
			_enemy[i].action_control = 1;
			_enemy[i].action_cnt = 0;
			_enemy[i].base_point = x;
			_enemy[i].detection_sound = 0;
			_variable.boss_hit[0] = _none;
			_variable.boss_hit[1] = _none;
			switch(type) {
				//後にエネミーのタイプごとに設定する
			case CHARA_TYPE_ENEMY1: 
			case CHARA_TYPE_ENEMY3:
			case CHARA_TYPE_ENEMY5: {
				_enemy[i].movespeed = 2;
				_enemy[i].hit = { type, x + E1_HIT_X, y,  ENEMY_W,  ENEMY_H, _enemy[i].movespeed , 0, i };
				_enemy[i].search = { SEARCH_AREA1,x - 200, y - 150, 600, 500,0,0,i };
				_enemy[i].init_pointY = y;
				if(type == CHARA_TYPE_ENEMY1){ _enemy[i].hp = 3; }
				if (type == CHARA_TYPE_ENEMY3) { _enemy[i].hp = 5; }
				if (type == CHARA_TYPE_ENEMY5) { _enemy[i].hp = 10; }
				_enemy[i].maxhp = _enemy[i].hp;
				break;
			}
			case CHARA_TYPE_ENEMY2: 
			case CHARA_TYPE_ENEMY4: 
			case CHARA_TYPE_ENEMY6:	{
				_enemy[i].hit = { type, x , y,  E2_HIT_WH,  E2_HIT_WH, _enemy[i].movespeed , 0, i };
				_enemy[i].movespeed = 0;
				_enemy[i].search = { SEARCH_AREA2,x - 400, y - 400, 800, 800,0,0,i };
				if (type == CHARA_TYPE_ENEMY2) { _enemy[i].hp = 5; }
				if (type == CHARA_TYPE_ENEMY4) { _enemy[i].hp = 10; }
				if (type == CHARA_TYPE_ENEMY6) { _enemy[i].hp = 15; }
				_enemy[i].maxhp = _enemy[i].hp;
				break;
			}
			case CHARA_TYPE_ENEMY7:	{   
				_enemy[i].hp = 600;
				_enemy[i].maxhp = _enemy[i].hp;
				_enemy[i].hit = { type, x, y + 150,  E3_HIT_W,  E3_HIT_H, _enemy[i].movespeed , 0, i };
				_variable.boss_hit[0] = { BOSS_HIT1, x, y,  wing1_W,  wing1_H, _enemy[i].movespeed , 0, i};
				_variable.boss_hit[1] = { BOSS_HIT2, x, y,  wing2_W,  wing2_H, _enemy[i].movespeed , 0, i };
				_variable.boss_hit[2] = { BOSS_HIT3, x, y,  wing3_W,  wing3_H, _enemy[i].movespeed , 0, i };
				_variable.angle[0] = 0.0f;
				_variable.angle[1] = 0.0f;
				_enemy[i].movespeed = 2;
				_enemy[i].search = {SEARCH_AREA2,x - 600, y - 450, 1200, 975,0,0,i};
				_variable.search = { SEARCH_AREA3,0, 0, 3840, 2160,0,0,i };
				_variable.isguideB = true;
				break;
			}
			}
		
			// 追加できた配列番号を返す
			Add = i;
			return Add;
			break;
		}
	}
	// 追加できなかった
	if(Add == -1) {
		return Add;
	}
}

void EnemyBase::CommonProcess(MYCIRCLE_PLUS hit, int index, int iswhite, int isblack,int hp) {
	//　各エネミー共通の処理を呼び出し(当たり判定、対消滅判定など)

	if(HitProcess(hit, index, hp) == 1) {
		if(iswhite == 1) {
			_enemy[index].isWhite = true;

		}
		if(isblack == 1) {
			_enemy[index].isBlack = true;

		}
		if(_enemy[index].isWhite == true && _enemy[index].isBlack == true) {
			if(_enemy[index].isuse != false) {
				if(_enemy[index].type == CHARA_TYPE_ENEMY7) {
					// ボス敵時
					_music->MakeSe(_image->Se[10]);
					_enemy[index].hp -= 30;
					_enemy[index].isWhite = false;
					_enemy[index].isBlack = false;
				}
				else {
	                // 通常エネミー時
					_music->MakeSe(_image->Se[10]);
					_effect->SetEffect(_enemy[index].cx, _enemy[index].cy, EFFECT_TYPE_BULLET_ANNIHILAT, 0, 0, 0, 0,1, EFFECT_ENEMY);
					_enemy[index].hit = _none;
					_enemy[index].search = _none;
					_enemy[index].action_control = 0;
					_enemy[index].isuse = false;
					_enemy[index].bomber_se = 1;
					_enemy[index].bomber_count = 60;
				}
			}
		}
	}
}

void EnemyBase::EffectProcess() {
	tui.motcount++;
	jet.motcount++;

	if(tui.motcount >= tui.motspeed) {
		tui.motcount = 0;
		tui.motaddcount++;
	}

	if(tui.motaddcount * tui.motspeed > (tui.motseet - 1) * tui.motspeed) {
		tui.motcount = 0;
		tui.motaddcount = 0;
	}

	if(jet.motcount >= jet.motspeed) {
		jet.motcount = 0;
		jet.motaddcount++;
	}

	if(jet.motaddcount * jet.motspeed > (jet.motseet - 1) * jet.motspeed) {
		jet.motcount = 0;
		jet.motaddcount = 0;
	}


	
	boss_effect.fade += 2.0f * boss_effect.hang;

	if (boss_effect.fade >= 255 || boss_effect.fade <= 92.5) {
		boss_effect.hang *= -1;
		if (boss_effect.fade >= 255) {
			boss_effect.fade = 254;
		}
		else {
			boss_effect.fade = 93.5;
		}
	}
}

void EnemyBase::DirReset(int index) {
	// direction加算が2πを超えたらリセット
	if (_enemy[index].type == CHARA_TYPE_ENEMY7) {
		if (_enemy[index].direction >= 360.0f * 40) {
			_enemy[index].direction = 0.0f;
		}
	}
	else {
		if (_enemy[index].direction > 360.0f) {
			_enemy[index].direction = 0.0f;
			_enemy[index].pos.y = _enemy[index].init_pointY;
		}
	}
}

void EnemyBase::Process(int index, int chara_x, int chara_y, HITSLIDE search, HITSLIDE search2,int map_w, int map_h){
	// エネミーの挙動
	if (_enemy[index].isuse != false) {
		switch (_enemy[index].type) {
		case CHARA_TYPE_ENEMY1: {
			if (search.hit != 0) {
				_enemy[index].action_control = 3;
				if (_enemy[index].detection_sound == 0) {
					_enemy[index].detection_sound = 1;
					_music->MakeSe(_image->Se[24]);
				}
			}
			switch (_enemy[index].action_control) {
			case 1: {
				_enemy[index].movespeed = 2;
				_enemy[index].pos.x += _enemy[index].movespeed * _enemy[index].arrow;
				_enemy[index].pos.y += 1 * sin(_enemy[index].direction);
				PosSynchro(index);
				_enemy[index].direction++;
				DirReset(index);
				if (_enemy[index].base_point + 360 <= _enemy[index].pos.x) {
					_enemy[index].pos.x = _enemy[index].base_point + 360;
					PosSynchro(index);
					_enemy[index].action_control = 2;
				}
				if (_enemy[index].base_point - 360 >= _enemy[index].pos.x) {
					_enemy[index].pos.x = _enemy[index].base_point - 360;
					PosSynchro(index);
					_enemy[index].action_control = 2;
				}
				break;
			}
			case 2: {
				_enemy[index].movespeed = 0;

				_enemy[index].action_cnt++;
				_enemy[index].pos.y += 1 * sin(_enemy[index].direction);
				PosSynchro(index);
				_enemy[index].direction++;
				DirReset(index);
				if (_enemy[index].action_cnt >= 300) {
					_enemy[index].action_cnt = 0;
					_enemy[index].arrow *= -1;
					_enemy[index].movespeed = 2;
					_enemy[index].pos.x += _enemy[index].movespeed * _enemy[index].arrow;
					_enemy[index].action_control = 1;
				}
				break;
			}
			case 3: {
				_enemy[index].pos.y += 1 * sin(_enemy[index].direction);
				PosSynchro(index);
				_enemy[index].direction++;
				DirReset(index);
				if (search.hit == 0) {
					_enemy[index].action_control = 1;
				}
				break;
			}
			}
			break;
		}
		case CHARA_TYPE_ENEMY2: {
			if (search.hit != 0) {
				if (_enemy[index].detection_sound == 0) {
					_enemy[index].detection_sound = 1;
					_music->MakeSe(_image->Se[25]);
				}
				float rotspeed = 0.5f;
				if (RadToDeg(_enemy[index].direction) > 360) {
					_enemy[index].direction = 0.0f;
				}
				else if (RadToDeg(_enemy[index].direction) < 0) {
					_enemy[index].direction = 360.0f;
				}

				_enemy[index].action_control = 4;
				float dir;
				dir = atan2(_enemy[index].pos.y - 50 - chara_y, _enemy[index].pos.x - 50 - chara_x);
				if (RadToDeg(dir) < 0) {
					dir += DegToRad(360);
				}
				if(dir > _enemy[index].direction || RadToDeg(_enemy[index].direction) - RadToDeg(dir) > 200) {
					_enemy[index].direction += DegToRad(rotspeed);
				}
				else {
					_enemy[index].direction -= DegToRad(rotspeed);
				}
				PosSynchro(index);
			}
			else {
				if (RadToDeg(_enemy[index].direction) > 360) {
					_enemy[index].direction = 0.0f;
				}
				else if (RadToDeg(_enemy[index].direction) < 0) {
					_enemy[index].direction = 360.0f;
				}
				_enemy[index].action_control = 1;

				_enemy[index].direction += DegToRad(0.50);
				PosSynchro(index);
			}
			break;
		}
		case CHARA_TYPE_ENEMY3: {
			if (search.hit != 0) {
				_enemy[index].action_control = 3;
				if (_enemy[index].detection_sound == 0) {
					_enemy[index].detection_sound = 1;
					_music->MakeSe(_image->Se[24]);
				}
			}
			switch (_enemy[index].action_control) {
			case 1: {
				_enemy[index].movespeed = 2;
				_enemy[index].pos.x += _enemy[index].movespeed * _enemy[index].arrow;
				_enemy[index].pos.y += 1 * sin(_enemy[index].direction);
				PosSynchro(index);
				_enemy[index].direction++;
				DirReset(index);
				if (_enemy[index].base_point + 360 <= _enemy[index].pos.x) {
					_enemy[index].pos.x = _enemy[index].base_point + 360;
					PosSynchro(index);
					_enemy[index].action_control = 2;
				}
				if (_enemy[index].base_point - 360 >= _enemy[index].pos.x) {
					_enemy[index].pos.x = _enemy[index].base_point - 360;
					PosSynchro(index);
					_enemy[index].action_control = 2;
				}
				break;
			}
			case 2: {
				_enemy[index].movespeed = 0;

				_enemy[index].action_cnt++;
				_enemy[index].pos.y += 1 * sin(_enemy[index].direction);
				PosSynchro(index);
				_enemy[index].direction++;
				DirReset(index);
				if (_enemy[index].action_cnt >= 300) {
					_enemy[index].action_cnt = 0;
					_enemy[index].arrow *= -1;
					_enemy[index].movespeed = 2;
					_enemy[index].pos.x += _enemy[index].movespeed * _enemy[index].arrow;
					_enemy[index].action_control = 1;
				}
				break;
			}
			case 3: {
				_enemy[index].pos.y += 1 * sin(_enemy[index].direction);
				PosSynchro(index);
				_enemy[index].direction++;
				DirReset(index);
				if (search.hit == 0) {
					_enemy[index].action_control = 1;
				}
				break;
			}
			}
			break;
		}
		case CHARA_TYPE_ENEMY4: {
			if (search.hit != 0) {
				if (_enemy[index].detection_sound == 0) {
					_enemy[index].detection_sound = 1;
					_music->MakeSe(_image->Se[25]);
				}
				_enemy[index].action_control = 4;
				float rotspeed = 0.8f;
				if (RadToDeg(_enemy[index].direction) > 360) {
					_enemy[index].direction = -360.0f;
				}
				else if (RadToDeg(_enemy[index].direction) < -360) {
					_enemy[index].direction = 0.0f;
				}
				float dir;
				dir = atan2(_enemy[index].pos.y - 50 - chara_y, _enemy[index].pos.x - 50 - chara_x);
				if (RadToDeg(dir) > 0 || RadToDeg(dir) - RadToDeg(_enemy[index].direction) > 100) {
					dir -= DegToRad(360);
				}
				if (dir < _enemy[index].direction) {
					_enemy[index].direction -= DegToRad(rotspeed);
				}
				else {
					_enemy[index].direction += DegToRad(rotspeed);
				}
				PosSynchro(index);
			}
			else {
				if (RadToDeg(_enemy[index].direction) > 360) {
					_enemy[index].direction = -360.0f;
				}
				else if (RadToDeg(_enemy[index].direction) < -360) {
					_enemy[index].direction = 0.0f;
				}

				_enemy[index].action_control = 1;

				_enemy[index].direction -= DegToRad(0.50);
				PosSynchro(index);
			}
			break;
		}
		case CHARA_TYPE_ENEMY5: {
			if(search.hit != 0) {
				_enemy[index].action_control = 3;
				if(_enemy[index].detection_sound == 0) {
					_enemy[index].detection_sound = 1;
					_music->MakeSe(_image->Se[24]);
				}
			}
			switch(_enemy[index].action_control) {
			case 1: {
				_enemy[index].movespeed = 2;
				_enemy[index].pos.x += _enemy[index].movespeed * _enemy[index].arrow;
				_enemy[index].pos.y += 1 * sin(_enemy[index].direction);
				PosSynchro(index);
				_enemy[index].direction++;
				DirReset(index);
				if(_enemy[index].base_point + 360 <= _enemy[index].pos.x) {
					_enemy[index].pos.x = _enemy[index].base_point + 360;
					PosSynchro(index);
					_enemy[index].action_control = 2;
				}
				if(_enemy[index].base_point - 360 >= _enemy[index].pos.x) {
					_enemy[index].pos.x = _enemy[index].base_point - 360;
					PosSynchro(index);
					_enemy[index].action_control = 2;
				}
				break;
			}
			case 2: {
				_enemy[index].movespeed = 0;

				_enemy[index].action_cnt++;
				_enemy[index].pos.y += 1 * sin(_enemy[index].direction);
				PosSynchro(index);
				_enemy[index].direction++;
				DirReset(index);
				if(_enemy[index].action_cnt >= 300) {
					_enemy[index].action_cnt = 0;
					_enemy[index].arrow *= -1;
					_enemy[index].movespeed = 2;
					_enemy[index].pos.x += _enemy[index].movespeed * _enemy[index].arrow;
					_enemy[index].action_control = 1;
				}
				break;
			}
			case 3: {
				_enemy[index].pos.y += 1 * sin(_enemy[index].direction);
				PosSynchro(index);
				_enemy[index].direction++;
				DirReset(index);
				if(search.hit == 0) {
					_enemy[index].action_control = 1;
				}
				break;
			}
			}
			break;
		}
		case CHARA_TYPE_ENEMY6: {
			if(search.hit != 0) {
				if(_enemy[index].detection_sound == 0) {
					_enemy[index].detection_sound = 1;
					_music->MakeSe(_image->Se[25]);
				}
				float rotspeed = 1.0f;
				if(RadToDeg(_enemy[index].direction) > 360) {
					_enemy[index].direction = 0.0f;
				}
				else if(RadToDeg(_enemy[index].direction) < 0) {
					_enemy[index].direction = 360.0f;
				}

				_enemy[index].action_control = 4;

				float dir;
				dir = atan2(_enemy[index].pos.y - 50 - chara_y, _enemy[index].pos.x - 50 - chara_x);
				if(RadToDeg(dir) < 0) {
					dir += DegToRad(360);
				}
				if(dir > _enemy[index].direction || RadToDeg(_enemy[index].direction) - RadToDeg(dir) > 200) {
					_enemy[index].direction += DegToRad(rotspeed);
				}
				else {
					_enemy[index].direction -= DegToRad(rotspeed);
				}
				PosSynchro(index);
			}
			else {
				if(RadToDeg(_enemy[index].direction) > 360) {
					_enemy[index].direction = 0.0f;
				}
				else if(RadToDeg(_enemy[index].direction) < 0) {
					_enemy[index].direction = 360.0f;
				}
				_enemy[index].action_control = 1;

				_enemy[index].direction += DegToRad(0.50);
				PosSynchro(index);
			}
			break;
		}
		case CHARA_TYPE_ENEMY7: {
		
			BossMotion(index, chara_x, chara_y, search, search2, map_w, map_h);
				break;
			}
		}
	}
};

void EnemyBase::PosFix(int index, int mapHit) {
	// 壁に当たった時の位置調整
	if(_enemy[index].isuse != false) {
		if(mapHit != 0) {
			switch(_enemy[index].type) {
			case CHARA_TYPE_ENEMY1: {
				switch(_enemy[index].action_control) {
				case 1: {
					PosSynchro(index);
					_enemy[index].arrow *= -1;
					break;
				}
				case 2: {
					PosSynchro(index);
					break;
				}
				case 3:
					PosSynchro(index);
					_enemy[index].action_control = 2;
					break;
				}
				break;
			}
			case CHARA_TYPE_ENEMY3: {
				switch(_enemy[index].action_control) {
				case 1: {
					PosSynchro(index);
					_enemy[index].arrow *= -1;
					break;
				}
				case 2: {
					PosSynchro(index);
					break;
				}
				case 3:
					PosSynchro(index);
					_enemy[index].action_control = 2;
					break;
				}
				break;
			}
			case CHARA_TYPE_ENEMY5: {
				switch(_enemy[index].action_control) {
				case 1: {
					PosSynchro(index);
					_enemy[index].arrow *= -1;
					break;
				}
				case 2: {
					PosSynchro(index);
					break;
				}
				case 3:
					PosSynchro(index);
					_enemy[index].action_control = 2;
					break;
				}
				break;
			}
			}
		}
	}
}
void EnemyBase::Draw(MATRIX mview, int snipecnt, int plx, int ply) {
	// エネミーの描画
	for(int i = 0; i < ENEMY_MAX; i++) {
		if(_enemy[i].isuse == true) {
			VECTOR enemy = VGet(_enemy[i].cx, _enemy[i].cy, 0);
			switch(_enemy[i].type) {
			case CHARA_TYPE_ENEMY1: {
				switch(_enemy[i].arrow) {
				case 1: {
					MyDrawTurnModiGraph(mview, VGet(enemy.x+5,enemy.y + 75,0), 1.f, 0.f, 200, 200, _image->GetEnemy_One_Effect(jet.motaddcount));
					MyDrawTurnModiGraph(mview, enemy, 1.f, 0.f, GRAPH_W, GRAPH_H, _image->GetCgEnemy(0));
					break;
				}
				case -1: {
					MyDrawModiGraph(mview, VGet(enemy.x-5, enemy.y + 75, 0), 1.f, 0.f, 200, 200, _image->GetEnemy_One_Effect(jet.motaddcount));
					MyDrawModiGraph(mview, enemy, 1.f, 0.f, GRAPH_W, GRAPH_H, _image->GetCgEnemy(0));
					break;
				}
				}
				break;
			}
			case CHARA_TYPE_ENEMY2: {
				MyDrawTurnModiGraph(mview, enemy, 1.f, 0.f, 100, 100, _image->GetCgEnemy(3));
				MyDrawTurnModiGraph(mview, enemy, 1.f, _enemy[i].direction, 100, 100, _image->GetCgEnemy(4));
				break;
			}
			case CHARA_TYPE_ENEMY3: {
				switch(_enemy[i].arrow) {
				case 1: {
					MyDrawTurnModiGraph(mview, VGet(enemy.x + 5, enemy.y + 75, 0), 1.f, 0.f, 200, 200, _image->GetEnemy_One_Effect(jet.motaddcount));
					MyDrawTurnModiGraph(mview, enemy, 1.f, 0.f, GRAPH_W, GRAPH_H, _image->GetCgEnemy(1));
					break;
				}
				case -1: {
					MyDrawModiGraph(mview, VGet(enemy.x - 5, enemy.y + 75, 0), 1.f, 0.f, 200, 200, _image->GetEnemy_One_Effect(jet.motaddcount));
					MyDrawModiGraph(mview, enemy, 1.f, 0.f, GRAPH_W, GRAPH_H, _image->GetCgEnemy(1));
					break;
				}
				}
				break;
			}
			case CHARA_TYPE_ENEMY4: {
				MyDrawTurnModiGraph(mview, enemy, 1.f, 0.f, 100, 100, _image->GetCgEnemy(5));
				MyDrawTurnModiGraph(mview, enemy, 1.f, _enemy[i].direction, 100, 100, _image->GetCgEnemy(6));
				break;
			}
			case CHARA_TYPE_ENEMY5:{
			switch(_enemy[i].arrow) {
			case 1: {
				MyDrawTurnModiGraph(mview, VGet(enemy.x + 5, enemy.y + 75, 0), 1.f, 0.f, 200, 200, _image->GetEnemy_One_Effect(jet.motaddcount));
				MyDrawTurnModiGraph(mview, enemy, 1.f, 0.f, GRAPH_W, GRAPH_H, _image->GetCgEnemy(2));
				break;
			}
			case -1: {
				MyDrawModiGraph(mview, VGet(enemy.x - 5, enemy.y + 75, 0), 1.f, 0.f, 200, 200, _image->GetEnemy_One_Effect(jet.motaddcount));
				MyDrawModiGraph(mview, enemy, 1.f, 0.f, GRAPH_W, GRAPH_H, _image->GetCgEnemy(2));
				break;
			}
			}
			break;
			}
			case CHARA_TYPE_ENEMY6:{
				MyDrawTurnModiGraph(mview, enemy, 1.f, 0.f, 100, 100, _image->GetCgEnemy(7));
				MyDrawTurnModiGraph(mview, enemy, 1.f, _enemy[i].direction, 100, 100, _image->GetCgEnemy(8));
				break;
			}			
			case CHARA_TYPE_ENEMY7:{
				switch(_enemy[i].arrow) {
				case 1: {
					MyDrawTurnModiGraph(mview, enemy, 2.0f, 0.f, BOSS_GRAPH_WH, BOSS_GRAPH_WH, _image->GetCgEnemy(9));

					if (_enemy[i].isWhite == true) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, boss_effect.fade);
						MyDrawTurnModiGraph(mview, VGet(enemy.x, enemy.y, 0), 2.0f, 0.f, BOSS_GRAPH_WH + 100, BOSS_GRAPH_WH, _image->GetBossEffectAura(1));
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, boss_effect.fade);
					}
					else if (_enemy[i].isBlack == true) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, boss_effect.fade);
						MyDrawTurnModiGraph(mview, VGet(enemy.x, enemy.y, 0), 2.0f, 0.f, BOSS_GRAPH_WH + 100, BOSS_GRAPH_WH, _image->GetBossEffectAura(0));
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, boss_effect.fade);
					}
					break;
				}
				case -1: {
					MyDrawModiGraph(mview, enemy, 2.0f, 0.f, BOSS_GRAPH_WH, BOSS_GRAPH_WH, _image->GetCgEnemy(9));

					if (_enemy[i].isWhite == true) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, boss_effect.fade);
						MyDrawModiGraph(mview, VGet(enemy.x, enemy.y, 0), 2.0f, 0.f, BOSS_GRAPH_WH + 100, BOSS_GRAPH_WH, _image->GetBossEffectAura(1));
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, boss_effect.fade);
					}
					else if (_enemy[i].isBlack == true) {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, boss_effect.fade);
						MyDrawModiGraph(mview, VGet(enemy.x, enemy.y, 0), 2.0f, 0.f, BOSS_GRAPH_WH + 100, BOSS_GRAPH_WH, _image->GetBossEffectAura(0));
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, boss_effect.fade);
					}
					break;
				}
				}

				if (snipecnt >= 1200) {
					MyDrawLine(mview, plx, ply, _enemy[i].cx, _enemy[i].cy, GetColor(255, 0, 0));
				}

				break;
			}
			}
			//-------------------------------------------------------------------------------------------
			//エフェクト
			if (_enemy[i].type != CHARA_TYPE_ENEMY7) {
				if (_enemy[i].isWhite == true) {
					MyDrawModiGraph(mview, enemy, 1.f, 0.f, GRAPH_W, GRAPH_H, _image->GetEffectWhite(tui.motaddcount));
				}
				else if (_enemy[i].isBlack == true) {
					MyDrawModiGraph(mview, enemy, 1.f, 0.f, GRAPH_W, GRAPH_H, _image->GetEffectBlack(tui.motaddcount));
				}
			}
			else {
				if (_enemy[i].isWhite == true) {
					MyDrawModiGraph(mview, enemy, 1.f, 0.f, 600, 600, _image->GetBossEffectWhite(tui.motaddcount));
				}
				else if (_enemy[i].isBlack == true) {
					MyDrawModiGraph(mview, enemy, 1.f, 0.f, 600, 600, _image->GetBossEffectBlack(tui.motaddcount));
				}
			}
		}
	}
}