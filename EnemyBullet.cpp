/*****************************************************************//**
 * \file   EnemyBullet.cpp
 * \brief  �G�l�~�[�̒e���
 *
 * \author �ޗǏ[���A�V�� ��H
 * \date   August 2023
 *********************************************************************/

#include "EnemyBullet.h"
#include "Character.h"
#include "main.h"
#include "mydraw.h"



EnemyBullet::EnemyBullet() {
	

	info_bullet.w = 60;
	info_bullet.h = 60;

	bullet_anim.motaddcount = 0;
	bullet_anim.motcount = 0;
	bullet_anim.motspeed = 8;
	bullet_anim.motseet = 20;

	for(int i = 0; i < ENEMY_MAX; i++) {
		info_bullet.bulletmax[i] = 0;
		for(int j = 0; j < 2; j++) {
			info_bullet.delaycnt[i][j] = 0;
		}
		info_bullet.limit[i] = 0;


		for(int j = 0; j < E_BULLET_MAX; j++) {
			e_bullet[i][j].type = BULLET_TYPE_ENEMY;
			e_bullet[i][j].bullettype = E_BULLET_0;
			e_bullet[i][j].Xspeed = 0;
			e_bullet[i][j].Yspeed = 0;

			e_bullet[i][j].isuse = false;
			e_bullet[i][j].x = 0;
			e_bullet[i][j].y = 0;
			e_bullet[i][j].cx = 0;
			e_bullet[i][j].cy = 0;
			e_bullet[i][j].arrow = 0;
			e_bullet[i][j].aiming = 0;
			e_bullet[i][j].special = 0;
			e_bullet[i][j].BWstate = 0;

			b_hitcircle[i][j].x = 0.0f;
			b_hitcircle[i][j].y = 0.0f;
			b_hitcircle[i][j].r = 0.0f;
		}
	}
	for (int i = 0; i < 100; i++) {
		_boss_parameter[i] = 0;
	}
}

EnemyBullet::~EnemyBullet() {

}

void EnemyBullet::BulletInit(int index, int bullet) {

	e_bullet[index][bullet].type = BULLET_TYPE_ENEMY;
	e_bullet[index][bullet].bullettype = E_BULLET_0;
	e_bullet[index][bullet].Xspeed = 0;
	e_bullet[index][bullet].Yspeed = 0;

	e_bullet[index][bullet].isuse = false;
	e_bullet[index][bullet].x = 0;
	e_bullet[index][bullet].y = 0;
	e_bullet[index][bullet].cx = 0;
	e_bullet[index][bullet].cy = 0;
	e_bullet[index][bullet].arrow = 0;
	e_bullet[index][bullet].aiming = 0;
	e_bullet[index][bullet].special = 0;
	e_bullet[index][bullet].BWstate = 0;

	b_hitcircle[index][bullet].x = 0.0f;
	b_hitcircle[index][bullet].y = 0.0f;
	b_hitcircle[index][bullet].r = 0.0f;
}

void EnemyBullet::BulletDir(int index, int bullet, int aiming, int arrow, int speed, int bullet_type ,float direction) {
// �e�̕����i�s�w��
	e_bullet[index][bullet].arrow = arrow;
	e_bullet[index][bullet].aiming = aiming;
	switch(bullet_type) {
	case E_BULLET_1:
	case E_BULLET_3:
	case E_BULLET_5: {
			switch(e_bullet[index][bullet].arrow) {
			case 1: {
				switch(e_bullet[index][bullet].aiming) {
				case 0: {
					e_bullet[index][bullet].Xspeed = speed;
					e_bullet[index][bullet].Yspeed = 0;
					break;
				}
				case 1: {
					e_bullet[index][bullet].Xspeed = speed * cos(Rad6);
					e_bullet[index][bullet].Yspeed = speed * sin(Rad6);
					break;
				}
				case 2: {
					e_bullet[index][bullet].Xspeed = speed * cos(Rad1);
					e_bullet[index][bullet].Yspeed = speed * sin(Rad1);
					break;
				}
				}
				break;
			}
			case -1: {
				switch(e_bullet[index][bullet].aiming) {
				case 0: {
					e_bullet[index][bullet].Xspeed = -speed;
					e_bullet[index][bullet].Yspeed = 0;
					break;
				}
				case 1: {
					e_bullet[index][bullet].Xspeed = speed * cos(Rad4);
					e_bullet[index][bullet].Yspeed = speed * sin(Rad4);
					break;
				}
				case 2: {
					e_bullet[index][bullet].Xspeed = speed * cos(Rad3);
					e_bullet[index][bullet].Yspeed = speed * sin(Rad3);
					break;
				}
				}
				break;
			}
			}
	}
			break;
	case E_BULLET_2:
	case E_BULLET_4:
	case E_BULLET_6:
	case E_BULLET_7:
	case E_BULLET_8:
	case E_BULLET_9: {
		e_bullet[index][bullet].Xspeed = speed * cos(direction);
		e_bullet[index][bullet].Yspeed = speed * sin(direction);
		break;
	}
}

}

