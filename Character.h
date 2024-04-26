/*****************************************************************//**
 * \file   Character.cpp
 * \brief  �L�����N�^�[���
 * 
 * \author �ޗǏ[��
 * \date   August 2023
 *********************************************************************/

#pragma once


 // ���[�V�����ԍ��B0�Ԃ���̒ʂ��ԍ��ł��邱��
 // �v���C���[�p
#define	MOTION_R_STAND		0
#define	MOTION_L_STAND		1
#define	MOTION_R_RUN		2
#define	MOTION_L_RUN		3
#define	MOTION_R_ATTACK		4
#define	MOTION_L_ATTACK		5
#define	MOTION_R_DAMAGE		6
#define	MOTION_L_DAMAGE		7
#define	MOTION_R_JUMP_UP	8
#define	MOTION_L_JUMP_UP	9
#define	MOTION_R_JUMP_DOWN	10
#define	MOTION_L_JUMP_DOWN	11
// �A�C�e���p
#define	MOTION_ITEM_POINT_0_NORMAL	12	// ���F��
#define	MOTION_ITEM_POINT_1_NORMAL	13	// ���F��
#define	MOTION_ITEM_POINT_2_NORMAL	14	// ���F��
#define	MOTION_ITEM_POINT_3_NORMAL	15	// ���F��


// �A�j���[�V�����p�^�[���p��`
// �z��̔ԍ��͊Ԃ��󂯂ė]�T�������Đݒ肵�Ă��܂�
// �v���C���[
#define	PT_STAND		0		//  0�` 20��
#define	PT_RUN		20		//  20�` 6��
#define	PT_ATTACK	30		//  30�` 7��
#define	PT_DAMAGE	40		//  40�` 1��
#define	PT_JUMP_UP	50		//  50�` 2��
#define	PT_JUMP_DOWN	60		//  60�` 2��

#define	_PT_CHARA_ALLNUM_	    200		// �S�p�^�[������

//���[�V�����p�^�[��
#define _PT_CHARA_ATTACK_NORMAL  0
#define _PT_CHARA_ATTACK_REFLECT 1
#define _PT_CHARA_ATTACK_TRUST   2
#define _PT_CHARA_ATTACK_BLACK   3
#define _PT_CHARA_STAND_LEFT     4
#define _PT_CHARA_STAND_RIGHT    5
#define _PT_CHARA_RUN_LEFT       6
#define _PT_CHARA_RUN_RIGHT      7
#define _PT_CHARA_JAMP_LEFT      8
#define _PT_CHARA_JAMP_RIGHT     9


#define _PT_ENEMY_ALLNUM    10

// �L�����^�C�vID�@
#define	CHARA_TYPE_NONE		0	// �L���������iuse=0�I�Ɏg�p�j
#define	CHARA_TYPE_PLAYER	1	// �v���C���[
#define	CHARA_TYPE_ENEMY1	2	// �G�l�~�[1
#define	CHARA_TYPE_ENEMY2	3	// �G�l�~�[2
#define	CHARA_TYPE_ENEMY3	4	// �G�l�~�[3
#define	CHARA_TYPE_ENEMY4	5	// �G�l�~�[4
#define	CHARA_TYPE_ENEMY5	6	// �G�l�~�[5
#define	CHARA_TYPE_ENEMY6	7	// �G�l�~�[6
#define	CHARA_TYPE_ENEMY7	8	// �G�l�~�[7
#define	CHARA_TYPE_ENEMY8	9	// �G�l�~�[8
#define	CHARA_TYPE_ENEMY9	10	// �G�l�~�[9

#define BULLET_TYPE_PLAYER  20
#define BULLET_TYPE_ENEMY   30
// �G�l�~�[���Ƃɒe�̉������������ȉ����g�p�i�����蔻�蓙�j
#define BULLET_TYPE_ENEMY1  31
#define BULLET_TYPE_ENEMY2  32
#define BULLET_TYPE_ENEMY3  33
#define BULLET_TYPE_ENEMY4  34
#define BULLET_TYPE_ENEMY5  35
#define BULLET_TYPE_ENEMY6  36
#define BULLET_TYPE_ENEMY7  37
#define BULLET_TYPE_ENEMY8  38
#define BULLET_TYPE_ENEMY9  39
#define BOSS_HIT1           40
#define BOSS_HIT2           41
#define BOSS_HIT3			43

#define	ITEM_TYPE_AMMO		50	// �A�C�e���F�񕜔�
#define	ITEM_TYPE_TRE		51	// �A�C�e���F�g���W���[�{�b�N�X
#define	ITEM_TYPE_HEAL		52	// �A�C�e���F�q�[���J�v�Z��
#define	ITEM_TYPE_A_MATTER	53	// �A�C�e���F������
#define	ITEM_TYPE_LEVER		54	// �A�C�e���F���o�[
#define	OBJ_TYPE_DOOR	    60	// �I�u�W�F�N�g�F�W���[�i��	

#define SEARCH_AREA1        70
#define SEARCH_AREA2        71 
#define SEARCH_AREA3        72

#define Black_Hole			777 
#define White_Hole			888
#define Fix_Black_Hole			444 
#define Fix_White_Hole			666

#define	CHARA_MAX		100		// �L������

// �����蔻��p�̂��ꂼ��̕�
#define PLAYER_W    60
#define PLAYER_H    200
#define P_BULLET_W  30
#define P_BULLET_H  15
#define ENEMY_W      80
#define ENEMY_H     200
#define ENEMY_TWO_W 100
#define ENEMY_TWO_H 100
#define E_BULLET_W  30
#define E_BULLET_H  15

