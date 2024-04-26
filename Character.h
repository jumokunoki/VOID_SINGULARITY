/*****************************************************************//**
 * \file   Character.cpp
 * \brief  キャラクター情報
 * 
 * \author 奈良充樹
 * \date   August 2023
 *********************************************************************/

#pragma once


 // モーション番号。0番からの通し番号であること
 // プレイヤー用
#define	MOTION_R_STAND		0
#define	MOTION_L_STAND		1
#define	MOTION_R_RUN		2
#define	MOTION_L_RUN		3
#define	MOTION_R_ATTACK		4
#define	MOTION_L_ATTACK		5
#define	MOTION_R_DAMAGE		6
#define	MOTION_L_DAMAGE		7
#define	MOTION_R_JUMP_UP	8
#define	MOTION_L_JUMP_UP	9
#define	MOTION_R_JUMP_DOWN	10
#define	MOTION_L_JUMP_DOWN	11
// アイテム用
#define	MOTION_ITEM_POINT_0_NORMAL	12	// 光：青
#define	MOTION_ITEM_POINT_1_NORMAL	13	// 光：緑
#define	MOTION_ITEM_POINT_2_NORMAL	14	// 光：赤
#define	MOTION_ITEM_POINT_3_NORMAL	15	// 光：黄


// アニメーションパターン用定義
// 配列の番号は間を空けて余裕を持って設定しています
// プレイヤー
#define	PT_STAND		0		//  0～ 20枚
#define	PT_RUN		20		//  20～ 6枚
#define	PT_ATTACK	30		//  30～ 7枚
#define	PT_DAMAGE	40		//  40～ 1枚
#define	PT_JUMP_UP	50		//  50～ 2枚
#define	PT_JUMP_DOWN	60		//  60～ 2枚

#define	_PT_CHARA_ALLNUM_	    200		// 全パターン枚数

//モーションパターン
#define _PT_CHARA_ATTACK_NORMAL  0
#define _PT_CHARA_ATTACK_REFLECT 1
#define _PT_CHARA_ATTACK_TRUST   2
#define _PT_CHARA_ATTACK_BLACK   3
#define _PT_CHARA_STAND_LEFT     4
#define _PT_CHARA_STAND_RIGHT    5
#define _PT_CHARA_RUN_LEFT       6
#define _PT_CHARA_RUN_RIGHT      7
#define _PT_CHARA_JAMP_LEFT      8
#define _PT_CHARA_JAMP_RIGHT     9


#define _PT_ENEMY_ALLNUM    10

// キャラタイプID　
#define	CHARA_TYPE_NONE		0	// キャラ無し（use=0的に使用）
#define	CHARA_TYPE_PLAYER	1	// プレイヤー
#define	CHARA_TYPE_ENEMY1	2	// エネミー1
#define	CHARA_TYPE_ENEMY2	3	// エネミー2
#define	CHARA_TYPE_ENEMY3	4	// エネミー3
#define	CHARA_TYPE_ENEMY4	5	// エネミー4
#define	CHARA_TYPE_ENEMY5	6	// エネミー5
#define	CHARA_TYPE_ENEMY6	7	// エネミー6
#define	CHARA_TYPE_ENEMY7	8	// エネミー7
#define	CHARA_TYPE_ENEMY8	9	// エネミー8
#define	CHARA_TYPE_ENEMY9	10	// エネミー9

#define BULLET_TYPE_PLAYER  20
#define BULLET_TYPE_ENEMY   30
// エネミーごとに弾の何かが違ったら以下を使用（当たり判定等）
#define BULLET_TYPE_ENEMY1  31
#define BULLET_TYPE_ENEMY2  32
#define BULLET_TYPE_ENEMY3  33
#define BULLET_TYPE_ENEMY4  34
#define BULLET_TYPE_ENEMY5  35
#define BULLET_TYPE_ENEMY6  36
#define BULLET_TYPE_ENEMY7  37
#define BULLET_TYPE_ENEMY8  38
#define BULLET_TYPE_ENEMY9  39
#define BOSS_HIT1           40
#define BOSS_HIT2           41
#define BOSS_HIT3			43

#define	ITEM_TYPE_AMMO		50	// アイテム：回復箱
#define	ITEM_TYPE_TRE		51	// アイテム：トレジャーボックス
#define	ITEM_TYPE_HEAL		52	// アイテム：ヒールカプセル
#define	ITEM_TYPE_A_MATTER	53	// アイテム：反物質
#define	ITEM_TYPE_LEVER		54	// アイテム：レバー
#define	OBJ_TYPE_DOOR	    60	// オブジェクト：ジャーナル	

#define SEARCH_AREA1        70
#define SEARCH_AREA2        71 
#define SEARCH_AREA3        72

#define Black_Hole			777 
#define White_Hole			888
#define Fix_Black_Hole			444 
#define Fix_White_Hole			666

#define	CHARA_MAX		100		// キャラ数

// 当たり判定用のそれぞれの幅
#define PLAYER_W    60
#define PLAYER_H    200
#define P_BULLET_W  30
#define P_BULLET_H  15
#define ENEMY_W      80
#define ENEMY_H     200
#define ENEMY_TWO_W 100
#define ENEMY_TWO_H 100
#define E_BULLET_W  30
#define E_BULLET_H  15

