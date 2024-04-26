/*****************************************************************//**
 * \file   SceneTest.h
 * \brief  ゲーム本編
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#pragma once

#include "SceneBase.h"
#include "SceneGameOver.h"
#include "gamemain.h"
#include "MapData.h"
#include "Camera.h"
#include "player.h"
#include "Portal.h"
#include "Gimmick.h"
#include "Pause.h"
#include "EnemyBase.h"
#include "EnemyBullet.h"
#include "mymath.h"
#include "gamemainUI.h"
#include "Cutin.h"
#include "CharDraw.h"
#include "relay_point.h"

#define TEST_SE_MAX 9
#define TEST_BGM_MAX 7

#define B_OUT_WAIT 60 

const int STAGE_MAX = 5;

class SceneTest : public SceneBase
{
public:
	SceneTest();			// コンストラクタ
	virtual ~SceneTest();	// デストラクタ

	void    StartMovie();							 // ムービー
	void    PortGene();								 // ポータル生成
	void    PlProcess();							 // プレイヤー
	void    EneProcess();							 // エネミー
	int       HpStock(int now_hp,int stock);//ｈｐが100を超えた時にストックを一つ増やす関数です　ｈｐが１００回復したときように作ったものですがそのままストックを+1してもよいです。
	int       StockBreak(int now_hp, int stock);//もしストックがあってプレイヤーのｈｐが０を下回った時ストックを崩して１００回復する関数です。　　↑の関数と合わせてプレイヤーのcppに持って行ってもらっても大丈夫です。
	void    SaveSet();                   //マップ切り替えのセーブ
	void    FloorPosInit();             // フロア遷移後のプレイヤーの出現位置
	void    FloorScaleInit();           // フロアごとのカメラの”ひき、より”の度合
	void    FloorCamInit();             // フロア遷移後のカメラ位置
	void    FloorProcess(int Floornum); // フロア固有の処理
	void    FloorCommon(int x, int y, int FloorNum); //　フロアの共通処理
	void    CameraProcess();						 // カメラ
	void    UiProcess();							 // UI
	void    Staging();								 // 演出
	void    GameOver();								 // ゲームオーバー
	void    BgmProcess();							 // BGM
	void    VolumProcess();							 // ヴォリューム
	void    BgProcess();							 // 背景
	void	   Process() override;	// 計算
	void    LineTerminalProcess();

	// 描画関連
	void    ArrowDraw(MATRIX mView);
	void    FloorDraw();
	void    StagingDraw();
	void    UIDraw();   //UIを描画するときにこの中にいろいろ書き込んでいます。
	void    SinarioDraw();
	void	   Draw()    override;	// 描画
	void    MovieDraw();

	// 演出にかかわる関数
	void B_Out_Entry();  //　暗転突入の共通箇所　
	void B_Out_Cancel();  //　暗転解除の共通箇所
	void B_OutBox();

	// 各キャラの当たり判定用(エネミー・バレット・アイテム以外でインデックスを使わない場合は0にする)
	MYRECT_PLUS	GetHitRect(int type, int index, int mx, int my);
	int CheckHitMap(int type, int index, int mx, int my);
	void  PorDelete();//ポータル飛んだ後に消す処理


	// ヒットボックス反動もしくはすり抜け防止用
	HITSLIDE IsHitRect(MYRECT_PLUS pl, MYRECT_PLUS rc);	// キャラ同士の当たり判定
	MYCIRCLE_PLUS HitPlbEne(int index, int cx1, int cy1, int r, MYRECT_PLUS rc); //仮置きのプレイヤー弾と敵の当たった時の処理
    int HitPlbGim(int index, int cx1, int cy1, int r, MYRECT_PLUS rc); //プレイヤー弾とギミック（ドア）の当たった時の処理
    int HitEnbPl(int index, int bullet, int cx1, int cy1, int r, MYRECT_PLUS rc); //敵弾とプレイヤーの当たった時の処理

	// デバッグ用//後に消す///////////////////////////////////////////////
	void    DebugFloorMove(int FloorNum);

protected:

	int _start_movie_use;  //動画を見たかどうか
	int _stageNum;           // 背景切り替え番号
	int _Initcnt; // ステージ初期化のカウント
	bool _fInit;  // フロアの初期化フラグ
	bool _ispop[FLOOR_MAX];  // 画面遷移した時に再度ポップするか　これを用いたif文の枠内は二度目のリポップをしない
	float _fScale[FLOOR_MAX];	// フロアごとのカメラスケール
	float _inputS;   // セットする用のスケール
	bool  _isPMove;   // ポート移動したか
	int   _RelCnt;   // ポートを開放するカウント
	bool  _isZoom;   // 待機状態でズームするか
	float _scaleCnt; // スケールのイージングカウント
	float _camX;  // カメラの移動位置X（イージング）
	float _camY;  // カメラの移動位置Y（イージング）
	float _fcntX; // カメラのイージングカウントX
	float _fcntY; // カメラのイージングカウントY
	int _stacnt[20];  // 演出用のカウント変数（配列で増やしても可） 0:ダメージ 1:ヒール 2:アンチマター 3.4:フロア移動暗転(片方のみでも可)　 10:弾回復　11:ドア解錠 12:HP100回復 13:HP上限100増加 14:転移弾増加 15:敵反物質化 16:黒弾増加 17:貫通増加 18:反射増加 
	bool _stajudge[20]; // 演出用の判定、基本的に上と連動
	int _arrowcnt;   // 矢印動かしのカウント
	int _pause;  //ポーズ画面移行カウント  0の時、通常、1の時ポーズ
	int _stock;  //hpストック
	int bgm_count;//bgmの番号を入れる変数

	

	struct Default_Position {
		// l：左から入ってきたときのポジション、r：右から入ってきたときのポジション
		int  lx[FLOOR_MAX];
		int  ly[FLOOR_MAX];
		int  lx_sub[FLOOR_MAX];
		int  ly_sub[FLOOR_MAX];
		int  rx[FLOOR_MAX];
		int  ry[FLOOR_MAX];	
		int  rx_sub[FLOOR_MAX];
		int  ry_sub[FLOOR_MAX];
	};
	Default_Position _p_pos;

	MYRECT_PLUS _none = { 0,0,0,0,0,0,0,0 };

	ANIMCNT anim[2];


	// マップデータ
	MapData	_mapData;

	// カメラ
	Camera	_cam;

	// プレイヤー
	Player  _player;

	PlayerBullet _plBullet;

	// ポータル
	Portal  _portal;
	
	// ギミック・アイテム
	Gimmick  _gimmick;

	// エネミー
	EnemyBase _enemy;
	EnemyBullet _enBullet;

	// ポーズ
	Pause* _gPause;

	//UI
	gamemainUI _Ui;

	//カットイン演出
	Cutin _cutin;

	//seやbgm

	CharDraw  _talk;

};

