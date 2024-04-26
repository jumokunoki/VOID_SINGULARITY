/*****************************************************************//**
 * \file   SceneTestCollision.cpp
 * \brief  キャラの当たり判定情報
 *
 * \author 奈良充樹
 * \date   August 2023
 *********************************************************************/

#include "SceneTest.h"
#include "DxLib.h"
#include "gamemain.h"
#include "mymath.h"
#include "mydraw.h"

MYRECT_PLUS SceneTest::GetHitRect(int type, int index, int mx, int my) {
	MYRECT_PLUS rc = { 0, 0, 0, 0, 0, 0, 0, 0 };

	if(type != CHARA_TYPE_NONE) {
		switch(type) {
		case CHARA_TYPE_NONE: {
			rc = _none;
			break;
		}
		case CHARA_TYPE_PLAYER: {
			rc.type = type;
			rc.x = _player.GetPosX() + 135;
			rc.y = _player.GetPosY() + 75;
			rc.w = PLAYER_W;
			rc.h = PLAYER_H;

			rc.mx = mx;
			rc.my = my;
			rc.index = 0;

			break;
		}
		case CHARA_TYPE_ENEMY1:
		case CHARA_TYPE_ENEMY2:
		case CHARA_TYPE_ENEMY3:
		case CHARA_TYPE_ENEMY4:
		case CHARA_TYPE_ENEMY5:
		case CHARA_TYPE_ENEMY6:
		case CHARA_TYPE_ENEMY7:
		case CHARA_TYPE_ENEMY8:
		case CHARA_TYPE_ENEMY9: {
			rc = _enemy.GetRect_P(index);

			break;
		}
		case BOSS_HIT1: {

			rc = _enemy.GetRect_BOSSF(index);

			break;
		}
		case BOSS_HIT2: {

			rc = _enemy.GetRect_BOSSS(index);

			break;
		}
		case BOSS_HIT3: {

			rc = _enemy.GetRect_BOSST(index);

			break;
		}
		case BULLET_TYPE_PLAYER: {
			rc.type = type;
			rc.x = _plBullet.GetPosX(index);
			rc.y = _plBullet.GetPosY(index);
			rc.w = P_BULLET_W;
			rc.h = P_BULLET_H;

			rc.mx = mx;
			rc.my = my;
			rc.index = index;

			break;
		}
		case ITEM_TYPE_AMMO: {
			rc.type = type;
			rc.x = _gimmick.GetPosGimX(index);
			rc.y = _gimmick.GetPosGimY(index);
			rc.w = GIM_W;
			rc.h = GIM_H;

			rc.mx = 0;
			rc.my = 0;
			rc.index = index;

			break;
		}
		case ITEM_TYPE_TRE: {
			rc.type = type;
			rc.x = _gimmick.GetPosGimX(index);
			rc.y = _gimmick.GetPosGimY(index);
			rc.w = GIM_W;
			rc.h = GIM_H;

			rc.mx = 0;
			rc.my = 0;
			rc.index = index;

			break;
		}
		case ITEM_TYPE_HEAL: {
			rc.type = type;
			rc.x = _gimmick.GetPosGimX(index);
			rc.y = _gimmick.GetPosGimY(index);
			rc.w = GIM_W;
			rc.h = GIM_H;

			rc.mx = 0;
			rc.my = 0;
			rc.index = index;
			break;
		}
		case ITEM_TYPE_A_MATTER: {
			rc.type = type;
			rc.x = _gimmick.GetPosGimX(index);
			rc.y = _gimmick.GetPosGimY(index);
			rc.w = GIM_W;
			rc.h = GIM_H;

			rc.mx = 0;
			rc.my = 0;
			rc.index = index;
			break;
		}
		case ITEM_TYPE_LEVER: {
			rc.type = type;
			rc.x = _gimmick.GetPosGimX(index);
			rc.y = _gimmick.GetPosGimY(index);
			rc.w = GIM_W;
			rc.h = GIM_H;

			rc.mx = 0;
			rc.my = 0;
			rc.index = index;
			break;
		}
		case OBJ_TYPE_DOOR: {
			rc.type = type;
			rc.x = _gimmick.GetPosGimX(index) + 20;
			rc.y = _gimmick.GetPosGimY(index) + 40;
			rc.w = DOOR_W ;
			rc.h = DOOR_H - 80;

			rc.mx = 0;
			rc.my = 0;
			rc.index = index;
			break;
		}
		case Black_Hole: {
			rc.type = type;
			rc.x = _portal.GetPosBX();
			rc.y = _portal.GetPosBY();
			rc.w = PORT_W;
			rc.h = PORT_H;

			rc.mx = 0;
			rc.my = 0;
			rc.index = 0;

			break;
		}
		case White_Hole: {
			rc.type = type;
			rc.x = _portal.GetPosWX();
			rc.y = _portal.GetPosWY();
			rc.w = PORT_W;
			rc.h = PORT_H;

			rc.mx = 0;
			rc.my = 0;
			rc.index = 0;

			break;
		}
		case Fix_Black_Hole: {
			rc = _portal.GetRectFixB();
			break;
		}
		case Fix_White_Hole: {
			rc = _portal.GetRectFixW();
			break;
		}

		// 索敵範囲
		case SEARCH_AREA1: {
			rc = _enemy.GetRectSearch(index);
			break;
		}
		case SEARCH_AREA2: {
			rc = _enemy.GetRectSearch(index);
			break;
		}
		case SEARCH_AREA3: {
			rc = _enemy.GetRectSearchBoss();
			break;
		}
		}
	}
	return rc;
}