void EnemyBullet::E_ShootProcess(int index, int type, int A_cont, int eneX, int eneY, int aiming, int arrow, int chara_x, int chara_y,float turret_dir) {
// �G�l�~�[�̒e����
	switch(type) {
	case CHARA_TYPE_ENEMY1: {
		if(A_cont == 3) {
	int speed = 0;

	info_bullet.delaycnt[index][0]++;

	if(info_bullet.delaycnt[index][0] > COOLTIME3) {
		if(info_bullet.limit[index] > 2) {
			info_bullet.limit[index] = 0;
		}
		if(info_bullet.limit[index] < 3) {
			info_bullet.delaycnt[index][1]++;
			if(info_bullet.delaycnt[index][1] >= COOLTIME1) {
				for(int i = 0; i < E_BULLET_MAX; i++) {
					if(e_bullet[index][i].isuse != true) {
						e_bullet[index][i].isuse = true;

						// ���W�̓G�C�~���O�ɂ���Ĉʒu���킹���K�v(�e�X�g�i�K�̓v���C���[�̔���)
						// �܂��̃G�C�~���O�ɑg�ݍ��ނ���
						e_bullet[index][i].x = eneX + 115;
						e_bullet[index][i].y = eneY + 20;
						e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
						e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
						e_bullet[index][i].bullettype = E_BULLET_1;
						speed = B_SPEED1;

						BulletDir(index, i, aiming, arrow, speed, e_bullet[index][i].bullettype,0);
						info_bullet.limit[index]++;
						info_bullet.delaycnt[index][1] = 0;
						if(info_bullet.limit[index] > 2) {
							info_bullet.delaycnt[index][0] = 0;
						}
									_music->MakeSe(_image->Se[12]);
								break;
							}
						}
					}
				}
			}
		}
		break;
	}
	case CHARA_TYPE_ENEMY3: {
		if(A_cont == 3) {
			int speed = 0;

			info_bullet.delaycnt[index][0]++;
			if(info_bullet.delaycnt[index][0] > COOLTIME3) {
				if(info_bullet.limit[index] > 2) {
					info_bullet.limit[index] = 0;
				}
				if(info_bullet.limit[index] < 3) {
					info_bullet.delaycnt[index][1]++;
					if(info_bullet.delaycnt[index][1] >= COOLTIME1) {
						for(int i = 0; i < E_BULLET_MAX; i++) {
							if(e_bullet[index][i].isuse != true) {
								e_bullet[index][i].isuse = true;

								// ���W�̓G�C�~���O�ɂ���Ĉʒu���킹���K�v(�e�X�g�i�K�̓v���C���[�̔���)
								// �܂��̃G�C�~���O�ɑg�ݍ��ނ���
								e_bullet[index][i].x = eneX + 115;
								e_bullet[index][i].y = eneY + 20;
								e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
								e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
								e_bullet[index][i].bullettype = E_BULLET_3;
								speed = B_SPEED1;

								BulletDir(index, i, aiming, arrow, speed, e_bullet[index][i].bullettype, 0);
								info_bullet.limit[index]++;
								info_bullet.delaycnt[index][1] = 0;
								if(info_bullet.limit[index] > 2) {
									info_bullet.delaycnt[index][0] = 0;
								}
								_music->MakeSe(_image->Se[12]);
								break;
							}
						}
					}
				}
			}
		}
		break;
	}
	case CHARA_TYPE_ENEMY5: {
		if(A_cont == 3) {
			int speed = 0;

			info_bullet.delaycnt[index][0]++;
			if(info_bullet.delaycnt[index][0] > COOLTIME3) {
				if(info_bullet.limit[index] > 2) {
					info_bullet.limit[index] = 0;
				}
				if(info_bullet.limit[index] < 3) {
					info_bullet.delaycnt[index][1]++;
					if(info_bullet.delaycnt[index][1] >= COOLTIME1) {
						for(int i = 0; i < E_BULLET_MAX; i++) {
							if(e_bullet[index][i].isuse != true) {
								e_bullet[index][i].isuse = true;

								// ���W�̓G�C�~���O�ɂ���Ĉʒu���킹���K�v(�e�X�g�i�K�̓v���C���[�̔���)
								// �܂��̃G�C�~���O�ɑg�ݍ��ނ���
								e_bullet[index][i].x = eneX + 115;
								e_bullet[index][i].y = eneY + 20;
								e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
								e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
								e_bullet[index][i].bullettype = E_BULLET_5;
								speed = B_SPEED1;

								BulletDir(index, i, aiming, arrow, speed, e_bullet[index][i].bullettype, 0);
								info_bullet.limit[index]++;
								info_bullet.delaycnt[index][1] = 0;
								if(info_bullet.limit[index] > 2) {
									info_bullet.delaycnt[index][0] = 0;
								}
									_music->MakeSe(_image->Se[12]);
								break;
							}
						}
					}
				}
			}
		}
		break;
	}
	case CHARA_TYPE_ENEMY2: {
		if (A_cont == 4) {
			int speed = 0;

			info_bullet.delaycnt[index][0]++;

			if (info_bullet.delaycnt[index][0] > COOLTIME2) {
				if (info_bullet.limit[index] > 2) {
					info_bullet.limit[index] = 0;
				}
				if (info_bullet.limit[index] < 3) {
					info_bullet.delaycnt[index][1]++;
					if (info_bullet.delaycnt[index][1] >= COOLTIME1) {
						for (int i = 0; i < E_BULLET_MAX; i++) {
							if (e_bullet[index][i].isuse != true) {
								e_bullet[index][i].isuse = true;

								// ���W�̓G�C�~���O�ɂ���Ĉʒu���킹���K�v(�e�X�g�i�K�̓v���C���[�̔���)
								// �܂��̃G�C�~���O�ɑg�ݍ��ނ���
								e_bullet[index][i].x = eneX + 70;
								e_bullet[index][i].y = eneY + 70;
								e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
								e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
								e_bullet[index][i].bullettype = E_BULLET_2;
								speed = B_SPEED1;

								e_bullet[index][i].direction = turret_dir + DegToRad(180);//atan2�͍���0�ŉE��180 �������ŏオ��
								BulletDir(index, i, 0, 2, speed, e_bullet[index][i].bullettype, e_bullet[index][i].direction);

								info_bullet.limit[index]++;
								info_bullet.delaycnt[index][1] = 0;
								if (info_bullet.limit[index] > 2) {
									info_bullet.delaycnt[index][0] = 0;
								}
								_music->MakeSe(_image->Se[13]);
								break;
							}
						}
					}
				}
			}
		}
		break;
	}
	case CHARA_TYPE_ENEMY4: {
		if(A_cont == 4) {
			int speed = 0;

			info_bullet.delaycnt[index][0]++;

			if(info_bullet.delaycnt[index][0] > COOLTIME2) {
				if(info_bullet.limit[index] > 2) {
					info_bullet.limit[index] = 0;
				}
				if(info_bullet.limit[index] < 3) {
					info_bullet.delaycnt[index][1]++;
					if(info_bullet.delaycnt[index][1] >= COOLTIME1) {
						for(int i = 0; i < E_BULLET_MAX; i++) {
							if(e_bullet[index][i].isuse != true) {
								e_bullet[index][i].isuse = true;

								// ���W�̓G�C�~���O�ɂ���Ĉʒu���킹���K�v(�e�X�g�i�K�̓v���C���[�̔���)
								// �܂��̃G�C�~���O�ɑg�ݍ��ނ���
								e_bullet[index][i].x = eneX + 70;
								e_bullet[index][i].y = eneY + 70;
								e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
								e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
								e_bullet[index][i].bullettype = E_BULLET_4;
								speed = B_SPEED1;

								e_bullet[index][i].direction = turret_dir + DegToRad(180);//atan2�͍���0�ŉE��180 �������ŏオ��
								BulletDir(index, i, 0, 2, speed, e_bullet[index][i].bullettype, e_bullet[index][i].direction);

								info_bullet.limit[index]++;
								info_bullet.delaycnt[index][1] = 0;
								if(info_bullet.limit[index] > 2) {
									info_bullet.delaycnt[index][0] = 0;
								}
								_music->MakeSe(_image->Se[13]);
								break;
							}
						}
					}
				}
			}
		}
		break;
	}
	case CHARA_TYPE_ENEMY6: {
		if(A_cont == 4) {
			int speed = 0;

			info_bullet.delaycnt[index][0]++;

			if(info_bullet.delaycnt[index][0] > COOLTIME2) {
				if(info_bullet.limit[index] > 2) {
					info_bullet.limit[index] = 0;
				}
				if(info_bullet.limit[index] < 3) {
					info_bullet.delaycnt[index][1]++;
					if(info_bullet.delaycnt[index][1] >= COOLTIME1) {
						for(int i = 0; i < E_BULLET_MAX; i++) {
							if(e_bullet[index][i].isuse != true) {
								e_bullet[index][i].isuse = true;

								// ���W�̓G�C�~���O�ɂ���Ĉʒu���킹���K�v(�e�X�g�i�K�̓v���C���[�̔���)
								// �܂��̃G�C�~���O�ɑg�ݍ��ނ���
								e_bullet[index][i].x = eneX + 70;
								e_bullet[index][i].y = eneY + 70;
								e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
								e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
								e_bullet[index][i].bullettype = E_BULLET_6;
								speed = B_SPEED1;

								e_bullet[index][i].direction = turret_dir + DegToRad(180);//atan2�͍���0�ŉE��180 �������ŏオ��
								BulletDir(index, i, 0, 2, speed, e_bullet[index][i].bullettype, e_bullet[index][i].direction);

								info_bullet.limit[index]++;
								info_bullet.delaycnt[index][1] = 0;
								if(info_bullet.limit[index] > 2) {
									info_bullet.delaycnt[index][0] = 0;
								}
								_music->MakeSe(_image->Se[13]);
								break;
							}
						}
					}
				}
			}
		}
		break;
	}
	}
}

