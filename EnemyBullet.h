/*****************************************************************//**
 * \file   EnemyBullet.h
 * \brief  エネミーの弾情報
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "gamemain.h" 
#include "PlayerBullet.h"
#include "EnemyBase.h"

 // 角度などはプレイヤーバレットから引っ張ってくる

#define E_BULLET_MAX    10

// 基本的にエネミーの番号に対応
#define E_BULLET_0      0
#define E_BULLET_1      1
#define E_BULLET_2      2
#define E_BULLET_3      3
#define E_BULLET_4      4
#define E_BULLET_5      5
#define E_BULLET_6      6
#define E_BULLET_7      7
#define E_BULLET_8      8
#define E_BULLET_9      9
#define E_BULLET_10     10

#define COOLTIME1       10
#define COOLTIME2       20
#define COOLTIME3       30
#define COOLTIME4       40
#define COOLTIME5       50
#define COOLTIME6       60
#define COOLTIME7       1200
#define COOLTIME8       180

#define B_SPEED0        10
#define B_SPEED1        20
#define B_SPEED2        40
#define B_SPEED3        60
#define B_SPEED4		50

class EnemyBullet
{
public:
	EnemyBullet();
	virtual ~EnemyBullet();

	void BulletInit(int index, int bullet);
	void BulletDir(int index, int bullet, int aiming, int arrow, int speed, int bullet_type, float direction);

	void E_ShootProcess(int index, int type, int A_cont, int eneX, int eneY, int aiming, int arrow, int chara_x, int chara_y, float turret_dir);
	void E7_ShootProcess(int index, int type, int A_cont, int eneX, int eneY, int chara_x, int chara_y, bool detect, bool guide, bool snipe,int arrow,int BWstate);
	void GuideCurveProcess(int index, int bullet, float chara_x, float chara_y, float chara_w, float chara_h);
	void CommonProcess(int index, float chara_x, float chara_y, float chara_w, float chara_h, float dir);
	void BossEffect(int index);
	void BulletEffect();

	void MapHitProcess(int index, int bullet);
	void DrawTurret(MATRIX mview);
	void Draw(MATRIX mview);

	int GetHitCX(int index, int bullet) { return b_hitcircle[index][bullet].x; }
	int GetHitCY(int index, int bullet) { return b_hitcircle[index][bullet].y; }
	int GetHitCR(int index, int bullet) { return b_hitcircle[index][bullet].r; }
	int GetBWstate(int index, int bullet){return e_bullet[index][bullet].BWstate;}
	int GetType(int index, int bullet) { return e_bullet[index][bullet].bullettype; }
	int GetSnipeCnt() { return _boss_parameter[3]; }

	

protected:

	struct BULLETINFO { // プログラム中で単一の情報、もしくは変わらない情報
		int w, h;               // 画像拡縮
		int bulletmax[ENEMY_MAX];  // 最大弾数
		int limit[ENEMY_MAX];       // 画面に出る弾の限度（例外として0に通常の構え、3に通常の連射）
		int delaycnt[ENEMY_MAX][2];    // 連射速度 (発射までのカウントと連射の間隔のディレイ)
	};

	int _boss_parameter[100];   // ボスの複数の弾(ディレイ1、ディレイ２、リミットは3つでひとまとめなので３つ使う)
	//1.2.3が誘導弾用にカウント使用、3.4.5がスナイプ用にカウント使用、6.7が誘導弾の曲がるまでのクールタイム,
	//弾ごとの曲がった回数のカウントに使用する


	struct E_BULLET { // 弾ごとに持っている情報

		int type;
		int bullettype; // もしもの時につけるエネミーごとのタイプ
		bool isuse;  // この弾が使われているか 
		int	x, y;		// プレイヤー座標基準
		float cx, cy;
		int Xspeed;     // 弾の速さX
		int Yspeed;     // 弾の速さY
		int arrow;      // 弾の向き、-1：左、1：右
		int BWstate;    // 弾が撃たれた時のエネミーの状態（白・黒）

		int aiming;     // プレイヤーのエイムの引き取り
		bool special;    // 一回だけ適用される特殊処理に関しての変数（反射・貫通）

		float direction; //エネミー2で使わせてもらっている角度を格納する変数です　大変申し訳ございません。
	};
	E_BULLET e_bullet[ENEMY_MAX][E_BULLET_MAX];
	BULLETINFO info_bullet;

	MYCIRCLE b_hitcircle[ENEMY_MAX][E_BULLET_MAX];
	
	MOTION bullet_anim;
};

