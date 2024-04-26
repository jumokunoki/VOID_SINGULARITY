/*****************************************************************//**
 * \file   SceneTestFloorProcess.cpp
 * \brief  テストにおけるフロア固有の処理
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date  August 2023
 *********************************************************************/

#include "SceneTest.h"
#include "DxLib.h"
#include "gamemain.h"
#include "mymath.h"
#include "mydraw.h"
#include "MapData.h"

void SceneTest::FloorPosInit(){
	// プレイヤーが出てくる位置設定
	// プロローグ1
	_p_pos.rx[0] = 3540;
	_p_pos.ry[0] = 600;
	// プロローグ2
	_p_pos.lx[1] = 180;
	_p_pos.ly[1] = 1020;
	_p_pos.rx[1] = 3480;
	_p_pos.ry[1] = 540;
	// プロローグ3
	_p_pos.lx[2] = 240;
	_p_pos.ly[2] = 420;
	_p_pos.rx[2] = 3540;
	_p_pos.ry[2] = 1560;
	// プロローグ4
	_p_pos.lx[3] = 240;
	_p_pos.ly[3] = 1680;
	_p_pos.rx[3] = 3600;
	_p_pos.ry[3] = 540;
	// ステージ1-1
	_p_pos.lx[4] = 240;
	_p_pos.ly[4] = 1020;
	_p_pos.rx[4] = 3540;
	_p_pos.ry[4] = 1800;
	// ステージ1-2
	_p_pos.lx[5] = 180;
	_p_pos.ly[5] = 420;
	_p_pos.rx[5] = 3540;
	_p_pos.ry[5] = 900;
	_p_pos.rx_sub[5] = 3540;
	_p_pos.ry_sub[5] = 1800;
	// ステージ1-3
	_p_pos.lx[6] = 180;
	_p_pos.ly[6] = 900;
	_p_pos.lx_sub[6] = 180;
	_p_pos.ly_sub[6] = 1800;
	_p_pos.rx[6] = 3540;
	_p_pos.ry[6] = 1800;
	// ステージ1-4
	_p_pos.lx[7] = 240;
	_p_pos.ly[7] = 1800;
	_p_pos.rx[7] = 3540;
	_p_pos.ry[7] = 1800;
	// ステージ1-5
	_p_pos.lx[8] = 180;
	_p_pos.ly[8] = 1800;
	_p_pos.rx[8] = 3540;
	_p_pos.ry[8] = 1320;
	// ステージ1-6
	_p_pos.lx[9] = 180;
	_p_pos.ly[9] = 900;
	_p_pos.rx[9] = 3600;
	_p_pos.ry[9] = 1800;
	// ステージ2-1
	_p_pos.lx[10] = 240;
	_p_pos.ly[10] = 1830;
	_p_pos.rx[10] = 3600;
	_p_pos.ry[10] = 420;
	// ステージ2-2
	_p_pos.lx[11] = 240;
	_p_pos.ly[11] = 452;
	_p_pos.rx[11] = 0;
	_p_pos.ry[11] = 0;
	// ステージ2-3
	_p_pos.lx[12] = 200;
	_p_pos.ly[12] = 512;
	_p_pos.lx_sub[12] = 1980;
	_p_pos.ly_sub[12] = 510;
	// ステージ2-4
	_p_pos.lx[13] = 120;
	_p_pos.ly[13] = 540;
	_p_pos.rx[13] = 3540;
	_p_pos.ry[13] = 1800;
	// ステージ2-5
	_p_pos.lx[14] = 240;
	_p_pos.ly[14] = 400;
	_p_pos.rx[14] = 3540;
	_p_pos.ry[14] = 780;
	// ステージ2-6
	_p_pos.lx[15] = 180;
	_p_pos.ly[15] = 1440;
	_p_pos.rx[15] = 0;
	_p_pos.ry[15] = 0;
	// ボスステージ
	_p_pos.lx[16] = 180;
	_p_pos.ly[16] = 1700;
	_p_pos.rx[16] = 0;
	_p_pos.ry[16] = 0;
}

