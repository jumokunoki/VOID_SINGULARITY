/*****************************************************************//**
 * \file   Player.h
 * \brief  プレイヤーの情報
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "character.h"
#include "DxLib.h"
#include "mymath.h"
#include "PlayerBullet.h"
#include "relay_point.h"

class Player
{
public:
	Player();
	virtual ~Player();

	void Gravity();
	void DetectGravity(int Gjudge);
	void PotInvProcess();
	void MoveProcess();
	void PosHitSynchro();
	void HitObj(HITSLIDE HitObj, MYRECT_PLUS enemy);
	void AimProcess(int remRF, int remTR, int remBR, int remPW, int remPB,int deray);
	void DamageProcess(int hit);
	void EffectDraw(MATRIX mview);
	void Draw(MATRIX mView);
	void AddIT();
	void DoFrameCount(int stock);
	void SetMotSpeed();
	void PortalMoveSet(int PorX, int PorY);
	void PortalMoveProcess();
	void ChengeFrameCount(int handred, int ten, int one, int oldmot);
	// ステージ遷移による武器の開放処理
	void ReleaseRef() { _Re_release = 1; }
	void ReleaseTr() { _Tr_release = 1; }

	// ゲッター・セッター
	int GetcharaType() { return _gPlayer.type; }
	int GetPosX() { return _gPlayer.x; }
	int GetPosY() { return _gPlayer.y; }
	int GetPosW() { return _gPlayer.w; }
	int GetPosH() { return _gPlayer.h; }
	int GetPosCX() { return _gPlayer.x+135+30; }
	int GetPosCY() { return _gPlayer.y+75+100; }
	MYRECT_PLUS GetRect() { return _gPlayer.hit; }
	float GetGravity() { return _gPlayer.gravity; }
	int GetRunSpeed() { return _gPlayer.Rspeed; }
	int GetArrow() { return _gPlayer.arrow; }
	int GetAiming() { return _gPlayer.aiming; }
	int GetBWP_select() { return b_select.BWPselect; }
	int GetBulletType() { return b_select.bulletType; }
    bool GetD_judge() { return _S_damjudge; }
	bool GetI_judge() { return _invijudge; }
	int GetInviT() { return _invincible_time; }
	int GetHitSX() { return _hitslideX; }
	int GetHitSY() { return _hitslideY; }
	int GetPotInv() { return _gPlayer.Portal_invincibility; }
	int GetPorDel() { return _gPlayer.Portal_delete; }
	VECTOR GetStaPoint() { return _start_point; }

	void ReSetBulletType() {b_select.bulletType = 0; }

	void SetPosX(int x) { _gPlayer.x = x; }
	void SetPosY(int y) { _gPlayer.y = y; }
	void SetD_judge() { _S_damjudge = false; }
	void SetPotInv(int index) { _gPlayer.Portal_invincibility = index; }
	void SetPorDel() { _gPlayer.Portal_delete = 0; }
	void SetTerminal(VECTOR terminal) { _terminal = terminal; }

	void AddPosX(int x) { _gPlayer.x += x; }
	void AddPosY(int y) { _gPlayer.y += y; }
	void AddMaxHP() { _gPlayer.maxhp += 100; }
	void HealHP(){ _gPlayer.hp += 100;}

	//UI
	int GetHp() { return _gPlayer.hp; }
	int GetHpMax() { return _gPlayer.maxhp; }
	int GetReflectRelease() { return _Re_release; }
	int GetTrustRelease() { return _Tr_release; }

	void SetOldMotion() { _gPlayer.oldmot = 0 + _gPlayer.motten * 10 + 0; }
	int  GetMotAdd() { return _gPlayer.motaddnum; }
	int  GetMotionH() { return _gPlayer.mothandred; }
	int  GetMotionT() { return _gPlayer.motten; }
	int  GetMotionO() { return _gPlayer.motone; }
	int  GetOldMotion() { return _gPlayer.oldmot; }
	void SetHpToMax() { _gPlayer.hp  = 100; }
	void SetDamage(int damage) { _gPlayer.hp -= damage; }
	void SetRecovery(int recovery) { _gPlayer.hp += recovery; }

protected:
	// プレイやーの情報
	struct CHARA {
		int		 type;		// キャラタイプ。 CHARA_TYPE_xxxx
		int		 x, y;		// 配置座標
		int      w, h;       // 地形判定用
		MYRECT_PLUS hit;    // 当たり判定用
		int		 hx, hy, hw, hh;		// ダメージ当たり判定
		int		 hp, maxhp;	// 体力/最大体力
		
		int		 arrow;		// 向き。左 = -1, 右 = 1
		int      Rspeed;     //　走るスピード
	
		int		 useGravity;	// 重力処理をするなら1, 落ちないなら0
		float	 gravity;	// 重力による加速値
		int		 stand;		// 床フラグ。着地していたら1
		int      isAim;
		int      aiming;     // 銃の照準。arrowと併用。arrow(0,1)*5方向で10方向アニメーションと弾の方向を設定 0:横1:斜め上2:斜め下3:上4:下
	
		int     Portal_invincibility;
		int     Portal_delete;

		int		 motaddnum;		// モーションID。 MOTION_xxxx_xxxxx
		int      mothandred;
		int      motten;
		int      motone;
		int		 motcnt;		// モーションカウンタ。0～
		int      oldmot;     // 前のモーション
		int      motsheet;   // モーションシート
		int      motspeed;   // モーションのスピード
		int      falling_mot;
		int      loop;
		//int		animcnt;	// アニメーションカウンタ。0～
	};
	struct CHARA _gPlayer;
	

	struct B_SELECT {
		int BWPselect;    // 白(通常)・黒・黒ポータル・白ポータル
		int bulletType;   // 通常・反射・貫通・黒
	};
	B_SELECT b_select;

	struct PORTAL_MOVE {
		int x, y;
		int count, max_count;
	};
	PORTAL_MOVE port;
	int jampcount;
	int waitcount;
	// 何かに当たった時の反動
	int _hitslideX;
	int _hitslideY;
	// 無敵時間判定用
	bool _invijudge;
	int _invincible_time;
	int _Re_release;     // 反射の解放
	int _Tr_release;     // 貫通の解放
	bool _S_damjudge;   // 画面演出用（ダメージ時）
	MYRECT_PLUS _none = { 0,0,0,0,0,0,0,0 };
	VECTOR _start_point; // 照準線の始点
	VECTOR _terminal;   // 照準線の終端
};