int SceneTest::CheckHitMap(int type, int index, int mx, int my) {
	int hit = 0;

	// マップチップとの当たり判定
	MapData::HITSLIDE hitSlide;
	MYRECT_PLUS rc = GetHitRect(type,index, mx, my);
	hitSlide = _mapData.IsHitBox(rc.x, rc.y, rc.w, rc.h, rc.mx, rc.my);
	if(hitSlide.hit != 0) {
		switch(type) {
		case CHARA_TYPE_PLAYER: {
			// 当たったので、位置を動かす
			_player.AddPosX(hitSlide.slide_x);
			_player.AddPosY(hitSlide.slide_y);
			break;
		}
		//case CHARA_TYPE_ENEMY1: {
		//	// 当たったので、位置を動かす
		//	_enemy.AddPosX(hitSlide.slide_x, index);
		//	_enemy.AddPosY(hitSlide.slide_y, index);
		//	break;
		//}
		case Black_Hole: {
			// 当たったので、位置を動かす
			_portal.AddPosBX(hitSlide.slide_x);
			_portal.AddPosBY(hitSlide.slide_y);
			break;
		}
		case White_Hole: {
			// 当たったので、位置を動かす
			_portal.AddPosWX(hitSlide.slide_x);
			_portal.AddPosWY(hitSlide.slide_y);
			break;
		}
		}
		hit = 1;
	}

	return hit;
}

