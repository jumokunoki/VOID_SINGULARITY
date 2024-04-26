/*****************************************************************//**
 * \file   Enemy_BossMotion.cpp
 * \brief  ボスの挙動のみ
 *
 * \author 奈良充樹
 * \date   September 2023
 *********************************************************************/

#include "enemybase.h"
#include "DxLib.h"
#include "mydraw.h"

void EnemyBase::BossMotion(int index, int chara_x, int chara_y, HITSLIDE search, HITSLIDE search2, int map_w, int map_h) {
	// エネミーのスピード設定
	if (_enemy[index].isBlack == true) {
		_enemy[index].movespeed = 2 ;
	}
	else {
	_enemy[index].movespeed = 5;
	}

	switch (_enemy[index].action_control) {
	// 登場時
	case 1: {
		// 画面上部外から指定位置まで降りてくる
		_enemy[index].action_cnt++;
		if (_enemy[index].action_cnt >= 120) {
			_enemy[index].pos.y = EasingLinear(_variable.easingcnt, _enemy[index].pos.y, 800.0f, 500.0f * 30);
		_variable.easingcnt++;
		PosSynchro(index);
		}
		if (_enemy[index].action_cnt >= 480) {
			_variable.easingcnt = 0;
			_enemy[index].action_cnt = 0;
			_enemy[index].action_control = 2;
		}
		break;
	}
	case 2: {
		// その場で滞空
		_enemy[index].movespeed = 0;
		_enemy[index].action_cnt++;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / velocity_adjustment);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;
		DirReset(index);
		if (_enemy[index].action_cnt >= 300) {
			_enemy[index].action_cnt = 0;
			_enemy[index].action_control = 3;
		}
		break;
	}
	case 3: {
		// 画面右に去っていく
		_enemy[index].pos.x += _enemy[index].movespeed;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / velocity_adjustment);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;
		DirReset(index);
		if (_enemy[index].pos.x > map_w) {
			_enemy[index].action_cnt++;
			if (_enemy[index].action_cnt >= 120) {
				BossPosChange(index);
			}
		}
		break;
	}
	// パターン1
	case 11: {
		// 画面右で対空
		_enemy[index].movespeed = 0;
		_enemy[index].action_cnt++;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / velocity_adjustment);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;
		DirReset(index);
		if (_enemy[index].action_cnt >= 500) {
			_enemy[index].action_cnt = 0;
			_enemy[index].action_control = 12;
		}
		break;
	}
	case 12: {
		// 画面右に消える
		_enemy[index].pos.x += _enemy[index].movespeed;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / velocity_adjustment);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;
		DirReset(index);
		if (_enemy[index].pos.x > map_w) {
			_enemy[index].action_cnt++;
			if (_enemy[index].action_cnt >= 120) {
				BossPosChange(index);
			}
		}
		break;
	}
	case 13: {
		// 画面左から右に進出
		_enemy[index].pos.x += _enemy[index].movespeed;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / velocity_adjustment);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;

		DirReset(index);
		if (_enemy[index].pos.x >= 100) {
			_enemy[index].action_control = 14;
		}
		break;
	}
	case 14: {
		// 画面左で対空
		_enemy[index].movespeed = 0;
		_enemy[index].action_cnt++;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / velocity_adjustment);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;

		DirReset(index);
		if (_enemy[index].action_cnt >= 500) {
			_enemy[index].action_cnt = 0;
			_enemy[index].action_control = 15;
		}
		break;
	}
	case 15: {
		// 画面左に消える
		_enemy[index].pos.x += _enemy[index].movespeed * -1;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / velocity_adjustment);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;

		DirReset(index);
		if (_enemy[index].pos.x < -800) {
			_enemy[index].action_cnt++;
			if (_enemy[index].action_cnt >= 30) {
				BossPosChange(index);
			}
		}
		break;
	}
	case 16: {
		// 画面右から左に進出
		_enemy[index].pos.x += _enemy[index].movespeed * -1;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / velocity_adjustment);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;

		DirReset(index);
		if (_enemy[index].pos.x <= 2940) {
			_enemy[index].action_control = 11;
		}
		break;
	}
	// パターン2
	case 21: {
		//　左右移動＋徐々に昇る
		_enemy[index].pos.x += _enemy[index].movespeed * _enemy[index].arrow;
		_enemy[index].pos.y -= 3;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / velocity_adjustment);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;

		DirReset(index);
		if (_enemy[index].arrow != -1 && _enemy[index].pos.x > map_w || _enemy[index].pos.y + BOSS_GRAPH_WH < -30)  {
			_enemy[index].action_cnt++;
			if (_enemy[index].action_cnt >= 60) {
				BossPosChange(index);
			}
		}
		if (_enemy[index].arrow != 1 && _enemy[index].pos.x  +BOSS_GRAPH_WH < -1000 || _enemy[index].pos.y + BOSS_GRAPH_WH < -30) {
			_enemy[index].action_cnt++;
			if (_enemy[index].action_cnt >= 60) {
				BossPosChange(index);
			}
		}
		break;
	}
	case 22: {
		//　左右移動
		_enemy[index].pos.x += _enemy[index].movespeed * _enemy[index].arrow;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / velocity_adjustment);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;

		DirReset(index);
		if (_enemy[index].arrow != -1 && _enemy[index].pos.x > map_w) {
			_enemy[index].action_cnt++;
			if (_enemy[index].action_cnt >= 60) {
				BossPosChange(index);
			}
		}
		if (_enemy[index].arrow != 1 && _enemy[index].pos.x + BOSS_GRAPH_WH < -1000) {
			_enemy[index].action_cnt++;
			if (_enemy[index].action_cnt >= 60) {
				BossPosChange(index);
			}
		}
		break;
	}
	case 23: {
		//　左右移動＋徐々に下がる
		_enemy[index].pos.x += _enemy[index].movespeed * _enemy[index].arrow;
		_enemy[index].pos.y += 3;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / velocity_adjustment);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;

		DirReset(index);
		if (_enemy[index].arrow != -1 && _enemy[index].pos.x > map_w || _enemy[index].pos.y > map_h + 30) {
			_enemy[index].action_cnt++;
			if (_enemy[index].action_cnt >= 60) {
				BossPosChange(index);
			}
		}
		if (_enemy[index].arrow != 1 && _enemy[index].pos.x < -1000 || _enemy[index].pos.y > map_h + 30) {
			_enemy[index].action_cnt++;
			if (_enemy[index].action_cnt >= 60) {
				BossPosChange(index);
			}
		}
		break;
	}
	 
	// パターン3
	case 31: {
		// 左右切り返し（カウントの数だけ）
		_enemy[index].pos.x += _enemy[index].movespeed * _enemy[index].arrow;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / velocity_adjustment);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;
		DirReset(index);
		if (_variable.turncnt < 2) {
			if (_enemy[index].arrow != -1 && _enemy[index].pos.x + BOSS_GRAPH_WH >= map_w-100) {
				_enemy[index].pos.x = map_w - 100 - BOSS_GRAPH_WH;
				_enemy[index].action_cnt++;
				PosSynchro(index);

				if (_enemy[index].action_cnt >= 180) {
					_enemy[index].action_cnt = 0;
					_enemy[index].arrow *= -1;
					_variable.turncnt++;

					_enemy[index].pos.x += _enemy[index].movespeed * _enemy[index].arrow;
					PosSynchro(index);
				}
			}
			else if (_enemy[index].arrow != 1 && _enemy[index].pos.x <= 0 + 100 ) {
				_enemy[index].pos.x = 0 + 100;
				_enemy[index].action_cnt++;
				PosSynchro(index);

			if (_enemy[index].action_cnt >= 180) {
				_enemy[index].action_cnt = 0;
				_enemy[index].arrow *= -1;
				_variable.turncnt++;

				_enemy[index].pos.x += _enemy[index].movespeed * _enemy[index].arrow;
				PosSynchro(index);
			}
			}

		}

		if (_enemy[index].arrow != -1 && _enemy[index].pos.x > map_w + 100) {
			_enemy[index].action_cnt++;
			if (_enemy[index].action_cnt >= 60) {
				_variable.turncnt = 0;
				BossPosChange(index);
			}
		}
		else if (_enemy[index].arrow != 1 && _enemy[index].pos.x + BOSS_GRAPH_WH < -1000) {
			_enemy[index].action_cnt++;
			if (_enemy[index].action_cnt >= 60) {
				_variable.turncnt = 0;
				BossPosChange(index);
			}
		}
		break;
	}
	// 画面中央留まり32～34
	case 32: {
		// 画面内に進入
		float flame = 300.0f;
		_enemy[index].pos.x = EasingInQuad(_enemy[index].action_cnt, _enemy[index].pos.x, 1720, flame);
		_enemy[index].pos.y = EasingInQuad(_enemy[index].action_cnt, _enemy[index].pos.y, 880, flame);
		_enemy[index].action_cnt++;
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);

		if (_enemy[index].action_cnt >= 120) {
			_enemy[index].action_cnt = 0;
			_enemy[index].action_control = 33;
		}
		break;
	}
	case 33: {
		// 画面中央でとどまる
		_enemy[index].movespeed = 0;
		_enemy[index].action_cnt++;
		_enemy[index].pos.y += 2 * sin(_enemy[index].direction / 50);
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);
		_enemy[index].direction++;

		DirReset(index);
		if (_enemy[index].action_cnt >= 150) {
			_enemy[index].action_cnt = 0;
			_enemy[index].action_control = 34;
		}
		break;
	}
	case 34: {
		// 画面外に消える
		float flame = 300.0f;
		if (_enemy[index].action_cnt <= 0) {
			int only_arrow; // 今回のみ使用する方向
			only_arrow = rand() % 3;
			switch (only_arrow) {
			case 0: {
				_variable.targetX = -1000;
				_variable.targetY = _enemy[index].pos.y;
				break;
			}
			case 1: {
				_variable.targetX = _enemy[index].pos.x;
				_variable.targetY = -1000;
				break;
			}
			case 2: {
				_variable.targetX = 4180;
				_variable.targetY = _enemy[index].pos.y;
				break;
			}
			}
		}
		_enemy[index].pos.x = EasingInQuad(_enemy[index].action_cnt, _enemy[index].pos.x, _variable.targetX, flame);
		_enemy[index].pos.y = EasingInQuad(_enemy[index].action_cnt, _enemy[index].pos.y, _variable.targetY, flame);
		_enemy[index].action_cnt++;
		RadCalculateE7(index, chara_x, chara_y, search, search2);
		PosSynchro(index);

		if (_enemy[index].action_cnt >= 210) {
			_variable.targetX = 0;
			_variable.targetY = 0;
			BossPosChange(index);
		}
		break;
	}
	}
}