void SceneTest::FloorScaleInit() {
	// フロアごとの画面のよりひき
	_fScale[0] = 1.0f;
	_fScale[1] = 0.8f;
	_fScale[2] = 0.75f;
	_fScale[3] = 0.67f;
	_fScale[4] = 0.83f;
	_fScale[5] = 0.83f;
	_fScale[6] = 0.76f;
	_fScale[7] = 0.83f;
	_fScale[8] = 0.83f;
	_fScale[9] = 0.90f;
	_fScale[10]= 0.92f;
	_fScale[11]= 0.88f;
	_fScale[12]= 0.88f;
	_fScale[13]= 1.00f;
	_fScale[14]= 1.00f;
	_fScale[15]= 1.00f;
	_fScale[16]= 0.75f;
}

void SceneTest::SaveSet() {
	_Save->SetBullet_Num(0, _plBullet.GetRemainBulTR());
	_Save->SetBullet_Num(1, _plBullet.GetRemainBulRF());
	_Save->SetBullet_Num(2, _plBullet.GetRemainBulB());
	_Save->SetBullet_Max(0, _plBullet.GetMaxBulTR());
	_Save->SetBullet_Max(1, _plBullet.GetMaxBulRF());
	_Save->SetBullet_Max(2, _plBullet.GetMaxBulB());
	_Save->SetNowHp(_player.GetHp() + _stock * 100);
	_Save->SetMaxHp(_player.GetHpMax());
	_Save->SetStage(_mapData.GetFloorNum());
}

void SceneTest::FloorCamInit() {
	// フロアごとのカメラの初期化
	float right = _player.GetPosX() + _player.GetPosW() / 2 + 100;
	float left = _player.GetPosX() + _player.GetPosW() / 2 - 100;

	// キャラ中心座標
	//float flatX = _player.GetPosX() + _player.GetPosW() / 2;
	float flatY = _player.GetPosY();


	switch (_player.GetArrow()) {
	case 1: {
		if (_camX != right) {
			_camX = right;
		}
		break;
	}
	case -1: {
		if (_camX != left) {
			_camX = left;
		}
		break;
	}
	}

	if (_camY != flatY) {
		_camY = flatY;
	}

	VECTOR pos = VGet(_camX, _camY, 0);

	_cam.SetPos(pos);

	// カメラ処理を呼ぶ
	_cam.Process();
}

void SceneTest::FloorCommon(int x, int y, int FloorNum) {
	// フロア移動時の共通処理
	_player.SetPosX(x);
	_player.SetPosY(y);
	_player.ReSetBulletType();
	_enemy.AllInit();
	_plBullet.SetCutinUse();
	_plBullet.SetPortalB(0);
	_plBullet.SetPortalW(0);
	_portal.ResetPortW();
	_portal.ResetPortB();
	_gimmick.Save(FloorNum);
	_gimmick.GimInit();
	for(int i = 0; i < BULLET_MAX; i++) {
		_plBullet.BulletInit(i);
	}
	for(int i = 0; i < ENEMY_MAX; i++) {
		for(int j = 0; j < E_BULLET_MAX; j++) {
			_enBullet.BulletInit(i, j);
		}
	}

	if (CheckSoundMem(_image->Se[16]) == 1) {
		_music->StopSe(_image->Se[16]);
	}

	_Initcnt = 0;
}