void EnemyBullet::E7_ShootProcess(int index, int type, int A_cont, int eneX, int eneY, int chara_x, int chara_y, bool detect, bool guide, bool snipe, int enearrow, int BWstate) {
// �{�X�̒e����
	if (A_cont != 0) {
		// �ʏ�e
		if (detect == true) {
			int speed = 0;

			info_bullet.delaycnt[index][0]++;

			if (info_bullet.delaycnt[index][0] > COOLTIME2) {
				if (info_bullet.limit[index] > 2) {
					info_bullet.limit[index] = 0;
				}
				if (info_bullet.limit[index] < 3) {
					info_bullet.delaycnt[index][1]++;
					if (info_bullet.delaycnt[index][1] >= COOLTIME1) {
						for (int i = 0; i < E_BULLET_MAX; i++) {
							if (e_bullet[index][i].isuse != true) {
								e_bullet[index][i].isuse = true;

								// ���W�̓G�C�~���O�ɂ���Ĉʒu���킹���K�v(�e�X�g�i�K�̓v���C���[�̔���)
								// �܂��̃G�C�~���O�ɑg�ݍ��ނ���
								if (enearrow == -1) {
									e_bullet[index][i].x = eneX + 200;
									e_bullet[index][i].y = eneY + 500;
								}
								if (enearrow == 1) {
									e_bullet[index][i].x = eneX + 600;
									e_bullet[index][i].y = eneY + 500;
								}
								e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
								e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
								e_bullet[index][i].bullettype = E_BULLET_7;
								speed = B_SPEED1;

								e_bullet[index][i].BWstate = BWstate;
								e_bullet[index][i].direction = atan2(chara_y + 150 - e_bullet[index][i].y, chara_x + 150 - e_bullet[index][i].x);//atan2�͍���0�ŉE��180 �������ŏオ��
								BulletDir(index, i, 0, 2, speed, e_bullet[index][i].bullettype, e_bullet[index][i].direction);

								info_bullet.limit[index]++;
								info_bullet.delaycnt[index][1] = 0;
								if (info_bullet.limit[index] > 2) {
									info_bullet.delaycnt[index][0] = 0;
								}
								_music->MakeSe(_image->Se[13]);
								break;
							}
						}
					}
				}
			}
		}
		// �U���e
		if (guide == true) {
			int speed = 0;

			_boss_parameter[0]++;

			if (_boss_parameter[0] > COOLTIME5) {
				if (_boss_parameter[2] > 0) {
					_boss_parameter[2] = 0;
				}
				_boss_parameter[1]++;
				if (_boss_parameter[1] >= COOLTIME6) {
					for (int i = 0; i < E_BULLET_MAX; i++) {
						if (e_bullet[index][i].isuse != true) {
							e_bullet[index][i].isuse = true;

							// ���W�̓G�C�~���O�ɂ���Ĉʒu���킹���K�v(�e�X�g�i�K�̓v���C���[�̔���)
							// �܂��̃G�C�~���O�ɑg�ݍ��ނ���
							if (enearrow == -1) {
								e_bullet[index][i].x = eneX + 400;
								e_bullet[index][i].y = eneY + 500;
							}
							if (enearrow == 1) {
								e_bullet[index][i].x = eneX + 400;
								e_bullet[index][i].y = eneY + 500;
							}
							e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
							e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
							e_bullet[index][i].bullettype = E_BULLET_8;
							speed = B_SPEED0;

							e_bullet[index][i].BWstate = BWstate;
							e_bullet[index][i].direction = atan2(chara_y + 150 - e_bullet[index][i].y, chara_x + 150 - e_bullet[index][i].x);//atan2�͍���0�ŉE��180 �������ŏオ��
							BulletDir(index, i, 0, 2, speed, e_bullet[index][i].bullettype, e_bullet[index][i].direction);

							_boss_parameter[2]++;
							_boss_parameter[1] = 0;
							_boss_parameter[6] = 0;
							_boss_parameter[7] = 0;
							if (_boss_parameter[2] > 0) {
								_boss_parameter[0] = 0;
							}
							_music->MakeSe(_image->Se[27]);
							break;
						}
					}
				}
			}
		}
		// �����e
		if (snipe == true) {
			int speed = 0;

			_boss_parameter[3]++;

			if (_boss_parameter[3] > COOLTIME7) {
				if (_boss_parameter[5] > 0) {
					_boss_parameter[5] = 0;
				}
				_boss_parameter[4]++;
				if (_boss_parameter[4] >= COOLTIME8) {
					for (int i = 0; i < E_BULLET_MAX; i++) {
						if (e_bullet[index][i].isuse != true) {
							e_bullet[index][i].isuse = true;

							// ���W�̓G�C�~���O�ɂ���Ĉʒu���킹���K�v(�e�X�g�i�K�̓v���C���[�̔���)
							// �܂��̃G�C�~���O�ɑg�ݍ��ނ���
							if (enearrow == -1) {
								e_bullet[index][i].x = eneX + 400;
								e_bullet[index][i].y = eneY + 500;
							}
							if (enearrow == 1) {
								e_bullet[index][i].x = eneX + 400;
								e_bullet[index][i].y = eneY + 500;
							}
							e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
							e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
							e_bullet[index][i].bullettype = E_BULLET_9;
							speed = B_SPEED4;

							e_bullet[index][i].BWstate = BWstate;
							e_bullet[index][i].direction = atan2(chara_y + 150 - e_bullet[index][i].y, chara_x + 150 - e_bullet[index][i].x);//atan2�͍���0�ŉE��180 �������ŏオ��
							BulletDir(index, i, 0, 2, speed, e_bullet[index][i].bullettype, e_bullet[index][i].direction);

							_boss_parameter[5]++;
							_boss_parameter[4] = 0;
							if (_boss_parameter[5] > 0) {
								_boss_parameter[3] = 0;
							}
							_music->MakeSe(_image->Se[13]);
							break;
						}
					}
				}
			}
		}
	}
}

