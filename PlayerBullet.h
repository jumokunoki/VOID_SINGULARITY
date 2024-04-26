/*****************************************************************//**
 * \file   PlayerBullet.h
 * \brief  �v���C���[�̒e���
 *
 * \author �ޗǏ[���A�V�� ��H
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "gamemain.h"
#include "mymath.h"
#include "relay_point.h"


#define WHITE_BULLET     0
#define BLACK_BULLET     1
#define WPORTAL_BULLET   2
#define BPORTAL_BULLET   3 
#define REFLECT_BULLET   4
#define TRUST_BULLET     5
#define P_BULLET_KINDS   6   // ��0�A��1�A�|�[�^����2�A�|�[�^����3�A����4�A�ђ�5�̌v

#define P_BULLET_TYPE    4   // �����̎��

#define BULLET_SE_MAX    4

// �ύX�g
#define BULLET_MAX       100 // �e�̘g�i�������̕ύX�p�ɗ]�T�������Ă��܂��j 
#define NORMAL_COOLTIME  10  // �e�̍\���̃f�B���C�iF�j
#define NORMAL_COOLTIME_B 20  // �e�̘A�˂̃f�B���C�iF�j
#define REFLECT_COOLTIME 30
#define TRUST_COOLTIME   60
const int CHARGE_CNT = 90;

// �e�̎�ނɂ��X�s�[�h
#define NORMAL_SPEED     40
#define REFLECT_SPEED    10
#define TRUST_SPEED      60

// �΂ߌ����̉摜�p�x��O�p�֐��v�Z�Ɏg�p
#define DEG1             45
#define DEG2             90
#define DEG3             135
#define DEG4             225
#define DEG5             270
#define DEG6             315

	// �΂ߌ����̉摜�p�x��O�p�֐��v�Z�Ɏg�p
const float  Rad1 = DegToRad(DEG1);
const float  Rad2 = DegToRad(DEG2);
const float  Rad3 = DegToRad(DEG3);
const float  Rad4 = DegToRad(DEG4);
const float  Rad5 = DegToRad(DEG5);
const float  Rad6 = DegToRad(DEG6);

#define BULLET_SHOT_POINT 125

class PlayerBullet
{
public:
	PlayerBullet();
	virtual ~PlayerBullet();
	
	void BulletInit(int index);
	void BWPjudge(int index, int BWPselect);
	void BulletDir(int index, int aiming, int arrow ,int speed ,int plx, int ply,int bullet_type,int reflect,int );       // �e�̏��t��

	void ShootProcess(int Select_Bullet, int BWPselect, int plx, int ply,int aiming , int arrow);
	int  MapHitProcess(int index, int maphit, int point, int aftermovemaphit);
	void Draw(MATRIX mview, int plx, int ply);
	void EffectProcess(int index);

	int GetRemainBulB() { return info_bullet.remainbullet[BLACK_BULLET]; }
	int GetRemainBulPW() { return info_bullet.remainbullet[WPORTAL_BULLET]; }
	int GetRemainBulPB() { return info_bullet.remainbullet[BPORTAL_BULLET]; }
	int GetRemainBulRF() { return info_bullet.remainbullet[REFLECT_BULLET]; }
	int GetRemainBulTR() { return info_bullet.remainbullet[TRUST_BULLET]; }
	int GetUsePortalW() { return info_bullet.usePortalW; }
	int GetUsePortalB() { return info_bullet.usePortalB; }
	int GetStanceType() { return info_bullet.stance_type;}

	int  GetMaxBulB() { return info_bullet.bulletmax[BLACK_BULLET]; }
	int GetMaxBulPW() { return info_bullet.bulletmax[WPORTAL_BULLET]; }
	int GetMaxBulPB() { return info_bullet.bulletmax[BPORTAL_BULLET]; }
	int GetMaxBulRF() { return info_bullet.bulletmax[REFLECT_BULLET]; }
	int GetMaxBulTR() { return info_bullet.bulletmax[TRUST_BULLET]; }

	int GetbulArrow(int index) { return p_bullet[index].arrow; }
	int GetBulletType(int index) { return p_bullet[index].state.bullettype; }
	int GetBulletUse(int index) { return p_bullet[index].usebullet; }
	int GetbulPortal(int index) { return p_bullet[index].state.isPortal; }
	int GetbulW(int index) { return p_bullet[index].state.isWhite; }
	int GetbulB(int index) { return p_bullet[index].state.isBlack; }
	int GetPosX(int index){return p_bullet[index].x;}
	int GetPosY(int index) { return p_bullet[index].y; }
	int GetXspeed(int index) { return p_bullet[index].Xspeed; }
	int GetYspeed(int index) { return p_bullet[index].Yspeed; }
	void SetDeray(int index,int set){info_bullet.delaycnt[index] = set;}
	int GetDeray(int index) { return info_bullet.delaycnt[index]; }
	int GetCharge() { return _power_charge; }
	int GetChargeMax() { return _power_max; }

	void ChargeRemainBul(int B_type) { info_bullet.remainbullet[B_type] = info_bullet.bulletmax[B_type]; }
	void AddBulletMaX(int B_type, int Add) { info_bullet.bulletmax[B_type] += Add; }
	void AddRemBullet(int B_type, int Add) { info_bullet.remainbullet[B_type] += Add; }

	void SetPortalW(int set) { info_bullet.usePortalW = set; }
	void SetPortalB(int set) { info_bullet.usePortalB = set; }

	int GetHitCX(int index) { return b_hitcircle[index].x; }
	int GetHitCY(int index) { return b_hitcircle[index].y; }
	int GetHitCR(int index) { return b_hitcircle[index].r; }

	void SetCutinUse() { cutin_use[0] = 0; cutin_use[1] = 0; }

	

	//�J�b�g�C���֘A
	int GetCutIn() { return cutin; }
	void SetCutIn() { cutin = 0; }



protected:
	struct BULLETINFO { // �v���O�������ŒP��̏��A�������͕ς��Ȃ����
		int usePortalB;   // ���݂���H
		int usePortalW;   // ���݂���H
		// ���e�������̏����Ŕ����̏����͂���
		// �X�ɐݒ肷��ꍇ�͔z��ő��₵�Ă�������
		int w, h;               // �摜�g�k
		float cx, cy;
		int remainbullet[P_BULLET_KINDS];     // ���݂̒e�� �i�ʏ�e�͒e�������Ȃ������A�������̗p�Ӂj
		int bulletmax[P_BULLET_KINDS];  // �ő�e��
		int limit[P_BULLET_TYPE];       // ��ʂɏo��e�̌��x
		int delaycnt[P_BULLET_TYPE];    // �A�ˑ��x
		int stance_type;
	};

	struct BULLETSTATE {   // �e�̑���
		int bullettype; // �ʏ�F0,���ˁF1,�ђʁF�Q
		int isBlack;    // �����e���ǂ���
		int isWhite;    // �����e���ǂ���
		int isPortal;   // �|�[�^���e���H��Q�ƕ��p���Ĕ���
		int cutin_black;//�J�b�g�C�����g�p�������ǂ���
		int cutin_white;//�J�b�g�C�����g�p�������ǂ���
	};

	struct P_BULLET { // �e���ƂɎ����Ă�����

		BULLETSTATE state;      // �e�̃X�e�[�^�X

		int type;
		int usebullet;  // ���̒e���g���Ă��邩 
		int	x, y;		// �v���C���[���W�
		float hx, hy, hw, hh;   // �����蔻��p
		int Xspeed;     // �e�̑���X
		int Yspeed;     // �e�̑���Y
		int arrow;      // �e�̌����A-1�F���A1�F�E
		int aiming;     // �v���C���[�̃G�C���̈������
		bool special;    // ��񂾂��K�p�������ꏈ���Ɋւ��Ă̕ϐ��i���ˁE�ђʁj
		float angle_type; //�ʂ̃G�t�F�N�g�̂��߂̊p�x��ۑ����Ă����֐�
		
	};
	P_BULLET p_bullet[BULLET_MAX];
	BULLETINFO info_bullet;

	MYCIRCLE b_hitcircle[BULLET_MAX];
	
	int _power_charge;
	int _power_max;
	int count[100];
	int cutin;  //1:�ђʁ@2�F��
	int cutin_use[2]; //�O�F���@�P�F��
	bool _trg[4];

};				

