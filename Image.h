/*****************************************************************//**
 * \file   Image.h
 * \brief  画像情報
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#pragma once

#define EFFECT_TYPE_BULLET_NOLMAR	  0
#define EFFECT_TYPE_BULLET_RIFLECT	  1
#define EFFECT_TYPE_BULLET_TRUST      2
#define EFFECT_TYPE_BULLET_BRACK      3
#define EFFECT_TYPE_BULLET_BPORTAL    4
#define EFFECT_TYPE_BULLET_WPORTAL    5
#define EFFECT_TYPE_BULLET_ANNIHILAT  6 
#define EFFECT_TYPE_RIFFLECT_WALL     7 
#define EFFECT_TYPE_NORMAL_WALL       8
#define EFFECT_TYPE_NORMAL_SHOT       9
#define EFFECT_TYPE_RIFLECT_BOOST     10
#define EFFECT_TYPE_BLACK_BOOST       11
#define EFFECT_TYPE_BOMBER            12

#define ATTACK_VOICE                  0
#define CUTIN_VOICE                   3
#define DAMEGE_VOICE                  5
#define DEAD_VOICE                    8
#define GET_VOICE                     10
#define JUMP_VOICE                    12
#define STAND_VOICE                   14

#define RANDAM_TWO                    2
#define RANDAM_THREE                  3



#define EFFECT_MAX 800
#define	EFFECT_TYPE_MAX 13
#define EFFECT_SHEETS_MAX 30

#define EFFECT_PLAYER 0
#define EFFECT_ENEMY  1
#define EFFECT_BOSS   2

class Image
{
public:
	Image();
	~Image();
	void ImageInit();
	void TitleLoad();
	void GameMainLoad();
	void LoadingProcess();
	void LoadingDraw();

	//ハンドルゲッター

	//タイトルのエフェクト
	int GetEffectCg(int index) { return effectcg[index]; }
	int GetHand_Effect(int index) { return hand_effect[index]; }
	//チュートリアル
	int GetTutorial_Handle(int index) { return tutorial_handle[index]; }
	//ゲームクリア
	int GetClear_Cg() { return clear_cg; }
	int GetClear_Font_Target(int index) { return clear_font_target[index]; }
	int GetAfter_Clear_Font(int index) { return after_clear_font[index]; }
	//ローディング
	int GetLoading_Bg() { return loading_Bg; }
	int GetLoading_Chara() { return loading_chara; }
	int GetLoading_Gauge(int index) { return loading_gauge[index]; }
	int GetLoading_Handle(int index) { return loading_handle[index]; }
	//エネミー
	int GetCgEnemy(int index) { return _cgEnemy[index]; }
	int GetEnemyBullet(int index) { return enemy_bullet_handle[index]; }
	int GetEffectBlack(int index) { return effectblack[index]; }
	int GetEffectWhite(int index) { return effectwhite[index]; }
	int GetBossEffectAura(int index) { return boss_aura[index]; }
	int GetBossEffectBlack(int index) { return boss_effectblack[index]; }
	int GetBossEffectWhite(int index) { return boss_effectwhite[index]; }
	int GetEnemy_One_Effect(int index) { return enemy_one_effect[index]; }
	//エネミーの珠
	int GetCgBullet(int index) { return _cgBullet[index]; }
	int GetMissil() { return missil; }
	//ギミック
	int Get_graAmmo(int index) { return _graAmmo[index]; }
	int Get_graTre(int index) { return _graTre[index]; }
	int Get_graHeal(int index) { return _graHeal[index]; }
	int Get_graA_Matter(int index) { return _graA_Matter[index]; }
	int Get_graSwitch(int index) { return _graSwitch[index]; }
	int Get_graDoor(int index) { return _graDoor[index]; }
	//ポータル
	int GetBlack_Portal_Handle(int index) { return black_portal_handle[index]; }
	int GetWhite_Portal_Handle(int index) { return white_portal_handle[index]; }
	int GetBlack_Portal_Effect_Handle(int index) { return black_portal_effect_handle[index]; }
	int GetWhite_Portal_Effect_Handle(int index) { return white_portal_effect_handle[index]; }
	//プレイヤー
	int Get_cgPlayer(int index, int j) { return _cgPlayer[index][j]; }
	//シナリオ
	int GetBodyHandle(int index) { return BodyHandle[index]; }
	int GetFaceHandle(int index) { return FaceHandle[index]; }
	int GetText_Handle() { return text_handle; }
	int GetText_Arrow() { return text_arrow; }
	int GetSkip() { return skip; }

	int GetStaff_Roll() { return staff_roll; }
	int GetStart_Movie() { return start_movie; }
	//カットイン
	int GetCgCutin(int index, int j) { return cgCutin[index][j]; }
	//エフェクト
	int GetCgEffect(int index, int j) { return cgEffect[index][j]; }
	//UI
	int GetFloor_Handle(int index) { return floor_handle[index]; }

	int GetHp_Handle() { return hp_handle; }
	int GetHp_Circle_Back() { return hp_circle_back; }
	int GetHp_Circle_Top() { return hp_circle_top; }
	int GetHp_Gauge_Back() { return hp_gauge_back; }
	int GetHp_Gauge_Easing(int index) { return hp_gauge_easing[index]; }
	int GetHp_Gauge_Top() { return hp_gauge_top; }


	int GetBoss_Hp_Frame() { return boss_hp_frame; }                             
	int GetBoss_Hp_Gauge(int index) { return boss_hp_gauge[index]; }			
	int GetBoss_Hp_Gauge_Back() { return boss_hp_gauge_back;}					

	int GetWeapon_Normal_Handle(int index){ return weapon_normal_handle[index]; }       
	int GetWeapon_Reflect_Handle(int index) { return weapon_reflect_handle[index]; }		 
	int GetWeapon_Trust_Handle(int index) { return weapon_trust_handle[index];}		     
	int GetWeapon_Black_Handle(int index) { return weapon_black_handle[index];}   
	int GetWeapon_White_Portal_Handle(int index) { return weapon_white_portal_handle[index]; }
	int GetWeapon_Black_Portal_Handle(int index){ return weapon_black_portal_handle[index]; }    

	int GetBig_Num_Handle(int index){ return big_num_handle[index]; }
	int GetMin_Num_Handle(int index){ return min_num_handle[index]; }	 
	int GetWeapon_Num_Handle(int index) { return weapon_num_handle[index]; }

	int GetInf_B() { return  inf_B; }
	int GetInf_S(){return  inf_S;}
	int GetInf_W() { return inf_W; }

	int GetSnow_Handle(int index) { return snow_handle[index]; }
	int GetSmock_Handle(int index) { return smock_handle[index]; }
	//マップチップ
	//オプション
	int GetOption_Bg() { return Option_Bg; }

	int GetGauge_Handle() { return gauge_handle; }
	int GetGauge_Ber() { return gauge_ber; }
	int GetGauge_Border(int index,int j){ return gauge_border[index][j]; }
	int GetSound_Switch(int index) { return sound_switch[index]; }
	int GetCutin_On_Handle(int index) { return cutin_on_handle[index]; }
	int GetCutin_Off_Handle(int index) { return cutin_off_handle[index]; }

	//ポーズ画面
	int GetPause_Handle() { return pause_handle; } 
	int GetControle_Handle() { return controle_Handle; } 
	int GetCharaHandle() { return charahandle; }          

	int GetParcent_Gauge() { return parcent_gauge; }       
	int GetParcent_Handle() { return parcent_handle; }  
	int GetName_Handle() { return name_handle; }     
	int GetPurpose_Handle() { return purpose_handle; }  
	int GetBox_Handle(int index) { return box_handle[index]; } 
	int GetSelect_Box_Handle(int index, int j) { return select_box_handle[index][j]; }
	int GetEnd_Bg() { return end_bg; }
	int GetYes_Handle(int index) { return yes_handle[index]; }
	int GetNo_Handle(int index) { return no_handle[index]; }

	int GetNumber_Big(int index) { return number_big[index]; }  
	int GetNumber_Min(int index) { return number_min[index]; }  

	//メイン
	int Get_CgBg(int index) { return _cgBg[index]; }   
	int Get_Floor(int index) { return _floor[index]; }   
	int GetScreen_Effect(int index) { return screen_effect[index]; }
	int Get_Item_log(int index) { return _item_log[index]; }           
	int Get_Gra_arrow(int index) { return _gra_arrow[index]; }    

	int GetBlur(int index) { return blur[index]; }

	//------------------------
	//ゲッター

	int  GetCount(int index) { return count[index]; }
	int  GetOrder(int index) { return order[index]; }
	int  GetLoadComplet() { return load_complet; }
	void SetLoadComplet(int index) { load_complet = index; }

	//音
	int Bgm[8];
	int scenario_Bgm[4];
	int Se[31];
	int chara_voice[16];

	//------------------------------------------------------------------
protected:
    //ハンドル
	//タイトルのエフェクト
	int effectcg[600];   
	int hand_effect[91]; 

	//チュートリアル
	int tutorial_handle[25];

	//ゲームクリア
	int clear_cg;
	int clear_font_target[2];
	int	after_clear_font[3];
	
	//ローディング
	int loading_Bg;       
	int loading_chara;	  
	int loading_gauge[4]; 
	int loading_handle[4];

	//エネミー
	int	_cgEnemy[10];	// キャラ画像 
	int effectblack[10];      
	int effectwhite[10];	  
	int boss_aura[2];
	int boss_effectblack[10];
	int boss_effectwhite[10];
	int enemy_one_effect[30]; 
	//エネミーの弾
	int _cgBullet[2];//
	int missil;
	int enemy_bullet_handle[20];
	//ギミック
	int _graAmmo[2];
	int _graTre[6];
	int _graHeal[2];
	int _graA_Matter[2];
	int _graSwitch[2];
	int _graDoor[50];
	//ポータル
	int black_portal_handle[20];
	int white_portal_handle[20];
	int black_portal_effect_handle[41];
	int white_portal_effect_handle[41];
	//プレイヤー
	int _cgPlayer[195][61]; //　一つ目の配列　一桁目　mirror　二桁目　type　三桁目　角度　二つ目の配列　シートの数 
	//シナリオ
	int BodyHandle[20];//1謎の少女　2大佐　3オペレーター
	int FaceHandle[14];                            
	int text_handle;                               
	int text_arrow;                                
	int skip; 

	int staff_roll;                                
	int start_movie;                               
	//カットイン
	int cgCutin[2][32];                            
	//エフェクト
	int cgEffect[EFFECT_TYPE_MAX][EFFECT_SHEETS_MAX];
	//UI
	int floor_handle[17];                          

	int hp_handle;  //hpの画像ハンドル               
	int hp_circle_back    ;//円の黒い方				
	int hp_circle_top     ;//円のゲージのほう			
	int hp_gauge_back     ;//棒ゲージの黒いほう			
	int hp_gauge_easing[2];							
	int hp_gauge_top;//棒ゲージのほう					

	int boss_hp_frame;                             
	int boss_hp_gauge[4];							
	int boss_hp_gauge_back;							

	int weapon_normal_handle[2];//通常銃         
	int weapon_reflect_handle[3];//反射銃		    
	int weapon_trust_handle[3];//貫通銃		    
	int weapon_black_handle[3];//黒銃		    
	int weapon_white_portal_handle[2];//白弾	    
	int weapon_black_portal_handle[2];//黒弾	    
												
	int big_num_handle[10];//大きい数字のフォント	 
	int min_num_handle[10];//小さい数字のフォント	 
	int weapon_num_handle[10];//武器の数字のフォント

	int inf_B;
	int inf_S;
	int inf_W;

	int snow_handle[60];
	int smock_handle[300];
	
	//オプション
	int Option_Bg;

	int gauge_handle;
	int gauge_ber;
	int gauge_border[3][2];
	int sound_switch[2];
	int cutin_on_handle[4];
	int cutin_off_handle[4];

	//ポーズ画面
	int pause_handle; //画像ハンドル 
	int controle_Handle; 
	int charahandle;          //キャラクターの画像ハンドル 
	int end_bg;

	int parcent_gauge;       //弾のゲージのハンドル 
	int parcent_handle;  
	int name_handle;     
	int purpose_handle;  
	int box_handle[6];   
	int select_box_handle[3][3];
	int yes_handle[3];
	int no_handle[3];

	int number_big[10];   
	int number_min[10];   

	//メイン
	int _cgBg[6];    // 背景画像
	int _floor[18];   // ステージ階層
	int screen_effect[4];  // 画面全体のエフェクト
	int _item_log[9]; // アイテムログ              
	int _gra_arrow[36];// 行先指定用の矢印          

	int blur[5];



	//-------------------------------------
	//変数
	
	//loading
	float loading_add[4];
	int count[4];
	int order[4];

	int load_complet;


	int title_complet;
	int main_complet;

};