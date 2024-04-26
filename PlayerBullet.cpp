/*****************************************************************//**
 * \file   PlayerBullet.cpp
 * \brief  プレイヤーの弾情報
 *
 * \author 奈良充樹
 * \date   August 2023
 *********************************************************************/

#include "PlayerBullet.h"
#include "Character.h"
#include <cmath>
#include "mydraw.h"
#include "main.h"

PlayerBullet::PlayerBullet() {

	cutin = 0;
	for (int i = 0; i < 2; i++){
		cutin_use[i] = 0;
	}
	info_bullet.usePortalB = 0;
	info_bullet.usePortalW = 0;
	info_bullet.stance_type = 0;
	info_bullet.w = 30;
	info_bullet.h = 30;

	for(int i = 0; i < 4; i++) {
		_trg[i] = true;
	}
	
	for(int i = 0; i < P_BULLET_KINDS; i++) {
		//通常∞　貫通20　反射50　黒10　白ポ10　黒ポ10
		switch(i) {
		case 1:
			info_bullet.remainbullet[i] = _Save->GetBullet_Num(2);
			info_bullet.bulletmax[i] = _Save->GetBullet_Max(2);
			break;
		case 2:
			info_bullet.remainbullet[i] = 10;
			info_bullet.bulletmax[i] = info_bullet.remainbullet[i];
			break;
		case 3:
			info_bullet.remainbullet[i] = 10;
			info_bullet.bulletmax[i] = info_bullet.remainbullet[i];
			break;
		case 4:
			info_bullet.remainbullet[i] = _Save->GetBullet_Num(0);
			info_bullet.bulletmax[i] = _Save->GetBullet_Max(0);
			break;
		case 5:
			info_bullet.remainbullet[i] = _Save->GetBullet_Num(1);
			info_bullet.bulletmax[i] = _Save->GetBullet_Max(1);
			break;
		}
	}

	for(int i = 0; i < P_BULLET_TYPE; i++) {
		info_bullet.delaycnt[i] = 0;
		info_bullet.limit[i] = 0;
	}
	
	for(int i = 0; i < BULLET_MAX; i++) {
		p_bullet[i].type = BULLET_TYPE_PLAYER;
		p_bullet[i].state.bullettype = 0;
		p_bullet[i].state.isWhite = 0;
		p_bullet[i].state.isBlack = 0;
		p_bullet[i].state.isPortal = 0;
		p_bullet[i].Xspeed = 0;
		p_bullet[i].Yspeed = 0;
		p_bullet[i].angle_type = 0;

		p_bullet[i].usebullet = 0;  
		p_bullet[i].x = 0;
		p_bullet[i].y = 0;
		p_bullet[i].hx = 0;
		p_bullet[i].hy = 0;
		p_bullet[i].hw = 0;
		p_bullet[i].hh = 0;
		p_bullet[i].arrow = 0;
		p_bullet[i].aiming = 0;
		p_bullet[i].special = 0;

		b_hitcircle[i].x = 0.0f;
		b_hitcircle[i].y = 0.0f;
		b_hitcircle[i].r = 0.0f;

		count[i] = 0;
	}
	_power_charge = 0;
}

PlayerBullet::~PlayerBullet() {
	
}

void PlayerBullet::BulletInit(int index) {
	p_bullet[index].state.isWhite = 0;
	p_bullet[index].state.isBlack = 0;
	p_bullet[index].state.isPortal = 0;
	p_bullet[index].Xspeed = 0;
	p_bullet[index].Yspeed = 0;
			 
	p_bullet[index].usebullet = 0;
	p_bullet[index].x = 0;
	p_bullet[index].y = 0;
	p_bullet[index].hx = 0;
	p_bullet[index].hy = 0;
	p_bullet[index].hw = 0;
	p_bullet[index].hh = 0;
	p_bullet[index].arrow = 0;
	p_bullet[index].aiming = 0;
	p_bullet[index].special = 0;

	b_hitcircle[index].x = 0.0f;
	b_hitcircle[index].y = 0.0f;
	b_hitcircle[index].r = 0.0f;
}

void PlayerBullet::BWPjudge(int index, int BWPselect) {
	// ポータル判別
	switch(BWPselect) {
	case 0: {
		// 弾属性：なし
		p_bullet[index].state.isPortal = 0;
		break;
	}
	case 1: {
		// 弾属性：白ポータル
		if(info_bullet.remainbullet[WPORTAL_BULLET] != 0) {
			p_bullet[index].state.isPortal = 1;
			info_bullet.remainbullet[WPORTAL_BULLET]--;
		}
		else {
			p_bullet[index].state.isPortal = 0;
		}
		break;
	}
	case 2: {
		// 弾属性：黒ポータル
		if(info_bullet.remainbullet[BPORTAL_BULLET] != 0) {
			p_bullet[index].state.isPortal = 1;
			info_bullet.remainbullet[BPORTAL_BULLET]--;
		}
		else {
			p_bullet[index].state.isPortal = 0;
		}
		break;
	}
	}
}