// キャラ同士のの当たり判定（前者記述が反動を受ける・・・後者も？　ブラックホールの移動も兼任）
HITSLIDE SceneTest::IsHitRect(MYRECT_PLUS pl, MYRECT_PLUS rc) {
	HITSLIDE hitSlide;
	hitSlide.hit = 0;
	hitSlide.slide_x = 0;
	hitSlide.slide_y = 0;
	hitSlide.index = -1;

	if(pl.type == CHARA_TYPE_PLAYER) {
		if(IsHitBox(pl.x, pl.y, pl.w, pl.h, rc.x, rc.y, rc.w, rc.h) == 1) {
			switch(rc.type) {
			case CHARA_TYPE_ENEMY1:
			case CHARA_TYPE_ENEMY2:
			case CHARA_TYPE_ENEMY3:
			case CHARA_TYPE_ENEMY4:
			case CHARA_TYPE_ENEMY5:
			case CHARA_TYPE_ENEMY6:
			case CHARA_TYPE_ENEMY7:
			case CHARA_TYPE_ENEMY8:
			case CHARA_TYPE_ENEMY9: {
				hitSlide.hit = rc.type;

				if(pl.x + pl.w/2 > rc.x + rc.w/2 /*|| pl.mx == 0 && rc.mx > 0*/)
				{	// 左に動いていたので、右に補正
					int x = rc.x + rc.w - (pl.x);
					hitSlide.slide_x =  x;
				}
				if(pl.x + pl.w / 2 <= rc.x + rc.w / 2 /*|| pl.mx == 0 && rc.mx < 0*/)
				{	// 右に動いていたので、左に補正
					int x = (pl.x + pl.w) - rc.x ;
					hitSlide.slide_x = -x;
				}
				if(pl.y + pl.h < rc.y /*|| pl.my == 0 && rc.my < 0*/)
				{	// 下に動いていたので、上に補正
					hitSlide.slide_y = -10;
					if(pl.x > rc.x + rc.w / 2) {
						int x = rc.x + rc.w - (pl.x);
						hitSlide.slide_x = x;
					}
					if(pl.x < rc.x + rc.w / 2) {
						int x = (pl.x + pl.w) - rc.x;
						hitSlide.slide_x = -x;
					}
				}
				if(pl.y > rc.y + rc.h)
				{	// 上に動いていたので、下に補正
					hitSlide.slide_y = 10;
					if(pl.x > rc.x + rc.w / 2) {
						int x = rc.x + rc.w - (pl.x);
						hitSlide.slide_x = x;
				}
					if(pl.x < rc.x + rc.w / 2) {
						int x = (pl.x + pl.w) - rc.x;
						hitSlide.slide_x = -x;
					}
				}

				CheckHitMap(_player.GetcharaType(), 0, _player.GetHitSX(), _player.GetHitSY());
				
				break;
			}
			case BULLET_TYPE_ENEMY: {
				hitSlide.hit = BULLET_TYPE_ENEMY;
				break;
			}
			case ITEM_TYPE_AMMO: {
				hitSlide.hit = ITEM_TYPE_AMMO;
				if(_gimmick.GetPossible(rc.index) != false) {
				_plBullet.ChargeRemainBul(BLACK_BULLET);
				_plBullet.ChargeRemainBul(WPORTAL_BULLET);
				_plBullet.ChargeRemainBul(BPORTAL_BULLET);
				_plBullet.ChargeRemainBul(REFLECT_BULLET);
				_plBullet.ChargeRemainBul(TRUST_BULLET);
				_gimmick.SetPossible(false, rc.index);
				_music->MakeSe(_image->Se[7]);
				_music->MakeVoice(GET_VOICE, RANDAM_TWO);
				_music->SetCoolVoice();
				_stajudge[5] = true;
				_stajudge[10] = true;
				}
				break;
			}
			case ITEM_TYPE_TRE: {
				hitSlide.hit = ITEM_TYPE_TRE;
				if(_gimmick.GetPossible(rc.index) != false) {
				switch(_gimmick.Getstate(rc.index)) {
				case 0: {
					_gimmick.SetPossible(false, rc.index);
					_music->MakeSe(_image->Se[7]);
					_music->MakeVoice(GET_VOICE, RANDAM_TWO);
					_music->SetCoolVoice();
					break;
				}
				case 1: {
					_player.AddMaxHP();
					_player.HealHP();
					_gimmick.SetPossible(false, rc.index);
					_music->MakeSe(_image->Se[7]);
					_music->MakeVoice(GET_VOICE, RANDAM_TWO);
					_music->SetCoolVoice();
					_stajudge[1] = true;
					_stajudge[13] = true;
					break;
				}
				case 2: {
					_plBullet.AddBulletMaX(REFLECT_BULLET, 2);
					_plBullet.AddRemBullet(REFLECT_BULLET, 2);
					_gimmick.SetPossible(false, rc.index);
					_music->MakeSe(_image->Se[7]);
					_music->MakeVoice(GET_VOICE, RANDAM_TWO);
					_music->SetCoolVoice();
					_stajudge[18] = true;
					break;
				}
				case 3: {
					_plBullet.AddBulletMaX(TRUST_BULLET, 1);
						_plBullet.AddRemBullet(TRUST_BULLET, 1);
					_gimmick.SetPossible(false, rc.index);
					_music->MakeSe(_image->Se[7]);
					_music->MakeVoice(GET_VOICE, RANDAM_TWO);
					_music->SetCoolVoice();
					_stajudge[17] = true;
					break;
				}
				case 4: {
					_plBullet.AddBulletMaX(BLACK_BULLET, 1);
						_plBullet.AddRemBullet(BLACK_BULLET, 1);
					_gimmick.SetPossible(false, rc.index);
					_music->MakeSe(_image->Se[7]);
					_music->MakeVoice(GET_VOICE, RANDAM_TWO);
					_music->SetCoolVoice();
					_stajudge[16] = true;
					break;
				}
				case 5: {
					_plBullet.AddBulletMaX(WPORTAL_BULLET, 1);
					_plBullet.AddBulletMaX(BPORTAL_BULLET, 1);
						_plBullet.AddRemBullet(WPORTAL_BULLET, 1);
						_plBullet.AddRemBullet(BPORTAL_BULLET, 1);
					_gimmick.SetPossible(false, rc.index);
					_music->MakeSe(_image->Se[7]);
					_music->MakeVoice(GET_VOICE, RANDAM_TWO);
					_music->SetCoolVoice();
					_stajudge[14] = true;
					break;
				}
				}
				}
				break;
			}
			case ITEM_TYPE_HEAL: {
				hitSlide.hit = ITEM_TYPE_HEAL;
				if(_gimmick.GetPossible(rc.index) != false) {
				_player.HealHP();
				if(_player.GetHp() + _stock * 100 > _player.GetHpMax()) {
					_player.SetHpToMax();
				}
				_gimmick.SetPossible(false, rc.index);
				_music->MakeSe(_image->Se[8]);
				_music->MakeVoice(GET_VOICE, RANDAM_TWO);
				_music->SetCoolVoice();
					_stajudge[1] = true;
					_stajudge[12] = true;
				}
				break;
			}
			case ITEM_TYPE_A_MATTER: {
				hitSlide.hit = ITEM_TYPE_A_MATTER;
				if(_gimmick.GetPossible(rc.index) != false) {
				_enemy.AllAddBlack();
				_gimmick.SetPossible(false, rc.index);
				_music->MakeSe(_image->Se[7]);
				_music->MakeVoice(GET_VOICE, RANDAM_TWO);
				_music->SetCoolVoice();
					_stajudge[2] = true;
					_stajudge[15] = true;
				}
				break;
			}
			case ITEM_TYPE_LEVER: {
				hitSlide.hit = ITEM_TYPE_LEVER;
				hitSlide.slide_x = rc.index; //超特別仕様
				break;
			}
			case OBJ_TYPE_DOOR: {
				hitSlide.hit = OBJ_TYPE_DOOR;
				if(pl.mx < 0)
				{	// 左に動いていたので、右に補正
					hitSlide.slide_x = 10;
				}
				if(pl.mx > 0)
				{	// 右に動いていたので、左に補正
					hitSlide.slide_x = -10;
				}
				break;
			}
			case Fix_Black_Hole: {
				if (_player.GetPotInv() <= 0) {
					_player.SetPotInv(60);
					_Fade->CharaFadeSet();
					_music->MakeSe(_image->Se[1]);
					_player.PortalMoveSet(GetHitRect(Fix_Black_Hole, 0, 0, 0).x, GetHitRect(Fix_Black_Hole, 0, 0, 0).y);
				}
				hitSlide.hit = Fix_Black_Hole;
				if (_player.GetPotInv() <= 30) {
					MYRECT_PLUS FWHole = _portal.GetRectFixW();
					hitSlide.slide_x = FWHole.x - 60;
					hitSlide.slide_y = FWHole.y - 60;
				}
					_fcntX = 0;
					_fcntY = 0;
					_isPMove = true;

				break;
			}
			case Black_Hole: {
				if(_plBullet.GetUsePortalW() == 1 && _plBullet.GetUsePortalB() == 1) {
					if (_player.GetPotInv() <= 0) {
						_player.SetPotInv(60);
						_Fade->CharaFadeSet();
						_player.PortalMoveSet(_portal.GetPosBX(), _portal.GetPosBY());
						_music->MakeSe(_image->Se[1]);
					}
					hitSlide.hit = Black_Hole;
					if (_player.GetPotInv()<= 30) {
					MYRECT_PLUS WHole = _portal.GetRectWhite();
					hitSlide.slide_x = WHole.x - 60;
					hitSlide.slide_y = WHole.y - 60;
					}
	              	_fcntX = 0;
					_fcntY = 0;
					_isPMove = true;
				}
				break;
			}
			case SEARCH_AREA1: {
				hitSlide.hit = SEARCH_AREA1;
				if(pl.x < rc.x + rc.w / 2) {
					_enemy.SetArrow(rc.index, -1);
				}
				if(pl.x > rc.x + rc.w / 2) {
					_enemy.SetArrow(rc.index, 1);
				}
				if(pl.y < rc.y + rc.h / 2 && pl.y > rc.y) {
					_enemy.SetAiming(rc.index, 0);
				}
				if(pl.y < rc.y) {
					_enemy.SetAiming(rc.index, 1);
				}
				if(pl.y > rc.y + rc.h / 2) {
					_enemy.SetAiming(rc.index, 2);
				}
				break;
			}
			case SEARCH_AREA2: {
				hitSlide.hit = SEARCH_AREA2;
				break;
			}
			case SEARCH_AREA3: {
				hitSlide.hit = SEARCH_AREA3;
				break;
			}
			}

		}
	}

	return hitSlide;
}

