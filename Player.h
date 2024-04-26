/*****************************************************************//**
 * \file   Player.h
 * \brief  �v���C���[�̏��
 *
 * \author �ޗǏ[���A�V�� ��H
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "character.h"
#include "DxLib.h"
#include "mymath.h"
#include "PlayerBullet.h"
#include "relay_point.h"

class Player
{
public:
	Player();
	virtual ~Player();

	void Gravity();
	void DetectGravity(int Gjudge);
	void PotInvProcess();
	void MoveProcess();
	void PosHitSynchro();
	void HitObj(HITSLIDE HitObj, MYRECT_PLUS enemy);
	void AimProcess(int remRF, int remTR, int remBR, int remPW, int remPB,int deray);
	void DamageProcess(int hit);
	void EffectDraw(MATRIX mview);
	void Draw(MATRIX mView);
	void AddIT();
	void DoFrameCount(int stock);
	void SetMotSpeed();
	void PortalMoveSet(int PorX, int PorY);
	void PortalMoveProcess();
	void ChengeFrameCount(int handred, int ten, int one, int oldmot);
	// �X�e�[�W�J�ڂɂ�镐��̊J������
	void ReleaseRef() { _Re_release = 1; }
	void ReleaseTr() { _Tr_release = 1; }

	// �Q�b�^�[�E�Z�b�^�[
	int GetcharaType() { return _gPlayer.type; }
	int GetPosX() { return _gPlayer.x; }
	int GetPosY() { return _gPlayer.y; }
	int GetPosW() { return _gPlayer.w; }
	int GetPosH() { return _gPlayer.h; }
	int GetPosCX() { return _gPlayer.x+135+30; }
	int GetPosCY() { return _gPlayer.y+75+100; }
	MYRECT_PLUS GetRect() { return _gPlayer.hit; }
	float GetGravity() { return _gPlayer.gravity; }
	int GetRunSpeed() { return _gPlayer.Rspeed; }
	int GetArrow() { return _gPlayer.arrow; }
	int GetAiming() { return _gPlayer.aiming; }
	int GetBWP_select() { return b_select.BWPselect; }
	int GetBulletType() { return b_select.bulletType; }
    bool GetD_judge() { return _S_damjudge; }
	bool GetI_judge() { return _invijudge; }
	int GetInviT() { return _invincible_time; }
	int GetHitSX() { return _hitslideX; }
	int GetHitSY() { return _hitslideY; }
	int GetPotInv() { return _gPlayer.Portal_invincibility; }
	int GetPorDel() { return _gPlayer.Portal_delete; }
	VECTOR GetStaPoint() { return _start_point; }

	void ReSetBulletType() {b_select.bulletType = 0; }

	void SetPosX(int x) { _gPlayer.x = x; }
	void SetPosY(int y) { _gPlayer.y = y; }
	void SetD_judge() { _S_damjudge = false; }
	void SetPotInv(int index) { _gPlayer.Portal_invincibility = index; }
	void SetPorDel() { _gPlayer.Portal_delete = 0; }
	void SetTerminal(VECTOR terminal) { _terminal = terminal; }

	void AddPosX(int x) { _gPlayer.x += x; }
	void AddPosY(int y) { _gPlayer.y += y; }
	void AddMaxHP() { _gPlayer.maxhp += 100; }
	void HealHP(){ _gPlayer.hp += 100;}

	//UI
	int GetHp() { return _gPlayer.hp; }
	int GetHpMax() { return _gPlayer.maxhp; }
	int GetReflectRelease() { return _Re_release; }
	int GetTrustRelease() { return _Tr_release; }

	void SetOldMotion() { _gPlayer.oldmot = 0 + _gPlayer.motten * 10 + 0; }
	int  GetMotAdd() { return _gPlayer.motaddnum; }
	int  GetMotionH() { return _gPlayer.mothandred; }
	int  GetMotionT() { return _gPlayer.motten; }
	int  GetMotionO() { return _gPlayer.motone; }
	int  GetOldMotion() { return _gPlayer.oldmot; }
	void SetHpToMax() { _gPlayer.hp  = 100; }
	void SetDamage(int damage) { _gPlayer.hp -= damage; }
	void SetRecovery(int recovery) { _gPlayer.hp += recovery; }

protected:
	// �v���C��[�̏��
	struct CHARA {
		int		 type;		// �L�����^�C�v�B CHARA_TYPE_xxxx
		int		 x, y;		// �z�u���W
		int      w, h;       // �n�`����p
		MYRECT_PLUS hit;    // �����蔻��p
		int		 hx, hy, hw, hh;		// �_���[�W�����蔻��
		int		 hp, maxhp;	// �̗�/�ő�̗�
		
		int		 arrow;		// �����B�� = -1, �E = 1
		int      Rspeed;     //�@����X�s�[�h
	
		int		 useGravity;	// �d�͏���������Ȃ�1, �����Ȃ��Ȃ�0
		float	 gravity;	// �d�͂ɂ������l
		int		 stand;		// ���t���O�B���n���Ă�����1
		int      isAim;
		int      aiming;     // �e�̏Ə��Barrow�ƕ��p�Barrow(0,1)*5������10�����A�j���[�V�����ƒe�̕�����ݒ� 0:��1:�΂ߏ�2:�΂߉�3:��4:��
	
		int     Portal_invincibility;
		int     Portal_delete;

		int		 motaddnum;		// ���[�V����ID�B MOTION_xxxx_xxxxx
		int      mothandred;
		int      motten;
		int      motone;
		int		 motcnt;		// ���[�V�����J�E���^�B0�`
		int      oldmot;     // �O�̃��[�V����
		int      motsheet;   // ���[�V�����V�[�g
		int      motspeed;   // ���[�V�����̃X�s�[�h
		int      falling_mot;
		int      loop;
		//int		animcnt;	// �A�j���[�V�����J�E���^�B0�`
	};
	struct CHARA _gPlayer;
	

	struct B_SELECT {
		int BWPselect;    // ��(�ʏ�)�E���E���|�[�^���E���|�[�^��
		int bulletType;   // �ʏ�E���ˁE�ђʁE��
	};
	B_SELECT b_select;

	struct PORTAL_MOVE {
		int x, y;
		int count, max_count;
	};
	PORTAL_MOVE port;
	int jampcount;
	int waitcount;
	// �����ɓ����������̔���
	int _hitslideX;
	int _hitslideY;
	// ���G���Ԕ���p
	bool _invijudge;
	int _invincible_time;
	int _Re_release;     // ���˂̉��
	int _Tr_release;     // �ђʂ̉��
	bool _S_damjudge;   // ��ʉ��o�p�i�_���[�W���j
	MYRECT_PLUS _none = { 0,0,0,0,0,0,0,0 };
	VECTOR _start_point; // �Ə����̎n�_
	VECTOR _terminal;   // �Ə����̏I�[
};

