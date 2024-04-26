/*****************************************************************//**
 * \file   EnemyBullet.h
 * \brief  �G�l�~�[�̒e���
 *
 * \author �ޗǏ[���A�V�� ��H
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "gamemain.h" 
#include "PlayerBullet.h"
#include "EnemyBase.h"

 // �p�x�Ȃǂ̓v���C���[�o���b�g������������Ă���

#define E_BULLET_MAX    10

// ��{�I�ɃG�l�~�[�̔ԍ��ɑΉ�
#define E_BULLET_0      0
#define E_BULLET_1      1
#define E_BULLET_2      2
#define E_BULLET_3      3
#define E_BULLET_4      4
#define E_BULLET_5      5
#define E_BULLET_6      6
#define E_BULLET_7      7
#define E_BULLET_8      8
#define E_BULLET_9      9
#define E_BULLET_10     10

#define COOLTIME1       10
#define COOLTIME2       20
#define COOLTIME3       30
#define COOLTIME4       40
#define COOLTIME5       50
#define COOLTIME6       60
#define COOLTIME7       1200
#define COOLTIME8       180

#define B_SPEED0        10
#define B_SPEED1        20
#define B_SPEED2        40
#define B_SPEED3        60
#define B_SPEED4		50

class EnemyBullet
{
public:
	EnemyBullet();
	virtual ~EnemyBullet();

	void BulletInit(int index, int bullet);
	void BulletDir(int index, int bullet, int aiming, int arrow, int speed, int bullet_type, float direction);

	void E_ShootProcess(int index, int type, int A_cont, int eneX, int eneY, int aiming, int arrow, int chara_x, int chara_y, float turret_dir);
	void E7_ShootProcess(int index, int type, int A_cont, int eneX, int eneY, int chara_x, int chara_y, bool detect, bool guide, bool snipe,int arrow,int BWstate);
	void GuideCurveProcess(int index, int bullet, float chara_x, float chara_y, float chara_w, float chara_h);
	void CommonProcess(int index, float chara_x, float chara_y, float chara_w, float chara_h, float dir);
	void BossEffect(int index);
	void BulletEffect();

	void MapHitProcess(int index, int bullet);
	void DrawTurret(MATRIX mview);
	void Draw(MATRIX mview);

	int GetHitCX(int index, int bullet) { return b_hitcircle[index][bullet].x; }
	int GetHitCY(int index, int bullet) { return b_hitcircle[index][bullet].y; }
	int GetHitCR(int index, int bullet) { return b_hitcircle[index][bullet].r; }
	int GetBWstate(int index, int bullet){return e_bullet[index][bullet].BWstate;}
	int GetType(int index, int bullet) { return e_bullet[index][bullet].bullettype; }
	int GetSnipeCnt() { return _boss_parameter[3]; }

	

protected:

	struct BULLETINFO { // �v���O�������ŒP��̏��A�������͕ς��Ȃ����
		int w, h;               // �摜�g�k
		int bulletmax[ENEMY_MAX];  // �ő�e��
		int limit[ENEMY_MAX];       // ��ʂɏo��e�̌��x�i��O�Ƃ���0�ɒʏ�̍\���A3�ɒʏ�̘A�ˁj
		int delaycnt[ENEMY_MAX][2];    // �A�ˑ��x (���˂܂ł̃J�E���g�ƘA�˂̊Ԋu�̃f�B���C)
	};

	int _boss_parameter[100];   // �{�X�̕����̒e(�f�B���C1�A�f�B���C�Q�A���~�b�g��3�łЂƂ܂Ƃ߂Ȃ̂łR�g��)
	//1.2.3���U���e�p�ɃJ�E���g�g�p�A3.4.5���X�i�C�v�p�ɃJ�E���g�g�p�A6.7���U���e�̋Ȃ���܂ł̃N�[���^�C��,
	//�e���Ƃ̋Ȃ������񐔂̃J�E���g�Ɏg�p����


	struct E_BULLET { // �e���ƂɎ����Ă�����

		int type;
		int bullettype; // �������̎��ɂ���G�l�~�[���Ƃ̃^�C�v
		bool isuse;  // ���̒e���g���Ă��邩 
		int	x, y;		// �v���C���[���W�
		float cx, cy;
		int Xspeed;     // �e�̑���X
		int Yspeed;     // �e�̑���Y
		int arrow;      // �e�̌����A-1�F���A1�F�E
		int BWstate;    // �e�������ꂽ���̃G�l�~�[�̏�ԁi���E���j

		int aiming;     // �v���C���[�̃G�C���̈������
		bool special;    // ��񂾂��K�p�������ꏈ���Ɋւ��Ă̕ϐ��i���ˁE�ђʁj

		float direction; //�G�l�~�[2�Ŏg�킹�Ă�����Ă���p�x���i�[����ϐ��ł��@��ϐ\���󂲂����܂���B
	};
	E_BULLET e_bullet[ENEMY_MAX][E_BULLET_MAX];
	BULLETINFO info_bullet;

	MYCIRCLE b_hitcircle[ENEMY_MAX][E_BULLET_MAX];
	
	MOTION bullet_anim;
};