void SceneTest::FloorProcess(int FloorNum) {
	// フロアごとに行われる処理
	_Initcnt++;

	if (_Initcnt < 60) {
		if (GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
			_player.SetPosX(-135);
		}
		if (GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
			_player.SetPosX(_mapData.GetWorldSizeW() - 135 - _player.GetRect().w);
		}
	}

	switch(FloorNum) {
	case 0: {
		if(_player.GetPosX() + 135 < 0) {
			_player.SetPosX(-135);
		}
		_portal.PortalGenerate(Fix_White_Hole, 2220, 900);
		_portal.PortalGenerate(Fix_Black_Hole, 2220, 1260);

		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);
					_mapData.SetFloorNum(1);
					SaveSet();
					_Fade->FadeSet(0, 0, 60,0);
					//--------------------------
					_talk.SetScenario(1);
					_talk.SetTalkScene(1);
					_talk.SetLine();
					//--------------------------
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 0) { //プロローグフロア1
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3420, 750, 1);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 1: {
		if (_fInit == true && _Initcnt >= 60) {
			if (GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				B_Out_Entry();
				if (_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);
					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(0);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();

					_fInit = false;
				}
			}
			if (GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w / 2 > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if (_stacnt[3] >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);
					_Fade->FadeSet(0, 0, 60, 0);
					//--------------------------
					_talk.SetScenario(1);
					_talk.SetTalkScene(2);
					_talk.SetLine();
					//--------------------------
					_mapData.SetFloorNum(2);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();

					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 1) {//プロローグフロア2
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3180, 750, 4);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 1200, 1710, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 2880, 750, 0);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2220, 1080, -1);

					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}
		break;
	}
	case 2: {
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);
					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(1);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();

					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);
					
					_mapData.SetFloorNum(3);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_Fade->FadeSet(0, 0, 60, 0);
					//------------------------------
					_talk.SetScenario(2);
					_talk.SetTalkScene(3);
					_talk.SetLine();
					//-----------------------------
					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 2) { //プロローグフロア3
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 60, 930, 4);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3240, 1770, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 3420, 1770, 1);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 1080, 1770, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 1620, 1380, 0);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2460, 1620, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 3060, 1620, 1);

					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 3: {
		_portal.PortalGenerate(Fix_White_Hole, 3240, 660);
		_portal.PortalGenerate(Fix_Black_Hole, 3000, 1080);
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);
					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(2);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(4);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_Fade->FadeSet(0, 0, 60, 0);
					_player.ReleaseRef();
					_Save->SetRereas(0, 1);
					//--------------------------
					_talk.SetScenario(1);
					_talk.SetTalkScene(3);
					_talk.SetLine();
					//--------------------------

					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 3) {//プロローグフロア4
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3240, 750, 4);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 840, 1800, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 660, 1890, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 3420, 750, 0);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 1320, 1410, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 1800, 1740, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2160, 1740, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 2640, 1410, 1);
					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 4: {
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(3);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_music->MakeSe(_image->Se[6]);
			
					_mapData.SetFloorNum(5);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_Fade->FadeSet(0, 0, 60, 0);
					//------------------------------
					_talk.SetScenario(2);
					_talk.SetTalkScene(6);
					_talk.SetLine();
					//-----------------------------
					_fInit = false;
				}
			}
		}
		if (_mapData.GetFloorNum() == 4) {//ステージ1-1
			if (_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if (_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if (_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if (_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3660, 630, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3660, 990, 2);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 2820, 630, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 840, 1920, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 420, 1920, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 1320, 990, 0);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 1800, 520, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 2460, 500, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 1740, 1880, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2100, 1880, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2460, 1880, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2820, 1880, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 1980, 1520, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 2820, 1520, 1);
					_gimmick.GeneLeverDoor(180, 1970, 3300, 770);

					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 5: {
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(4);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW() && GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).y < 1300) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
			        FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);
					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(6);
					SaveSet();
					_Fade->FadeSet(0, 0, 60, 0);
					//--------------------------
					_talk.SetScenario(1);
					_talk.SetTalkScene(5);
					_talk.SetLine();
					//--------------------------
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW() && GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).y > 1300) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
				FloorCommon(_p_pos.lx_sub[FloorNum + 1], _p_pos.ly_sub[FloorNum + 1], FloorNum);
					_mapData.SetFloorNum(6);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_Fade->FadeSet(0, 0, 60, 0);
					//--------------------------
					_talk.SetScenario(1);
					_talk.SetTalkScene(5);
					_talk.SetLine();
					//--------------------------
					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 5) { //ステージ1-2
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3660, 690, 4);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3660, 1470, 2);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 1080, 690, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 60, 1470, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 2880, 690, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 2760, 2010, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 120, 840, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 1920, 1440, 0);
					_gimmick.GeneLeverDoor(2100, 660, 3720, 870);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 1860, 980, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2400, 980, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 3060, 980, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 540, 1340, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 1680, 1880, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2340, 1880, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 3060, 1880, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 3180, 1545, 1);

					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 6: {
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0 && GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).y < 1300) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);
					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(5);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0 && GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).y > 1300) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx_sub[FloorNum - 1], _p_pos.ry_sub[FloorNum - 1], FloorNum);

					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(5);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(7);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_player.ReleaseTr();
					_Save->SetRereas(1,1);
					//------------------------------
					_talk.SetScenario(2);
					_talk.SetTalkScene(5);
					_talk.SetLine();
					//-----------------------------
					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 6) {
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 3420, 1110, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 2160, 2010, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 2160, 1110, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 1320, 1590, 3);
						_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 2400, 1020, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 2400, 1920, 1);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);
					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 7: {
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_music->MakeSe(_image->Se[6]);
	                _portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetFloorNum(6);
					SaveSet();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(8);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_Fade->FadeSet(0, 0, 60, 0);
					//--------------------------
					_talk.SetScenario(1);
					_talk.SetTalkScene(6);
					_talk.SetLine();
					//--------------------------
					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 7) {
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 2040, 1290, 3);
						_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 3600, 1500, 1);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 600, 1230, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 3060, 930, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 2640, 2010, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 1320, 1200, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 1260, 1920, 0);
					_gimmick.GeneLeverDoor(3420, 900, 3060, 1080);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2520, 1140, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2160, 660, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 3300, 600, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 3240, 1860, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 240, 1080, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 2700, 1440, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 1460, 1780, 1);

					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 8: {
		_portal.PortalGenerate(Fix_White_Hole, 1860, 600);
		_portal.PortalGenerate(Fix_Black_Hole, 1560, 1860);
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(7);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
						FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);
					_music->MakeSe(_image->Se[6]);
				
					_mapData.SetFloorNum(9);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 8) {
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 1020, 1950, 4);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3300, 1530, 2);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 2730, 1950, 4);
						_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 3540, 1020, 1);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 780, 1170, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 1800, 1530, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 1620, 1560, 0);
					_gimmick.GeneLeverDoor(1260, 1020, 2820, 480);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 360, 1080, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2280, 540, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 2640, 540, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 3200, 960, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2400, 960, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2400, 1380, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY3, 3060, 1380, 1);


					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 9: {
		_portal.PortalGenerate(Fix_White_Hole, 1620, 1920);
		_portal.PortalGenerate(Fix_Black_Hole, 1140, 600);

		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(8);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);
					
	                _mapData.SetFloorNum(10);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_Fade->FadeSet(0, 0, 60, 0);
					//--------------------------
					_talk.SetScenario(1);
					_talk.SetTalkScene(7);
					_talk.SetLine();

					//--------------------------
					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 9) {
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {
					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 1740, 690, 4);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 2220, 1230, 4);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3420, 2010, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 120, 2010, 2);
						_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 2880, 1440, 1);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 1200, 2010, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 3360, 1530, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 3480, 1230, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 1980, 1440, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 960, 1920, 0);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 1640, 1380, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2100, 1860, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2460, 1860, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY3, 2820, 1860, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 3120, 1860, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 2580, 1520, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY5, 2580, 1080, 1);

					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 10: {
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
						FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);
					_mapData.SetFloorNum(9);
					SaveSet();
					_music->MakeSe(_image->Se[6]);
                    _mapData.SetFloorNum(9);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(11);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_music->MakeSe(_image->Se[6]);
					_music->MakeSe(_image->Se[6]);
					_mapData.SetMapData();
					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 10) {
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {
					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 2400, 1770, 3);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 2940, 1950, 4);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3300, 1230, 4);
						_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 2760, 1920, 0);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 120, 1590, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 1800, 630, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 2700, 1230, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 2640, 1950, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 2400, 1380, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 2880, 1140, 0);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 1800, 1620, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 2040, 1440, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 740, 900, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 1260, 960, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY3, 1560, 960, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 1860, 960, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 2220, 240, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 3120, 480, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 2880, 1020, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 3180, 1020, 1);

					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 11: {
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(10);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_music->MakeSe(_image->Se[6]);
					_mapData.SetMapData();
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).y + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).h > _mapData.GetWorldSizeH() && GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 1800) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
			FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);
					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(12);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
		}
		if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).y + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).h > _mapData.GetWorldSizeH() && GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x > 1800) {
			B_Out_Entry();
			if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.lx_sub[FloorNum + 1], _p_pos.ly_sub[FloorNum + 1], FloorNum);
				_music->MakeSe(_image->Se[6]);
				_mapData.SetFloorNum(12);
				SaveSet();
				_portal.FixResetPortW();
				_portal.FixResetPortB();
				_mapData.SetMapData();
				_fInit = false;
			}
		}
		if(_mapData.GetFloorNum() == 11) {
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 1860, 630, 2);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 420, 990, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 1860, 1410, 4);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 1140, 630, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 3600, 630, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 2700, 1590, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 1560, 1320, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 960, 1440, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 2400, 1920, 0);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY3, 1020, 1800, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 1220, 1380, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 1500, 1800, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 1980, 840, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 2580, 840, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY5, 3540, 840, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 2460, 480, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 3540, 1320, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 2340, 1320, 1);

					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 12: {
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).y + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).h > _mapData.GetWorldSizeH()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);
					
					_mapData.SetFloorNum(13);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_Fade->FadeSet(0, 0, 60, 0);
					//--------------------------
					_talk.SetScenario(1);
					_talk.SetTalkScene(8);
					_talk.SetLine();
					//--------------------------
					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 12) {
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 260, 1020, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 1800, 1860, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 780, 1950, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 2880, 1950, 3);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 840, 960, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 300, 1440, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY3, 600, 1440, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 1260, 1320, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2220, 960, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY3, 2520, 960, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY5, 2820, 960, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2520, 1440, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY5, 2820, 1440, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY5, 1140, 1800, 1);
					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 13: {//2-4
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				_player.SetPosX(-135);
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
				FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_music->MakeSe(_image->Se[6]);
				
					_mapData.SetFloorNum(14);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 13) {
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 720, 1830, 4);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 2220, 1110, 3);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3600, 1530, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 2940, 1110, 4);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3180, 1110, 3);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3420, 1110, 3);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3660, 1110, 2);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 1320, 690, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 1680, 1530, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 480, 1740, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 1920, 1440, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 1800, 1860, 0);
					_gimmick.GeneLeverDoor(960, 1800, 2400, 880);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY3, 1920, 960, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 2520, 1380, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 1920, 1800, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY5, 2640, 1800, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 3000, 1800, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 3540, 1800, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 2710, 840, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 3010, 840, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 2710, 1020, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 3010, 1020, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY1, 2200, 140, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY3, 2480, 140, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY5, 2700, 140, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY2, 2960, 200, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 3200, 200, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 3440, 200, 1);

					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 14: {//2-5
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(13);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_music->MakeSe(_image->Se[6]);
					_music->MakeSe(_image->Se[5]);
					
					_mapData.SetFloorNum(15);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 14) {
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 60, 2010, 4);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 1500, 1350, 3);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3660, 1770, 2);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 180, 1350, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 2280, 1710, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 2780, 990, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 240, 1980, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 1140, 480, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 2460, 1620, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 2340, 1080, 0);
					_gimmick.GeneLeverDoor(1440, 900, 3720, 720);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY3, 1080, 900, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 1020, 1260, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY3, 960, 1860, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 1980, 1860, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY5, 2880, 1860, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY4, 3240, 1920, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 3600, 1260, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY5, 2760, 1200, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 1500, 1140, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY6, 1980, 780, 1);
					_enemy.AddEnemy(CHARA_TYPE_ENEMY5, 1920, 1200, 1);
					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;
	}
	case 15: {
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_music->MakeSe(_image->Se[6]);
					_mapData.SetFloorNum(14);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w > _mapData.GetWorldSizeW()) {
				B_Out_Entry();
				if(_stacnt[3] >= 60) {
							FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(16);
					SaveSet();
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_Fade->FadeSet(0, 0, 60, 0);
					//--------------------------
					_talk.SetScenario(1);
					_talk.SetTalkScene(9);
					_talk.SetLine();
					//--------------------------
					_fInit = false;
				}
			}
		}
		if(_mapData.GetFloorNum() == 15) {
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {
						_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 2820, 1650, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 3000, 1620, 1);
						_gimmick.GeneGimmick(ITEM_TYPE_TRE, 3180, 1650, 4);
						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);

					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}
			B_Out_Cancel();
		}

		break;

	}
	case 16: {
		// 各フロアごとにカメラの処理を変えるならここで変更
		//_cam.Setscale(0.50f);
		if(_fInit == true && _Initcnt >= 60) {
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x < 0) {
				_player.SetPosX(-135);
			}
			if(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).x + GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0).w> _mapData.GetWorldSizeW()) {
				_player.SetPosX(_mapData.GetWorldSizeW() - 135 - _player.GetRect().w);
			}
		}
		if(_mapData.GetFloorNum() == 16) {
			if(_fInit == false) {
				_cam.Setscale(_fScale[FloorNum]);
				if(_stajudge[3] == true) {
					_stacnt[3]++;
				}
				if(_stacnt[3] <= 120) {

					FloorCamInit();
					// エネミーの追加などフロアごとの初期化時に利用
					if(_ispop[FloorNum] != true) {

						_ispop[FloorNum] = true;
					}
					_gimmick.Load(FloorNum);


					_enemy.AddEnemy(CHARA_TYPE_ENEMY7, 1500, -800, -1);

					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 240, 780, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 120, 780, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 420, 860, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 1800, 780, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 1620, 860, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 2040, 780, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_A_MATTER, 3300, 780, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 3600, 780, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 3480, 860, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 300, 1140, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_HEAL, 3420, 1140, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 120, 1230, 0);
					_gimmick.GeneGimmick(ITEM_TYPE_AMMO, 3600, 1230, 0);

					_fInit = true;
					_stajudge[3] = false;
					_stajudge[4] = true;
				}
			}		
			B_Out_Cancel();
		}
		break;
	}
	}
}