// 
void EnemyBase::BossPosChange(int index) {
	// 画面外に出た後のボスの行動決定
	int arrow = -1;
	int case_num = 0;
	
	arrow = rand() % 2;
	switch (arrow) {
	case 0:{
		_enemy[index].arrow = -1;

		while(true){
			case_num = rand() % 35;
			if (case_num == 16 || case_num == 21 || case_num == 22 || case_num == 23 || case_num == 31 || case_num == 32) {
				break;
			}
		}
		// 変更後のアクションコントロールの値で場所を決める
		switch (case_num) {
		case 16: {
			_enemy[index].action_cnt = 0;
			_enemy[index].pos.x = 4180;
			_enemy[index].pos.y = rand() % 2160;
			if (_enemy[index].pos.y <= 200) {
				_enemy[index].pos.y = 200;
			}
			if (_enemy[index].pos.y >= 1100) {
				_enemy[index].pos.y = 1100;
			}
			break;
		}
		case 21: {
			_enemy[index].action_cnt = 0;
			_enemy[index].pos.x = 4180;
			int range = rand() % 300;
			_enemy[index].pos.y = 1700 + range;
			break;
		}
		case 22: {
			_enemy[index].action_cnt = 0;
			_enemy[index].pos.x = 4180;
			int range = rand() % 800;
			_enemy[index].pos.y = 500 + range;

			break;
		}
		case 23: {
			_enemy[index].action_cnt = 0;
			_enemy[index].pos.x = 4180;
			int range = rand() % 100;
			_enemy[index].pos.y = 200 + range;
			break;
		}
		case 31: {
			_enemy[index].action_cnt = 0;
			_enemy[index].pos.x = 4180;
			int range = rand() % 600;
			_enemy[index].pos.y = 500 + range;
			break;
		}
		case 32: {
			_enemy[index].action_cnt = 0;
			_enemy[index].pos.x = 4180;
			int range = rand() % 1500;
			_enemy[index].pos.y = range;
			break;
		}
		}
		_enemy[index].action_control = case_num;
		break;
	}
	case 1: {
		_enemy[index].arrow = 1;

		while (true) {
			case_num = rand() % 35;
			if (case_num == 13 || case_num == 21 || case_num == 22 || case_num == 23 || case_num == 31 || case_num == 32) {
				break;
			}
		}
		// 変更後のアクションコントロールの値で場所を決める
		switch (case_num) {
		case 13: {
			_enemy[index].action_cnt = 0;
			_enemy[index].pos.x = -1000;
			if (_enemy[index].pos.y <= 500) {
				_enemy[index].pos.y = 500;
			}
			if (_enemy[index].pos.y >= 1100) {
				_enemy[index].pos.y = 1100;
			}
			break;
		}
		case 21: {
			_enemy[index].action_cnt = 0;
			_enemy[index].pos.x = -1000;
			int range = rand() % 300;
			_enemy[index].pos.y = 1700 + range;
			break;
		}
		case 22: {
			_enemy[index].action_cnt = 0;
			_enemy[index].pos.x = -1000;
			int range = rand() % 800;
			_enemy[index].pos.y = 500 + range;
			break;
		}
		case 23: {
			_enemy[index].action_cnt = 0;
			_enemy[index].pos.x = -1000;
			int range = rand() % 100;
			_enemy[index].pos.y = 200 + range;
			break;
		}
		case 31: {
			_enemy[index].action_cnt = 0;
			_enemy[index].pos.x = -1000;
			int range = rand() % 600;
			_enemy[index].pos.y = 500 + range;
			break;
		}
		case 32: {
			_enemy[index].action_cnt = 0;
			_enemy[index].pos.x = -1000;
			int range = rand() % 1500;
			_enemy[index].pos.y = range;
			break;
		}
		}
		_enemy[index].action_control = case_num;
		break;
	}
	}
}