MYCIRCLE_PLUS SceneTest::HitPlbEne(int index, int cx1, int cy1, int r, MYRECT_PLUS rc) {
	MYCIRCLE_PLUS re;
	re.hit = 0;
	re.x = cx1;
	re.y = cy1;
	re.r  = r;
	if(IsHitCircleRect(
		cx1, cy1, r,
		rc.x, rc.y, rc.w, rc.h
	) == 1) {
		_music->MakeSe(_image->Se[2]);
		if(_plBullet.GetbulW(index) == 1) {
			re.hit = 1;
		}
		if(_plBullet.GetbulB(index) == 1) {
			re.hit = 1;
		}
	}

	return re;
}

int SceneTest::HitPlbGim(int index, int cx1, int cy1, int r, MYRECT_PLUS rc) {
	int hit = 0;
	if(IsHitCircleRect(
		cx1, cy1, r,
		rc.x, rc.y, rc.w, rc.h
	) == 1) {
		switch(rc.type) {
		case OBJ_TYPE_DOOR: {
			_plBullet.BulletInit(index);
			hit = rc.type;
			break;
		}
		}
	}

	return hit;
}

int SceneTest::HitEnbPl(int index, int bullet, int cx1, int cy1, int r, MYRECT_PLUS rc) {
	int hit = 0;
	if(_player.GetI_judge() != true) {
	if(IsHitCircleRect(
		cx1, cy1, r,
		rc.x, rc.y, rc.w, rc.h
	) == 1) {
		//_music.MakeSe(Se[2]);

		switch(_enBullet.GetType(index, bullet)) {
		case E_BULLET_1: {
			hit = E_BULLET_1;
			_enBullet.BulletInit(index, bullet);
			break;
		}
		case E_BULLET_2: {
			hit = E_BULLET_2;
			_enBullet.BulletInit(index, bullet);
			break;
		}
		case E_BULLET_3: {
			hit = E_BULLET_3;
			_enBullet.BulletInit(index, bullet);
			break;
		}
		case E_BULLET_4: {
			hit = E_BULLET_4;
			_enBullet.BulletInit(index, bullet);
			break;
		}
		case E_BULLET_5: {
			hit = E_BULLET_5;
			_enBullet.BulletInit(index, bullet);
			break;
		}
		case E_BULLET_6: {
			hit = E_BULLET_6;
			_enBullet.BulletInit(index, bullet);
			break;
		}
		case E_BULLET_7: {
			hit = E_BULLET_7;
			if (_enBullet.GetBWstate(index, bullet) == 1) {
				hit = E_BULLET_8;
			}
			if (_enBullet.GetBWstate(index, bullet) == 2) {
				hit = E_BULLET_9;
			}
			_enBullet.BulletInit(index, bullet);
			break;
		}
		case E_BULLET_8: {
			hit = E_BULLET_6;
			if (_enBullet.GetBWstate(index, bullet) == 1) {
				hit = E_BULLET_7;
			}
			if (_enBullet.GetBWstate(index, bullet) == 2) {
				hit = E_BULLET_8;
			}
			_enBullet.BulletInit(index, bullet);
			break;
		}
		case E_BULLET_9: {
			hit = E_BULLET_9;
			if (_enBullet.GetBWstate(index, bullet) == 1) {
				hit = E_BULLET_9;
			}
			if (_enBullet.GetBWstate(index, bullet) == 2) {
				hit = E_BULLET_10;
			}
			_enBullet.BulletInit(index, bullet);
			break;
		}
		}
	}
	}
	return hit;
}

