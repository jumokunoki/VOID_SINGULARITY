/*****************************************************************//**
 * \file   Image.cpp
 * \brief  画像情報
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "Image.h"
#include <iostream>
#include "dxlib.h"


Image::Image() {
	ImageInit();
	for(int i = 0; i < 4; i++) {
		loading_add[i] = i * -12.5f;
		count[i] = 0;
		order[i] = 0;
	}
	load_complet = 0;
	title_complet = 0;
	main_complet = 0;
};

void Image::ImageInit() {
	for (int i = 0; i < 2; i++) {

		_cgBullet[i] = 0;
		_graHeal[i] = 0;
		_graA_Matter[i] = 0;
		_graAmmo[i] = 0;
		clear_font_target[i] = 0;
		weapon_normal_handle[i] = 0;
		weapon_white_portal_handle[i] = 0;
		weapon_black_portal_handle[i] = 0;
		hp_gauge_easing[i] = 0;
		sound_switch[i] = 0;
		for (int j = 0; j < 32; j++) {
			cgCutin[i][j] = 0;
		}
	}
	for (int i = 0; i < 3; i++) {
		after_clear_font[i] = 0;
		weapon_reflect_handle[i] = 0;
		weapon_trust_handle[i] = 0;
		weapon_black_handle[i] = 0;
		yes_handle[i] = 0;
		no_handle[i] = 0;
		screen_effect[i] = 0;
		for (int j = 0; j < 2; j++) {
			gauge_border[i][j] = 0;
		}
		for (int j = 0; j < 3; j++) {
			select_box_handle[i][j] = 0;
		}
	}
	for (int i = 0; i < 4; i++) {
		boss_hp_gauge[i] = 0;
		loading_gauge[i] = 0;
		loading_handle[i] = 0;
		cutin_on_handle[i] = 0;
		cutin_off_handle[i] = 0;
	}
	for (int i = 0; i < 5; i++) {
		_graTre[i] = 0;
		blur[i] = 0;
	}
	for (int i = 0; i < 6; i++) {
		box_handle[i] = 0;
		_cgBg[i] = 0;
	}
	for (int i = 0; i < 9; i++) {
		_item_log[i] = 0;
	}
	for (int i = 0; i < 10; i++) {
		_cgEnemy[i] = 0;
		big_num_handle[i] = 0;
		min_num_handle[i] = 0;
		weapon_num_handle[i] = 0;
		number_min[i] = 0;
		number_big[i] = 0;
		effectblack[i] = 0;
		effectwhite[i] = 0;
	}
	for (int i = 0; i < 14; i++) {
		FaceHandle[i] = 0;
	}
	for (int i = 0; i < 17; i++) {
		floor_handle[i] = 0;
	}
	for (int i = 0; i < 18; i++) {
		_floor[i] = 0;
	}
	for (int i = 0; i < 20; i++) {
		black_portal_handle[i] = 0;
		white_portal_handle[i] = 0;
		BodyHandle[i] = 0;
		enemy_bullet_handle[i] = 0;
	}
	for (int i = 0; i < 24; i++) {
		tutorial_handle[i] = 0;
	}
	for (int i = 0; i < 30; i++) {
		enemy_one_effect[i] = 0;
	}
	for (int i = 0; i < 36; i++) {
		_gra_arrow[i] = 0;
	}
	for (int i = 0; i < 50; i++) {
		_graDoor[i] = 0;
	}
	for (int i = 0; i < 60; i++) {
		snow_handle[i] = 0;
	}
	for (int i = 0; i < 90; i++) {
		hand_effect[i] = 0;
	}
	for (int i = 0; i < 195; i++) {
		for (int j = 0; j < 61; j++) {
			_cgPlayer[i][j] = 0;
		}
	}
	for (int i = 0; i < 300; i++) {
		smock_handle[i] = 0;
	}
	for (int i = 0; i < 600; i++) {
		effectcg[i] = 0;
	}
	for (int i = 0; i < EFFECT_TYPE_MAX; i++) {
		for (int j = 0; j < EFFECT_SHEETS_MAX; j++) {
			cgEffect[i][j] = 0;
		}
	}

	clear_cg = 0;
	_graSwitch[0] = 0;
	_graSwitch[1] = 0;
	text_handle = 0;
	text_arrow = 0;
	hp_handle = 0;
	hp_circle_back = 0;
	hp_circle_top = 0;
	hp_gauge_back = 0;
	hp_gauge_top = 0;
	Option_Bg = 0;
	pause_handle = 0;
	charahandle = 0;
	controle_Handle = 0;
	parcent_handle = 0;
	name_handle = 0;
	parcent_gauge = 0;
	purpose_handle = 0;
	loading_Bg = 0;
	loading_chara = 0;
	staff_roll = 0;
	start_movie = 0;
	boss_hp_frame = 0;
	boss_hp_gauge_back = 0;
	inf_B = 0;
	inf_S = 0;
	inf_W = 0;
	gauge_handle = 0;
	gauge_ber = 0;
	end_bg = 0;
	skip = 0;

	//-------------------------------------------
	for (int i = 0; i < 4; i++) {
		scenario_Bgm[i] = 0;
	}
	for (int i = 0; i < 8; i++) {
		Bgm[i] = 0;
	}
	for (int i = 0; i < 16; i++) {
		chara_voice[i] = 0;
	}
	for (int i = 0; i < 31; i++) {
		Se[i] = 0;
	}
};

Image::~Image() {
	for (int i = 0; i < 2; i++) {
		DeleteGraph(_cgBullet[i]);
		DeleteGraph(_graHeal[i]);
		DeleteGraph(_graA_Matter[i]);
		DeleteGraph(_graAmmo[i]);
		DeleteGraph(clear_font_target[i]);
		DeleteGraph(weapon_normal_handle[i]);
		DeleteGraph(weapon_white_portal_handle[i]);
		DeleteGraph(weapon_black_portal_handle[i]);
		DeleteGraph(hp_gauge_easing[i]);
		DeleteGraph(sound_switch[i]);
		for (int j = 0; j < 32; j++) {
			DeleteGraph(cgCutin[i][j]);
		}
	}
	for (int i = 0; i < 3; i++) {
		DeleteGraph(after_clear_font[i]);
		DeleteGraph(weapon_reflect_handle[i]);
		DeleteGraph(weapon_trust_handle[i]);
		DeleteGraph(weapon_black_handle[i]);
		DeleteGraph(yes_handle[i]);
		DeleteGraph(no_handle[i]);
		
		for (int j = 0; j < 2; j++) {
			DeleteGraph(gauge_border[i][j]);
		}
		for (int j = 0; j < 3; j++) {
			DeleteGraph(select_box_handle[i][j]);
		}
	}
	for (int i = 0; i < 4; i++) {
		DeleteGraph(boss_hp_gauge[i]);
		DeleteGraph(loading_gauge[i]);
		DeleteGraph(loading_handle[i]);
		DeleteGraph(cutin_on_handle[i]);
		DeleteGraph(cutin_off_handle[i]);
		DeleteGraph(screen_effect[i]);
	}
	for (int i = 0; i < 5; i++) {
		DeleteGraph(_graTre[i]);
		DeleteGraph(blur[i]);
	}
	for (int i = 0; i < 6; i++) {
		DeleteGraph(box_handle[i]);
		DeleteGraph(_cgBg[i]);
	}
	for (int i = 0; i < 9; i++) {
		DeleteGraph(_item_log[i]);
	}
	for (int i = 0; i < 10; i++) {
		DeleteGraph(_cgEnemy[i]);
		DeleteGraph(big_num_handle[i]);
		DeleteGraph(min_num_handle[i]);
		DeleteGraph(weapon_num_handle[i]);
		DeleteGraph(number_min[i]);
		DeleteGraph(number_big[i]);
		DeleteGraph(effectblack[i]);
		DeleteGraph(effectwhite[i]);
	}
	for (int i = 0; i < 14; i++) {
		DeleteGraph(FaceHandle[i]);
	}
	for (int i = 0; i < 17; i++) {
		DeleteGraph(floor_handle[i]);
	}
	for (int i = 0; i < 18; i++) {
		DeleteGraph(_floor[i]);
	}
	for (int i = 0; i < 20; i++) {
		DeleteGraph(black_portal_handle[i]);
		DeleteGraph(white_portal_handle[i]);
		DeleteGraph(BodyHandle[i]);
	
	}
	for (int i = 0; i < 24; i++) {
		DeleteGraph(tutorial_handle[i]);
	}	
	for (int i = 0; i < 30; i++) {
		DeleteGraph(enemy_one_effect[i]);
	}
	for (int i = 0; i < 36; i++) {
		DeleteGraph(_gra_arrow[i]);
	}
	for (int i = 0; i < 50; i++) {
		DeleteGraph(_graDoor[i]);
	}
	for (int i = 0; i < 60; i++) {
		DeleteGraph(snow_handle[i]);
	}
	for (int i = 0; i < 90; i++) {
		DeleteGraph(hand_effect[i]);
	}
	for (int i = 0; i < 195; i++) {
		for (int j = 0; j < 61; j++) {
			DeleteGraph(_cgPlayer[i][j]);
		}
	}
	for (int i = 0; i < 300; i++) {
		DeleteGraph(smock_handle[i]);
	}
	for (int i = 0; i < 600; i++) {
		DeleteGraph(effectcg[i]);
	}
	for(int i = 0; i < EFFECT_TYPE_MAX; i++) {
		for(int j = 0; j < EFFECT_SHEETS_MAX; j++) {
			DeleteGraph(cgEffect[i][j]);
		}
	}

	DeleteGraph(clear_cg);
	DeleteGraph(_graSwitch[0]);
	DeleteGraph(_graSwitch[1]);
	DeleteGraph(text_handle);
	DeleteGraph(text_arrow);
	DeleteGraph(hp_handle);
	DeleteGraph(hp_circle_back);
	DeleteGraph(hp_circle_top);
	DeleteGraph(hp_gauge_back);
	DeleteGraph(hp_gauge_top);
	DeleteGraph(Option_Bg);
	DeleteGraph(pause_handle);
	DeleteGraph(charahandle);
	DeleteGraph(controle_Handle);
	DeleteGraph(parcent_handle);
	DeleteGraph(name_handle);
	DeleteGraph(parcent_gauge);
	DeleteGraph(purpose_handle);
	DeleteGraph(loading_Bg);
	DeleteGraph(loading_chara);
	DeleteGraph(staff_roll);
	DeleteGraph(start_movie);
	DeleteGraph(boss_hp_frame);
	DeleteGraph(boss_hp_gauge_back);
	DeleteGraph(inf_B);
	DeleteGraph(inf_S);
	DeleteGraph(inf_W);
	DeleteGraph(gauge_handle);
	DeleteGraph(gauge_ber);
	DeleteGraph(end_bg);
	DeleteGraph(skip);
	//-------------------------------------------
	for (int i = 0; i < 4; i++) {
		DeleteSoundMem(scenario_Bgm[i]);
	}
	for (int i = 0; i < 8; i++) {
		DeleteSoundMem(Bgm[i]);
	}
	for (int i = 0; i < 16; i++) {
		DeleteSoundMem(chara_voice[i]);
	}
	for (int i = 0; i < 31; i++) {
		DeleteSoundMem(Se[i]);
	}

};

void Image::TitleLoad() {
	if(title_complet == 0) {
		//星があがるエフェクト
		char size[128];
		for(int i = 0; i < 600; i++) {
			sprintf(size, "res/title_animetion2/TITLE_AE_1_00%03d.png", i);
			effectcg[i] = LoadGraph(size);
		}

		for(int i = 0; i < 300; i++) {
			sprintf(size, "res/smock/MA_CROWD_5_%05d.png", i);
			smock_handle[i] = LoadGraph(size);
		}

		for (int i = 0; i < 91; i++) {
			sprintf(size, "res/hand_effect/TI_EFFECT_3_%05d.png", i);
			hand_effect[i] = LoadGraph(size);
		}

		//ゲームクリア
		clear_cg = LoadGraph("res/ending/End_illust.png");
		clear_font_target[0] = LoadGraph("res/ending/End_Font_3.png");
		clear_font_target[1] = LoadGraph("res/ending/End_Font_4.png");
		after_clear_font[0] = LoadGraph("res/ending/End_Font_1.png");
		after_clear_font[1] = LoadGraph("res/ending/End_Font_2.png");
		after_clear_font[2] = LoadGraph("res/ending/End_Font_5.png");

		//ローディング
		loading_Bg = LoadGraph("res/UI_LO/loading.png");
		loading_chara = LoadGraph("res/UI_LO/loading_chara.png");
		loading_gauge[0] = LoadGraph("res/UI_LO/loading_gauge_1.png");
		loading_gauge[1] = LoadGraph("res/UI_LO/loading_gauge_2.png");
		loading_gauge[2] = LoadGraph("res/UI_LO/loading_gauge_3.png");
		loading_gauge[3] = LoadGraph("res/UI_LO/loading_gauge_4.png");
		//loading
		loading_handle[0] = LoadGraph("res/loading_gauge_1.png");
		loading_handle[1] = LoadGraph("res/loading_gauge_2.png");
		loading_handle[2] = LoadGraph("res/loading_gauge_3.png");
		loading_handle[3] = LoadGraph("res/loading_gauge_4.png");

		//オプション
		Option_Bg = LoadGraph("res/UI_GS/Game_Setting.png");

		gauge_handle = LoadGraph("res/UI_GS/Game_Setting_gauge1.png");
		gauge_ber = LoadGraph("res/UI_GS/Game_Setting_button_1.png");
		gauge_border[0][0] = LoadGraph("res/UI_GS/Game_Setting_SE_1.png");
		gauge_border[0][1] = LoadGraph("res/UI_GS/Game_Setting_SE_2.png");
		gauge_border[1][0] = LoadGraph("res/UI_GS/Game_Setting_BGM_1.png");
		gauge_border[1][1] = LoadGraph("res/UI_GS/Game_Setting_BGM_2.png");
		gauge_border[2][0] = LoadGraph("res/UI_GS/Game_Setting_VOICE_1.png");
		gauge_border[2][1] = LoadGraph("res/UI_GS/Game_Setting_VOICE_2.png");

		sound_switch[0] = LoadGraph("res/UI_GS/Game_Setting_icon.png");
		sound_switch[1] = LoadGraph("res/UI_GS/Game_Setting_icon2.png");

		cutin_off_handle[0] = LoadGraph("res/UI_GS/Game_Setting_cutin_off1.png");
		cutin_off_handle[1] = LoadGraph("res/UI_GS/Game_Setting_cutin_off2.png");
		cutin_off_handle[2] = LoadGraph("res/UI_GS/Game_Setting_cutin_off3.png");
		cutin_off_handle[3] = LoadGraph("res/UI_GS/Game_Setting_cutin_off4.png");

		cutin_on_handle[0] = LoadGraph("res/UI_GS/Game_Setting_cutin_on4.png");
		cutin_on_handle[1] = LoadGraph("res/UI_GS/Game_Setting_cutin_on3.png");
		cutin_on_handle[2] = LoadGraph("res/UI_GS/Game_Setting_cutin_on2.png");
		cutin_on_handle[3] = LoadGraph("res/UI_GS/Game_Setting_cutin_on1.png");

		staff_roll = LoadGraph("res/staffroll/staffroll.mp4");
		title_complet = 1;
	}
};

void Image::GameMainLoad() {
	if(main_complet == 0) {
		SetUseASyncLoadFlag(TRUE);
		char size[128];
		//スタートムービー
		start_movie = LoadGraph("res/start_movie/movie2.mp4");
		//チュートリアル
		for (int i = 0; i < 25; i++) {
			sprintf(size,"res/tutorial/description%02d.png", i + 1);
			tutorial_handle[i] = LoadGraph(size);
		}
		//エネミー
		_cgEnemy[0] = LoadGraph("res/enemy/enemy_robot_1_2.png");
		_cgEnemy[1] = LoadGraph("res/enemy/enemy_robot_1_2_yellow.png");
		_cgEnemy[2] = LoadGraph("res/enemy/enemy_robot_1_2_red.png");
		_cgEnemy[3] = LoadGraph("res/enemy_2/enemy_turret_base/enemy_turret1_base.png");
		_cgEnemy[4] = LoadGraph("res/enemy_2/enemy_turret_gun/enemy_turret1_gun.png");
		_cgEnemy[5] = LoadGraph("res/enemy_2/enemy_turret_base/enemy_turret3_base.png");
		_cgEnemy[6] = LoadGraph("res/enemy_2/enemy_turret_gun/enemy_turret3_gun.png");
		_cgEnemy[7] = LoadGraph("res/enemy_2/enemy_turret_base/enemy_turret2_base.png");
		_cgEnemy[8] = LoadGraph("res/enemy_2/enemy_turret_gun/enemy_turret2_gun.png");
		_cgEnemy[9] = LoadGraph("res/enemy_boss/enemy_boss1_fix.png");

		LoadDivGraph("res/bullet_effect/enemy_effect_black_sheet.png", 10, 10, 1, 200, 200, effectblack);
		LoadDivGraph("res/bullet_effect/enemy_effect_white_sheet.png", 10, 10, 1, 200, 200, effectwhite);
		LoadDivGraph("res/bullet_effect/enemy_effect_2_00000_sheet.png", 30, 30, 1, 200, 200, enemy_one_effect);

		//エネミーの弾
		_cgBullet[0] = LoadGraph("res/Bullet_W.png");
		_cgBullet[1] = LoadGraph("res/Bullet_B.png");
		missil       = LoadGraph("res/missile_3.png");
		LoadDivGraph("res/enemy/enmybullet.png", 20, 20, 1, 100, 100, enemy_bullet_handle);

		//ギミック
		_graAmmo[0] = LoadGraph("res/gimmick/OB_AMMO.png");
		_graAmmo[1] = LoadGraph("res/gimmick/OB_AMMO_EFFECT_1.png");
		_graTre[0] = LoadGraph("res/gimmick/OB_CONTAINER1_green.png");
		_graTre[1] = LoadGraph("res/gimmick/OB_CONTAINER1_blue.png");
		_graTre[2] = LoadGraph("res/gimmick/OB_CONTAINER1_pink_w.png");
		_graTre[3] = LoadGraph("res/gimmick/OB_CONTAINER1_pink_b.png");
		_graTre[4] = LoadGraph("res/gimmick/OB_CONTAINER1_WB.png");
		_graTre[5] = LoadGraph("res/gimmick/OB_CONTAINER1_EFFECT_1.png");
		_graHeal[0] = LoadGraph("res/gimmick/OB_CAPSULE_HP.png");
		_graHeal[1] = LoadGraph("res/gimmick/OB_CAPSULE_EFFECT_3.png");
		_graA_Matter[0] = LoadGraph("res/gimmick/OB_CAPSULE_B.png");
		_graA_Matter[1] = LoadGraph("res/gimmick/OB_CAPSULE_EFFECT_3.png");
		_graSwitch[0] = LoadGraph("res/gimmick/OB_Link_Switch_01.png");
		_graSwitch[1] = LoadGraph("res/gimmick/OB_Link_Switch_02.png");
		LoadDivGraph("res/gimmick/MA_OB_DOOR_3_00000_sheet.png", 50, 10, 5, 100, 400, _graDoor);
		//ポータル
		LoadDivGraph("res/bullet_effect/portal_white_sheet_sai.png", 20, 5, 4, 200, 200, white_portal_handle);
		LoadDivGraph("res/bullet_effect/portal_black_sheet_sai.png", 20, 5, 4, 200, 200, black_portal_handle);
		LoadDivGraph("res/bullet_effect/effect_white_hole_2_00000_sheet.png", 41, 41, 1, 200, 200, white_portal_effect_handle);
		LoadDivGraph("res/bullet_effect/effect_black_hole_2_00000_sheet.png", 41, 41, 1, 200, 200, black_portal_effect_handle);
		//プレイヤー
		//左向き     
		LoadDivGraph("res/motion/standing/PC_IDLE_1_B.png", 31, 31, 1, 300, 300, &_cgPlayer[0][0]);                      //立ち状態　　　角度なし
		LoadDivGraph("res/motion/running/PC_RUN_B.png", 22, 22, 1, 300, 300, &_cgPlayer[10][0]);                         //走り状態　　　角度なし
		LoadDivGraph("res/motion/jump/jump_B.png", 31, 31, 1, 300, 300, &_cgPlayer[20][0]);                              //ジャンプ状態　角度なし
		LoadDivGraph("res/motion/gun/nomal_gun/left/PC_ATK_N_180.png", 21, 21, 1, 300, 300, &_cgPlayer[30][0]);          //通常弾　　　　正面
		LoadDivGraph("res/motion/gun/nomal_gun/left/PC_ATK_N_135.png", 21, 21, 1, 300, 300, &_cgPlayer[31][0]);          //通常弾　　　　斜め上
		LoadDivGraph("res/motion/gun/nomal_gun/left/PC_ATK_N_90_B.png", 21, 21, 1, 300, 300, &_cgPlayer[32][0]);         //通常弾　　　　上
		LoadDivGraph("res/motion/gun/nomal_gun/left/PC_ATK_N_225.png", 60, 20, 3, 300, 300, &_cgPlayer[33][0]);          //通常弾　　　　斜め下
		LoadDivGraph("res/motion/gun/reflex/left/PC_ATK_R_180.png", 60, 20, 3, 300, 300, &_cgPlayer[40][0]);             //反射弾　　　　正面
		LoadDivGraph("res/motion/gun/reflex/left/PC_ATK_R_135.png", 60, 20, 3, 300, 300, &_cgPlayer[41][0]);             //反射弾　　　　斜め上
		LoadDivGraph("res/motion/gun/reflex/left/PC_ATK_R_90_B.png", 60, 20, 3, 300, 300, &_cgPlayer[42][0]);            //反射弾　　　　上
		LoadDivGraph("res/motion/gun/reflex/left/PC_ATK_R_225.png", 60, 20, 3, 300, 300, &_cgPlayer[43][0]);             //反射弾　　　　斜め下    //
		LoadDivGraph("res/motion/gun/white_gun/left/PC_ATK_A_180.png", 60, 20, 3, 300, 300, &_cgPlayer[50][0]);          //貫通弾　　　　正面
		LoadDivGraph("res/motion/gun/white_gun/left/PC_ATK_A_135.png", 60, 20, 3, 300, 300, &_cgPlayer[51][0]);          //貫通弾　　　　斜め上
		LoadDivGraph("res/motion/gun/white_gun/left/PC_ATK_A_90_B.png", 60, 20, 3, 300, 300, &_cgPlayer[52][0]);         //貫通弾　　　　上
		LoadDivGraph("res/motion/gun/white_gun/left/PC_ATK_A_225.png", 60, 20, 3, 300, 300, &_cgPlayer[53][0]);          //貫通弾　　　　斜め下 
		LoadDivGraph("res/motion/gun/white_gun/left/PC_ATK_B_270_B.png", 60, 20, 3, 300, 300, &_cgPlayer[54][0]);        //貫通弾　　　　下 
		LoadDivGraph("res/motion/gun/black_nomal_gun/left/PC_ATK_B_180.png", 60, 20, 3, 300, 300, &_cgPlayer[60][0]);    //黒弾　　　　　正面
		LoadDivGraph("res/motion/gun/black_nomal_gun/left/PC_ATK_B_135.png", 60, 20, 3, 300, 300, &_cgPlayer[61][0]);    //黒弾　　　　　斜め上
		LoadDivGraph("res/motion/gun/black_nomal_gun/left/PC_ATK_B_90_B.png", 60, 20, 3, 300, 300, &_cgPlayer[62][0]);   //黒弾　　　　　上
		LoadDivGraph("res/motion/gun/black_nomal_gun/left/PC_ATK_B_225.png", 60, 20, 3, 300, 300, &_cgPlayer[63][0]);    //黒弾　　　　　斜め下 
		LoadDivGraph("res/motion/gun/black_nomal_gun/left/PC_ATK_B_270_B.png", 60, 20, 3, 300, 300, &_cgPlayer[64][0]);  //黒弾　　　　　下 
		LoadDivGraph("res/motion/gun/nomal_run/nomal_mae_run_B.png", 22, 11, 2, 300, 300, &_cgPlayer[70][0]);            //走り通常弾　　正面
		LoadDivGraph("res/motion/gun/nomal_run/nomal_45up_run_B.png", 22, 11, 2, 300, 300, &_cgPlayer[71][0]);         //走り通常弾　　斜め上
		LoadDivGraph("res/motion/gun/nomal_run/nomal_up_run_B.png", 22, 11, 2, 300, 300, &_cgPlayer[72][0]);             //走り通常弾　　上
		LoadDivGraph("res/motion/gun/nomal_run/nomal_45down_run_B.png", 22, 11, 2, 300, 300, &_cgPlayer[73][0]);           //走り通常弾　　斜め下 
		LoadDivGraph("res/motion/gun/reflex_run/reflex_mae_run_B.png", 22, 11, 2, 300, 300, &_cgPlayer[80][0]);          //走り反射弾　　正面
		LoadDivGraph("res/motion/gun/reflex_run/reflex_45up_run_B.png", 22, 11, 2, 300, 300, &_cgPlayer[81][0]);       //走り反射弾　　斜め上
		LoadDivGraph("res/motion/gun/reflex_run/reflex_up_run_B.png", 22, 11, 2, 300, 300, &_cgPlayer[82][0]);           //走り反射弾　　上
		LoadDivGraph("res/motion/gun/reflex_run/reflex_45down_run_B.png", 22, 11, 2, 300, 300, &_cgPlayer[83][0]);         //走り反射弾　　斜め下 

		//右向き														   	   
		LoadDivGraph("res/motion/standing/PC_IDLE_1_F.png", 31, 31, 1, 300, 300, &_cgPlayer[100][0]);    //立ち状態　　　角度なし
		LoadDivGraph("res/motion/running/PC_RUN_F.png", 22, 22, 1, 300, 300, &_cgPlayer[110][0]);    //走り状態　　　角度なし
		LoadDivGraph("res/motion/jump/jump_F.png", 31, 31, 1, 300, 300, &_cgPlayer[120][0]);    //ジャンプ状態　角度なし
		LoadDivGraph("res/motion/gun/nomal_gun/right/PC_ATK_N_0.png", 21, 21, 1, 300, 300, &_cgPlayer[130][0]);    //通常弾　　　　正面
		LoadDivGraph("res/motion/gun/nomal_gun/right/PC_ATK_N_45.png", 21, 21, 1, 300, 300, &_cgPlayer[131][0]);    //通常弾　　　　斜め上
		LoadDivGraph("res/motion/gun/nomal_gun/right/PC_ATK_N_90.png", 21, 21, 1, 300, 300, &_cgPlayer[132][0]);    //通常弾　　　　上
		LoadDivGraph("res/motion/gun/nomal_gun/right/PC_ATK_N_315.png", 60, 20, 3, 300, 300, &_cgPlayer[133][0]);    //通常弾　　　　斜め下
		LoadDivGraph("res/motion/gun/reflex/right/PC_ATK_R_0.png", 60, 20, 3, 300, 300, &_cgPlayer[140][0]);    //反射弾　　　　正面
		LoadDivGraph("res/motion/gun/reflex/right/PC_ATK_R_45.png", 60, 20, 3, 300, 300, &_cgPlayer[141][0]);    //反射弾　　　　斜め上
		LoadDivGraph("res/motion/gun/reflex/right/PC_ATK_R_90_F.png", 60, 20, 3, 300, 300, &_cgPlayer[142][0]);    //反射弾　　　　上
		LoadDivGraph("res/motion/gun/reflex/right/PC_ATK_R_315.png", 60, 20, 3, 300, 300, &_cgPlayer[143][0]);    //反射弾　　　　斜め下
		LoadDivGraph("res/motion/gun/white_gun/right/PC_ATK_A_0.png", 60, 20, 3, 300, 300, &_cgPlayer[150][0]);    //貫通弾　　　　正面
		LoadDivGraph("res/motion/gun/white_gun/right/PC_ATK_A_45.png", 60, 20, 3, 300, 300, &_cgPlayer[151][0]);    //貫通弾　　　　斜め上
		LoadDivGraph("res/motion/gun/white_gun/right/PC_ATK_A_90_F.png", 60, 20, 3, 300, 300, &_cgPlayer[152][0]);    //貫通弾　　　　上
		LoadDivGraph("res/motion/gun/white_gun/right/PC_ATK_A_315.png", 60, 20, 3, 300, 300, &_cgPlayer[153][0]);    //貫通弾　　　　斜め下
		LoadDivGraph("res/motion/gun/white_gun/right/PC_ATK_B_270_F.png", 60, 20, 3, 300, 300, &_cgPlayer[154][0]);    //貫通弾　　　　下
		LoadDivGraph("res/motion/gun/black_nomal_gun/right/PC_ATK_B_0.png", 60, 20, 3, 300, 300, &_cgPlayer[160][0]);    //黒弾　　　　　正面
		LoadDivGraph("res/motion/gun/black_nomal_gun/right/PC_ATK_B_45.png", 60, 20, 3, 300, 300, &_cgPlayer[161][0]);    //黒弾　　　　　斜め上
		LoadDivGraph("res/motion/gun/black_nomal_gun/right/PC_ATK_B_90_F.png", 60, 20, 3, 300, 300, &_cgPlayer[162][0]);    //黒弾　　　　　上
		LoadDivGraph("res/motion/gun/black_nomal_gun/right/PC_ATK_B_315.png", 60, 20, 3, 300, 300, &_cgPlayer[163][0]);    //黒弾　　　　　斜め下
		LoadDivGraph("res/motion/gun/black_nomal_gun/right/PC_ATK_B_270_F.png", 60, 20, 3, 300, 300, &_cgPlayer[164][0]);    //黒弾　　　　　下
		LoadDivGraph("res/motion/gun/nomal_run/nomal_mae_run_F.png", 22, 11, 2, 300, 300, &_cgPlayer[170][0]);            //走り通常弾　　正面
		LoadDivGraph("res/motion/gun/nomal_run/nomal_45up_run_F.png", 22, 11, 2, 300, 300, &_cgPlayer[171][0]);         //走り通常弾　　斜め上
		LoadDivGraph("res/motion/gun/nomal_run/nomal_up_run_F.png", 22, 11, 2, 300, 300, &_cgPlayer[172][0]);             //走り通常弾　　上
		LoadDivGraph("res/motion/gun/nomal_run/nomal_45down_run_F.png", 22, 11, 2, 300, 300, &_cgPlayer[173][0]);           //走り通常弾　　斜め下 
		LoadDivGraph("res/motion/gun/reflex_run/reflex_mae_run_F.png", 22, 11, 2, 300, 300, &_cgPlayer[180][0]);          //走り反射弾　　正面
		LoadDivGraph("res/motion/gun/reflex_run/reflex_45up_run_F.png", 22, 11, 2, 300, 300, &_cgPlayer[181][0]);       //走り反射弾　　斜め上
		LoadDivGraph("res/motion/gun/reflex_run/reflex_up_run_F.png", 22, 11, 2, 300, 300, &_cgPlayer[182][0]);           //走り反射弾　　上
		LoadDivGraph("res/motion/gun/reflex_run/reflex_45down_run_F.png", 22, 11, 2, 300, 300, &_cgPlayer[183][0]);         //走り反射弾　　斜め下 

		//シナリオ

		BodyHandle[0] = NULL;
		BodyHandle[1] = LoadGraph("res/mysterious_girl/whole_body/ST_GIRL_1.png");							//全体謎少女
		BodyHandle[2] = LoadGraph("res/mysterious_girl/whole_body/ST_GIRL_1_nantomo.png");					//なんとも
		BodyHandle[3] = LoadGraph("res/mysterious_girl/whole_body/ST_GIRL_1_odoroki.png");					//おどろき
		BodyHandle[4] = LoadGraph("res/mysterious_girl/whole_body/ST_GIRL_1_sinken.png");					//真剣
		BodyHandle[5] = LoadGraph("res/mysterious_girl/whole_body/ST_GIRL_1_smile.png");					//にっこり
		BodyHandle[6] = LoadGraph("res/colonel/ST_TAISA_1.png");							     			//大佐
		BodyHandle[7] = LoadGraph("res/colonel/ST_TAISA_1_akire.png");						     			//あきれ
		BodyHandle[8] = LoadGraph("res/colonel/ST_TAISA_1_ikari.png");						     			//怒
		BodyHandle[9] = LoadGraph("res/colonel/ST_TAISA_1_odoroki.png");									//驚き
		BodyHandle[10] = LoadGraph("res/operator/ST_OPERATOR_1.png");                                       //オペレーター
		BodyHandle[11] = LoadGraph("res/operator/ST_OPERATOR_1_aseri.png");									//焦り
		BodyHandle[12] = LoadGraph("res/operator/ST_OPERATOR_1_ikari.png");									//怒
		BodyHandle[13] = LoadGraph("res/operator/ST_OPERATOR_1_tere.png");									//テレ
		BodyHandle[14] = LoadGraph("res/stand_image/nazo_black.png");
		BodyHandle[15] = LoadGraph("res/stand_image/taisa_black.png");
		BodyHandle[16] = LoadGraph("res/stand_image/operator_black.png");

		BodyHandle[17] = LoadGraph("res/stand_image/ST_GIRL_1 (1).png");
		BodyHandle[18] = LoadGraph("res/stand_image/ST_OPERATOR_1.png");
		BodyHandle[19] = LoadGraph("res/stand_image/ST_TAISA_1.png");

		FaceHandle[0] = NULL;
		FaceHandle[1] = LoadGraph("res/mysterious_girl/shoulder_shot/ST_GIRL_1_FACE.png");					//顔グラ謎少女
		FaceHandle[2] = LoadGraph("res/mysterious_girl/shoulder_shot/ST_GIRL_1_FACE_nantomo.png");			//なんとも
		FaceHandle[3] = LoadGraph("res/mysterious_girl/shoulder_shot/ST_GIRL_1_FACE_odoroki.png");			//驚き
		FaceHandle[4] = LoadGraph("res/mysterious_girl/shoulder_shot/ST_GIRL_1_FACE_sinken.png");			//真剣
		FaceHandle[5] = LoadGraph("res/mysterious_girl/shoulder_shot/ST_GIRL_1_FACE_smile.png");			//にっこり
		//FaceHandle[6] = 
		//FaceHandle[7] =
		//FaceHandle[8] =
		//FaceHandle[9] =
		//FaceHandle[10] =
		//FaceHandle[11] =
		//FaceHandle[12] = 
		//FaceHandle[13] =

		text_handle = LoadGraph("res/UI_MA_TEXT_BOX/UI_MA_TEXT_BOX.png");
		text_arrow = LoadGraph("res/UI_MA_TEXT_BOX/UI_MA_TEXT_icon.png");
		skip = LoadGraph("res/skip.png");
		//カットイン


		
		for(int effect_load_count = 0; effect_load_count < 31; effect_load_count++) {
			sprintf(size, "res/15fps whitecut/white_cut 2_2%02d.png", effect_load_count);
			cgCutin[0][effect_load_count] = LoadGraph(size);
		}

		for(int effect_load_count = 0; effect_load_count < 31; effect_load_count++) {
			sprintf(size, "res/15fps blackcut/black_cut 2%02d.png", effect_load_count);
			cgCutin[1][effect_load_count] = LoadGraph(size);
		}

		//エフェクト
		LoadDivGraph("res/bullet_effect/effect.png", 10, 10, 1, 100, 100, &cgEffect[EFFECT_TYPE_BULLET_NOLMAR][0]);
		LoadDivGraph("res/bullet_effect/effect.png", 10, 10, 1, 100, 100, &cgEffect[EFFECT_TYPE_BULLET_RIFLECT][0]);
		LoadDivGraph("res/bullet_effect/effect.png", 10, 10, 1, 100, 100, &cgEffect[EFFECT_TYPE_BULLET_TRUST][0]);
		LoadDivGraph("res/bullet_effect/danndou_purple_00000_sheet.png", 13, 13, 1, 100, 100, &cgEffect[EFFECT_TYPE_BULLET_BRACK][0]);
		LoadDivGraph("res/bullet_effect/portal_black_sheet_sai.png", 20, 5, 4, 200, 200, &cgEffect[EFFECT_TYPE_BULLET_BPORTAL][0]);
		LoadDivGraph("res/bullet_effect/portal_white_sheet_sai.png", 20, 5, 4, 200, 200, &cgEffect[EFFECT_TYPE_BULLET_WPORTAL][0]);
		LoadDivGraph("res/bullet_effect/annihilation_sheet.png", 15, 5, 3, 200, 200, &cgEffect[EFFECT_TYPE_BULLET_ANNIHILAT][0]);
		LoadDivGraph("res/bullet_effect/hansya_hassya_00000_sheet.png", 11, 11, 1, 50, 50, &cgEffect[EFFECT_TYPE_RIFFLECT_WALL][0]);
		LoadDivGraph("res/bullet_effect/Normal_tyakudann_00000_sheet.png", 11, 11, 1, 100, 100, &cgEffect[EFFECT_TYPE_NORMAL_WALL][0]);
		LoadDivGraph("res/bullet_effect/Normal_hassya_00000_sheet.png", 11, 11, 1, 50, 50, &cgEffect[EFFECT_TYPE_NORMAL_SHOT][0]);
		LoadDivGraph("res/bullet_effect/explosion.png", 17, 17, 1, 400, 400, &cgEffect[EFFECT_TYPE_BOMBER][0]);
		cgEffect[EFFECT_TYPE_RIFLECT_BOOST][0] = LoadGraph("res/bullet_effect/ring blue_00000.png");
		cgEffect[EFFECT_TYPE_BLACK_BOOST][0] = LoadGraph("res/bullet_effect/ring purple_00000.png");

		boss_aura[0] = LoadGraph("res/boss_effect/enemy_boss1_effect_B.png");
		boss_aura[1] = LoadGraph("res/boss_effect/enemy_boss1_effect_W.png");
		LoadDivGraph("res/boss_effect/boss_effect_black_sheet.png", 10, 10, 1, 600, 600, boss_effectblack);
		LoadDivGraph("res/boss_effect/boss_effect_white_sheet.png", 10, 10, 1, 600, 600, boss_effectwhite);

		//UI

		hp_handle          = LoadGraph("res/UI_MA_HP/UI_MA_HP_1 .png");
		hp_circle_back     = LoadGraph("res/UI_MA_HP/UI_MA_HP_2.png");
		hp_circle_top      = LoadGraph("res/UI_MA_HP/UI_MA_HP_34.png");
		hp_gauge_back      = LoadGraph("res/UI_MA_HP/UI_MA_HP_4.png");
		hp_gauge_easing[0] = LoadGraph("res/UI_MA_HP/UI_MA_HP_555_R.png");
		hp_gauge_easing[1] = LoadGraph("res/UI_MA_HP/UI_MA_HP_555_B.png");
		hp_gauge_top       = LoadGraph("res/UI_MA_HP/UI_MA_HP_555.png");
											
		boss_hp_frame      = LoadGraph("res/UI_MA_HP/UI_MA_BOSS_frame6_1.png");
		boss_hp_gauge[0]   = LoadGraph("res/UI_MA_HP/UI_MA_BOSS_frame6_5_Red.png");
		boss_hp_gauge[1]   = LoadGraph("res/UI_MA_HP/UI_MA_BOSS_frame6_6_yellow.png");
		boss_hp_gauge[2]   = LoadGraph("res/UI_MA_HP/UI_MA_BOSS_frame6_4_GReeeeN.png");
		boss_hp_gauge[3]   = LoadGraph("res/UI_MA_HP/UI_MA_BOSS_frame6_2.png");
		boss_hp_gauge_back = LoadGraph("res/UI_MA_HP/UI_MA_BOSS_frame6_3.png");

		weapon_normal_handle[0] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_WEAPON_N_1.png");
		weapon_normal_handle[1] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_WEAPON_N_2.png");
		weapon_reflect_handle[1] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_WEAPON_R_1.png");
		weapon_reflect_handle[2] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_WEAPON_R_2.png");
		weapon_reflect_handle[0] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_WEAPON_R_3.png");
		weapon_trust_handle[1] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_WEAPON_A_1.png");
		weapon_trust_handle[2] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_WEAPON_A_2.png");
		weapon_trust_handle[0] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_WEAPON_A_3.png");
		weapon_black_handle[1] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_WEAPON_B_1.png");
		weapon_black_handle[2] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_WEAPON_B_2.png");
		weapon_black_handle[0] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_WEAPON_A_3.png");
		weapon_white_portal_handle[0] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_PORTAL_W_1.png");
		weapon_white_portal_handle[1] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_PORTAL_W_2.png");
		weapon_black_portal_handle[0] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_PORTAL_B_1.png");
		weapon_black_portal_handle[1] = LoadGraph("res/UI_MA_WEAPON/a/UI_MA_PORTAL_B_2.png");

		big_num_handle[0] = LoadGraph("res/UI_MA_HP_font_A/UI_MA_HP_font_A_0.png");
		big_num_handle[1] = LoadGraph("res/UI_MA_HP_font_A/UI_MA_HP_font_A_1.png");
		big_num_handle[2] = LoadGraph("res/UI_MA_HP_font_A/UI_MA_HP_font_A_2.png");
		big_num_handle[3] = LoadGraph("res/UI_MA_HP_font_A/UI_MA_HP_font_A_3.png");
		big_num_handle[4] = LoadGraph("res/UI_MA_HP_font_A/UI_MA_HP_font_A_4.png");
		big_num_handle[5] = LoadGraph("res/UI_MA_HP_font_A/UI_MA_HP_font_A_5.png");
		big_num_handle[6] = LoadGraph("res/UI_MA_HP_font_A/UI_MA_HP_font_A_6.png");
		big_num_handle[7] = LoadGraph("res/UI_MA_HP_font_A/UI_MA_HP_font_A_7.png");
		big_num_handle[8] = LoadGraph("res/UI_MA_HP_font_A/UI_MA_HP_font_A_8.png");
		big_num_handle[9] = LoadGraph("res/UI_MA_HP_font_A/UI_MA_HP_font_A_9.png");

		min_num_handle[0] = LoadGraph("res/UI_MA_HP_font_B/UI_MA_HP_font_B_0.png");
		min_num_handle[1] = LoadGraph("res/UI_MA_HP_font_B/UI_MA_HP_font_B_1.png");
		min_num_handle[2] = LoadGraph("res/UI_MA_HP_font_B/UI_MA_HP_font_B_2.png");
		min_num_handle[3] = LoadGraph("res/UI_MA_HP_font_B/UI_MA_HP_font_B_3.png");
		min_num_handle[4] = LoadGraph("res/UI_MA_HP_font_B/UI_MA_HP_font_B_4.png");
		min_num_handle[5] = LoadGraph("res/UI_MA_HP_font_B/UI_MA_HP_font_B_5.png");
		min_num_handle[6] = LoadGraph("res/UI_MA_HP_font_B/UI_MA_HP_font_B_6.png");
		min_num_handle[7] = LoadGraph("res/UI_MA_HP_font_B/UI_MA_HP_font_B_7.png");
		min_num_handle[8] = LoadGraph("res/UI_MA_HP_font_B/UI_MA_HP_font_B_8.png");
		min_num_handle[9] = LoadGraph("res/UI_MA_HP_font_B/UI_MA_HP_font_B_9.png");

		weapon_num_handle[0] = LoadGraph("res/UI_MA_WEAPON/UI_MA_FONT/UI_MA_FONT_0.png");
		weapon_num_handle[1] = LoadGraph("res/UI_MA_WEAPON/UI_MA_FONT/UI_MA_FONT_1.png");
		weapon_num_handle[2] = LoadGraph("res/UI_MA_WEAPON/UI_MA_FONT/UI_MA_FONT_2.png");
		weapon_num_handle[3] = LoadGraph("res/UI_MA_WEAPON/UI_MA_FONT/UI_MA_FONT_3.png");
		weapon_num_handle[4] = LoadGraph("res/UI_MA_WEAPON/UI_MA_FONT/UI_MA_FONT_4.png");
		weapon_num_handle[5] = LoadGraph("res/UI_MA_WEAPON/UI_MA_FONT/UI_MA_FONT_5.png");
		weapon_num_handle[6] = LoadGraph("res/UI_MA_WEAPON/UI_MA_FONT/UI_MA_FONT_6.png");
		weapon_num_handle[7] = LoadGraph("res/UI_MA_WEAPON/UI_MA_FONT/UI_MA_FONT_7.png");
		weapon_num_handle[8] = LoadGraph("res/UI_MA_WEAPON/UI_MA_FONT/UI_MA_FONT_8.png");
		weapon_num_handle[9] = LoadGraph("res/UI_MA_WEAPON/UI_MA_FONT/UI_MA_FONT_9.png");

		inf_B = LoadGraph("res/UI_MA_WEAPON/UI_MA_FONT/UI_MA_FONT_m.png");
		inf_W = LoadGraph("res/UI_PO/UI_MA_FONT_m_w.png");

		//--------------------
		for(int i = 5; i < 60; i += 10) {
			sprintf(size, "res/snow/MA_STAGE_EFFECT_SNOW_%05d.png", i);
			snow_handle[i] = LoadGraph(size);
		}

		floor_handle[0] = LoadGraph("res/floorname/floorname.png");

		for(int i = 2; i < 18; i++) {
			sprintf(size, "res/floorname/floorname_%d.png", i);
			floor_handle[i - 1] = LoadGraph(size);
		}


	
		//ポーズ画面
		charahandle = LoadGraph("res/UI_PO/UI_PO_CHARACTER.png");
		pause_handle = LoadGraph("res/UI_PO/UI_PO_BLUR.png");
		controle_Handle = LoadGraph("res/Controller_Setting.png");
		parcent_gauge = LoadGraph("res/UI_PO/UI_PO_gauge.png");
		name_handle = LoadGraph("res/UI_PO/UI_PO_NAME_BOX.png");
		purpose_handle = LoadGraph("res/UI_PO/UI_PO_TGT_0.png");
		end_bg = LoadGraph("res/UI_PO/UI_PO_CHECK_BOX.png");
		box_handle[0] = LoadGraph("res/UI_PO/UI_PO_HP.png");
		box_handle[1] = LoadGraph("res/UI_PO/UI_PO_WEAPON_R.png");
		box_handle[2] = LoadGraph("res/UI_PO/UI_PO_WEAPON_A.png");
		box_handle[3] = LoadGraph("res/UI_PO/UI_PO_WEAPON_B.png");
		box_handle[4] = LoadGraph("res/UI_PO/UI_PO_PORTAL_W.png");
		box_handle[5] = LoadGraph("res/UI_PO/UI_PO_PORTAL_B.png");
		select_box_handle[0][0] = LoadGraph("res/UI_PO/UI_PO_CONTROL_1.png");
		select_box_handle[0][1] = LoadGraph("res/UI_PO/UI_PO_CONTROL_2.png");
		select_box_handle[0][2] = LoadGraph("res/UI_PO/UI_PO_CONTROL_3.png");
		select_box_handle[1][0] = LoadGraph("res/UI_PO/UI_PO_SETTING_1.png");
		select_box_handle[1][1] = LoadGraph("res/UI_PO/UI_PO_SETTING_2.png");
		select_box_handle[1][2] = LoadGraph("res/UI_PO/UI_PO_SETTING_3.png");
		select_box_handle[2][0] = LoadGraph("res/UI_PO/UI_PO_EXIT_1.png");
		select_box_handle[2][1] = LoadGraph("res/UI_PO/UI_PO_EXIT_2.png");
		select_box_handle[2][2] = LoadGraph("res/UI_PO/UI_PO_EXIT_3.png");
		//大きい数字
		number_big[0] = LoadGraph("res/UI_PO/UI_NUMBER/UI_NUMBER_0.png");
		number_big[1] = LoadGraph("res/UI_PO/UI_NUMBER/UI_NUMBER_1.png");
		number_big[2] = LoadGraph("res/UI_PO/UI_NUMBER/UI_NUMBER_2.png");
		number_big[3] = LoadGraph("res/UI_PO/UI_NUMBER/UI_NUMBER_3.png");
		number_big[4] = LoadGraph("res/UI_PO/UI_NUMBER/UI_NUMBER_4.png");
		number_big[5] = LoadGraph("res/UI_PO/UI_NUMBER/UI_NUMBER_5.png");
		number_big[6] = LoadGraph("res/UI_PO/UI_NUMBER/UI_NUMBER_6.png");
		number_big[7] = LoadGraph("res/UI_PO/UI_NUMBER/UI_NUMBER_7.png");
		number_big[8] = LoadGraph("res/UI_PO/UI_NUMBER/UI_NUMBER_8.png");
		number_big[9] = LoadGraph("res/UI_PO/UI_NUMBER/UI_NUMBER_9.png");
		//小さい数字
		number_min[0] = LoadGraph("res/UI_PO/UI_NUMBER2/UI_NUMBER2_0.png");
		number_min[1] = LoadGraph("res/UI_PO/UI_NUMBER2/UI_NUMBER2_1.png");
		number_min[2] = LoadGraph("res/UI_PO/UI_NUMBER2/UI_NUMBER2_2.png");
		number_min[3] = LoadGraph("res/UI_PO/UI_NUMBER2/UI_NUMBER2_3.png");
		number_min[4] = LoadGraph("res/UI_PO/UI_NUMBER2/UI_NUMBER2_4.png");
		number_min[5] = LoadGraph("res/UI_PO/UI_NUMBER2/UI_NUMBER2_5.png");
		number_min[6] = LoadGraph("res/UI_PO/UI_NUMBER2/UI_NUMBER2_6.png");
		number_min[7] = LoadGraph("res/UI_PO/UI_NUMBER2/UI_NUMBER2_7.png");
		number_min[8] = LoadGraph("res/UI_PO/UI_NUMBER2/UI_NUMBER2_8.png");
		number_min[9] = LoadGraph("res/UI_PO/UI_NUMBER2/UI_NUMBER2_9.png");
		parcent_handle = LoadGraph("res/UI_PO/UI_NUMBER2/UI_Perc.png");
		//yes no
		yes_handle[0] = LoadGraph("res/UI_PO/UI_PO_CHECK_YES_1.png");
		yes_handle[1] = LoadGraph("res/UI_PO/UI_PO_CHECK_YES_2.png");
		yes_handle[2] = LoadGraph("res/UI_PO/UI_PO_CHECK_YES_3.png");

		no_handle[0] = LoadGraph("res/UI_PO/UI_PO_CHECK_NO_1.png");
		no_handle[1] = LoadGraph("res/UI_PO/UI_PO_CHECK_NO_2.png");
		no_handle[2] = LoadGraph("res/UI_PO/UI_PO_CHECK_NO_3.png");


		//メイン
		_cgBg[0] = LoadGraph("res/bg/BG_openingstage.png");
		_cgBg[1] = LoadGraph("res/bg/BG_City1.png");
		_cgBg[2] = LoadGraph("res/bg/BG_City2.png");
		_cgBg[3] = LoadGraph("res/bg/BG_UG.png");
		_cgBg[4] = LoadGraph("res/bg/BG_Lab1.png");
		_cgBg[5] = LoadGraph("res/bg/BG_Lab2.png");
		_floor[0] = LoadGraph("res/bg/PF1.png");
		_floor[1] = LoadGraph("res/bg/PF2.png");
		_floor[2] = LoadGraph("res/bg/PF3.png");
		_floor[3] = LoadGraph("res/bg/PF4.png");
		_floor[4] = LoadGraph("res/bg/BG_City1.png");
		_floor[5] = LoadGraph("res/bg/BG_City2.png");
		_floor[6] = LoadGraph("res/bg/S1H3.png");
		_floor[7] = LoadGraph("res/bg/S1H4.png");
		_floor[8] = LoadGraph("res/bg/S1H5.png");
		_floor[9] = LoadGraph("res/bg/S1H6.png");
		_floor[10] = LoadGraph("res/bg/S2F1.png");
		_floor[11] = LoadGraph("res/bg/S2F2.png");
		_floor[12] = LoadGraph("res/bg/S2F3.png");
		_floor[13] = LoadGraph("res/bg/S2F4.png");
		_floor[14] = LoadGraph("res/bg/S2F5.png");
		_floor[15] = LoadGraph("res/bg/S2F6.png");
		_floor[16] = LoadGraph("res/bg/Boss.png");
		screen_effect[0] = LoadGraph("res/effect/MA_PC_HIT_EFFECT.png");
		screen_effect[1] = LoadGraph("res/effect/MA_PC_HEAL_EFFECT.png");
		screen_effect[2] = LoadGraph("res/effect/MA_PC_SINGULARITY_EFFECT.png");
		screen_effect[3] = LoadGraph("res/effect/MA_PC_AMMO_EFFECT.png");
		_item_log[0] = LoadGraph("res/itemlog/Get_Font_Ammo.png");
		_item_log[1] = LoadGraph("res/itemlog/Get_Font_Door.png");
		_item_log[2] = LoadGraph("res/itemlog/Get_Font_HP1.png");
		_item_log[3] = LoadGraph("res/itemlog/Get_Font_HP2.png");
		_item_log[4] = LoadGraph("res/itemlog/Get_Font_Portal.png");
		_item_log[5] = LoadGraph("res/itemlog/Get_Font_SINGULARITY.png");
		_item_log[6] = LoadGraph("res/itemlog/Get_Font_WeponB.png");
		_item_log[7] = LoadGraph("res/itemlog/Get_Font_WeponT.png");
		_item_log[8] = LoadGraph("res/itemlog/Get_Font_WeponR.png");
		LoadDivGraph("res/MA_YAJIRUSHI_00000_sheet.png", 36, 36, 1, 200, 200, &_gra_arrow[0]);

		blur[0] = LoadGraph("res/sinario/BG_STORY_0.png");
		blur[1] = LoadGraph("res/sinario/BG_STORY_1.png");
		blur[2] = LoadGraph("res/sinario/BG_STORY_2.png");
		blur[3] = LoadGraph("res/sinario/BG_STORY_3.png");
		blur[4] = LoadGraph("res/sinario/BG_STORY_4.png");

		//bgm
		Bgm[0] = LoadSoundMem("res/BGM/Capitalism.mp3");
		Bgm[1] = LoadSoundMem("res/BGM/Around_the_Darkness.mp3");
		Bgm[2] = LoadSoundMem("res/BGM/039clock.mp3");
		Bgm[3] = LoadSoundMem("res/BGM/Sirius.mp3");
		Bgm[4] = LoadSoundMem("res/BGM/Laboratory.mp3");
		Bgm[5] = LoadSoundMem("res/BGM/Paper_City.mp3");
		Bgm[6] = LoadSoundMem("res/BGM/wind.mp3");
		Bgm[7] = LoadSoundMem("res/BGM/Despair_and_Hope.mp3");

		scenario_Bgm[0] = LoadSoundMem("res/BGM/Yesterday.mp3");
		scenario_Bgm[1] = LoadSoundMem("res/BGM/Blue_Restaurant.mp3");
		scenario_Bgm[2] = LoadSoundMem("res/BGM/Rain.mp3");
		scenario_Bgm[3] = LoadSoundMem("res/BGM/Yorisou.mp3");

		Se[0] = LoadSoundMem("res/SE/select06.mp3");             //ポーズ画面転移音
		Se[1] = LoadSoundMem("res/SE/SE_PORTAL.mp3");            //ポータル音
		Se[2] = LoadSoundMem("res/SE/SE_DESTROY1.mp3");          //破壊音
		Se[3] = LoadSoundMem("res/SE/SE_CUTIN_1.mp3");           //カットイン
		Se[4] = LoadSoundMem("res/SE/SE_GUN_P.mp3");             //カットイン後の銃声
		Se[5] = LoadSoundMem("res/SE/SE_BOSS_ALERT.mp3");        //ボス部屋音
		Se[6] = LoadSoundMem("res/SE/SE_STAGE_MOVE.mp3");        //ステージ編イオン
		Se[7] = LoadSoundMem("res/SE/SE_ITEM.mp3");              //アイテム取得音
		Se[8] = LoadSoundMem("res/SE/SE_HP.mp3");                //回復音
		Se[9] = LoadSoundMem("res/SE/SE_DESTROY2.mp3");          //対消滅後破壊音
		Se[10] = LoadSoundMem("res/SE/SE_SINGULARITY_FIX.mp3");   //対消滅音
		Se[11] = LoadSoundMem("res/SE/SE_GUN_N.mp3");             //通常団
		Se[12] = LoadSoundMem("res/SE/SE_GUN_R.mp3");             //反射弾
		Se[13] = LoadSoundMem("res/SE/SE_GUN_P.mp3");             //貫通弾
		Se[14] = LoadSoundMem("res/SE/SE_HIT.mp3");               //着弾音
		Se[15] = LoadSoundMem("res/SE/SE_DOOR.mp3");              //ドア
		Se[16] = LoadSoundMem("res/SE/SE_RUN_FIX.mp3");           //走る音
		Se[17] = LoadSoundMem("res/SE/SE_RELOAD.mp3");            //ポータル弾
		Se[18] = LoadSoundMem("res/SE/SE_SELECT.mp3");            //武器切り替え音
		Se[19] = LoadSoundMem("res/SE/SE_JUMP.mp3");              //ジャンプ
		Se[20] = LoadSoundMem("res/SE/SE_LAND_.mp3");             //着地音
		Se[21] = LoadSoundMem("res/SE/SE_SELECT.mp3");            //セレクト音
		Se[22] = LoadSoundMem("res/SE/SE_SELECT_ENTER1.mp3");     //決定音
		Se[23] = LoadSoundMem("res/SE/SE_SELECT_BACK1.mp3");      //キャンセル音
		Se[24] = LoadSoundMem("res/SE/SE_ROBOT_DETECTED.mp3");    //お掃除ロボット探知
		Se[25] = LoadSoundMem("res/SE/SE_TURRET_DETECTED.mp3");   //タレット探知音
		Se[26] = LoadSoundMem("res/SE/Get_Weapon.wav");           //武器ゲット音
		Se[27] = LoadSoundMem("res/SE/missile.mp3");              //ボスミサイル音
		Se[28] = LoadSoundMem("res/SE/gun_charge2.mp3");//武器チャージ音
		//キャラボイス
		 chara_voice[0] = LoadSoundMem("res/voice/main_voice/attack_1.wav");//攻撃
		 chara_voice[1] = LoadSoundMem("res/voice/main_voice/attack_2.wav");
		 chara_voice[2] = LoadSoundMem("res/voice/main_voice/attack_3.wav");
		 chara_voice[3] = LoadSoundMem("res/voice/main_voice/cutin_1.wav");//カットイン
		 chara_voice[4] = LoadSoundMem("res/voice/main_voice/cutin_2.wav");
		 chara_voice[5] = LoadSoundMem("res/voice/main_voice/dameag_1.wav");//ダメージ
		 chara_voice[6] = LoadSoundMem("res/voice/main_voice/dameag_2.wav");
		 chara_voice[7] = LoadSoundMem("res/voice/main_voice/dameag_3.wav");
		 chara_voice[8] = LoadSoundMem("res/voice/main_voice/dead_1.wav");//死亡
		 chara_voice[9] = LoadSoundMem("res/voice/main_voice/dead_2.wav");
		chara_voice[10] = LoadSoundMem("res/voice/main_voice/get_aitem_1.wav");//アイテムゲット
		chara_voice[11] = LoadSoundMem("res/voice/main_voice/get_aitem_2.wav");
		chara_voice[12] = LoadSoundMem("res/voice/main_voice/jump1.wav");//ジャンプ
		chara_voice[13] = LoadSoundMem("res/voice/main_voice/jump2.wav");
		chara_voice[14] = LoadSoundMem("res/voice/main_voice/stand_1.wav");//たち
		chara_voice[15] = LoadSoundMem("res/voice/main_voice/stand_2.wav");


		main_complet = 1;
		SetUseASyncLoadFlag(FALSE);
	}
}

void Image::LoadingProcess() {
	
	for(int i = 0; i < 4; i++) {
		if((count[i]++ % 6) == 0) {
			loading_add[i] += 12.5f;
			if(order[i] > 0) {
				order[i]--;
			}
		}
		
		if(loading_add[i] > 100) {
			loading_add[i] = 12.5f;
			order[i] = 4;
		}

		if(count[i] >= 300) {
			
			count[i] = 0;
			
			load_complet = 1;
		}
		
	}
}

void Image::LoadingDraw() {
	DrawGraph(0, 0, GetLoading_Bg(), true);
	DrawGraph(1920 - 438, 1080 - 588, GetLoading_Chara(), true);
	DrawCircleGauge(1920 - 144, 1080 - 123, 100, GetLoading_Gauge(3), true);
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (i == order[j]) {
				DrawCircleGauge(1920 - 144, 1080 - 123, loading_add[j], GetLoading_Gauge(j), true);
			}
		}
	}
}