void PlayerBullet::BulletDir(int index, int aiming, int arrow, int speed, int plx, int ply,int bullet_type,int reflect, int black) {
	// 弾の角度決め
	int point = 80;
	p_bullet[index].arrow = arrow;
	p_bullet[index].aiming = aiming;

	switch(p_bullet[index].arrow) {
	case 1: {
		switch(p_bullet[index].aiming) {
		case 0: {
			p_bullet[index].Xspeed = speed;
			p_bullet[index].Yspeed = 0;
			if(black != 1 && bullet_type < 2) {
				if(reflect == 0) {
					p_bullet[index].x = (plx + BULLET_SHOT_POINT) + point * cos(0);
					p_bullet[index].y = (ply + BULLET_SHOT_POINT) + point * sin(0);
				}
			}
			else {
				p_bullet[index].x = (plx + BULLET_SHOT_POINT)      + point * cos(0);
				p_bullet[index].y = (ply + BULLET_SHOT_POINT) + 60 + point * sin(0);
			}
			p_bullet[index].angle_type = 0;
			break;
		}
		case 1: {
			p_bullet[index].Xspeed = speed  * cos(Rad6);
			p_bullet[index].Yspeed = speed  * sin(Rad6);
			if(black != 1 && bullet_type < 2) {
				if(reflect == 0) {
					p_bullet[index].x = (plx + BULLET_SHOT_POINT) + point * cos(Rad6);
					p_bullet[index].y = (ply + BULLET_SHOT_POINT) + point * sin(Rad6);
				}
			}
			else {
				p_bullet[index].x = (plx + BULLET_SHOT_POINT) - 10 + point * cos(Rad6);
				p_bullet[index].y = (ply + BULLET_SHOT_POINT) + 30 + point * sin(Rad6);
			}
			p_bullet[index].angle_type = 315;
			break;
		}
		case 2: {
			p_bullet[index].Xspeed = speed * cos(Rad1);
			p_bullet[index].Yspeed = speed * sin(Rad1);
			if(black != 1 && bullet_type < 2) {
				if(reflect == 0) {
					p_bullet[index].x = (plx + BULLET_SHOT_POINT) + point * cos(Rad1);
					p_bullet[index].y = (ply + BULLET_SHOT_POINT) + point * sin(Rad1);
				}
			}
			else {
				p_bullet[index].x = (plx + BULLET_SHOT_POINT) - 100 + point * cos(Rad1);
				p_bullet[index].y = (ply + BULLET_SHOT_POINT)       + point * sin(Rad1);
			}
			p_bullet[index].angle_type = 45;
			break;
		}
		case 3: {
			p_bullet[index].Xspeed = 0;
			p_bullet[index].Yspeed = -speed;
			if(black != 1 && bullet_type < 2) {
				if(reflect == 0) {
					p_bullet[index].y = (ply + BULLET_SHOT_POINT) + -90 + point * sin(270);
					p_bullet[index].x = (plx + BULLET_SHOT_POINT) + -90 + point * cos(270);
				}
			}
			else {
				p_bullet[index].x = (plx + BULLET_SHOT_POINT) - 150 + point * cos(270);
				p_bullet[index].y = (ply + BULLET_SHOT_POINT) -  50 + point * sin(270);
			}
			p_bullet[index].angle_type = 270;
			break;
		}
		case 4: {
			p_bullet[index].Xspeed = 0;
			p_bullet[index].Yspeed = speed;
			if(black != 1 && bullet_type < 2) {
				if(reflect == 0) {
					p_bullet[index].x = (plx + BULLET_SHOT_POINT) + 45 + point * cos(90);
					p_bullet[index].y = (ply + BULLET_SHOT_POINT) + point * sin(90);
				}
			}
			else {
				p_bullet[index].x = (plx + BULLET_SHOT_POINT) + 40 + point * cos(90);
				p_bullet[index].y = (ply + BULLET_SHOT_POINT) + 60 + point * sin(90);
			}
			p_bullet[index].angle_type = 90;
			break;
		}
		}
		break;
	}
	case -1: {
		switch(p_bullet[index].aiming) {
		case 0: {
			p_bullet[index].Xspeed = -speed;
			p_bullet[index].Yspeed = 0;
			if(black != 1 && bullet_type < 2) {
				if(reflect == 0) {
					p_bullet[index].x = (plx + BULLET_SHOT_POINT) - 20 + point * cos(180);
					p_bullet[index].y = (ply + BULLET_SHOT_POINT) + 30 + point * sin(180);
				}
			}
			else {
				p_bullet[index].x = (plx + BULLET_SHOT_POINT)      + point * cos(180);
				p_bullet[index].y = (ply + BULLET_SHOT_POINT) + 100 + point * sin(180);
			}
			p_bullet[index].angle_type = 180;
			break;
		}
		case 1: {
			p_bullet[index].Xspeed = speed * cos(Rad4);
			p_bullet[index].Yspeed = speed * sin(Rad4);
			if(black != 1 && bullet_type < 2) {
				if(reflect == 0) {
					p_bullet[index].x = (plx + BULLET_SHOT_POINT) + 20 + point * cos(Rad4);
					p_bullet[index].y = (ply + BULLET_SHOT_POINT) - 20 + point * sin(Rad4);
				}
			}
			else {
				p_bullet[index].x = (plx + BULLET_SHOT_POINT)  + 30 + point * cos(Rad4);
				p_bullet[index].y = (ply + BULLET_SHOT_POINT)       + point * sin(Rad4);
			}
			p_bullet[index].angle_type = 225;
			break;
		}
		case 2: {
			p_bullet[index].Xspeed = speed * cos(Rad3);
			p_bullet[index].Yspeed = speed * sin(Rad3);
			if(black != 1 && bullet_type < 2) {
				if(reflect == 0) {
					p_bullet[index].x = (plx + BULLET_SHOT_POINT) + point * cos(Rad3);
					p_bullet[index].y = (ply + BULLET_SHOT_POINT) + point * sin(Rad3);
				}
			}
			else {
				p_bullet[index].x = (plx + BULLET_SHOT_POINT)  + 65 + point * cos(Rad3);
				p_bullet[index].y = (ply + BULLET_SHOT_POINT) + 60 + point * sin(Rad3);
			}
			p_bullet[index].angle_type = 135;
			break;
		}
		case 3: {
			p_bullet[index].Xspeed = 0;
			p_bullet[index].Yspeed = -speed;
			if(black != 1 && bullet_type < 2) {
				if(reflect == 0) {
					p_bullet[index].x = (plx + BULLET_SHOT_POINT) - 40 + point * cos(270);
					p_bullet[index].y = (ply + BULLET_SHOT_POINT) - 90 + point * sin(270);
				}
			}
			else {
				p_bullet[index].x = (plx + BULLET_SHOT_POINT) + 20 + point * cos(270);
				p_bullet[index].y = (ply + BULLET_SHOT_POINT) - 50 + point * sin(270);
			}
			p_bullet[index].angle_type = 270;
			break;
		}
		case 4: {
			p_bullet[index].Xspeed = 0;
			p_bullet[index].Yspeed = speed;
			if(black != 1 && bullet_type < 2) {
				if(reflect == 0) {
					p_bullet[index].x = (plx + BULLET_SHOT_POINT) + 45 + point * cos(90);
					p_bullet[index].y = (ply + BULLET_SHOT_POINT) + point * sin(90);
				}
			}
			else {
				p_bullet[index].x = (plx + BULLET_SHOT_POINT) + 100 + point * cos(90);
				p_bullet[index].y = (ply + BULLET_SHOT_POINT) + 60 + point * sin(90);
			}
			p_bullet[index].angle_type = 90;
			break;
		}
		}
		break;
	}
	}
}



