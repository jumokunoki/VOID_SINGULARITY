/*****************************************************************//**
 * \file   SceneTest.cpp
 * \brief  ゲーム本編
 *
 * \author 奈良充樹,齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#include "SceneTest.h"
#include "DxLib.h"
#include "main.h"
#include "gamemain.h"
#include "mydraw.h"

SceneTest::SceneTest() {

	_gPause = new Pause();

	////bgm
	_image->GameMainLoad();
	bgm_count = 0;
	_start_movie_use = _Save->GetMovieUse();

	// カメラのリミット設定
	_Initcnt = 0;
	MYRECT rc = { 0,0,_mapData.GetWorldSizeW(),_mapData.GetWorldSizeH() };
	_cam.SetrcLimit(rc);

	_fInit = false;

	_Initcnt = 0;
	_isPMove = false;
	_RelCnt = 0;
	_isZoom = false;
	_scaleCnt = 0.0f;
	_fcntX = 0.0f;
	_fcntY = 0.0f;
	_arrowcnt = 0;
	_stageNum = 0;
	_Initcnt = 0;
	for(int i = 0; i < 20; i++) {
		_stacnt[i] = 0;
		_stajudge[i] = false;
	}

	for(int i = 0; i < 2; i++) {
		anim[i].num   = 0;
		anim[i].count = 0;
	}

	anim[0].use = 1;
	anim[1].use = 0;

	_stock = 0;

	_Fade->FadeSet(0, 0, 60, 0);

	_talk.SetScenario(1);
	_talk.SetTalkScene(0);
	_talk.SetLine();
	_talk.SetProcessStop();
	FloorPosInit();
	FloorScaleInit();
	_inputS = _fScale[0];
	_camX = _player.GetPosX() + _player.GetPosW() / 2 + 300;
	_camY = _player.GetPosY() ;

	if (_mapData.GetFloorNum() != 0) {
		FloorCommon(_p_pos.lx[_Save->GetStage()], _p_pos.ly[_Save->GetStage()], _Save->GetStage());
	}

}

SceneTest::~SceneTest() {
	
}


void SceneTest::PlProcess() {

	_player.PotInvProcess();

	if (_talk.GetProcessStop() == 0) {
		if (_player.GetPotInv() <= 0) {
		PorDelete();
		
		_player.DoFrameCount(_stock);
		
		_player.Gravity();

		_player.DetectGravity(CheckHitMap(_player.GetcharaType(), 0, 0, _player.GetGravity()));

		if (_plBullet.GetStanceType() == 0 && _player.GetHp() > 0) {
			_player.MoveProcess();
		}

		CheckHitMap(_player.GetcharaType(), 0, _player.GetRunSpeed(), 0);



		for (int i = 0; i < ENEMY_MAX; i++) {
			_player.HitObj(IsHitRect(GetHitRect(CHARA_TYPE_PLAYER, 0, _player.GetRunSpeed(), _player.GetGravity()), GetHitRect(_enemy.GetType(i), i, 0, 0)), _enemy.GetRect_P(i));
			if (CheckHitMap(_player.GetcharaType(), 0, _player.GetHitSX(), _player.GetHitSY()) == 1) {
				if (_player.GetHitSX() > 0) {
					_player.SetPosX(_enemy.GetRect_P(i).x - (135 + _player.GetRect().w + _enemy.GetRect_P(i).w / 2));
				}
				if (_player.GetHitSX() < 0) {
					_player.SetPosX(_enemy.GetRect_P(i).x + _enemy.GetRect_P(i).w - 135);
				}
			}
			for (int j = 0; j < E_BULLET_MAX; j++) {
				_player.DamageProcess(HitEnbPl(i, j, _enBullet.GetHitCX(i, j), _enBullet.GetHitCY(i, j), _enBullet.GetHitCR(i, j), GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0)));
			}
		}
		}

		_player.HitObj(IsHitRect(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0), GetHitRect(Black_Hole, 0, 0, 0)), _none);
		_player.HitObj(IsHitRect(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0), GetHitRect(Fix_Black_Hole, 0, 0, 0)), _none);

		// ダメージ演出用の処理
		Staging();

		_player.AddIT();

		for (int i = 0; i < GIMMAX; i++) {
			_player.HitObj(IsHitRect(GetHitRect(CHARA_TYPE_PLAYER, 0, _player.GetRunSpeed(), 0), GetHitRect(_gimmick.GetGimType(i), i, 0, 0)), _none);
			if (_gimmick.Process(IsHitRect(GetHitRect(CHARA_TYPE_PLAYER, 0, _player.GetRunSpeed(), 0), GetHitRect(_gimmick.GetGimType(i), i, 0, 0))) == 1) {
				_stajudge[11] = true;
			}
		}

		if (_plBullet.GetStanceType() == 0 && _player.GetHp() > 0) {
			_player.AimProcess(_plBullet.GetRemainBulRF(), _plBullet.GetRemainBulTR(), _plBullet.GetRemainBulB(), _plBullet.GetRemainBulPW(), _plBullet.GetRemainBulPB(),_plBullet.GetDeray(2));
		}

		LineTerminalProcess();

		_player.PortalMoveProcess();

		_gimmick.MotProcess();

		if (_player.GetMotionT() != 5) {
			if (_plBullet.GetDeray(2) < 0) {
				_plBullet.SetDeray(2, 0);
			}
		}
		if ( _player.GetHp() > 0) {
			_plBullet.ShootProcess(_player.GetBulletType(), _player.GetBWP_select(), _player.GetPosX(), _player.GetPosY(), _player.GetAiming(), _player.GetArrow());
		}

		PortGene();

		_player.ChengeFrameCount(_player.GetMotionH(), _player.GetMotionT(), _player.GetMotionO(), _player.GetOldMotion());

		_player.SetOldMotion();

	}

	_stock = HpStock(_player.GetHp(), _stock);
	_stock = StockBreak(_player.GetHp(), _stock);
	GameOver();
}

int SceneTest::HpStock(int now_hp ,int stock) {
	int restock = stock;

	for(;;) {
		if(now_hp > 100) {
			restock++;
			_player.SetDamage(100);
			now_hp -= 100;
		}
		else {
			if(restock >= (_player.GetHpMax() / 100)) {
				restock = (_player.GetHpMax() / 100) - 1;
			}
			break;
		}
	}

	return restock;
}

int SceneTest::StockBreak(int now_hp, int stock) {
	if(now_hp <= 0) {
		if(stock > 0) {
			stock--;
			_player.SetRecovery(100);
			_Ui.SetDelay();
		}
	}
	return stock;
}

void SceneTest::EneProcess() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		HITSLIDE search1 = IsHitRect(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0), GetHitRect(_enemy.GetRectSearch(i).type, i, 0, 0));
		HITSLIDE search2 = IsHitRect(GetHitRect(CHARA_TYPE_PLAYER, 0, 0, 0), GetHitRect(_enemy.GetRectSearchBoss().type, i, 0, 0));
		_enemy.Process(i, _player.GetPosX(), _player.GetPosY(), search1, search2,_mapData.GetWorldSizeW(), _mapData.GetWorldSizeH());
		
	    _enemy.AnnihilationEffect(i);
		for(int j = 0; j < BULLET_MAX; j++) {
			MYRECT_PLUS rc = GetHitRect(_enemy.GetRect_P(i).type, i, 0, 0);
			// ボス用の当たり判定
			MYRECT_PLUS bf = GetHitRect(_enemy.GetRect_BOSSF(i).type, i, 0, 0);
			MYRECT_PLUS bs = GetHitRect(_enemy.GetRect_BOSSS(i).type, i, 0, 0);
			MYRECT_PLUS bt = GetHitRect(_enemy.GetRect_BOSST(i).type, i, 0, 0);

			_enemy.CommonProcess(HitPlbEne(j, _plBullet.GetHitCX(j), _plBullet.GetHitCY(j), _plBullet.GetHitCR(j), rc),i, _plBullet.GetbulW(j), _plBullet.GetbulB(j),_player.GetHp());
			// ボス用の当たり判定
			if (_enemy.GetType(i) == CHARA_TYPE_ENEMY7) {
			_enemy.CommonProcess(HitPlbEne(j, _plBullet.GetHitCX(j), _plBullet.GetHitCY(j), _plBullet.GetHitCR(j), bf), i, _plBullet.GetbulW(j), _plBullet.GetbulB(j), _player.GetHp());
			_enemy.CommonProcess(HitPlbEne(j, _plBullet.GetHitCX(j), _plBullet.GetHitCY(j), _plBullet.GetHitCR(j), bs), i, _plBullet.GetbulW(j), _plBullet.GetbulB(j), _player.GetHp());
			_enemy.CommonProcess(HitPlbEne(j, _plBullet.GetHitCX(j), _plBullet.GetHitCY(j), _plBullet.GetHitCR(j), bt), i, _plBullet.GetbulW(j), _plBullet.GetbulB(j), _player.GetHp());
			}
			if(IsHitCircleRect(_plBullet.GetHitCX(j), _plBullet.GetHitCY(j), _plBullet.GetHitCR(j), rc.x, rc.y, rc.w, rc.h) == 1) {
				if(_plBullet.GetBulletType(j) != 2) {
					_plBullet.BulletInit(j);
				}
			}
			// ボス用の当たり判定
			if (_enemy.GetType(i) == CHARA_TYPE_ENEMY7) {
			if(IsHitCircleRect(_plBullet.GetHitCX(j), _plBullet.GetHitCY(j), _plBullet.GetHitCR(j), bf.x, bf.y, bf.w, bf.h) == 1) {
				if(_plBullet.GetBulletType(j) != 2) {
					_plBullet.BulletInit(j);
				}
			}
			if(IsHitCircleRect(_plBullet.GetHitCX(j), _plBullet.GetHitCY(j), _plBullet.GetHitCR(j), bs.x, bs.y, bs.w, bs.h) == 1) {
				if(_plBullet.GetBulletType(j) != 2) {
					_plBullet.BulletInit(j);
				}
			}
				if (IsHitCircleRect(_plBullet.GetHitCX(j), _plBullet.GetHitCY(j), _plBullet.GetHitCR(j), bt.x, bt.y, bt.w, bt.h) == 1) {
					if (_plBullet.GetBulletType(j) != 2) {
						_plBullet.BulletInit(j);
					}
				}
			}
		}
		_enemy.PosFix(i, CheckHitMap(_enemy.GetType(i), i, _enemy.GetMX(i), 0));
		
		if (_enemy.GetType(i) != CHARA_TYPE_ENEMY7) {
		_enBullet.E_ShootProcess(i, _enemy.GetType(i), _enemy.GetACont(i), _enemy.GetPosEnemyX(i), _enemy.GetPosEnemyY(i), _enemy.GetAiming(i), _enemy.GetArrow(i), _player.GetPosX(), _player.GetPosY(), _enemy.GetBulletDir(i));
		}
		else if (_enemy.GetType(i) == CHARA_TYPE_ENEMY7) {
			_enBullet.E7_ShootProcess(i, _enemy.GetType(i), _enemy.GetACont(i), _enemy.GetPosEnemyX(i), _enemy.GetPosEnemyY(i), _player.GetPosX(), _player.GetPosY(), _enemy.GetDetectB(), _enemy.GetGuideB(), _enemy.GetSnipeB(),_enemy.GetArrow(i), _enemy.GetBWstate(i));
		}
		_enBullet.CommonProcess(i, _player.GetPosX(), _player.GetPosY(), _player.GetPosW(), _player.GetPosH(), _enemy.GetBulletDir(i));

		for(int j = 0; j < E_BULLET_MAX; j++) {
			if(_mapData.IsHitCircleMap(_enBullet.GetHitCX(i, j), _enBullet.GetHitCY(i, j), _enBullet.GetHitCR(i, j)) != 0) {
				_enBullet.MapHitProcess(i, j);
			}
		}
		_enBullet.BossEffect(i);
	}
	_enBullet.BulletEffect();
	_enemy.EffectProcess();
}

void SceneTest::UiProcess() {

	_Ui.Process(_mapData.GetFloorNum(),_player.GetHp(),_mapData.GetFloorNum());

	
	if (_mapData.GetFloorNum() == 16) {
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (_enemy.GetType(i) == CHARA_TYPE_ENEMY7) {
				_Ui.BossHpEasingSet(_enemy.GetHp(i));
				_Ui.BossHpEasingProcess(_enemy.GetHp(i));
			}
		}
	}

	if(_mapData.GetFloorNum() >= 11) {

		for(int i = 0; i < 2; i++) {
			for(int j = 0; j < 2; j++) {
				if(i == j) { continue; }

				if(anim[i].num >= 300 * 2 -1) {
					anim[i].num = 0;
					anim[i].use = 0;
				}

				if(anim[i].num >= 180 * 2 - 1) {
					if(anim[j].use == 0) {
						anim[j].use = 1;
					}
				}
			}

			if(anim[i].use != 0) {
				if((anim[i].count++ % 2) == 0) {
					anim[i].num++;
					if(anim[i].count >= 100) {
						anim[i].count = 0;
					}
				}
			}
		}
	}
};

void SceneTest::CameraProcess() {


	float right = _player.GetPosX() + _player.GetPosW() / 2 + 100;
	float left = _player.GetPosX() + _player.GetPosW() / 2 - 100;
	float up = _player.GetPosY() - 100;
	float down = _player.GetPosY() + 200;

	// キャラ基準座標
	float flatY = _player.GetPosY();

	// 移動にかけるフレーム
	float flame = 8.00f;
	float s_flame = 10.00f; // スケールのほうに対応
	float wait = 18.00f;

	// プレイヤーの向きによるカメラ位置調整
	switch(_player.GetArrow()) {
	case 1: {
		if(gPad._gTrg[0] & PAD_INPUT_RIGHT) {
			_fcntX = 0;
		}
		if(_camX != right) {
			_camX = EasingOutQuad(_fcntX, _camX, right, flame);
			_fcntX += 0.01f;
			if(_fcntX >= flame) {
				_camX = right;
				_fcntX = flame;
			}
		}
		break;
	}
	case -1: {
		if(gPad._gTrg[0] & PAD_INPUT_LEFT) {
			_fcntX = 0;
		}
		if(_camX != left) {
			_camX = EasingOutQuad(_fcntX, _camX, left, flame);
			_fcntX += 0.01f;
			if(_fcntX >= flame) {
				_camX = left;
				_fcntX = flame;
			}
		}
		break;
	}
	}

	if(gPad._gTrg[0] & PAD_INPUT_UP || gPad._gTrg[0] & PAD_INPUT_DOWN || gPad._gRel[0] & PAD_INPUT_UP || gPad._gRel[0] & PAD_INPUT_DOWN) {
		_fcntY = 0.00f;
	}
	if(gPad._gKey[0] & PAD_INPUT_UP) {
		if(_camY != up) {
			_camY = EasingOutQuad(_fcntY, _camY, up, flame);
			_fcntY += 0.01f;
			if(_fcntY >= flame) {
				_camY = up;
				_fcntY = flame;
			}
		}
	}
	else if(gPad._gKey[0] & PAD_INPUT_DOWN) {
		if(_camY != down) {
			_camY = EasingOutQuad(_fcntY, _camY, down, flame);
			_fcntY += 0.01f;
			if(_fcntY >= flame) {
				_camY = down;
				_fcntY = flame;
			}
		}
	}
	else {
		if(_camY != flatY) {
			if(_fcntY <= flame) {
				_camY = EasingOutQuad(_fcntY, _camY, flatY, flame);
				_fcntY += 0.01f;
			}
		}
		else {
			_camY = flatY;
			_fcntY = 0.0f;
		}
	}

	float Zup = _fScale[_mapData.GetFloorNum()] + 0.50f;
	// プレイヤーが止まっているときにズームアップ
	if (_fInit != false) {
		if (gPad._gTrg[0] & PAD_INPUT_UP || gPad._gTrg[0] & PAD_INPUT_DOWN || gPad._gTrg[0] & PAD_INPUT_LEFT || gPad._gTrg[0] & PAD_INPUT_RIGHT || gPad._gTrg[0] & PAD_INPUT_3 || gPad._gTrg[0] & PAD_INPUT_8 || gPad._gRel[0] & PAD_INPUT_UP || gPad._gRel[0] & PAD_INPUT_DOWN || gPad._gRel[0] & PAD_INPUT_LEFT || gPad._gRel[0] & PAD_INPUT_RIGHT) {
			if (_isZoom == true || _inputS == _fScale[_mapData.GetFloorNum()]) {
				_scaleCnt = 0.00f;
			}
			_isZoom = false;
		}
		else if (gPad._gKey[0] & PAD_INPUT_LEFT || gPad._gKey[0] & PAD_INPUT_RIGHT || gPad._gKey[0] & PAD_INPUT_UP || gPad._gKey[0] & PAD_INPUT_DOWN) {
			_isZoom = false;
		}
		else {
			if (_isZoom != true) {
				_scaleCnt += 0.01f;
			}
			if (_scaleCnt >= wait) {
				_isZoom = true;
				_scaleCnt = 0.00f;
			}
		}

		if (_isZoom == false) {
			if (_inputS != _fScale[_mapData.GetFloorNum()]) {
				if (_scaleCnt <= s_flame) {
					_inputS = EasingLinear(_scaleCnt, _inputS, _fScale[_mapData.GetFloorNum()], s_flame);
					_scaleCnt += 0.01f;
				}
				else {
					_inputS = _fScale[_mapData.GetFloorNum()];
				}
			}
		}
		else if (_isZoom == true) {
			if (_inputS != Zup) {
				if (_scaleCnt <= s_flame) {
					_inputS = EasingLinear(_scaleCnt, _inputS, Zup, s_flame);
					_scaleCnt += 0.01f;
				}
				else {
					_inputS = Zup;
				}
			}
		}
	}

	VECTOR pos = VGet(_camX, _camY, 0);

	_cam.SetPos(pos);
	_cam.Setscale(_inputS);

	// カメラ処理を呼ぶ
	_cam.Process();
}




void SceneTest::Process() {

	if(GetASyncLoadNum() <= 5 && _image->GetLoadComplet() == 1) {
		StartMovie();
		_effect->CountEffect();
		_effect->DoEffect();
		if(_start_movie_use == 1 && GetMovieStateToGraph(_image->GetStart_Movie()) == 0) {

			VolumProcess();
		
			_Fade->FadeProcess();

			// 後に消す///////////////////////////////////////////////////////////////////////////////////
			//DebugFloorMove(_mapData.GetFloorNum());
			///////////////////////////////////////////////////////////////////////////////////////////////////
		
			if(_plBullet.GetCutIn() == 0) {
				if (_pause == 0) {

					FloorProcess(_mapData.GetFloorNum());

					BgmProcess();
					BgProcess();


					if (_stacnt[3] > 0) {
						CameraProcess();
					}

					if (_talk.GetScenario() == 0) {

						if (_stacnt[3] <= 0) {

							_portal.PortalProcess();

							UiProcess();

							PlProcess();

							EneProcess();

							// プレイヤーの弾処理をエネミーで終えたのでギミックへの当たり処理を行う（ドア）
							for (int i = 0; i < GIMMAX; i++) {
								for (int j = 0; j < BULLET_MAX; j++) {
									HitPlbGim(j, _plBullet.GetHitCX(j), _plBullet.GetHitCY(j), _plBullet.GetHitCR(j), _gimmick.GetGimRect(i));
								}
							}

							CameraProcess();

							if (_player.GetPotInv() <= 0 && _talk.GetProcessStop() == 0 && _player.GetHp() > 0) {
								if (gPad._gTrg[0] & PAD_INPUT_12) {
									_music->MakeSe(_image->Se[21]);
									_pause = 1;
								}
							}


						}
					}
				}
				//-----------------------------------ポーズ画面のプロセス
				
				_gPause->Process(&_pause, _player.GetHp(), _stock, _plBullet.GetRemainBulRF(), _plBullet.GetRemainBulTR(), _plBullet.GetRemainBulB(), _plBullet.GetRemainBulPW(), _plBullet.GetRemainBulPB(),
				_player.GetHpMax(), _plBullet.GetMaxBulRF(), _plBullet.GetMaxBulTR(), _plBullet.GetMaxBulB(), _plBullet.GetMaxBulPW(), _plBullet.GetMaxBulPB());
				
			}
			else if(_plBullet.GetCutIn() != 0) {
				int recutin = 0;
				if(CheckSoundMem(_image->Se[3]) != 1) {
					_music->MakeSe(_image->Se[3]);
					_music->MakeVoice(CUTIN_VOICE, RANDAM_TWO);
				}
				_cutin.SetCutin(_plBullet.GetCutIn());
				recutin = _cutin.Process();
				if(recutin == 1) {
					_plBullet.SetCutIn();
					_music->MakeSe(_image->Se[4]);
				}
			}

			if(_talk.GetProcessStop() != 0 || _talk.GetScenario() != 0 ||_Fade->GetScene_Change() != 0) {

				if (_Fade->CheckFadeMove() == 1 || _Fade->Fade.scene_change != 0) {
					_talk.Process(_Fade->GetScene_Change());
				}
			}
		}
	}
	else {
		_image->LoadingProcess();
	}
	
}

void SceneTest::UIDraw() {

	_Ui.SnowDraw(_mapData.GetFloorNum());

	if(_mapData.GetFloorNum() >= 13) {
		for(int i = 0; i < 2; i++) {
			DrawGraph(0, 0, _image->GetEffectCg(anim[i].num), true);
		}
	}
	if (_talk.GetProcessStop() == 0) {
		_Ui.Draw(_mapData.GetFloorNum());
	}
	_Ui.HpDraw(_player.GetHp(), _player.GetHpMax(), _stock);

	for (int i = 0; i < ENEMY_MAX; i++) {
		if (_enemy.GetType(i) == CHARA_TYPE_ENEMY7) {
			_Ui.BossHpDraw(_enemy.GetHp(i), _mapData.GetFloorNum(),_enemy.GetMaxHp(i));
		}
	}

	_Ui.WeaponSelect(_player.GetBulletType(), _player.GetBWP_select(), _player.GetReflectRelease(),
	_player.GetTrustRelease(), _plBullet.GetRemainBulRF(), _plBullet.GetRemainBulTR(), _plBullet.GetRemainBulB(), _plBullet.GetRemainBulPW(), _plBullet.GetRemainBulPB(), _plBullet.GetChargeMax());

}

void SceneTest::FloorDraw() {
	DrawGraph(0, 0, _image->Get_CgBg(_stageNum), FALSE);
};

void SceneTest::Draw() {

	if(GetASyncLoadNum() <= 5 && _image->GetLoadComplet() == 1) {
		if(GetMovieStateToGraph(_image->GetStart_Movie()) == 0 && _start_movie_use != 0) {

			// カメラのView行列で、画面上の座標を計算（View座標）
			MATRIX	mView = _cam.GetViewMatrix();

			FloorDraw();

			// マップ描画
			_Ui.SmockDraw(_mapData.GetFloorNum());

			// 足場
			{
				// 画像の中心位置が基底位置になるので、(0,0)が画像の左上になるように、ワールド座標を計算
				int bgSize_w = 3840, bgSize_h = 2160;
				VECTOR world = VGet(bgSize_w / 2, bgSize_h / 2, 0);
				MyDrawModiGraph(mView, world, 1.f, 0.f, bgSize_w, bgSize_h, _image->Get_Floor(_mapData.GetFloorNum()));
				if (_mapData.GetFloorNum() == 4 || _mapData.GetFloorNum() == 5) {
					 world = VGet((float)bgSize_w / 2 , (float)bgSize_h / 2 + 20, 0);
					 MyDrawModiGraph(mView, world, 1.f, 0.f, bgSize_w, bgSize_h, _image->Get_Floor(_mapData.GetFloorNum()));
				}
				
			}

			ArrowDraw(mView);
			
            _portal.PortalDraw(mView);

			_gimmick.Draw(mView);

			_plBullet.Draw(mView, _player.GetPosX(), _player.GetPosY());

			_enBullet.Draw(mView);

        	_enemy.Draw(mView, _enBullet.GetSnipeCnt(), _player.GetPosCX(), _player.GetPosCY());

			_enBullet.DrawTurret(mView);
			
			_effect->Draw(mView);
			

			if (_player.GetPotInv() <= 0 || _player.GetPotInv() > 30) {

				_player.Draw(mView);

				_player.EffectDraw(mView);

			}

			UIDraw();
			// ダメージ演出用の描画
			StagingDraw();

			B_OutBox();

			//--------------------------------------------ポーズ画面の描画
		
			_gPause->Draw(_pause);
			_gPause->BulletDraw(_pause, _player.GetHp(), _stock, _plBullet.GetRemainBulRF(), _plBullet.GetRemainBulTR(), _plBullet.GetRemainBulB(), _plBullet.GetRemainBulPW(), _plBullet.GetRemainBulPB(),
				_player.GetHpMax(), _plBullet.GetMaxBulRF(), _plBullet.GetMaxBulTR(), _plBullet.GetMaxBulB(), _plBullet.GetMaxBulPW(), _plBullet.GetMaxBulPB());
			_gPause->OptionDraw(_pause);

			_cutin.Draw();

			SinarioDraw();

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, _Fade->Fade._FadeIn);
			DrawBox(0, 0, SCREEN_W, SCREEN_H, _Fade->Fade.FadeColor, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		else{
			MovieDraw();
		}
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	else {
		_image->LoadingDraw();
	}
}