/*****************************************************************//**
 * \file   EnemyBullet.cpp
 * \brief  エネミーの弾情報
 *
 * \author 奈良充樹、齋藤 瑚羽
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
// 弾の方向進行指定
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
// エネミーの弾発射
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

						// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
						// つまり後のエイミングに組み込むかも
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

								// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
								// つまり後のエイミングに組み込むかも
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

								// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
								// つまり後のエイミングに組み込むかも
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

								// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
								// つまり後のエイミングに組み込むかも
								e_bullet[index][i].x = eneX + 70;
								e_bullet[index][i].y = eneY + 70;
								e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
								e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
								e_bullet[index][i].bullettype = E_BULLET_2;
								speed = B_SPEED1;

								e_bullet[index][i].direction = turret_dir + DegToRad(180);//atan2は左が0で右が180 下が負で上が正
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

								// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
								// つまり後のエイミングに組み込むかも
								e_bullet[index][i].x = eneX + 70;
								e_bullet[index][i].y = eneY + 70;
								e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
								e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
								e_bullet[index][i].bullettype = E_BULLET_4;
								speed = B_SPEED1;

								e_bullet[index][i].direction = turret_dir + DegToRad(180);//atan2は左が0で右が180 下が負で上が正
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

								// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
								// つまり後のエイミングに組み込むかも
								e_bullet[index][i].x = eneX + 70;
								e_bullet[index][i].y = eneY + 70;
								e_bullet[index][i].cx = e_bullet[index][i].x + info_bullet.w / 2;
								e_bullet[index][i].cy = e_bullet[index][i].y + info_bullet.h / 2;
								e_bullet[index][i].bullettype = E_BULLET_6;
								speed = B_SPEED1;

								e_bullet[index][i].direction = turret_dir + DegToRad(180);//atan2は左が0で右が180 下が負で上が正
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
// ボスの弾発射
	if (A_cont != 0) {
		// 通常弾
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

								// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
								// つまり後のエイミングに組み込むかも
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
								e_bullet[index][i].direction = atan2(chara_y + 150 - e_bullet[index][i].y, chara_x + 150 - e_bullet[index][i].x);//atan2は左が0で右が180 下が負で上が正
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
		// 誘導弾
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

							// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
							// つまり後のエイミングに組み込むかも
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
							e_bullet[index][i].direction = atan2(chara_y + 150 - e_bullet[index][i].y, chara_x + 150 - e_bullet[index][i].x);//atan2は左が0で右が180 下が負で上が正
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
		// 高速弾
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

							// 座標はエイミングによって位置合わせが必要(テスト段階はプレイヤーの半分)
							// つまり後のエイミングに組み込むかも
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
							e_bullet[index][i].direction = atan2(chara_y + 150 - e_bullet[index][i].y, chara_x + 150 - e_bullet[index][i].x);//atan2は左が0で右が180 下が負で上が正
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
// 誘導弾のカーブのプロセス
	int max_direction = 15;   //曲がる角度の最大値です
	int curve_count = 100;    //曲がる回数です
	int cool_time = 10;       //曲がるまでのクールタイムです（フレーム単位）

	//球の角度を変える処理↓
	if (e_bullet[index][bullet].isuse == true) {
		if (e_bullet[index][bullet].bullettype == E_BULLET_8) {
			_boss_parameter[index+50]--;//曲がるクールタイムを減らす
			if (_boss_parameter[index+50] <= 0) {//クールタイムがなくなったら角度を変更する
				_boss_parameter[index + 70]++;	// 曲がる回数をカウントする
				if (_boss_parameter[index + 70] < curve_count) {		// 曲がる回数がまだ残っていたら動く　個々の数字を変えると曲がる回数を変えれる　曲がる角度を大きくするならここを変えないとすごい追尾してくる
					float bullet_direction = atan2(chara_y + chara_h / 2 - e_bullet[index][bullet].y, chara_x + chara_w / 2 - e_bullet[index][bullet].x);//角度を出す
					float newrad = DegToRad(bullet_direction);//PIを使うので計算しやすいようにradianに変換
					float rad = DegToRad(e_bullet[index][bullet].direction);
					float vRad = DegToRad(DegToRad(max_direction));	//これもradianに変換 数字を変えたら曲がる角度の最大値を変えられる　おすすめはカクカク動かない30度以下から遠回りしすぎない１５度のあいだぐらい
					
					float pi = DegToRad(PI);

					if (fabs(newrad - rad) < vRad) {//atan2が180～-180なので絶対値にすると計算しやすい
						e_bullet[index][bullet].direction = RadToDeg(newrad);		// 角度をdegreeに変換する
					}
					else {
						// 今の向きをvRadだけ新しい向きに近づける
						if (newrad < rad - pi) { rad -= pi * 2; }      
						else if (newrad > rad + pi) { rad += pi * 2; }
						if (newrad < rad) {
							rad -= vRad;
						}
						else {
							rad += vRad;
						}
						e_bullet[index][bullet].direction = RadToDeg(rad);		// 角度をdegreeに変換する

					}
				}
				else if (_boss_parameter[index + 70] >= curve_count) {
					_boss_parameter[index + 70] = 0;
				}
				_boss_parameter[index + 50] = cool_time;	// 角度を変えるためのクールタイム
			}
		}
	}

}

void EnemyBullet::CommonProcess(int index, float chara_x, float chara_y, float chara_w, float chara_h,float dir) {
	// 共通処理
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
			//　円判定の位置補正
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
				//エネミー２で使わせていただきます。　大変申し訳ございません。
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
	//ボス
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


	
//エネミー１３５の玉
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
	// マップに当たった時の処理
	if (e_bullet[index][bullet].isuse != 0) {
		_effect->SetEffect(b_hitcircle[index][bullet].x, b_hitcircle[index][bullet].y, EFFECT_TYPE_NORMAL_WALL, e_bullet[index][bullet].direction, 0, 0, 0, 1, EFFECT_ENEMY);
	}
	BulletInit(index, bullet);
}

void EnemyBullet::DrawTurret(MATRIX mview) {
	// 弾の描画
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
// 弾の描画
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