void PlayerBullet::ShootProcess(int BulletType, int BWPselect, int plx, int ply, int aiming, int arrow) {
	// 射撃処理
	int speed = 0;

	if(gPad._gTrg[0] & PAD_INPUT_2) {
		// 弾のディレイリセット(切り替え後に即撃てるように)
		switch(BulletType)
		{
		case 0: {
			info_bullet.delaycnt[0] = 0;
			break;
		}
		case 1: {
			info_bullet.delaycnt[1] = REFLECT_COOLTIME;
			break;
		}
		case 2: {
			info_bullet.delaycnt[2] = TRUST_COOLTIME;
			break;
		}
		case 3: {
			info_bullet.delaycnt[2] = NORMAL_COOLTIME_B;
			break;
		}
		}
	}
	if (gPad._gTrg[0] & PAD_INPUT_8) {
		// 弾のディレイリセット(切り替え後に即撃てるように)
		switch (BulletType)
		{
		case 0: {
			info_bullet.delaycnt[0] = 0;
			break;
		}
		case 1: {
			info_bullet.delaycnt[1] = REFLECT_COOLTIME;
			break;
		}
		case 2: {
			if (info_bullet.delaycnt[2] >= TRUST_COOLTIME) {
				info_bullet.stance_type = 1;
			}
			break;
		}
		case 3: {
			if (info_bullet.delaycnt[2] >= NORMAL_COOLTIME_B) {
				info_bullet.stance_type = 2;
				info_bullet.delaycnt[0] = 0;
			}
			break;
		}
		}
	}
	if (gPad._gTrg[0] & PAD_INPUT_6) {
		_power_charge = 0;
	}

	if (CHARGE_CNT <= _power_charge) {
		if (_power_max != 1) {
			if (CheckSoundMem(_image->Se[28]) != 0) {
				_music->StopSe(_image->Se[28]);
			}
			_music->MakeSe(_image->Se[17]);
			_power_max = 1;
		}
	}
	else {
		_power_max = 0;
	}

	// 弾の挙動判別
	switch(BulletType) {
	case 0: {
		if(gPad._gTrg[0] & PAD_INPUT_8) {
			info_bullet.delaycnt[0] = 0;
		}

		// 武器タイプ：通常
		if (gPad._gRel[0] & PAD_INPUT_6) {
			if (CHARGE_CNT <= _power_charge) {
				_music->MakeSe(_image->Se[11]);
				for (int i = 0; i < BULLET_MAX; i++) {
					if (p_bullet[i].usebullet != 1) {
						p_bullet[i].usebullet = 1;
						// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
						// つまり後のエイミングに組み込むかも
						p_bullet[i].state.bullettype = 0;
						speed = NORMAL_SPEED;
						p_bullet[i].state.isWhite = 1;
						p_bullet[i].state.isBlack = 0;
						p_bullet[i].state.isPortal = 1;
						BulletDir(i, aiming, arrow, speed, plx, ply, p_bullet[i].state.bullettype, 0, p_bullet[i].state.isBlack);
						_power_charge = 0;
						_music->MakeVoice(ATTACK_VOICE, RANDAM_THREE);
						_music->SetCoolVoice();
						break;
					}
				}
			}
			else {
				if (CheckSoundMem(_image->Se[28]) == 1) {
					_music->StopSe(_image->Se[28]);
				}
				_power_charge = 0;
			}
		}

		if (gPad._gKey[0] & PAD_INPUT_6) {
			if (CheckSoundMem(_image->Se[28]) == 0 && CHARGE_CNT >= _power_charge && _power_max == 0) {
				_music->MakeSe(_image->Se[28]);
			}
			_power_charge++;
		}
		else if(gPad._gKey[0] & PAD_INPUT_8) {
			info_bullet.delaycnt[0]++;
			info_bullet.delaycnt[3]++;
			if(info_bullet.delaycnt[3] >= NORMAL_COOLTIME_B) {
				if(info_bullet.delaycnt[0] >= NORMAL_COOLTIME) {
					_effect->SetEffect(0, 0, EFFECT_TYPE_NORMAL_SHOT, 0, 0, 0, 0,1, EFFECT_PLAYER);
					_music->MakeSe(_image->Se[11]);
					for(int i = 0; i < BULLET_MAX; i++) {
						if(p_bullet[i].usebullet != 1) {
							p_bullet[i].usebullet = 1;

							// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
							// つまり後のエイミングに組み込むかも
							p_bullet[i].state.bullettype = 0;
							speed = NORMAL_SPEED;
							p_bullet[i].state.isWhite = 1;
							p_bullet[i].state.isBlack = 0;
							p_bullet[i].state.isPortal = 0;
							BulletDir(i, aiming, arrow, speed, plx, ply, p_bullet[i].state.bullettype, 0, p_bullet[i].state.isBlack);
							info_bullet.delaycnt[3] = 0;
							_music->MakeVoice(ATTACK_VOICE, RANDAM_THREE);
							_music->SetCoolVoice();
							break;
						}
					}
				}
			}
		}
		break;
	}
	case 1: {
		// 武器タイプ：反射

		if (gPad._gRel[0] & PAD_INPUT_6) {
			if (CHARGE_CNT <= _power_charge) {
				_music->MakeSe(_image->Se[12]);
				for (int i = 0; i < BULLET_MAX; i++) {
					if (p_bullet[i].usebullet != 1) {
						p_bullet[i].usebullet = 1;
						// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
						// つまり後のエイミングに組み込むかも
						p_bullet[i].state.bullettype = 1;
						speed = REFLECT_SPEED;

						p_bullet[i].state.isWhite = 1;
						p_bullet[i].state.isBlack = 0;
						p_bullet[i].state.isPortal = 1;
						BulletDir(i, aiming, arrow, speed, plx, ply, p_bullet[i].state.bullettype, 0, p_bullet[i].state.isBlack);
						info_bullet.delaycnt[1] = 0;
						_power_charge = 0;
						_music->MakeVoice(ATTACK_VOICE, RANDAM_THREE);
						_music->SetCoolVoice();
						break;
					}
				}
			}
			else {
				if (CheckSoundMem(_image->Se[28]) == 1) {
					_music->StopSe(_image->Se[28]);
				}
				_power_charge = 0;
			}
		}

		if (gPad._gKey[0] & PAD_INPUT_6) {
			if (CheckSoundMem(_image->Se[28]) == 0 && CHARGE_CNT >= _power_charge && _power_max == 0) {
				_music->MakeSe(_image->Se[28]);
			}
			_power_charge++;
		}
		else {
			if (gPad._gTrg[0] & PAD_INPUT_8 && info_bullet.remainbullet[REFLECT_BULLET] > 0) {
				_trg[1] = false;
			}
			if (_trg[1] == false) {
				info_bullet.delaycnt[1]++;
			}
			if (_trg[1] == false && info_bullet.delaycnt[1] >= NORMAL_COOLTIME) {
				_music->MakeSe(_image->Se[12]);
				for (int i = 0; i < BULLET_MAX; i++) {
					if (p_bullet[i].usebullet != 1) {
						p_bullet[i].usebullet = 1;
						// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
						// つまり後のエイミングに組み込むかも
						p_bullet[i].state.bullettype = 1;
						speed = REFLECT_SPEED;

						p_bullet[i].state.isWhite = 1;
						p_bullet[i].state.isBlack = 0;
						p_bullet[i].state.isPortal = 0;
						BulletDir(i, aiming, arrow, speed, plx, ply, p_bullet[i].state.bullettype, 0, p_bullet[i].state.isBlack);
						info_bullet.remainbullet[REFLECT_BULLET]--;
						info_bullet.delaycnt[1] = 0;
						_trg[1] = true;
						_music->MakeVoice(ATTACK_VOICE, RANDAM_THREE);
						_music->SetCoolVoice();
						break;
					}
				}
			}
		}
		break;
	}
	case 2: {
		// 武器タイプ：貫通
		if (gPad._gRel[0] & PAD_INPUT_6) {
			if (CHARGE_CNT <= _power_charge) {
				if (info_bullet.delaycnt[0] >= 15) {
					for (int i = 0; i < BULLET_MAX; i++) {
						if (p_bullet[i].usebullet != 1) {
							p_bullet[i].usebullet = 1;
							// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
							// つまり後のエイミングに組み込むかも
							p_bullet[i].state.bullettype = 2;
							speed = TRUST_SPEED;

							p_bullet[i].state.isWhite = 1;
							p_bullet[i].state.isBlack = 0;
							p_bullet[i].state.isPortal = 1;
							BulletDir(i, aiming, arrow, speed, plx, ply, p_bullet[i].state.bullettype, 0, p_bullet[i].state.isBlack);
							info_bullet.delaycnt[0] = 0;
							info_bullet.delaycnt[2] = 0;
							info_bullet.delaycnt[3] = 0;

							info_bullet.stance_type = 0;

							break;
						}
					}
				}
			}
			else {
				if (CheckSoundMem(_image->Se[28]) == 1) {
					_music->StopSe(_image->Se[28]);
				}
				_power_charge = 0;
				info_bullet.delaycnt[0] = 0;
			}
		}

		if (gPad._gTrg[0] & PAD_INPUT_6) {
			info_bullet.delaycnt[0] = 0;
		}
		if (gPad._gKey[0] & PAD_INPUT_6) {
			if (CheckSoundMem(_image->Se[28]) == 0 && CHARGE_CNT >= _power_charge && _power_max == 0) {
				_music->MakeSe(_image->Se[28]);
			}
			_power_charge++;
			info_bullet.delaycnt[0]++;
		}
		else {
			if (info_bullet.stance_type != 1) {
				if (gPad._gRel[0] & PAD_INPUT_8) {
					info_bullet.delaycnt[0] = 0;
				}
			}
			if (info_bullet.delaycnt[2] >= 0 && info_bullet.remainbullet[TRUST_BULLET] > 0) {
				info_bullet.delaycnt[2]++;
			}
			if (info_bullet.stance_type == 1) {
				if (info_bullet.delaycnt[2] >= TRUST_COOLTIME) {
					info_bullet.delaycnt[0]++;
					if (info_bullet.delaycnt[0] >= 15) {
						for (int i = 0; i < BULLET_MAX; i++) {
							if (p_bullet[i].usebullet != 1) {
								p_bullet[i].usebullet = 1;
								// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
								// つまり後のエイミングに組み込むかも
								p_bullet[i].state.bullettype = 2;
								speed = TRUST_SPEED;

								p_bullet[i].state.isWhite = 1;
								p_bullet[i].state.isBlack = 0;
								p_bullet[i].state.isPortal = 0;
								BulletDir(i, aiming, arrow, speed, plx, ply, p_bullet[i].state.bullettype, 0, p_bullet[i].state.isBlack);
								info_bullet.remainbullet[TRUST_BULLET]--;
								info_bullet.delaycnt[0] = 0;
								info_bullet.delaycnt[2] = 0;
								info_bullet.delaycnt[3] = 0;
								if (BWPselect != 1) {
									if (cutin_swich == 0 && cutin_use[0] != 1) {
										cutin = 1;
										cutin_use[0] = 1;
									}
									else {
										_music->MakeSe(_image->Se[4]);
									}
								}

								info_bullet.stance_type = 0;
								break;
							}
						}
					}
				}
			}
		}
		break;

	}
	case 3: {
		// 武器タイプ：黒
		if (gPad._gRel[0] & PAD_INPUT_6) {
			if (CHARGE_CNT <= _power_charge) {
				_music->MakeSe(_image->Se[11]);
				for (int i = 0; i < BULLET_MAX; i++) {
					if (p_bullet[i].usebullet != 1) {
						p_bullet[i].usebullet = 1;
						// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
						// つまり後のエイミングに組み込むかも
						p_bullet[i].state.bullettype = 0;
						speed = NORMAL_SPEED;

						p_bullet[i].state.isWhite = 0;
						p_bullet[i].state.isBlack = 1;
						p_bullet[i].state.isPortal = 1;
						BulletDir(i, aiming, arrow, speed, plx, ply, p_bullet[i].state.bullettype, 0, p_bullet[i].state.isBlack);
						info_bullet.delaycnt[0] = 0;
						info_bullet.stance_type = 0;
						break;
					}
				}
			}
			else {
				if (CheckSoundMem(_image->Se[28]) == 1) {
					_music->StopSe(_image->Se[28]);
				}
				_power_charge = 0;
				info_bullet.delaycnt[0] = 0;
			}
		}
		
		
		if (gPad._gTrg[0] & PAD_INPUT_6) {
			info_bullet.delaycnt[0] = 0;
		}
		if (gPad._gKey[0] & PAD_INPUT_6) {
			if (CheckSoundMem(_image->Se[28]) == 0 && CHARGE_CNT >= _power_charge && _power_max == 0) {
				_music->MakeSe(_image->Se[28]);
			}
			_power_charge++;
			info_bullet.delaycnt[0]++;
		}
		else {
			if (info_bullet.stance_type != 2) {
				if (gPad._gRel[0] & PAD_INPUT_8) {
					info_bullet.delaycnt[0] = 0;
				}
			}
			if (info_bullet.delaycnt[2] >= 0 && info_bullet.remainbullet[BLACK_BULLET] > 0) {
				info_bullet.delaycnt[2]++;
			}
		}
		if(info_bullet.stance_type == 2) {
			if (info_bullet.delaycnt[2] >= NORMAL_COOLTIME_B) {
				info_bullet.delaycnt[0]++;
				if (info_bullet.delaycnt[0] >= 15) {
					for (int i = 0; i < BULLET_MAX; i++) {
						if (p_bullet[i].usebullet != 1) {
							p_bullet[i].usebullet = 1;
							// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
							// つまり後のエイミングに組み込むかも
							p_bullet[i].state.bullettype = 0;
							speed = NORMAL_SPEED;

							p_bullet[i].state.isWhite = 0;
							p_bullet[i].state.isBlack = 1;
							p_bullet[i].state.isPortal = 0;
							BulletDir(i, aiming, arrow, speed, plx, ply, p_bullet[i].state.bullettype, 0, p_bullet[i].state.isBlack);
							info_bullet.remainbullet[BLACK_BULLET]--;
							info_bullet.delaycnt[2] = 0;
							info_bullet.delaycnt[0] = 0;
							if (cutin_swich == 0 && cutin_use[1] != 1) {
								cutin = 2;
								cutin_use[1] = 1;
							}
							else {
								_music->MakeSe(_image->Se[4]);
							}
							info_bullet.stance_type = 0;
							break;
						}
					}
				}
			}
		}
		break;
	}
	}

	// 共通処理（弾丸前半）
	for(int i = 0; i < BULLET_MAX; i++) {
		if(p_bullet[i].usebullet == 0) { p_bullet[i].state.bullettype = 0; }
		else if(p_bullet[i].usebullet == 1) {
			p_bullet[i].x += p_bullet[i].Xspeed;
			p_bullet[i].y += p_bullet[i].Yspeed;
			if(p_bullet[i].x <= 0 || p_bullet[i].y <= 0) {
				BulletInit(i);
			}
			if((count[i]++ % 2) == 0) {
				if(p_bullet[i].state.bullettype == 2) {
					_effect->SetEffect(p_bullet[i].x + P_BULLET_W / 2, p_bullet[i].y + P_BULLET_H / 2, EFFECT_TYPE_RIFLECT_BOOST, p_bullet[i].angle_type, p_bullet[i].aiming, p_bullet[i].arrow, 0,1, EFFECT_PLAYER);
				}
				if(p_bullet[i].state.isBlack == 1) {
					_effect->SetEffect(p_bullet[i].x + P_BULLET_W / 2, p_bullet[i].y + P_BULLET_H / 2, EFFECT_TYPE_BLACK_BOOST, p_bullet[i].angle_type, p_bullet[i].aiming, p_bullet[i].arrow, 0,1, EFFECT_PLAYER);
				}
			}
			EffectProcess(i);
		}
		
		// 座標移動後に現在の当たり判定を取得
		p_bullet[i].hx = p_bullet[i].x ;
		p_bullet[i].hy = p_bullet[i].y ;
		p_bullet[i].hw = p_bullet[i].hx + P_BULLET_W;
		p_bullet[i].hh = p_bullet[i].hy + P_BULLET_H;

		//　円判定の位置補正
		switch(p_bullet[i].arrow) {
		case 1: {
			switch(p_bullet[i].aiming) {
			case 0: {
				b_hitcircle[i].x = p_bullet[i].x + 20.0f;
				b_hitcircle[i].y = p_bullet[i].y + 7.0f;
				break;
			}
			case 1: {
				b_hitcircle[i].x = p_bullet[i].x + 25.0f * cos(Rad1);
				b_hitcircle[i].y = p_bullet[i].y + 5.0f  * sin(Rad1);
				break;
			}
			case 2: {
				b_hitcircle[i].x = p_bullet[i].x + 25.0f * cos(Rad6);
				b_hitcircle[i].y = p_bullet[i].y + 10.0f;
				break;
			}
			case 3: {
				b_hitcircle[i].x = p_bullet[i].x + 15.0f;
				b_hitcircle[i].y = p_bullet[i].y + 5.0f * sin(PI / 2);
				break;
			}
			case 4: {
				b_hitcircle[i].x = p_bullet[i].x + 15.0f;
				b_hitcircle[i].y = p_bullet[i].y + -7.0f * sin(3*PI/2);
				break;
			}
			}
			break;
		}
		case -1: {
			switch(p_bullet[i].aiming) {
			case 0: {
				b_hitcircle[i].x = p_bullet[i].x + 13.0f;
				b_hitcircle[i].y = p_bullet[i].y + 7.0f;
				break;
			}
			case 1: {
				b_hitcircle[i].x = p_bullet[i].x + -12.0f * cos(Rad3);
				b_hitcircle[i].y = p_bullet[i].y + 0.0f * sin(Rad3);
				break;
			}
			case 2: {
				b_hitcircle[i].x = p_bullet[i].x + -15.0f * cos(Rad4);
				b_hitcircle[i].y = p_bullet[i].y + 10.0f;
				break;
			}
			case 3: {
				b_hitcircle[i].x = p_bullet[i].x + 15.0f;
				b_hitcircle[i].y = p_bullet[i].y + 5.0f * sin(PI / 2);
				break;
			}
			case 4: {
				b_hitcircle[i].x = p_bullet[i].x + 15.0f;
				b_hitcircle[i].y = p_bullet[i].y + -7.0f * sin(3 * PI / 2);
				break;
			}
			}
			break;
		}
		}
		b_hitcircle[i].r = 10.0f;

		if(plx + 50 + SCREEN_W*2 < p_bullet[i].hx || plx - 50 - SCREEN_W * 2 > p_bullet[i].hx || ply + 50 + SCREEN_H * 2 < p_bullet[i].hy || ply - 50 - SCREEN_H * 2 > p_bullet[i].hy) {
			BulletInit(i);
		}
	}
}

