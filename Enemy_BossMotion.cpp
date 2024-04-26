/*****************************************************************//**
 * \file   Enemy_BossMotion.cpp
 * \brief  �{�X�̋����̂�
 *
 * \author �ޗǏ[��
 * \date   September 2023
 *********************************************************************/

#include "enemybase.h"
#include "DxLib.h"
#include "mydraw.h"

void EnemyBase::BossMotion(int index, int chara_x, int chara_y, HITSLIDE search, HITSLIDE search2, int map_w, int map_h) {
	// �G�l�~�[�̃X�s�[�h�ݒ�
	if (_enemy[index].isBlack == true) {
		_enemy[index].movespeed = 2 ;
	}
	else {
	_enemy[index].movespeed = 5;
	}

	switch (_enemy[index].action_control) {
	// �o�ꎞ
	case 1: {
		// ��ʏ㕔�O����w��ʒu�܂ō~��Ă���
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
		// ���̏�ő؋�
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
		// ��ʉE�ɋ����Ă���
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
	// �p�^�[��1
	case 11: {
		// ��ʉE�ő΋�
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
		// ��ʉE�ɏ�����
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
		// ��ʍ�����E�ɐi�o
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
		// ��ʍ��ő΋�
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
		// ��ʍ��ɏ�����
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
		// ��ʉE���獶�ɐi�o
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
	// �p�^�[��2
	case 21: {
		//�@���E�ړ��{���X�ɏ���
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
		//�@���E�ړ�
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
		//�@���E�ړ��{���X�ɉ�����
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
	 
	// �p�^�[��3
	case 31: {
		// ���E�؂�Ԃ��i�J�E���g�̐������j
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
	// ��ʒ������܂�32�`34
	case 32: {
		// ��ʓ��ɐi��
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
		// ��ʒ����łƂǂ܂�
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
		// ��ʊO�ɏ�����
		float flame = 300.0f;
		if (_enemy[index].action_cnt <= 0) {
			int only_arrow; // ����̂ݎg�p�������
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
	// ��ʊO�ɏo����̃{�X�̍s������
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
		// �ύX��̃A�N�V�����R���g���[���̒l�ŏꏊ�����߂�
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
		// �ύX��̃A�N�V�����R���g���[���̒l�ŏꏊ�����߂�
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