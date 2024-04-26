/*****************************************************************//**
 * \file   SceneTest.h
 * \brief  �Q�[���{��
 *
 * \author �ޗǏ[���A�V�� ��H
 * \date   August 2023
 *********************************************************************/

#pragma once
class DataSave
{
public:
	DataSave();
	~DataSave();

	void SaveInit();

	//�Q�b�^�[
	int GetStage() { return now_stage; }
	int GetNowHp() { return now_hp; }
	int GetMaxHp() { return max_hp; }
	int GetRereas(int index) { return weapon_rereas[index]; }
	int GetBullet_Num(int index) { return bullet_number[index]; }
	int GetBullet_Max(int index) { return bullet_max[index]; }
	int GetScenario(int index,int j) { return read_scenario[index][j]; }
	int GetGameovercount() { return gameover_count; }
	int GetMovieUse() { return movie_use ; }
	//�Z�b�^�[

	void SetStage(int index) { now_stage = index; }
	void SetNowHp(int index) { now_hp = index; }
	void SetMaxHp(int index) { max_hp = index; }
	void SetRereas(int index,int j) { weapon_rereas[index] = j; }
	void SetBullet_Num(int index,int j) {  bullet_number[index] = j; }
	void SetBullet_Max(int index, int j) { bullet_max[index] = j; }
	void SetScenario(int index, int j) { read_scenario[index][j] = 1; }
	void SetGameovercount() { gameover_count++; }
	void SetMovieUse() { movie_use = 1; }

protected:
	int now_stage;
	int now_hp;
	int max_hp;
	int weapon_rereas[2];//0�F���ˁ@1�F�ђ�
	int bullet_number[3];//�O�F���ˁ@�P�F�ђʁ@�Q�F��
	int bullet_max[3];//�O�F���ˁ@�P�F�ђʁ@�Q�F��
	int read_scenario[20][100];
	int gameover_count;
	int movie_use;
};