// 後に消す/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void    SceneTest::DebugFloorMove(int FloorNum) {
	if (gPad._gKey[0] & PAD_INPUT_7) {
		if (gPad._gKey[0] & PAD_INPUT_5) {
			switch (FloorNum) {
			case 0: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[16], _p_pos.ly[16], FloorNum);

					_mapData.SetFloorNum(16);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 1: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(0);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 2: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(1);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}

				break;
			}
			case 3: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(2);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}

				break;
			}
			case 4: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(3);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();

					_fInit = false;
				}

				break;
			}
			case 5: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(4);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}

				break;
			}
			case 6: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(5);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}

				break;
			}
			case 7: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(6);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}

				break;
			}
			case 8: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(7);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}

				break;
			}
			case 9: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(8);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 10: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(9);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}

				break;
			}
			case 11: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(10);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}


				break;
			}
			case 12: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(11);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 13: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(12);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_stageNum--;
					_fInit = false;
				}

				break;
			}
			case 14: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(13);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 15: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(14);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 16: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.rx[FloorNum - 1], _p_pos.ry[FloorNum - 1], FloorNum);

					_mapData.SetFloorNum(15);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}

			}

		}
	}


	if (gPad._gKey[0] & PAD_INPUT_7) {
		if (gPad._gKey[0] & PAD_INPUT_6) {
			switch (FloorNum) {
			case 0: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(1);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 1: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(2);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}

				break;
			}
			case 2: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(3);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}

				break;
			}
			case 3: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(4);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();


					_fInit = false;
				}
				break;
			}
			case 4: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(5);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();

					_fInit = false;
				}
				break;
			}
			case 5: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(6);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 6: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(7);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}

				break;
			}
			case 7: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(8);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}

				break;
			}
			case 8: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(9);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 9: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(10);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 10: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(11);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}

				break;
			}
			case 11: {

				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(12);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 12: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(13);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_stageNum++;
					_fInit = false;
				}
				break;
			}
			case 13: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(14);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 14: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(15);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}
			case 15: {
				if (_fInit == true && _Initcnt >= 60) {
					FloorCommon(_p_pos.lx[FloorNum + 1], _p_pos.ly[FloorNum + 1], FloorNum);

					_mapData.SetFloorNum(16);
					_portal.FixResetPortW();
					_portal.FixResetPortB();
					_mapData.SetMapData();
					_fInit = false;
				}
				break;
			}

			}
		}
	}
}