void SceneTest::PorDelete() {
	if (_player.GetPotInv() <= 0 && _player.GetPorDel() == 1) {
		_plBullet.SetPortalW(0);
		_plBullet.SetPortalB(0);
		_portal.ResetPortW();
		_portal.ResetPortB();
		_player.SetPorDel();
	}
}

void SceneTest::PortGene() {
	// ポータル生成
	int X[BULLET_MAX];
	int Y[BULLET_MAX];
	int Xspeed[BULLET_MAX];
	int Yspeed[BULLET_MAX];
	int arrow[BULLET_MAX];
	int type = 0;
	for(int i = 0; i < BULLET_MAX; i++) {
		X[i] = _plBullet.GetHitCX(i);
		Y[i] = _plBullet.GetHitCY(i);
		Xspeed[i] = _plBullet.GetXspeed(i);
		Yspeed[i] = _plBullet.GetYspeed(i);
		arrow[i] = _plBullet.GetbulArrow(i);

		if(_plBullet.GetbulW(i) == 1) {
			if(_plBullet.MapHitProcess(i, _mapData.IsHitCircleMap(_plBullet.GetHitCX(i), _plBullet.GetHitCY(i), _plBullet.GetHitCR(i)), _mapData.IsHitC4Point(_plBullet.GetHitCX(i), _plBullet.GetHitCY(i), _plBullet.GetHitCR(i)), _mapData.IsHitCircleMap(_plBullet.GetHitCX(i) + _plBullet.GetXspeed(i) * 1.5, _plBullet.GetHitCY(i) + _plBullet.GetYspeed(i) * 1.5, _plBullet.GetHitCR(i))) == WPORTAL_BULLET) {
				_portal.PortalGenerate(WPORTAL_BULLET, X[i], Y[i]);
				_plBullet.SetPortalW(1);
				type = _portal.GetPortTypeW();
				if(CheckHitMap(type, 0, Xspeed[i], Yspeed[i]) != 0) {
					while(CheckHitMap(type, 0, 0, 0) != 0) {
						MYRECT_PLUS WH = _portal.GetRectWhite();
						if(_mapData.IsHitPointBox(WH.x, WH.y) != 0) {
							if(_mapData.IsHitPointBox(WH.x + PORT_W, WH.y) != 0) {
								_portal.AddPosWY(1);
							}
							else if(_mapData.IsHitPointBox(WH.x, WH.y + PORT_H) != 0) {
								_portal.AddPosWX(1);
							}
							else {
								if(Xspeed[i] < 0)
								{	// 左に動いていたので、右に補正
									_portal.AddPosWX(1);
								}
								if(Xspeed[i] > 0)
								{	// 右に動いていたので、左に補正
									_portal.AddPosWX(-1);
								}
								if(Yspeed[i] > 0)
								{	// 下に動いていたので、上に補正
									_portal.AddPosWY(-1);
									if(arrow[i] == 1) {
										_portal.AddPosWX(-1);
									}
								}
								if(Yspeed[i] < 0)
								{	// 上に動いていたので、下に補正
									_portal.AddPosWY(1);
									if(arrow[i] == -1) {
										_portal.AddPosWX(-1);
									}
								}
							}
						}
						else if(_mapData.IsHitPointBox(WH.x + PORT_W, WH.y) != 0) {
							if(_mapData.IsHitPointBox(WH.x, WH.y) != 0) {
								_portal.AddPosWY(1);
							}
							else if(_mapData.IsHitPointBox(WH.x + PORT_W, WH.y + PORT_H) != 0) {
								_portal.AddPosWX(-1);
							}
							else {
								if(Xspeed[i] < 0)
								{	// 左に動いていたので、右に補正
									_portal.AddPosWX(1);
								}
								if(Xspeed[i] > 0)
								{	// 右に動いていたので、左に補正
									_portal.AddPosWX(-1);
								}
								if(Yspeed[i] > 0)
								{	// 下に動いていたので、上に補正
									_portal.AddPosWY(-1);
									if(arrow[i] == 1) {
										_portal.AddPosWX(-1);
									}
								}
								if(Yspeed[i] < 0)
								{	// 上に動いていたので、下に補正
									_portal.AddPosWY(1);
									if(arrow[i] == -1) {
										_portal.AddPosWX(-1);
									}
								}
							}
						}
						else if(_mapData.IsHitPointBox(WH.x, WH.y + PORT_H) != 0) {
							if(_mapData.IsHitPointBox(WH.x, WH.y) != 0) {
								_portal.AddPosWX(1);
							}
							else if(_mapData.IsHitPointBox(WH.x + PORT_W, WH.y + PORT_H) != 0) {
								_portal.AddPosWY(-1);
							}
							else {
								if(Xspeed[i] < 0)
								{	// 左に動いていたので、右に補正
									_portal.AddPosWX(1);
								}
								if(Xspeed[i] > 0)
								{	// 右に動いていたので、左に補正
									_portal.AddPosWX(-1);
								}
								if(Yspeed[i] > 0)
								{	// 下に動いていたので、上に補正
									_portal.AddPosWY(-1);
									if(arrow[i] == 1) {
										_portal.AddPosWX(-1);
									}
								}
								if(Yspeed[i] < 0)
								{	// 上に動いていたので、下に補正
									_portal.AddPosWY(1);
									if(arrow[i] == -1) {
										_portal.AddPosWX(-1);
									}
								}
							}
						}
						else if(_mapData.IsHitPointBox(WH.x + PORT_W, WH.y + PORT_H) != 0) {
							if(_mapData.IsHitPointBox(WH.x + PORT_W, WH.y) != 0) {
								_portal.AddPosWX(-1);
							}
							else if(_mapData.IsHitPointBox(WH.x, WH.y + PORT_H) != 0) {
								_portal.AddPosWY(-1);
							}
							else {
								if(Xspeed[i] < 0)
								{	// 左に動いていたので、右に補正
									_portal.AddPosWX(1);
								}
								if(Xspeed[i] > 0)
								{	// 右に動いていたので、左に補正
									_portal.AddPosWX(-1);
								}
								if(Yspeed[i] > 0)
								{	// 下に動いていたので、上に補正
									_portal.AddPosWY(-1);
									if(arrow[i] == 1) {
										_portal.AddPosWX(-1);
									}
								}
								if(Yspeed[i] < 0)
								{	// 上に動いていたので、下に補正
									_portal.AddPosWY(1);
									if(arrow[i] == -1) {
										_portal.AddPosWX(-1);
									}
								}
							}
						}
						else {
							if(Xspeed[i] < 0)
							{	// 左に動いていたので、右に補正
								_portal.AddPosWX(1);
							}
							if(Xspeed[i] > 0)
							{	// 右に動いていたので、左に補正
								_portal.AddPosWX(-1);
							}
							if(Yspeed[i] > 0)
							{	// 下に動いていたので、上に補正
								_portal.AddPosWY(-1);
							}
							if(Yspeed[i] < 0)
							{	// 上に動いていたので、下に補正
								_portal.AddPosWY(1);
							}
						}

						if(CheckHitMap(type, 0, 0, 0) == 0) {
							break;
						}
					}
				}
			}
		}
		if(_plBullet.GetbulB(i) == 1) {                                                                                                                                                                                                     // 黒ポータルの時は貫通弾がないのでこれは意味をなさない                                                                        
			if(_plBullet.MapHitProcess(i, _mapData.IsHitCircleMap(_plBullet.GetHitCX(i), _plBullet.GetHitCY(i), _plBullet.GetHitCR(i)), _mapData.IsHitC4Point(_plBullet.GetHitCX(i), _plBullet.GetHitCY(i), _plBullet.GetHitCR(i)), _mapData.IsHitCircleMap(_plBullet.GetHitCX(i) + _plBullet.GetXspeed(i), _plBullet.GetHitCY(i) + _plBullet.GetYspeed(i), _plBullet.GetHitCR(i))) == BPORTAL_BULLET) {
				_portal.PortalGenerate(BPORTAL_BULLET, X[i], Y[i]);
				_plBullet.SetPortalB(1);
				type = _portal.GetPortTypeB();
				while(CheckHitMap(type, 0, Xspeed[i], Yspeed[i]) != 0) {
					MYRECT_PLUS BH = _portal.GetRectBlack();
					if(_mapData.IsHitPointBox(BH.x, BH.y) != 0) {
						if(_mapData.IsHitPointBox(BH.x + PORT_W, BH.y) != 0) {
							_portal.AddPosBY(1);
						}
						else if(_mapData.IsHitPointBox(BH.x, BH.y + PORT_H) != 0) {
							_portal.AddPosBX(1);
						}
						else {
							if(Xspeed[i] < 0)
							{	// 左に動いていたので、右に補正
								_portal.AddPosBX(1);
							}
							if(Xspeed[i] > 0)
							{	// 右に動いていたので、左に補正
								_portal.AddPosBX(-1);
							}
							if(Yspeed[i] > 0)
							{	// 下に動いていたので、上に補正
								_portal.AddPosBY(-1);
								if(arrow[i] == 1) {
									_portal.AddPosBX(-1);
								}
							}
							if(Yspeed[i] < 0)
							{	// 上に動いていたので、下に補正
								_portal.AddPosBY(1);
								if(arrow[i] == -1) {
									_portal.AddPosBX(-1);
								}
							}
						}
					}
					else if(_mapData.IsHitPointBox(BH.x + PORT_W, BH.y) != 0) {
						if(_mapData.IsHitPointBox(BH.x, BH.y) != 0) {
							_portal.AddPosBY(1);
						}
						else if(_mapData.IsHitPointBox(BH.x + PORT_W, BH.y + PORT_H) != 0) {
							_portal.AddPosBX(-1);
						}
						else {
							if(Xspeed[i] < 0)
							{	// 左に動いていたので、右に補正
								_portal.AddPosBX(1);
							}
							if(Xspeed[i] > 0)
							{	// 右に動いていたので、左に補正
								_portal.AddPosBX(-1);
							}
							if(Yspeed[i] > 0)
							{	// 下に動いていたので、上に補正
								_portal.AddPosBY(-1);
								if(arrow[i] == 1) {
									_portal.AddPosBX(-1);
								}
							}
							if(Yspeed[i] < 0)
							{	// 上に動いていたので、下に補正
								_portal.AddPosBY(1);
								if(arrow[i] == -1) {
									_portal.AddPosBX(-1);
								}
							}
						}
					}
					else if(_mapData.IsHitPointBox(BH.x, BH.y + PORT_H) != 0) {
						if(_mapData.IsHitPointBox(BH.x, BH.y) != 0) {
							_portal.AddPosBX(1);
						}
						else if(_mapData.IsHitPointBox(BH.x + PORT_W, BH.y + PORT_H) != 0) {
							_portal.AddPosBY(-1);
						}
						else {
							if(Xspeed[i] < 0)
							{	// 左に動いていたので、右に補正
								_portal.AddPosBX(1);
							}
							if(Xspeed[i] > 0)
							{	// 右に動いていたので、左に補正
								_portal.AddPosBX(-1);
							}
							if(Yspeed[i] > 0)
							{	// 下に動いていたので、上に補正
								_portal.AddPosBY(-1);
								if(arrow[i] == 1) {
									_portal.AddPosBX(-1);
								}
							}
							if(Yspeed[i] < 0)
							{	// 上に動いていたので、下に補正
								_portal.AddPosBY(1);
								if(arrow[i] == -1) {
									_portal.AddPosBX(-1);
								}
							}
						}
					}
					else if(_mapData.IsHitPointBox(BH.x + PORT_W, BH.y + PORT_H) != 0) {
						if(_mapData.IsHitPointBox(BH.x + PORT_W, BH.y) != 0) {
							_portal.AddPosBX(-1);
						}
						else if(_mapData.IsHitPointBox(BH.x, BH.y + PORT_H) != 0) {
							_portal.AddPosBY(-1);
						}
						else {
							if(Xspeed[i] < 0)
							{	// 左に動いていたので、右に補正
								_portal.AddPosBX(1);
							}
							if(Xspeed[i] > 0)
							{	// 右に動いていたので、左に補正
								_portal.AddPosBX(-1);
							}
							if(Yspeed[i] > 0)
							{	// 下に動いていたので、上に補正
								_portal.AddPosBY(-1);
								if(arrow[i] == 1) {
									_portal.AddPosBX(-1);
								}
							}
							if(Yspeed[i] < 0)
							{	// 上に動いていたので、下に補正
								_portal.AddPosBY(1);
								if(arrow[i] == -1) {
									_portal.AddPosBX(-1);
								}
							}
						}
					}
					else {
						if(Xspeed[i] < 0)
						{	// 左に動いていたので、右に補正
							_portal.AddPosBX(1);
						}
						if(Xspeed[i] > 0)
						{	// 右に動いていたので、左に補正
							_portal.AddPosBX(-1);
						}
						if(Yspeed[i] > 0)
						{	// 下に動いていたので、上に補正
							_portal.AddPosBY(-1);
						}
						if(Yspeed[i] < 0)
						{	// 上に動いていたので、下に補正
							_portal.AddPosBY(1);
						}
					}

					if(CheckHitMap(type, 0, Xspeed[i], Yspeed[i]) == 0) {
						break;
					}
				}
			}
		}
	}
}

