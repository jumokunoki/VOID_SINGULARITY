/*****************************************************************//**
 * \file   SceneTest.h
 * \brief  ゲーム本編
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#pragma once
class DataSave
{
public:
	DataSave();
	~DataSave();

	void SaveInit();

	//ゲッター
	int GetStage() { return now_stage; }
	int GetNowHp() { return now_hp; }
	int GetMaxHp() { return max_hp; }
	int GetRereas(int index) { return weapon_rereas[index]; }
	int GetBullet_Num(int index) { return bullet_number[index]; }
	int GetBullet_Max(int index) { return bullet_max[index]; }
	int GetScenario(int index,int j) { return read_scenario[index][j]; }
	int GetGameovercount() { return gameover_count; }
	int GetMovieUse() { return movie_use ; }
	//セッター

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
	int weapon_rereas[2];//0：反射　1：貫通
	int bullet_number[3];//０：反射　１：貫通　２：黒
	int bullet_max[3];//０：反射　１：貫通　２：黒
	int read_scenario[20][100];
	int gameover_count;
	int movie_use;
};