void PlayerBullet::EffectProcess(int i) {
	if(p_bullet[i].state.bullettype != 1) {
		_effect->SetEffect(p_bullet[i].x + P_BULLET_W / 2, p_bullet[i].y + P_BULLET_H / 2, p_bullet[i].state.bullettype, p_bullet[i].angle_type, p_bullet[i].aiming, p_bullet[i].arrow, p_bullet[i].state.isBlack,1, EFFECT_PLAYER);
	}

	if(p_bullet[i].state.bullettype == 1) {
		if(_effect->GetCoolTime() <= 0) {
			_effect->SetEffect(p_bullet[i].x + P_BULLET_W / 2, p_bullet[i].y + P_BULLET_H / 2, p_bullet[i].state.bullettype, p_bullet[i].angle_type, p_bullet[i].aiming, p_bullet[i].arrow, 0, 1, EFFECT_PLAYER);
		}
	}
}

int PlayerBullet::MapHitProcess(int index, int maphit, int point, int aftermovemaphit) {
	int portal = 0;
	if(p_bullet[index].usebullet != 0) {
		if(maphit != 0) {
			switch(p_bullet[index].state.isPortal) {
			case 0: {
				_music->MakeSe(_image->Se[14]);
				switch(p_bullet[index].state.bullettype) {
				case 0: {
					_effect->SetEffect(p_bullet[index].x + P_BULLET_W / 2, p_bullet[index].y + P_BULLET_H / 2, EFFECT_TYPE_NORMAL_WALL, 0, 0, 0,0, 1, EFFECT_PLAYER);
					BulletInit(index);
					break;
				}
				case 1: {
					if(p_bullet[index].special == 0) {
						_effect->SetEffect(p_bullet[index].x + P_BULLET_W / 2, p_bullet[index].y + P_BULLET_H / 2, EFFECT_TYPE_RIFFLECT_WALL, 0, 0, 0,0, 1, EFFECT_PLAYER);
						_effect->EffectCoolTime(11);
						p_bullet[index].special++;
						switch(p_bullet[index].arrow) {
						case 1: {
							switch(p_bullet[index].aiming) {
							case 0: {
								BulletDir(index, 0, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								break;
							}
							case 1: {
								if(point == 0) {
									BulletDir(index, 1, -1, REFLECT_SPEED,p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								if(point == 3) {
									BulletDir(index, 2, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}

								break;
							}
							case 2: {
								if(point == 0) {
									BulletDir(index, 2, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								if(point == 1) {
									BulletDir(index, 1, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								break;
							}
							case 3: {
								BulletDir(index, 4, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								break;
							}
							case 4: {
								BulletDir(index, 3, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								break;
							}
							}
							break;
						}
						case -1: {
							switch(p_bullet[index].aiming) {
							case 0: {
								BulletDir(index, 0, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								break;
							}
							case 1: {
								if(point == 2) {
									BulletDir(index, 1, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								if(point == 3) {
									BulletDir(index, 2, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								break;
							}
							case 2: {
								if(point == 2) {
									BulletDir(index, 2, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								if(point == 1) {
									BulletDir(index, 1, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								break;
							}
							case 3: {
								BulletDir(index, 4, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								break;
							}
							case 4: {
								BulletDir(index, 3, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								break;
							}
							}
							break;
						}
						}

					}
					else if(p_bullet[index].special == 1) {
						_effect->SetEffect(p_bullet[index].x + P_BULLET_W / 2, p_bullet[index].y + P_BULLET_H / 2, EFFECT_TYPE_RIFFLECT_WALL, 0, 0, 0, 0, 1, EFFECT_PLAYER);
						BulletInit(index);
					}
					break;
				}
				case 2: {
					if(p_bullet[index].special == 0) {
						_effect->SetEffect(p_bullet[index].x + P_BULLET_W / 2, p_bullet[index].y + P_BULLET_H / 2, EFFECT_TYPE_RIFFLECT_WALL, 0, 0, 0, 0, 1, EFFECT_PLAYER);
						p_bullet[index].x += p_bullet[index].Xspeed * 1.5;
						p_bullet[index].y += p_bullet[index].Yspeed * 1.5;
						if(aftermovemaphit != 0) {
							BulletInit(index);
						}
						else {
							p_bullet[index].special++;
						}
					}
					else if(p_bullet[index].special == 1) {
						_effect->SetEffect(p_bullet[index].x + P_BULLET_W / 2, p_bullet[index].y + P_BULLET_H / 2, EFFECT_TYPE_RIFFLECT_WALL, 0, 0, 0, 0, 1, EFFECT_PLAYER);
						BulletInit(index);
					}
					break;
				}
				}
				break;
			}
			case 1: {
				switch(p_bullet[index].state.bullettype) {
				case 0: {
					_music->MakeSe(_image->Se[1]);
					if(p_bullet[index].state.isWhite == 1) {
						portal = WPORTAL_BULLET;
						BulletInit(index);
					}
					if(p_bullet[index].state.isBlack == 1) {
						portal = BPORTAL_BULLET;
						BulletInit(index);
					}
					break;
				}
				case 1: {
					if(p_bullet[index].special == 0) {
						_music->MakeSe(_image->Se[14]);
						p_bullet[index].special++;
						switch(p_bullet[index].arrow) {
						case 1: {
							switch(p_bullet[index].aiming) {
							case 0: {
								BulletDir(index, 0, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								break;
							}
							case 1: {
								if(point == 0) {
									BulletDir(index, 1, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								if(point == 3) {
									BulletDir(index, 2, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype,1 , p_bullet[index].state.isBlack);
								}

								break;
							}
							case 2: {
								if(point == 0) {
									BulletDir(index, 2, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								if(point == 1) {
									BulletDir(index, 1, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								break;
							}
							case 3: {
								BulletDir(index, 4, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								break;
							}
							case 4: {
								BulletDir(index, 3, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								break;
							}
							}
							break;
						}
						case -1: {
							switch(p_bullet[index].aiming) {
							case 0: {
								BulletDir(index, 0, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								break;
							}
							case 1: {
								if(point == 2) {
									BulletDir(index, 1, 1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								if(point == 3) {
									BulletDir(index, 2, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								break;
							}
							case 2: {
								if(point == 2) {
									BulletDir(index, 2, 1, REFLECT_SPEED,p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								if(point == 1) {
									BulletDir(index, 1, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								}
								break;
							}
							case 3: {
								BulletDir(index, 4, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								break;
							}
							case 4: {
								BulletDir(index, 3, -1, REFLECT_SPEED, p_bullet[index].x, p_bullet[index].y, p_bullet[index].state.bullettype, 1, p_bullet[index].state.isBlack);
								break;
							}
							}
							break;
						}
						}

					}
					else if(p_bullet[index].special == 1) {
						_music->MakeSe(_image->Se[1]);
						portal = WPORTAL_BULLET;
						BulletInit(index);
					}
					break;
				}
				case 2: {
					if(p_bullet[index].special == 0) {
						_music->MakeSe(_image->Se[14]);
						p_bullet[index].x += p_bullet[index].Xspeed * 1.5;
						p_bullet[index].y += p_bullet[index].Yspeed * 1.5;
						if(aftermovemaphit != 0) {
							BulletInit(index);
						}
						else {
							p_bullet[index].special++;
						}
					}
					else if(p_bullet[index].special == 1) {
						_music->MakeSe(_image->Se[1]);
						portal = WPORTAL_BULLET;
						BulletInit(index);
					}
					break;
				}
				}
				break;
			}
			}
		}
	}
	return portal;
}

void PlayerBullet::Draw(MATRIX mview,int plx, int ply) {
	for(int i = 0; i < BULLET_MAX; i++) {
		VECTOR BULLET = VGet(p_bullet[i].x + P_BULLET_W/2, p_bullet[i].y + P_BULLET_H/2, 0);
		if(p_bullet[i].usebullet == 1) {
			if(p_bullet[i].state.bullettype == 0) {
				_effect->NormalDraw(mview, BULLET, p_bullet[i].angle_type);
			}
		}
		if(p_bullet[i].state.isBlack == 1) {
			if(p_bullet[i].arrow == -1) {
				switch(p_bullet[i].aiming) {
				case 0: {
					MyDrawTurnModiGraph(mview, BULLET, 1.f, 0.f, info_bullet.w, info_bullet.h, _image->GetCgBullet(BLACK_BULLET));
					break;
				}
				case 1: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad4, info_bullet.w, info_bullet.h, _image->GetCgBullet(BLACK_BULLET));
					break;
				}
				case 2: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad3, info_bullet.w, info_bullet.h, _image->GetCgBullet(BLACK_BULLET));
					break;
				}
				case 3: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad5, info_bullet.w, info_bullet.h, _image->GetCgBullet(BLACK_BULLET));
					break;
				}
				case 4: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad2, info_bullet.w, info_bullet.h, _image->GetCgBullet(BLACK_BULLET));
					break;
				}
				}
			}
			else {
				switch(p_bullet[i].aiming) {
				case 0: {
					MyDrawModiGraph(mview, BULLET, 1.f, 0.f, info_bullet.w, info_bullet.h, _image->GetCgBullet(BLACK_BULLET));
					break;
				}
				case 1: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad6, info_bullet.w, info_bullet.h, _image->GetCgBullet(BLACK_BULLET));
					break;
				}
				case 2: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad1, info_bullet.w, info_bullet.h, _image->GetCgBullet(BLACK_BULLET));
					break;
				}
				case 3: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad5, info_bullet.w, info_bullet.h, _image->GetCgBullet(BLACK_BULLET));
					break;
				}
				case 4: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad2, info_bullet.w, info_bullet.h, _image->GetCgBullet(BLACK_BULLET));
					break;
				}
				}
			}
		}
		if(p_bullet[i].state.isWhite == 1) {
			if(p_bullet[i].arrow == -1) {
				switch(p_bullet[i].aiming) {
				case 0: {
					MyDrawTurnModiGraph(mview, BULLET, 1.f, 0.f, info_bullet.w, info_bullet.h, _image->GetCgBullet(WHITE_BULLET));
					break;
				}
				case 1: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad4, info_bullet.w, info_bullet.h, _image->GetCgBullet(WHITE_BULLET));
					break;
				}
				case 2: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad3, info_bullet.w, info_bullet.h, _image->GetCgBullet(WHITE_BULLET));
					break;
				}
				case 3: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad5, info_bullet.w, info_bullet.h, _image->GetCgBullet(WHITE_BULLET));
					break;
				}
				case 4: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad2, info_bullet.w, info_bullet.h, _image->GetCgBullet(WHITE_BULLET));
					break;
				}
				}
			}
			else {
				switch(p_bullet[i].aiming) {
				case 0: {
					MyDrawModiGraph(mview, BULLET, 1.f, 0.f, info_bullet.w, info_bullet.h, _image->GetCgBullet(WHITE_BULLET));
					break;
				}
				case 1: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad6, info_bullet.w, info_bullet.h, _image->GetCgBullet(WHITE_BULLET));
					break;
				}
				case 2: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad1, info_bullet.w, info_bullet.h, _image->GetCgBullet(WHITE_BULLET));
					break;
				}
				case 3: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad5, info_bullet.w, info_bullet.h, _image->GetCgBullet(WHITE_BULLET));
					break;
				}
				case 4: {
					MyDrawModiGraph(mview, BULLET, 1.f, Rad2, info_bullet.w, info_bullet.h, _image->GetCgBullet(WHITE_BULLET));
					break;
				}
				}
			}
		}		
	}

}
