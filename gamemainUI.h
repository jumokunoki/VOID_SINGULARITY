/*****************************************************************//**
 * \file   gamemainUI.h
 * \brief  UI
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#pragma once
#include "Player.h"
#include "PlayerBullet.h"
#include "mymath.h"
class gamemainUI
{
public:
	gamemainUI();
	~gamemainUI();

	void Process(int floor, int now_hp,int boss_hp);
	void PlayerHpEasingSet(int now_hp);
	void PlayerHpEasingProcess(int now_hp);
	void BossHpEasingSet(int now_hp);
	void BossHpEasingProcess(int now_hp);
	void SnowDraw(int floor);
	void Draw(int floor);
	void SmockDraw(int floor);
	void HpDraw(int now_hp, int max_hp, int stock);
	void BossHpDraw(int now_hp, int floor,int max_hp);
	void BalletNumDraw(int x, int y, int num);
	void WeaponSelect(int weapon_type, int bullet_attribute, int reflect_release, int trust_release, int reflect, int trust, int black, int Pwhite, int Pblack, int bullet_charge);

	void SetDelay() { hp.delay = 60; }

protected:
	Player _player;
	PlayerBullet _bullet;

	int floor_x, floor_y;
	float Fade;
	int old_floor;
	int hang;

	//銃の画像ハンドル
#define WEAPON_MAX 6
#define HP_MAX 100


	struct HP {
		int x, y;   //hpの位置
		int h;      //hpバーの高さ
		//↓イージング
		int old;
		int easing_count;
		int easing_max_count;
		float hold;
		float back;
		int delay;
		int color;
	};
	struct SIZE {
		int w, h;
	};
	struct Box {
		int x, y;
	};
	Box snow[4];

	
	MOTION snow_anim;
	MOTION smock;

	SIZE min;
	SIZE big;
	SIZE weapon;
	SIZE weapon_handle[2];
	SIZE portal_handle[2];
	HP hp;
	HP boss_hp;

};

