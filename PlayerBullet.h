/*****************************************************************//**
 * \file   PlayerBullet.h
 * \brief  プレイヤーの弾情報
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "gamemain.h"
#include "mymath.h"
#include "relay_point.h"


#define WHITE_BULLET     0
#define BLACK_BULLET     1
#define WPORTAL_BULLET   2
#define BPORTAL_BULLET   3 
#define REFLECT_BULLET   4
#define TRUST_BULLET     5
#define P_BULLET_KINDS   6   // 白0、黒1、ポータル黒2、ポータル白3、反射4、貫通5の計

#define P_BULLET_TYPE    4   // 挙動の種類

#define BULLET_SE_MAX    4

// 変更枠
#define BULLET_MAX       100 // 弾の枠（もしもの変更用に余裕を持っています） 
#define NORMAL_COOLTIME  10  // 銃の構えのディレイ（F）
#define NORMAL_COOLTIME_B 20  // 銃の連射のディレイ（F）
#define REFLECT_COOLTIME 30
#define TRUST_COOLTIME   60
const int CHARGE_CNT = 90;

// 弾の種類によるスピード
#define NORMAL_SPEED     40
#define REFLECT_SPEED    10
#define TRUST_SPEED      60

// 斜め撃ちの画像角度や三角関数計算に使用
#define DEG1             45
#define DEG2             90
#define DEG3             135
#define DEG4             225
#define DEG5             270
#define DEG6             315

	// 斜め撃ちの画像角度や三角関数計算に使用
const float  Rad1 = DegToRad(DEG1);
const float  Rad2 = DegToRad(DEG2);
const float  Rad3 = DegToRad(DEG3);
const float  Rad4 = DegToRad(DEG4);
const float  Rad5 = DegToRad(DEG5);
const float  Rad6 = DegToRad(DEG6);

#define BULLET_SHOT_POINT 125

class PlayerBullet
{
public:
	PlayerBullet();
	virtual ~PlayerBullet();
	
	void BulletInit(int index);
	void BWPjudge(int index, int BWPselect);
	void BulletDir(int index, int aiming, int arrow ,int speed ,int plx, int ply,int bullet_type,int reflect,int );       // 弾の情報付け

	void ShootProcess(int Select_Bullet, int BWPselect, int plx, int ply,int aiming , int arrow);
	int  MapHitProcess(int index, int maphit, int point, int aftermovemaphit);
	void Draw(MATRIX mview, int plx, int ply);
	void EffectProcess(int index);

	int GetRemainBulB() { return info_bullet.remainbullet[BLACK_BULLET]; }
	int GetRemainBulPW() { return info_bullet.remainbullet[WPORTAL_BULLET]; }
	int GetRemainBulPB() { return info_bullet.remainbullet[BPORTAL_BULLET]; }
	int GetRemainBulRF() { return info_bullet.remainbullet[REFLECT_BULLET]; }
	int GetRemainBulTR() { return info_bullet.remainbullet[TRUST_BULLET]; }
	int GetUsePortalW() { return info_bullet.usePortalW; }
	int GetUsePortalB() { return info_bullet.usePortalB; }
	int GetStanceType() { return info_bullet.stance_type;}

	int  GetMaxBulB() { return info_bullet.bulletmax[BLACK_BULLET]; }
	int GetMaxBulPW() { return info_bullet.bulletmax[WPORTAL_BULLET]; }
	int GetMaxBulPB() { return info_bullet.bulletmax[BPORTAL_BULLET]; }
	int GetMaxBulRF() { return info_bullet.bulletmax[REFLECT_BULLET]; }
	int GetMaxBulTR() { return info_bullet.bulletmax[TRUST_BULLET]; }

	int GetbulArrow(int index) { return p_bullet[index].arrow; }
	int GetBulletType(int index) { return p_bullet[index].state.bullettype; }
	int GetBulletUse(int index) { return p_bullet[index].usebullet; }
	int GetbulPortal(int index) { return p_bullet[index].state.isPortal; }
	int GetbulW(int index) { return p_bullet[index].state.isWhite; }
	int GetbulB(int index) { return p_bullet[index].state.isBlack; }
	int GetPosX(int index){return p_bullet[index].x;}
	int GetPosY(int index) { return p_bullet[index].y; }
	int GetXspeed(int index) { return p_bullet[index].Xspeed; }
	int GetYspeed(int index) { return p_bullet[index].Yspeed; }
	void SetDeray(int index,int set){info_bullet.delaycnt[index] = set;}
	int GetDeray(int index) { return info_bullet.delaycnt[index]; }
	int GetCharge() { return _power_charge; }
	int GetChargeMax() { return _power_max; }

	void ChargeRemainBul(int B_type) { info_bullet.remainbullet[B_type] = info_bullet.bulletmax[B_type]; }
	void AddBulletMaX(int B_type, int Add) { info_bullet.bulletmax[B_type] += Add; }
	void AddRemBullet(int B_type, int Add) { info_bullet.remainbullet[B_type] += Add; }

	void SetPortalW(int set) { info_bullet.usePortalW = set; }
	void SetPortalB(int set) { info_bullet.usePortalB = set; }

	int GetHitCX(int index) { return b_hitcircle[index].x; }
	int GetHitCY(int index) { return b_hitcircle[index].y; }
	int GetHitCR(int index) { return b_hitcircle[index].r; }

	void SetCutinUse() { cutin_use[0] = 0; cutin_use[1] = 0; }

	

	//カットイン関連
	int GetCutIn() { return cutin; }
	void SetCutIn() { cutin = 0; }



protected:
	struct BULLETINFO { // プログラム中で単一の情報、もしくは変わらない情報
		int usePortalB;   // 存在する？
		int usePortalW;   // 存在する？
		// 着弾した時の処理で白黒の処理はする
		// 個々に設定する場合は配列で増やしてください
		int w, h;               // 画像拡縮
		float cx, cy;
		int remainbullet[P_BULLET_KINDS];     // 現在の弾数 （通常弾は弾数制限なしだが、もしもの用意）
		int bulletmax[P_BULLET_KINDS];  // 最大弾数
		int limit[P_BULLET_TYPE];       // 画面に出る弾の限度
		int delaycnt[P_BULLET_TYPE];    // 連射速度
		int stance_type;
	};

	struct BULLETSTATE {   // 弾の属性
		int bullettype; // 通常：0,反射：1,貫通：２
		int isBlack;    // 黒い弾かどうか
		int isWhite;    // 白い弾かどうか
		int isPortal;   // ポータル弾か？上２つと併用して判定
		int cutin_black;//カットインを使用したかどうか
		int cutin_white;//カットインを使用したかどうか
	};

	struct P_BULLET { // 弾ごとに持っている情報

		BULLETSTATE state;      // 弾のステータス

		int type;
		int usebullet;  // この弾が使われているか 
		int	x, y;		// プレイヤー座標基準
		float hx, hy, hw, hh;   // 当たり判定用
		int Xspeed;     // 弾の速さX
		int Yspeed;     // 弾の速さY
		int arrow;      // 弾の向き、-1：左、1：右
		int aiming;     // プレイヤーのエイムの引き取り
		bool special;    // 一回だけ適用される特殊処理に関しての変数（反射・貫通）
		float angle_type; //玉のエフェクトのための角度を保存しておく関数
		
	};
	P_BULLET p_bullet[BULLET_MAX];
	BULLETINFO info_bullet;

	MYCIRCLE b_hitcircle[BULLET_MAX];
	
	int _power_charge;
	int _power_max;
	int count[100];
	int cutin;  //1:貫通　2：黒
	int cutin_use[2]; //０：白　１：黒
	bool _trg[4];

};				