void SceneTest::LineTerminalProcess(/*VECTOR stapoint, int arrow, int aiming, int bullettype*/) {
	VECTOR terminal = _player.GetStaPoint();
	//VECTOR terminal = VGet(0, 0, 0);
	int arrow = _player.GetArrow();
	int aiming = _player.GetAiming();
	int type = _player.GetBulletType();
	float dir = 0.f;

	switch (type) {
	case 0:
	case 1: {
		switch (arrow) {//右
		case 1: {
			switch (aiming) {
			case 0: {//横
				dir = DegToRad(0);
				break;
			}
			case 1: {//斜め上
				dir = Rad6;
				break;
			}
			case 2: {//斜め下
				dir = Rad1;
				break;
			}
			case 3: {//上
				dir = DegToRad(270);
				break;
			}
			case 4: {//下
				dir = DegToRad(90);
				break;
			}
			}
			break;
		}
		case -1: {
			switch (aiming) {
			case 0: {//横
				dir = DegToRad(180);
				break;
			}
			case 1: {//斜め上
				dir = Rad4;
				break;
			}
			case 2: {//斜め下
				dir = Rad3;
				break;
			}
			case 3: {//上
				dir = DegToRad(270);
				break;
			}
			case 4: {//下
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
		switch (arrow) {//右
		case 1: {
			switch (aiming) {
			case 0: {//横
				dir = DegToRad(0);
				break;
			}
			case 1: {//斜め上
				dir = Rad6;
				break;
			}
			case 2: {//斜め下
				dir = Rad1;
				break;
			}
			case 3: {//上
				dir = DegToRad(270);
				break;
			}
			case 4: {//下
				dir = DegToRad(90);
				break;
			}
			}
			break;
		}
		case -1: {
			switch (aiming) {
			case 0: {//横
				dir = DegToRad(180);
				break;
			}
			case 1: {//斜め上
				dir = Rad4;
				break;
			}
			case 2: {//斜め下
				dir = Rad3;
				break;
			}
			case 3: {//上
				dir = DegToRad(270);
				break;
			}
			case 4: {//下
				dir = DegToRad(90);
				break;
			}
			}
			break;
		}
		}
	}
	}

	while (true) {
		terminal.x += 10 * cos(dir);
		terminal.y += 10 * sin(dir);
		if (_mapData.IsHitPointBox(terminal.x, terminal.y) != 0) {
			if (aiming == 1 || aiming == 3) {
				terminal.x -= 20 * cos(dir);
				terminal.y -= 30 * sin(dir);
				if (_mapData.IsHitPointBox(terminal.x += 20 * cos(dir), terminal.y) != 0) {
					terminal.y += 30 * sin(dir);
				}
				else {
					terminal.x -= 20 * cos(dir);
				}
			}
			break;
		}
		if (terminal.x <= 0 || terminal.y <= 0 || terminal.x >= 3840 || terminal.y >= 2160 ) {
			break;
		}
	}

	_player.SetTerminal(terminal);
}
