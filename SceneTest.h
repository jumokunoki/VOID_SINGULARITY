/*****************************************************************//**
 * \file   SceneTest.h
 * \brief  �Q�[���{��
 *
 * \author �ޗǏ[���A�V�� ��H
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
	SceneTest();			// �R���X�g���N�^
	virtual ~SceneTest();	// �f�X�g���N�^

	void    StartMovie();							 // ���[�r�[
	void    PortGene();								 // �|�[�^������
	void    PlProcess();							 // �v���C���[
	void    EneProcess();							 // �G�l�~�[
	int       HpStock(int now_hp,int stock);//������100�𒴂������ɃX�g�b�N������₷�֐��ł��@�������P�O�O�񕜂����Ƃ��悤�ɍ�������̂ł������̂܂܃X�g�b�N��+1���Ă��悢�ł��B
	int       StockBreak(int now_hp, int stock);//�����X�g�b�N�������ăv���C���[�̂������O������������X�g�b�N������ĂP�O�O�񕜂���֐��ł��B�@�@���̊֐��ƍ��킹�ăv���C���[��cpp�Ɏ����čs���Ă�����Ă����v�ł��B
	void    SaveSet();                   //�}�b�v�؂�ւ��̃Z�[�u
	void    FloorPosInit();             // �t���A�J�ڌ�̃v���C���[�̏o���ʒu
	void    FloorScaleInit();           // �t���A���Ƃ̃J�����́h�Ђ��A���h�̓x��
	void    FloorCamInit();             // �t���A�J�ڌ�̃J�����ʒu
	void    FloorProcess(int Floornum); // �t���A�ŗL�̏���
	void    FloorCommon(int x, int y, int FloorNum); //�@�t���A�̋��ʏ���
	void    CameraProcess();						 // �J����
	void    UiProcess();							 // UI
	void    Staging();								 // ���o
	void    GameOver();								 // �Q�[���I�[�o�[
	void    BgmProcess();							 // BGM
	void    VolumProcess();							 // ���H�����[��
	void    BgProcess();							 // �w�i
	void	   Process() override;	// �v�Z
	void    LineTerminalProcess();

	// �`��֘A
	void    ArrowDraw(MATRIX mView);
	void    FloorDraw();
	void    StagingDraw();
	void    UIDraw();   //UI��`�悷��Ƃ��ɂ��̒��ɂ��낢�돑������ł��܂��B
	void    SinarioDraw();
	void	   Draw()    override;	// �`��
	void    MovieDraw();

	// ���o�ɂ������֐�
	void B_Out_Entry();  //�@�Ó]�˓��̋��ʉӏ��@
	void B_Out_Cancel();  //�@�Ó]�����̋��ʉӏ�
	void B_OutBox();

	// �e�L�����̓����蔻��p(�G�l�~�[�E�o���b�g�E�A�C�e���ȊO�ŃC���f�b�N�X���g��Ȃ��ꍇ��0�ɂ���)
	MYRECT_PLUS	GetHitRect(int type, int index, int mx, int my);
	int CheckHitMap(int type, int index, int mx, int my);
	void  PorDelete();//�|�[�^����񂾌�ɏ�������


	// �q�b�g�{�b�N�X�����������͂��蔲���h�~�p
	HITSLIDE IsHitRect(MYRECT_PLUS pl, MYRECT_PLUS rc);	// �L�������m�̓����蔻��
	MYCIRCLE_PLUS HitPlbEne(int index, int cx1, int cy1, int r, MYRECT_PLUS rc); //���u���̃v���C���[�e�ƓG�̓����������̏���
    int HitPlbGim(int index, int cx1, int cy1, int r, MYRECT_PLUS rc); //�v���C���[�e�ƃM�~�b�N�i�h�A�j�̓����������̏���
    int HitEnbPl(int index, int bullet, int cx1, int cy1, int r, MYRECT_PLUS rc); //�G�e�ƃv���C���[�̓����������̏���

	// �f�o�b�O�p//��ɏ���///////////////////////////////////////////////
	void    DebugFloorMove(int FloorNum);

protected:

	int _start_movie_use;  //������������ǂ���
	int _stageNum;           // �w�i�؂�ւ��ԍ�
	int _Initcnt; // �X�e�[�W�������̃J�E���g
	bool _fInit;  // �t���A�̏������t���O
	bool _ispop[FLOOR_MAX];  // ��ʑJ�ڂ������ɍēx�|�b�v���邩�@�����p����if���̘g���͓�x�ڂ̃��|�b�v�����Ȃ�
	float _fScale[FLOOR_MAX];	// �t���A���Ƃ̃J�����X�P�[��
	float _inputS;   // �Z�b�g����p�̃X�P�[��
	bool  _isPMove;   // �|�[�g�ړ�������
	int   _RelCnt;   // �|�[�g���J������J�E���g
	bool  _isZoom;   // �ҋ@��ԂŃY�[�����邩
	float _scaleCnt; // �X�P�[���̃C�[�W���O�J�E���g
	float _camX;  // �J�����̈ړ��ʒuX�i�C�[�W���O�j
	float _camY;  // �J�����̈ړ��ʒuY�i�C�[�W���O�j
	float _fcntX; // �J�����̃C�[�W���O�J�E���gX
	float _fcntY; // �J�����̃C�[�W���O�J�E���gY
	int _stacnt[20];  // ���o�p�̃J�E���g�ϐ��i�z��ő��₵�Ă��j 0:�_���[�W 1:�q�[�� 2:�A���`�}�^�[ 3.4:�t���A�ړ��Ó](�Е��݂̂ł���)�@ 10:�e�񕜁@11:�h�A���� 12:HP100�� 13:HP���100���� 14:�]�ڒe���� 15:�G�������� 16:���e���� 17:�ђʑ��� 18:���ˑ��� 
	bool _stajudge[20]; // ���o�p�̔���A��{�I�ɏ�ƘA��
	int _arrowcnt;   // ��󓮂����̃J�E���g
	int _pause;  //�|�[�Y��ʈڍs�J�E���g  0�̎��A�ʏ�A1�̎��|�[�Y
	int _stock;  //hp�X�g�b�N
	int bgm_count;//bgm�̔ԍ�������ϐ�

	

	struct Default_Position {
		// l�F����������Ă����Ƃ��̃|�W�V�����Ar�F�E��������Ă����Ƃ��̃|�W�V����
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


	// �}�b�v�f�[�^
	MapData	_mapData;

	// �J����
	Camera	_cam;

	// �v���C���[
	Player  _player;

	PlayerBullet _plBullet;

	// �|�[�^��
	Portal  _portal;
	
	// �M�~�b�N�E�A�C�e��
	Gimmick  _gimmick;

	// �G�l�~�[
	EnemyBase _enemy;
	EnemyBullet _enBullet;

	// �|�[�Y
	Pause* _gPause;

	//UI
	gamemainUI _Ui;

	//�J�b�g�C�����o
	Cutin _cutin;

	//se��bgm

	CharDraw  _talk;

};

