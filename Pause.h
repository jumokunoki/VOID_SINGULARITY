/*****************************************************************//**
 * \file   Pause.h
 * \brief  ポーズ
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "Option.h"

 //-----------------------------
 // //マクロ
#define BOX_MAX 6
#define SELECT_BOX_MAX 3
#define HP_MAX 100
#define LIF_MAX 20
#define TRU_MAX 20
#define BLA_MAX  5
#define WPO_MAX  5
#define BPO_MAX 10


//-----------------------------
class Pause
{
public:
	Pause();
	virtual ~Pause();

	void PauseInit();//初期化
	void Process(int* pause, int hp, int hp_stock , int normal, int riflect, int trust, int wpo, int bpo , int hp_max, int max_normal, int max_riflect, int max_trust, int max_wpo, int max_bpo);
	void SelectMove(int select, int instructions, int instructions_count);//選択画面の明滅処理
	void GaugeProcess(int now_bullet_nam, int max_bullet_nam, int i, float time);//ゲージのイージングをまとめた関数
	void Draw(int pause);
	void BulletDraw(int pause, int hp, int hp_stock, int normal, int riflect, int trust, int wpo, int bpo, int hp_max, int max_normal, int max_riflect, int max_trust, int max_wpo, int max_bpo);//銃系統の描画をまとめたもの
	void OptionDraw(int pause);//オプション画面の描画
	void BalletNumDraw(int x, int y, int bullet_num);//弾の数の描画
	void ParcentDraw(int x, int y, int now_bullet, int max_bullet, int time);//パーセントの文字の描画

protected:


	//---------------------
	//ポーズ画面の表示周りの変数


	int screen_count;   //画面を描画するまでのカウント　
	int old_count;      //毎フレームスクリーンカウントを更新し -するときに変換したもの使っている　使用しているもの


	float time[6];           //パラメーターボックスのイージングに使用
	float select_box_time[3];//選択ボックスのイージングに使用
	float gauge_time[6];//ゲージのイージングに使用

	float brend;           //キャラのブレンドに使用
	float brend_box[6];    //パラメータボックスのブレンドに使用
	int brend_box_time[6];
	float select_brend_box;//選択ボックスのブレンドに使用

	struct Box {
		int x, y;
		int w, h;
	};

	Box box[6];//武器や体力の情報を描くときのｘ、ｙ
	Box select_box[3];//セレクト画面の情報を描くときのｘ、ｙ
	float bullet_parcent[6];//弾のゲージをイージングでやるときに使う //6はhpゲージ二週目
	//---------------------
	//ポーズ画面の選択周りの変数
	int select_count;      //選択するときのカウント
	int instructions;      //セレクトカウントと連動して 移動するためのカウント
	int instructions_count;//ポーズから派生する画面に移動するときの変数
	int instructions_handle_count[2];//画像の番号を入れる変数
	int select_handle_count[3];//画像の番号を入れる変数
	int waitcount;         //点滅の待機時間
	int use;               //選択できるようになったら１にする

	float flashing;//点滅の処理に使う掛け算
	int hang;//点滅の処理の掛け算に使う変数

	int num_size_min_x, num_size_min_y;//数字ハンドルの大きさを格納する変数（小）
	int num_size_big_x, num_size_big_y;//数字ハンドルの大きさを格納する変数（大）


	Option option;

};