void EnemyBullet::GuideCurveProcess(int index, int bullet, float chara_x, float chara_y, float chara_w,float chara_h) {
// �U���e�̃J�[�u�̃v���Z�X
	int max_direction = 15;   //�Ȃ���p�x�̍ő�l�ł�
	int curve_count = 100;    //�Ȃ���񐔂ł�
	int cool_time = 10;       //�Ȃ���܂ł̃N�[���^�C���ł��i�t���[���P�ʁj

	//���̊p�x��ς��鏈����
	if (e_bullet[index][bullet].isuse == true) {
		if (e_bullet[index][bullet].bullettype == E_BULLET_8) {
			_boss_parameter[index+50]--;//�Ȃ���N�[���^�C�������炷
			if (_boss_parameter[index+50] <= 0) {//�N�[���^�C�����Ȃ��Ȃ�����p�x��ύX����
				_boss_parameter[index + 70]++;	// �Ȃ���񐔂��J�E���g����
				if (_boss_parameter[index + 70] < curve_count) {		// �Ȃ���񐔂��܂��c���Ă����瓮���@�X�̐�����ς���ƋȂ���񐔂�ς����@�Ȃ���p�x��傫������Ȃ炱����ς��Ȃ��Ƃ������ǔ����Ă���
					float bullet_direction = atan2(chara_y + chara_h / 2 - e_bullet[index][bullet].y, chara_x + chara_w / 2 - e_bullet[index][bullet].x);//�p�x���o��
					float newrad = DegToRad(bullet_direction);//PI���g���̂Ōv�Z���₷���悤��radian�ɕϊ�
					float rad = DegToRad(e_bullet[index][bullet].direction);
					float vRad = DegToRad(DegToRad(max_direction));	//�����radian�ɕϊ� ������ς�����Ȃ���p�x�̍ő�l��ς�����@�������߂̓J�N�J�N�����Ȃ�30�x�ȉ����牓��肵�����Ȃ��P�T�x�̂��������炢
					
					float pi = DegToRad(PI);

					if (fabs(newrad - rad) < vRad) {//atan2��180�`-180�Ȃ̂Ő�Βl�ɂ���ƌv�Z���₷��
						e_bullet[index][bullet].direction = RadToDeg(newrad);		// �p�x��degree�ɕϊ�����
					}
					else {
						// ���̌�����vRad�����V���������ɋ߂Â���
						if (newrad < rad - pi) { rad -= pi * 2; }      
						else if (newrad > rad + pi) { rad += pi * 2; }
						if (newrad < rad) {
							rad -= vRad;
						}
						else {
							rad += vRad;
						}
						e_bullet[index][bullet].direction = RadToDeg(rad);		// �p�x��degree�ɕϊ�����

					}
				}
				else if (_boss_parameter[index + 70] >= curve_count) {
					_boss_parameter[index + 70] = 0;
				}
				_boss_parameter[index + 50] = cool_time;	// �p�x��ς��邽�߂̃N�[���^�C��
			}
		}
	}

}

