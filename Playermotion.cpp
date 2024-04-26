/*****************************************************************//**
 * \file   Playermotion.cpp
 * \brief  �v���C���[���[�V����
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/
#include "Player.h"

//�v���C���[�̃��[�V�������܂Ƃ߂�������

void Player::DoFrameCount(int stock) {
	SetMotSpeed();
	_gPlayer.motcnt++;

	if(_gPlayer.motcnt >= _gPlayer.motspeed) {
		_gPlayer.motaddnum++;
		_gPlayer.motcnt = 0;
	}
	//���̒l�܂ōs�����烂�[�V�������O�ɂ���
	if(_gPlayer.motspeed * _gPlayer.motaddnum > _gPlayer.motspeed * (_gPlayer.motsheet - 1)) {
		_gPlayer.motaddnum = 0;
		_gPlayer.motcnt = 0;
		//���[�v����ԍ��̎w��
		if(_gPlayer.motten == 3) {
			_gPlayer.motaddnum = 17;
		}
		else if( _gPlayer.motten == 4 || _gPlayer.motten == 5 || _gPlayer.motten == 6 ) {
			_gPlayer.motaddnum = 40;
		}
		//�W�����v��͂����̃��[�V����
		if(_gPlayer.motten == 2 ) {
			_gPlayer.motten = 0;
		}
	}

	//������0�ɂȂ����炽���̃��[�V�����ɕύX
	if (_gPlayer.hp <= 0 && stock <= 0) {
		_gPlayer.motone = 0;
		_gPlayer.motten = 0;
	}
}
void Player::SetMotSpeed() {
	//���[�V�����X�s�[�h��ς������Ƃ��̓V�[�g�̔ԍ������ă��[�V�����X�s�[�h��ς���
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
	//�O�̃��[�V�����ԍ��ƈ�����烂�[�V������ύX����
	if (oldmot != 0 + (ten * 10) + 0) {
		_gPlayer.motaddnum = 0;
		_gPlayer.motcnt = 0;
		_gPlayer.loop = 0;
		switch (handred) {
		case 0: {
			switch (ten) {
			case 0:
				//����
				_gPlayer.motsheet = 31;
				_gPlayer.motspeed = 4;
				break;
			case 1:
				//����
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 2;
				break;
			case 2:
				//�W�����v
				_gPlayer.motsheet = 24;
				_gPlayer.motspeed = 1;
				_gPlayer.motaddnum = 3;
				break;
			case 3:
				//�ʏ�e
				_gPlayer.motsheet = 21;
				_gPlayer.motspeed = 3;
				break;
			case 4:
				//���˒e
				_gPlayer.motsheet = 60;
				_gPlayer.motspeed = 1;
				break;
			case 5:
				//�ђʒe
				_gPlayer.motsheet = 60;
				_gPlayer.motspeed = 1;
				break;
			case 6:
				//������
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 3;
				break;
			case 7:
				//�����{�ʏ�e
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 2;
				break;
			case 8:
				//�����{���˒e
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 2;
				break;
			}
		}
		case 1: {
			switch (ten) {
			case 0:
				//����
				_gPlayer.motsheet = 31;
				_gPlayer.motspeed = 4;
				break;
			case 1:
				//����
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 2;
				break;
			case 2:
				//�W�����v
				_gPlayer.motsheet = 24;
				_gPlayer.motspeed = 1;
				_gPlayer.motaddnum = 3;

				break;
			case 3:
				//�ʏ�e
				_gPlayer.motsheet = 21;
				_gPlayer.motspeed = 1;
				break;
			case 4:
				//���˒e
				_gPlayer.motsheet = 60;
				_gPlayer.motspeed = 1;
				break;
			case 5:
				//�ђʒe
				_gPlayer.motsheet = 60;
				_gPlayer.motspeed = 1;
				break;
			case 6:
				//������
				_gPlayer.motsheet = 60;
				_gPlayer.motspeed = 1;
				break;
			case 7:
				//�����{�ʏ�e
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 2;
				break;
			case 8:
				//�����{���˒e
				_gPlayer.motsheet = 22;
				_gPlayer.motspeed = 2;
				break;
			}
		}
		}
	}

	//�������e�������[�V�����̎��Ɏ~�܂�����e���\������Ԃ���n�߂�
	if (oldmot == 70 && ten * 10 == 30) {
		_gPlayer.motaddnum = 17;
	}
	else if (oldmot == 80 && ten * 10 == 40) {
		_gPlayer.motaddnum = 40;
	}

}