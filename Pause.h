/*****************************************************************//**
 * \file   Pause.h
 * \brief  �|�[�Y
 *
 * \author �V�� ��H
 * \date   August 2023
 *********************************************************************/

#pragma once
#include "Option.h"

 //-----------------------------
 // //�}�N��
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

	void PauseInit();//������
	void Process(int* pause, int hp, int hp_stock , int normal, int riflect, int trust, int wpo, int bpo , int hp_max, int max_normal, int max_riflect, int max_trust, int max_wpo, int max_bpo);
	void SelectMove(int select, int instructions, int instructions_count);//�I����ʂ̖��ŏ���
	void GaugeProcess(int now_bullet_nam, int max_bullet_nam, int i, float time);//�Q�[�W�̃C�[�W���O���܂Ƃ߂��֐�
	void Draw(int pause);
	void BulletDraw(int pause, int hp, int hp_stock, int normal, int riflect, int trust, int wpo, int bpo, int hp_max, int max_normal, int max_riflect, int max_trust, int max_wpo, int max_bpo);//�e�n���̕`����܂Ƃ߂�����
	void OptionDraw(int pause);//�I�v�V������ʂ̕`��
	void BalletNumDraw(int x, int y, int bullet_num);//�e�̐��̕`��
	void ParcentDraw(int x, int y, int now_bullet, int max_bullet, int time);//�p�[�Z���g�̕����̕`��

protected:


	//---------------------
	//�|�[�Y��ʂ̕\������̕ϐ�


	int screen_count;   //��ʂ�`�悷��܂ł̃J�E���g�@
	int old_count;      //���t���[���X�N���[���J�E���g���X�V�� -����Ƃ��ɕϊ��������̎g���Ă���@�g�p���Ă������


	float time[6];           //�p�����[�^�[�{�b�N�X�̃C�[�W���O�Ɏg�p
	float select_box_time[3];//�I���{�b�N�X�̃C�[�W���O�Ɏg�p
	float gauge_time[6];//�Q�[�W�̃C�[�W���O�Ɏg�p

	float brend;           //�L�����̃u�����h�Ɏg�p
	float brend_box[6];    //�p�����[�^�{�b�N�X�̃u�����h�Ɏg�p
	int brend_box_time[6];
	float select_brend_box;//�I���{�b�N�X�̃u�����h�Ɏg�p

	struct Box {
		int x, y;
		int w, h;
	};

	Box box[6];//�����̗͂̏���`���Ƃ��̂��A��
	Box select_box[3];//�Z���N�g��ʂ̏���`���Ƃ��̂��A��
	float bullet_parcent[6];//�e�̃Q�[�W���C�[�W���O�ł��Ƃ��Ɏg�� //6��hp�Q�[�W��T��
	//---------------------
	//�|�[�Y��ʂ̑I������̕ϐ�
	int select_count;      //�I������Ƃ��̃J�E���g
	int instructions;      //�Z���N�g�J�E���g�ƘA������ �ړ����邽�߂̃J�E���g
	int instructions_count;//�|�[�Y����h�������ʂɈړ�����Ƃ��̕ϐ�
	int instructions_handle_count[2];//�摜�̔ԍ�������ϐ�
	int select_handle_count[3];//�摜�̔ԍ�������ϐ�
	int waitcount;         //�_�ł̑ҋ@����
	int use;               //�I���ł���悤�ɂȂ�����P�ɂ���

	float flashing;//�_�ł̏����Ɏg���|���Z
	int hang;//�_�ł̏����̊|���Z�Ɏg���ϐ�

	int num_size_min_x, num_size_min_y;//�����n���h���̑傫�����i�[����ϐ��i���j
	int num_size_big_x, num_size_big_y;//�����n���h���̑傫�����i�[����ϐ��i��j


	Option option;

};