void EnemyBullet::CommonProcess(int index, float chara_x, float chara_y, float chara_w, float chara_h,float dir) {
	// ���ʏ���
	for(int i = 0; i < E_BULLET_MAX; i++) {
		if (e_bullet[index][i].bullettype == E_BULLET_8) {
			GuideCurveProcess(index, i, chara_x, chara_y, chara_w, chara_h);
			int speed = B_SPEED0;
			BulletDir(index, i, 0, 2, speed, e_bullet[index][i].bullettype, e_bullet[index][i].direction);
		}
			if (e_bullet[index][i].isuse == true) {
				e_bullet[index][i].x += e_bullet[index][i].Xspeed;
				e_bullet[index][i].y += e_bullet[index][i].Yspeed;
				e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
				e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
			}
			//�@�~����̈ʒu�␳
			switch (e_bullet[index][i].arrow) {
			case 1: {
				switch (e_bullet[index][i].aiming) {
				case 0: {
					b_hitcircle[index][i].x = e_bullet[index][i].x + 20.0f + 13.f;
					b_hitcircle[index][i].y = e_bullet[index][i].y + 15.0f + 15.f;
					break;
				}
				case 1: {
					b_hitcircle[index][i].x = e_bullet[index][i].x + 25.0f * cos(Rad1) + 13.f;
					b_hitcircle[index][i].y = e_bullet[index][i].y + 5.0f * sin(Rad1) + 22.f;
					break;
				}
				case 2: {
					b_hitcircle[index][i].x = e_bullet[index][i].x + 25.0f * cos(Rad6) + 17.f;
					b_hitcircle[index][i].y = e_bullet[index][i].y + 10.0f + 16.f;
					break;
				}
				}
				break;
			}
			case -1: {
				switch (e_bullet[index][i].aiming) {
				case 0: {
					b_hitcircle[index][i].x = e_bullet[index][i].x + 13.0f + 15.f;
					b_hitcircle[index][i].y = e_bullet[index][i].y + 15.0f + 15.f;
					break;
				}
				case 1: {
					b_hitcircle[index][i].x = e_bullet[index][i].x + -25.0f * cos(Rad3) + 15.f;
					b_hitcircle[index][i].y = e_bullet[index][i].y + 15.0f * sin(Rad3) + 15.f;
					break;
				}
				case 2: {
					b_hitcircle[index][i].x = e_bullet[index][i].x + -15.0f * cos(Rad4) + 13.f;
					b_hitcircle[index][i].y = e_bullet[index][i].y + 10.0f + 18.f;
					break;
				}
				}
				break;
			}
			case 2: {
				//�G�l�~�[�Q�Ŏg�킹�Ă��������܂��B�@��ϐ\���󂲂����܂���B
				if (e_bullet[index][i].bullettype != E_BULLET_7 && e_bullet[index][i].bullettype != E_BULLET_8 && e_bullet[index][i].bullettype != E_BULLET_9) {
					b_hitcircle[index][i].x = (e_bullet[index][i].x + 30) + 75 * cos(e_bullet[index][i].direction);
					b_hitcircle[index][i].y = (e_bullet[index][i].y + 30) + 75 * sin(e_bullet[index][i].direction);
				}
				else {
					b_hitcircle[index][i].x = (e_bullet[index][i].x + 30) + 15 * cos(e_bullet[index][i].direction);
					b_hitcircle[index][i].y = (e_bullet[index][i].y + 30) + 15 * sin(e_bullet[index][i].direction);
				}
				break;
			}
			}						
		


		b_hitcircle[index][i].r = 10.0f;

		if(3840 < e_bullet[index][i].x || 0 > e_bullet[index][i].x || 2160 < e_bullet[index][i].y || 0 > e_bullet[index][i].y) {
			BulletInit(index, i);
	
		}
	}
}

