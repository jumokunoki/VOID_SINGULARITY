/*****************************************************************//**
 * \file   gamemainUI.cpp
 * \brief  ゲームメインUI
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "gamemainUI.h"
gamemainUI::gamemainUI() {

	hp.x = 20;
	hp.y = 20;
	hp.h = 60;
	hp.old = 100;
	hp.easing_count = 50;
    hp.easing_max_count = 50;
	hp.hold = 0;
	hp.back = 100;
	hp.delay = 0;
	hp.color = 0;

	boss_hp.x = 20;
	boss_hp.y = 20;
	boss_hp.h = 60;
	
	boss_hp.old = 100;
	boss_hp.easing_count = 00;
	boss_hp.easing_max_count = 180;
	boss_hp.hold = 0;
	boss_hp.back = 0;
	boss_hp.delay = 200;
	boss_hp.color = 0;

	for(int i = 0; i < 4; i++) {
		snow[i].x = 0;
		snow[i].y = -1080 - i * 540;
	}

	snow_anim.motaddcount = 0;
	snow_anim.motcount = 0;
	snow_anim.motseet = 60;
	snow_anim.motspeed = 4;

	Fade = 0.f;
	old_floor = -1;
	hang = 1;

	floor_x = 0;
	floor_y = 0;



	smock.motaddcount = 0;
	smock.motcount = 0;
	smock.motseet = 300;
	smock.motspeed = 3;
	smock.got = -1;

	min.w = 12;
	min.h = 13;
	big.w = 40;
	big.h = 45;
	weapon.w = 35;
	weapon.h = 35;

	weapon_handle[0].w = 190;
	weapon_handle[0].h = 128;
	weapon_handle[1].w = 250;
	weapon_handle[1].h = 167;
	portal_handle[0].w = 177;
	portal_handle[0].h = 142;
	portal_handle[1].w = 233;
	portal_handle[1].h = 200;

};

gamemainUI::~gamemainUI() {
	
};

void gamemainUI::PlayerHpEasingSet(int now_hp) {
	//プレイヤーがダメージを受けたときのイージングのセット
	if (now_hp != hp.old) {
		hp.easing_count = 0;
		hp.hold = hp.back;
		hp.easing_max_count = 50;
		if (now_hp > hp.old) {
			hp.color = 1;
		}
		else {
			hp.color = 0;
		}
	}
	hp.old = now_hp;
};

void gamemainUI::PlayerHpEasingProcess(int now_hp) {
	//プレイヤーがダメージを受けたときのイージングの処理
	if (hp.easing_count <= hp.easing_max_count) {
		hp.back = EasingLinear(hp.easing_count, hp.hold, now_hp, hp.easing_max_count);
		hp.easing_count++;
	}
	if (hp.delay > 0) {
		hp.delay--;
	}
	if (hp.back <= 0) {
		hp.back = 0;
	}
}

void gamemainUI::BossHpEasingSet(int now_hp) {
	//ボスがダメージを受けたときのイージングのセット
	if (now_hp != boss_hp.old) {
		if (boss_hp.easing_count >= boss_hp.easing_max_count) {
			boss_hp.hold = boss_hp.old;
		}
		else {
			boss_hp.hold = boss_hp.back;
		}

		if (now_hp >= 100) {
			boss_hp.easing_max_count = 180;
		}
		else {
			boss_hp.easing_max_count = 60;
		}
		boss_hp.easing_count = 0;
		boss_hp.color = 1;
	}
	boss_hp.old = now_hp;
};

void gamemainUI::BossHpEasingProcess(int now_hp) {
	//プレイヤーがダメージを受けたときのイージングの処理
	if (boss_hp.easing_count <= boss_hp.easing_max_count) {
		if (boss_hp.delay <= 180) {
			boss_hp.back = EasingOutSine(boss_hp.easing_count, boss_hp.hold, now_hp, boss_hp.easing_max_count);
			boss_hp.easing_count++;
		}
	}
	if (boss_hp.delay > 0) {
		boss_hp.delay--;
	}
	if (boss_hp.back <= 0) {
		boss_hp.back = 0;
	}
}

void gamemainUI::Process(int floor ,int now_hp,int boss_hp) {

	PlayerHpEasingSet(now_hp);

	PlayerHpEasingProcess(now_hp);

	//ステージ1で雪を降らせる処理
	for(int i = 0; i < 4; i++) {
		snow[i].y += 4;
		if(snow[i].y >= 1080) {
			snow[i].y = -1080;
		}
	}

	//フロアに入ったときの名前を出す処理
	if(floor != old_floor) {
		old_floor = floor;
		Fade = 1;
		hang = 1;
	}

	if(Fade > 0){
		Fade += 2.55 * hang;
		if(Fade >= 255) {
			hang *= -1;
		}

	}

	//煙を出す処理
	if(floor > 5 && floor < 10 || floor < 4 || floor == 16) {
		smock.motcount++;
		if(smock.motcount >= smock.motspeed) {
			smock.motcount = 0;
			switch(smock.got) {
			case 1:
				smock.motaddcount--;
				break;
			case -1:
				smock.motaddcount++;
				break;
			}
			if((smock.motaddcount % smock.motseet) == 0) {
				smock.motcount = 0;
				smock.got *= -1;
				switch(smock.got) {
				case 1:
					smock.motaddcount--;
					break;
				case -1:
					smock.motaddcount++;
					break;
				}
			}
		}
	}
};

void gamemainUI::SnowDraw(int floor) {
	//雪の描画
	if(floor <= 1) {
		for(int i = 0; i < 4; i++) {
			DrawGraph(snow[i].x, snow[i].y, _image->GetSnow_Handle(i * 10 + 5), true);
		}
	}
};

void gamemainUI::SmockDraw(int floor) {
	//煙の描画
	if(floor != 5 && floor != 10 && floor != 11 && floor != 12 && floor != 15) {
		DrawGraph(0, 0, _image->GetSmock_Handle(smock.motaddcount), true);
	}
};

void gamemainUI::Draw(int floor) {
	//フロアネームの描画
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fade);
	DrawGraph(floor_x,floor_y, _image->GetFloor_Handle(floor), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
};

void gamemainUI::HpDraw(int now_hp, int max_hp,int hp_stock) {
	//プレイヤーＨＰの描画
	if (now_hp < 0) { now_hp = 0; }
	float hp_gauge = now_hp;
	if (hp.delay > 0) {
		hp_gauge = 0;
	}

	DrawGraph(hp.x, hp.y - 30, _image->GetHp_Handle(), true);//フレーム
	DrawGraph(hp.x, hp.y - 30, _image->GetHp_Circle_Back(), true);//透過した円ゲージ
	DrawGraph(hp.x, hp.y - 30, _image->GetHp_Gauge_Back(), true);//透過した長いゲージ
	DrawCircleGauge(hp.x + 99, hp.y + 105 - 30 ,(12.5 * hp_stock), _image->GetHp_Circle_Top());//消えるエンゲージ
	//裏側のいーじんぐ
	DrawModiGraph(hp.x + 172 + 3, hp.y + 107, hp.x + 172 + 3 + (2.48 *  hp.back) , hp.y + 107 , hp.x + 172 + (2.48 *  hp.back), hp.y + 112 , hp.x + 172, hp.y + 112, _image->GetHp_Gauge_Easing(hp.color), true);
	DrawModiGraph(hp.x + 172 + 3, hp.y + 107, hp.x + 172 + 3 + (2.48 * hp_gauge) , hp.y + 107 , hp.x + 172 + (2.48 * hp_gauge), hp.y + 112 , hp.x + 172, hp.y + 112, _image->GetHp_Gauge_Top(), true);
		//w170 h 135　ゲージのずれ x 252 y 7
	
	//hpの描画
	int hp = now_hp ;
	int one = hp % 10;
	int ten = (hp / 10) % 10;
	int handred = (hp / 100) % 10;
	int min_w = min.w;//フォントの横の長さ
	int big_w = big.w;
	int min_x = 420;
	int min_y = 95;//125
	int big_x = 340;
	int big_y = 70;//98

	DrawGraph(big_x, big_y, _image->GetBig_Num_Handle(one), true);
	DrawGraph(big_x - big_w, big_y, _image->GetBig_Num_Handle(ten), true);
	DrawGraph(big_x - big_w * 2 , big_y, _image->GetBig_Num_Handle(handred), true);

	////maxhpの描画
	one = HP_MAX % 10;
	ten = (HP_MAX / 10) % 10;
	handred = (HP_MAX / 100) % 10;
	DrawGraph(min_x, min_y, _image->GetMin_Num_Handle(one), true);
	DrawGraph(min_x - min_w, min_y, _image->GetMin_Num_Handle(ten), true);
	DrawGraph(min_x - min_w * 2, min_y, _image->GetMin_Num_Handle(handred), true);

	//通常∞　貫通20　反射50　黒10　白ポ10　黒ポ10
}

void gamemainUI::BossHpDraw(int now_hp, int floor,int max_hp) {

	if (floor == 16) {
		//ボスフレームの描画
		DrawGraph((1920 - 1200) / 2, 950, _image->GetBoss_Hp_Frame(), true);


		float hp[4];
		float easing_hp[4];
		for (int i = 0; i < 4; i++) {
			hp[i] = now_hp;
			easing_hp[i] = boss_hp.back;

			//描画順をずらすための処理
			hp[i] -= (float)25 * max_hp * i / 100 ;
			easing_hp[i] -= (float)25 * max_hp * i / 100 ;

			//もろもろのはみ出さないようにする処理
			if (hp[i] <= 0) {
				hp[i] = 0;
				easing_hp[i] = 0;
			}
			//ｈｐゲージはみ出さないようにする処理
			if (now_hp > (float)25 * max_hp * (i + 1) / 100 ) {
				hp[i] = (float)25 * max_hp / 100;
			}

			//削れているところのはみ出さないようにする処理
			if (boss_hp.back > (float)25 * max_hp * (i + 1) / 100 ) {
				easing_hp[i] = (float)25 * max_hp / 100 ;
			}

			//登場するときの処理
			if (boss_hp.delay > 0) {
				hp[i] = (float)boss_hp.back;
				hp[i] -= (float)25 * i * max_hp / 100 ;
				if (hp[i] >= (float)25 * max_hp / 100 ){
					hp[i] = (float)25 * max_hp / 100;
				}
				else if(hp[i] <= 0){
					hp[i] = 0;
				}
				easing_hp[i] = 0;
			}

			//ボスゲージの描画
			//青→緑→黄色→赤の順番で描画
			DrawModiGraph(410, 1027, 410 + (easing_hp[i] * 4 * 1100 / max_hp), 1027, 410 + (easing_hp[i] * 4 * 1100 / max_hp), 1032, 410, 1032, _image->GetBoss_Hp_Gauge_Back(), true);
			DrawModiGraph(410, 1027, 410 + (hp[i] * 4 * 1100 / max_hp), 1027, 410 + (hp[i] * 4 * 1100 / max_hp), 1032, 410, 1032, _image->GetBoss_Hp_Gauge(i), true);

		}
	}
};

void gamemainUI::BalletNumDraw(int x, int y, int bullet_num) {
	//球の数の描画
	int bullet = bullet_num;
	if(bullet_num <= 0) { bullet = 0; }
	int one = bullet % 10;
	int ten = (bullet / 10) % 10;

	int w = weapon.w;//フォントの横の長さ

	DrawGraph(x, y, _image->GetWeapon_Num_Handle(one), true);
	DrawGraph(x - w + 10, y, _image->GetWeapon_Num_Handle(ten), true);


}

void gamemainUI::WeaponSelect(int weapon_type, int bullet_attribute,int reflect_release, int trust_release, 
	                          int reflect, int trust, int black, int Pwhite, int Pblack,int bullet_charge) {
	//選択されている武器や弾の描画

	   
//-----------------------------------------------------------------
	int x = 30;//40
	int y = 40;
	int gap = -30;
	int num_x = 32;
	int num_y = -34;

		//銃が選択された時のアイコン
		switch(weapon_type) {
		case 0: {
			DrawGraph(480 + x + gap, y, _image->GetWeapon_Normal_Handle(1), true);//ノーマル
			DrawGraph(398 + num_x - weapon.w + weapon_handle[1].w, 150 - 12, _image->GetInf_B(), true);
			   if(reflect_release != 0) {
			   DrawGraph(720 + x, y, _image->GetWeapon_Reflect_Handle(1), true);
			   BalletNumDraw(720 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h , reflect);
			   }
			   if(trust_release != 0) {
			   DrawGraph(960 + x, y, _image->GetWeapon_Trust_Handle(1), true);
			   BalletNumDraw(960 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h , trust);
			   }
			DrawGraph(1200+ x, y, _image->GetWeapon_Black_Handle(1), true);
			BalletNumDraw(1200 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h , black);
			break;
		}
		case 1: {
			DrawGraph(480 + x, y, _image->GetWeapon_Normal_Handle(0), true);
			DrawGraph(468 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h, _image->GetInf_B(), true);
			   if(reflect_release != 0) {
			   DrawGraph(720 + x + gap, y, _image->GetWeapon_Reflect_Handle(2), true);//リフレクト
			   BalletNumDraw(720 + num_x - weapon.w + weapon_handle[1].w - 70, 150 -12, reflect);
			   }
			   if(trust_release != 0) {
				   DrawGraph(960 + x, y, _image->GetWeapon_Trust_Handle(1), true);
				   BalletNumDraw(960 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h, trust);
			   }
			DrawGraph(1200 + x, y, _image->GetWeapon_Black_Handle(1), true);
			BalletNumDraw(1200 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h , black);
			break;
		}
		case 2: {
			DrawGraph(480 + x, y, _image->GetWeapon_Normal_Handle(0), true);
			DrawGraph(468 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h, _image->GetInf_B(), true);
			if(reflect_release != 0) {
				DrawGraph(720 + x, y, _image->GetWeapon_Reflect_Handle(1), true);
				BalletNumDraw(720 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h, reflect);
			}
			if(trust_release != 0) {
				DrawGraph(960 + x + gap, y, _image->GetWeapon_Trust_Handle(2), true);//トラスト
				BalletNumDraw(960 + num_x - weapon.w + weapon_handle[1].w - 70, 150 - 12, trust);
			}
			DrawGraph(1200 + x, y, _image->GetWeapon_Black_Handle(1), true);
			BalletNumDraw(1200 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h , black);
			break;
		}
		case 3: {
			DrawGraph(480 + x, y, _image->GetWeapon_Normal_Handle(0), true);
			DrawGraph(468 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h, _image->GetInf_B(), true);
			if(reflect_release != 0) {
				DrawGraph(720 + x, y, _image->GetWeapon_Reflect_Handle(1), true);
				BalletNumDraw(720 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h, reflect);
			}
			if(trust_release != 0) {
				DrawGraph(960 + x, y, _image->GetWeapon_Trust_Handle(1), true);
				BalletNumDraw(960 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h, trust);
			}
			DrawGraph(1200 + x + gap, y, _image->GetWeapon_Black_Handle(2), true);//黒
			BalletNumDraw(1200 + num_x - weapon.w + weapon_handle[1].w - 70, 150-12 , black);
			break;
		}
		default:{
			DrawGraph(480 + x, y, _image->GetWeapon_Normal_Handle(0), true);
			DrawGraph(468 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h, _image->GetInf_B(), true);
			if(reflect_release != 0) {
				DrawGraph(720 + x, y, _image->GetWeapon_Reflect_Handle(1), true);
				BalletNumDraw(720 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h, reflect);
			}
			if(trust_release != 0) {
				DrawGraph(960 + x, y, _image->GetWeapon_Trust_Handle(1), true);
				BalletNumDraw(960 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h, trust);
			}
			DrawGraph(1200 + x, y, _image->GetWeapon_Black_Handle(1), true);
			BalletNumDraw(1200 + num_x - weapon.w + weapon_handle[0].w - 9, 150 - weapon.h, black);
			break;
		}
	    }
//-------------------------------------------------------------------
		//黒白のポータル弾の選択された時のアイコン
		int lock = bullet_attribute;
		if (bullet_charge == 0) {
			lock = 0;
		}
		switch (lock) {
		case 0: {//選択なし
			DrawGraph(1440 + x, y, _image->GetWeapon_White_Portal_Handle(0), true);
			DrawGraph(1468 - weapon.w + portal_handle[0].w - 14, 160 - weapon.h + 5, _image->GetInf_B(), true);
			DrawGraph(1620 + x, y, _image->GetWeapon_Black_Portal_Handle(0), true);
			DrawGraph(1648 - weapon.w + portal_handle[0].w - 14, 160 - weapon.h + 5, _image->GetInf_B(), true);
			break;
		}
		case 1: {
				DrawGraph(1410 + x, y, _image->GetWeapon_White_Portal_Handle(1), true);//白
				DrawGraph(1438 - weapon.w + portal_handle[1].w - 35, 160, _image->GetInf_B(), true);
				DrawGraph(1620 + x, y, _image->GetWeapon_Black_Portal_Handle(0), true);
				DrawGraph(1648 - weapon.w + portal_handle[0].w - 14, 160 - weapon.h + 5, _image->GetInf_B(), true);
			break;
		}
		case 2: {
			DrawGraph(1440 + x, y, _image->GetWeapon_White_Portal_Handle(0), true);
			DrawGraph(1468 - weapon.w + portal_handle[0].w - 14, 160 - weapon.h + 5, _image->GetInf_B(), true);
			DrawGraph(1590 + x, y, _image->GetWeapon_Black_Portal_Handle(1), true);//黒
			DrawGraph(1618 - weapon.w + portal_handle[1].w - 35, 160, _image->GetInf_B(), true);
			break;
		}
		}
		
//--------------------------------------------------------------------
		//解放前の状態
		if(reflect_release == 0) {
			DrawGraph(720 + x, y, _image->GetWeapon_Reflect_Handle(0), true);
		}
		if(trust_release == 0) {
			DrawGraph(960 + x, y, _image->GetWeapon_Trust_Handle(0), true);
		}
//--------------------------------------------------------------------
		
}