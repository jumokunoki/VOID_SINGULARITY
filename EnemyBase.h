/*****************************************************************//**
 * \file   EnemyBase.h
 * \brief  �G�l�~�[�֘A�̊�
 *
 * \author �ޗǏ[���A�V�� ��H
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "character.h"
#include "gamemain.h"
#include "DxLib.h"
#include "mymath.h"
#include "relay_point.h"

// �G�̍ő吔
constexpr int  ENEMY_MAX     = 30;
// �摜�̑傫��
constexpr int  GRAPH_W       = 200;
constexpr int  GRAPH_H       = 200;
constexpr int  BOSS_GRAPH_WH = 600;

 //�@�����蔻��̋�`�v�Z���A���Z���鐔�l
constexpr int  E1_HIT_X  = 60;
constexpr int  E2_HIT_XY = 50;
constexpr int  E2_HIT_WH = 100;
constexpr int  E3_HIT_X  = 50;
constexpr int  E3_HIT_Y  = 50;
constexpr int  E3_HIT_W  = 720;
constexpr int  E3_HIT_H  = 270;

// ��̗��̑傫��
constexpr int wing1_W = 320;
constexpr int wing1_H = 150;
// ���̗��̑傫��
constexpr int wing2_W = 530;
constexpr int wing2_H = 250;
// ����
constexpr int wing3_W = 580;
constexpr int wing3_H = 70;

// �U������
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

	// �v�Z����
	void RadCalculateE7(int index, int chara_x, int chara_y, HITSLIDE search, HITSLIDE search2);  // �G�l�~�[7�p�̃��W�A���v�Z

	// �{�X�̋���(Enemy_BossMotion.cpp)
	void BossMotion(int index, int chara_x, int chara_y, HITSLIDE search, HITSLIDE search2, int map_w, int map_h);
	void BossPosChange(int index);

// ������
	void CharaInit(int index);
	void BossInit();
	void AllInit();

// �Q�b�^�[�E�Z�b�^�[
	int GetPosEnemyX(int index) { return _enemy[index].pos.x; }
	int GetPosEnemyY(int index) { return _enemy[index].pos.y; }
	int GetArrow(int index) { return _enemy[index].arrow; }
	int GetAiming(int index) { return _enemy[index].aiming; }
	int GetMX(int index) { return _enemy[index].movespeed * _enemy[index].arrow; }
	int GetType(int index) { return _enemy[index].type; }
	// �����蔻��̋�`
	MYRECT_PLUS GetRect_P(int index) { return _enemy[index].hit; }
	MYRECT_PLUS GetRect_BOSSF(int index) { return _variable.boss_hit[0]; }
	MYRECT_PLUS GetRect_BOSSS(int index) { return _variable.boss_hit[1]; }
	MYRECT_PLUS GetRect_BOSST(int index) { return _variable.boss_hit[2]; }
	// �T�[�`�̔���̋�`(�{�X�͕��p)
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

	//�V�[���؂�ւ��p
	int GetHp(int index) { return _enemy[index].hp; }
	int GetMaxHp(int index) { return _enemy[index].maxhp; }
	float GetBulletDir(int index) { return _enemy[index].direction; }
	
protected:

	struct ENEMY {
		int		type;		// �L�����^�C�v�B CHARA_TYPE_xxxx
		VECTOR  pos;        // �ʒu����
		MYRECT  graph;		// �摜���W�E�傫��
		MYRECT_PLUS hit;    // �����蔻��p
		MYRECT_PLUS search; // �T�[�`�p��`
		int     cx, cy;		// �L�����̒��S�ʒu
		int		init_pointY;// ��G�l�~�[�̉�������C�����邽�߂ɗp����ϐ��iAddEnemy�����ۂ�Y���W�j 
		int     base_point; // �L�����̍s���͈͂̊�_
		int		hp;	        // �̗�
		int     maxhp;      //�@�ő�̗̑�
	
		bool     isuse;
		int     action_control;   // �s���̊Ǘ��ԍ�
		int     action_cnt;       // �s�����̃f�B���C
		bool    isAim;      // �v���C���[���͈͓��ɓ����Ă����Ƃ�ON
		float   direction;  // ���낢��g���p�x
		float   angle;      // �{�X�G�l�~�[�̎˒��p
		int		arrow;		// �����B�� = -1, �E = 1
		int     aiming;     // �e�̏Ə��Barrow�ƕ��p�Barrow(0,1)*5������10�����A�j���[�V�����ƒe�̕�����ݒ� 0:��1:�΂ߏ�2:�΂߉�3:��4:��

		int bomber_se;//�����̃Z�b�g
		int bomber_count;//�����܂ł̃J�E���g
		int detection_sound;//�T�m��

		int     movespeed;  //�@����X�s�[�h
		bool    isWhite;    //  �G�ɔ����t�^����Ă��邩
		bool    isBlack;    //  �G�ɍ����t�^����Ă��邩

		// �摜�E�A�j���[�V�����֘A
		int		motId;		// ���[�V����ID�B MOTION_xxxx_xxxxx
		int		motcnt;		// ���[�V�����J�E���^�B0�`
		int		animcnt;	// �A�j���[�V�����J�E���^�B0�`
	};

	ENEMY _enemy[ENEMY_MAX];

	struct BOSS {
		// �{�X�p�̃p�����[�^
		MYRECT_PLUS boss_hit[3];    // BOSS�����蔻��p
		MYRECT_PLUS search; // �ǉ��T�[�`�p��`
		float   angle[2];      // �{�X�G�l�~�[�̎˒��p
		bool    isdetectB;	   // �^���b�g�e�̔��˔���
		bool    isguideB;	   // �U���e�̔��˔���
		bool    issnipeB;      // �X�i�C�v�e�̔��˔���
		int     easingcnt;     // �C�[�W���O�ɗv����J�E���g
		int     turncnt;       // ��ʓ��Ő؂�Ԃ��Ƃ��̃J�E���g
		float   targetX;       // ��ʊO�ɏo��Ƃ��̖ڕW���WX
		float   targetY;       // ��ʊO�ɏo��Ƃ��̖ڕW���WY
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
	
	int _contlCnt[5];			// �G�l�~�[�̍s�������Ԑ��䂷�邽�߂̃J�E���g
	MYRECT_PLUS _none = { 0,0,0,0,0,0,0,0 };
};