void EnemyBullet::BossEffect(int index) {
	//�{�X
	for (int i = 0; i < E_BULLET_MAX; i++) {
		if (e_bullet[index][i].isuse == true) {
			switch (e_bullet[index][i].bullettype) {
			case 8: {
				_effect->SetEffect(e_bullet[index][i].cx, e_bullet[index][i].cy, 3, RadToDeg(e_bullet[index][i].direction), 0, 0, 0, 1, EFFECT_BOSS);
				break;
			}
			case 9: {
				_effect->SetEffect(e_bullet[index][i].cx, e_bullet[index][i].cy, 3, RadToDeg(e_bullet[index][i].direction), 0, 0, 0, 1, EFFECT_BOSS);
				break;
			}
			}
		}
	}
};

void EnemyBullet::BulletEffect() {


	
//�G�l�~�[�P�R�T�̋�
	bullet_anim.motcount++;
	if (bullet_anim.motcount >= bullet_anim.motspeed) {
		bullet_anim.motcount = 0;
		bullet_anim.motaddcount++;
	}
	if (bullet_anim.motaddcount * bullet_anim.motspeed > (bullet_anim.motseet - 1) * bullet_anim.motspeed) {
		bullet_anim.motcount = 0;
		bullet_anim.motaddcount = 0;
	}
}

