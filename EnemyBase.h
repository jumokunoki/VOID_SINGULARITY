/*****************************************************************//**
 * \file   EnemyBase.h
 * \brief  エネミー関連の基
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "character.h"
#include "gamemain.h"
#include "DxLib.h"
#include "mymath.h"
#include "relay_point.h"

// 敵の最大数
constexpr int  ENEMY_MAX     = 30;
// 画像の大きさ
constexpr int  GRAPH_W       = 200;
constexpr int  GRAPH_H       = 200;
constexpr int  BOSS_GRAPH_WH = 600;

 //　当たり判定の矩形計算時、加算する数値
constexpr int  E1_HIT_X  = 60;
constexpr int  E2_HIT_XY = 50;
constexpr int  E2_HIT_WH = 100;
constexpr int  E3_HIT_X  = 50;
constexpr int  E3_HIT_Y  = 50;
constexpr int  E3_HIT_W  = 720;
constexpr int  E3_HIT_H  = 270;

// 上の翼の大きさ
constexpr int wing1_W = 320;
constexpr int wing1_H = 150;
// 下の翼の大きさ
constexpr int wing2_W = 530;
constexpr int wing2_H = 250;
// 尾翼
constexpr int wing3_W = 580;
constexpr int wing3_H = 70;

// 振幅調整
constexpr int velocity_adjustment = 60;

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	int AddEnemy(int type, int x, int y, int arrow);
	int  HitProcess(MYCIRCLE_PLUS hit, int index, int hp);
	void PosSynchro(int index);
	void AnnihilationEffect(int index);
	void AllAddBlack();
	void CommonProcess(MYCIRCLE_PLUS hit, int index, int iswhite, int isblack,int hp);
	void Process(int index, int chara_x, int chara_y,HITSLIDE search, HITSLIDE search2, int map_w, int map_h);
	void DirReset(int index);
	void PosFix(int index, int mapHit);
	void Draw(MATRIX mview, int snipecnt, int plx, int ply);

	void EffectProcess();

	// 計算処理
	void RadCalculateE7(int index, int chara_x, int chara_y, HITSLIDE search, HITSLIDE search2);  // エネミー7用のラジアン計算

	// ボスの挙動(Enemy_BossMotion.cpp)
	void BossMotion(int index, int chara_x, int chara_y, HITSLIDE search, HITSLIDE search2, int map_w, int map_h);
	void BossPosChange(int index);

// 初期化
	void CharaInit(int index);
	void BossInit();
	void AllInit();

// ゲッター・セッター
	int GetPosEnemyX(int index) { return _enemy[index].pos.x; }
	int GetPosEnemyY(int index) { return _enemy[index].pos.y; }
	int GetArrow(int index) { return _enemy[index].arrow; }
	int GetAiming(int index) { return _enemy[index].aiming; }
	int GetMX(int index) { return _enemy[index].movespeed * _enemy[index].arrow; }
	int GetType(int index) { return _enemy[index].type; }
	// 当たり判定の矩形
	MYRECT_PLUS GetRect_P(int index) { return _enemy[index].hit; }
	MYRECT_PLUS GetRect_BOSSF(int index) { return _variable.boss_hit[0]; }
	MYRECT_PLUS GetRect_BOSSS(int index) { return _variable.boss_hit[1]; }
	MYRECT_PLUS GetRect_BOSST(int index) { return _variable.boss_hit[2]; }
	// サーチの判定の矩形(ボスは併用)
	MYRECT_PLUS GetRectSearch(int index) { return _enemy[index].search; }
	MYRECT_PLUS GetRectSearchBoss() { return _variable.search; }
	int GetACont(int index) { return _enemy[index].action_control; }
	int GetCnt(int index) { return _enemy[index].action_cnt; }
	bool GetDetectB() { return _variable.isdetectB; }
	bool GetGuideB() { return _variable.isguideB; }
	bool GetSnipeB() { return _variable.issnipeB; }
    int  GetBWstate(int index);

	void SetArrow(int index, int arrow) { _enemy[index].arrow = arrow; }
	void SetAiming(int index, int aiming) { _enemy[index].aiming = aiming; }

	void AddPosX(int x, int index) { _enemy[index].pos.x += x; }
	void AddPosY(int y, int index) { _enemy[index].pos.y += y; }

	//シーン切り替え用
	int GetHp(int index) { return _enemy[index].hp; }
	int GetMaxHp(int index) { return _enemy[index].maxhp; }
	float GetBulletDir(int index) { return _enemy[index].direction; }
	
protected:

	struct ENEMY {
		int		type;		// キャラタイプ。 CHARA_TYPE_xxxx
		VECTOR  pos;        // 位置決定
		MYRECT  graph;		// 画像座標・大きさ
		MYRECT_PLUS hit;    // 当たり判定用
		MYRECT_PLUS search; // サーチ用矩形
		int     cx, cy;		// キャラの中心位置
		int		init_pointY;// 奇数エネミーの下ずれを修正するために用いる変数（AddEnemyした際のY座標） 
		int     base_point; // キャラの行動範囲の基点
		int		hp;	        // 体力
		int     maxhp;      //　最大の体力
	
		bool     isuse;
		int     action_control;   // 行動の管理番号
		int     action_cnt;       // 行動時のディレイ
		bool    isAim;      // プレイヤーが範囲内に入ってきたときON
		float   direction;  // いろいろ使う角度
		float   angle;      // ボスエネミーの射程角
		int		arrow;		// 向き。左 = -1, 右 = 1
		int     aiming;     // 銃の照準。arrowと併用。arrow(0,1)*5方向で10方向アニメーションと弾の方向を設定 0:横1:斜め上2:斜め下3:上4:下

		int bomber_se;//爆発のセット
		int bomber_count;//爆発までのカウント
		int detection_sound;//探知音

		int     movespeed;  //　走るスピード
		bool    isWhite;    //  敵に白が付与されているか
		bool    isBlack;    //  敵に黒が付与されているか

		// 画像・アニメーション関連
		int		motId;		// モーションID。 MOTION_xxxx_xxxxx
		int		motcnt;		// モーションカウンタ。0～
		int		animcnt;	// アニメーションカウンタ。0～
	};

	ENEMY _enemy[ENEMY_MAX];

	struct BOSS {
		// ボス用のパラメータ
		MYRECT_PLUS boss_hit[3];    // BOSS当たり判定用
		MYRECT_PLUS search; // 追加サーチ用矩形
		float   angle[2];      // ボスエネミーの射程角
		bool    isdetectB;	   // タレット弾の発射判定
		bool    isguideB;	   // 誘導弾の発射判定
		bool    issnipeB;      // スナイプ弾の発射判定
		int     easingcnt;     // イージングに要するカウント
		int     turncnt;       // 画面内で切り返すときのカウント
		float   targetX;       // 画面外に出るときの目標座標X
		float   targetY;       // 画面外に出るときの目標座標Y
	};

	BOSS _variable;

	struct MOTION_EFFECT {
		int motaddcount;
		int motcount;
		int motspeed;
		int motseet;
	};
	MOTION_EFFECT tui;
	MOTION_EFFECT jet;
	ALPHA boss_effect;
	
	int _contlCnt[5];			// エネミーの行動を時間制御するためのカウント
	MYRECT_PLUS _none = { 0,0,0,0,0,0,0,0 };
};
