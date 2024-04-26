/*****************************************************************//**
 * \file   EnemyRadCalculate.cpp
 * \brief  エネミーのサーチ矩形の挙動
 *
 * \author 奈良充樹
 * \date   September 2023
 *********************************************************************/

#include "enemybase.h"
#include "DxLib.h"
#include "mydraw.h"

void EnemyBase::RadCalculateE7(int index, int chara_x, int chara_y, HITSLIDE search, HITSLIDE search2) {
	// タレット弾用のサーチ矩形動作
	if (search.hit == SEARCH_AREA2) {
		if (_enemy[index].type == CHARA_TYPE_ENEMY7) {
			_variable.isdetectB = true;
		}

		float rotspeed = 1.0f;
		if (RadToDeg(_variable.angle[0]) > 360) {
			_variable.angle[0] = 0.0f;
		}
		else if (RadToDeg(_variable.angle[0]) < 0) {
			_variable.angle[0] = 360.0f;
		}

		float dir;
		dir = atan2(_enemy[index].pos.y - chara_y, _enemy[index].pos.x - chara_x);
		if (RadToDeg(dir) < 0) {
			dir += DegToRad(360);
		}
		if (dir > _variable.angle[0] || RadToDeg(_variable.angle[0]) - RadToDeg(dir) > 200) {
			_variable.angle[0] += DegToRad(rotspeed);
		}
		else {
			_variable.angle[0] -= DegToRad(rotspeed);
		}

		PosSynchro(index);
	}
	else {
		if (_enemy[index].type == CHARA_TYPE_ENEMY7) {
			_variable.isdetectB = false;
		}
		if (RadToDeg(_variable.angle[0]) > 360) {
			_variable.angle[0] = 0.0f;
		}
		else if (RadToDeg(_variable.angle[0]) < 0) {
			_variable.angle[0] = 360.0f;
		}

		_variable.angle[0] += DegToRad(0.50);
		PosSynchro(index);
	}
	// スナイプ用のサーチ矩形判定
	if (_enemy[index].type == CHARA_TYPE_ENEMY7) {
		if (search2.hit == SEARCH_AREA3) {
			_variable.issnipeB = true;
		}
		else {
			_variable.issnipeB = false;
		}
	}
}