void  EnemyBullet::MapHitProcess(int index, int bullet) {
	// �}�b�v�ɓ����������̏���
	if (e_bullet[index][bullet].isuse != 0) {
		_effect->SetEffect(b_hitcircle[index][bullet].x, b_hitcircle[index][bullet].y, EFFECT_TYPE_NORMAL_WALL, e_bullet[index][bullet].direction, 0, 0, 0, 1, EFFECT_ENEMY);
	}
	BulletInit(index, bullet);
}

void EnemyBullet::DrawTurret(MATRIX mview) {
	// �e�̕`��
	for (int i = 0; i < ENEMY_MAX; i++) {
		for (int j = 0; j < E_BULLET_MAX; j++) {
			VECTOR BULLET = VGet(e_bullet[i][j].cx + 60 * cos(e_bullet[i][j].direction), e_bullet[i][j].cy + 60 * sin(e_bullet[i][j].direction), 0);
			switch (e_bullet[i][j].bullettype) {
			case E_BULLET_2:
			case E_BULLET_4:
			case E_BULLET_6:{
				MyDrawModiGraph(mview, BULLET, 1.f, e_bullet[i][j].direction, info_bullet.w, info_bullet.h, _image->GetMissil());
				break;
			}
			}
		}
	}
};
void EnemyBullet::Draw(MATRIX mview) {
// �e�̕`��
	for(int i = 0; i < ENEMY_MAX; i++) {
		for(int j = 0; j < E_BULLET_MAX; j++) {
			VECTOR BULLET = VGet(e_bullet[i][j].cx, e_bullet[i][j].cy, 0);
			switch(e_bullet[i][j].bullettype) {
			case E_BULLET_1:
			case E_BULLET_3:
			case E_BULLET_5: {
				if(e_bullet[i][j].arrow == -1) {
					switch(e_bullet[i][j].aiming) {
					case 0: {
						MyDrawTurnModiGraph(mview, BULLET, 1.f, 0.f, info_bullet.w, info_bullet.h, _image->GetEnemyBullet(bullet_anim.motaddcount));
						break;
					}
					case 1: {
						MyDrawModiGraph(mview, BULLET, 1.f, Rad4, info_bullet.w, info_bullet.h, _image->GetEnemyBullet(bullet_anim.motaddcount));
						break;
					}
					case 2: {
						MyDrawModiGraph(mview, BULLET, 1.f, Rad3, info_bullet.w, info_bullet.h, _image->GetEnemyBullet(bullet_anim.motaddcount));
						break;
					}
					}
				}
				else {
					switch(e_bullet[i][j].aiming) {
					case 0: {
						MyDrawModiGraph(mview, BULLET, 1.f, 0.f, info_bullet.w, info_bullet.h, _image->GetEnemyBullet(bullet_anim.motaddcount));
						break;
					}
					case 1: {
						MyDrawModiGraph(mview, BULLET, 1.f, Rad6, info_bullet.w, info_bullet.h, _image->GetEnemyBullet(bullet_anim.motaddcount));
						break;
					}
					case 2: {
						MyDrawModiGraph(mview, BULLET, 1.f, Rad1, info_bullet.w, info_bullet.h, _image->GetEnemyBullet(bullet_anim.motaddcount));
						break;
					}
					}
				}
				break;
			}
			case E_BULLET_7:
			case E_BULLET_8:
			case E_BULLET_9: {
				MyDrawModiGraph(mview, BULLET, 1.f, e_bullet[i][j].direction, info_bullet.w, info_bullet.h, _image->GetMissil());
				break;
			}
			}
		}
	}
}