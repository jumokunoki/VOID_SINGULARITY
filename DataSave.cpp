/*****************************************************************//**
 * \file   Player.cpp
 * \brief  ƒvƒŒƒCƒ„[‚Ì‹““®
 *
 * \author   âV“¡ Œè‰H
 * \date   August 2023
 *********************************************************************/

#include "DataSave.h"
DataSave::DataSave() {
	SaveInit();
};

DataSave::~DataSave() {

};

void DataSave::SaveInit() {
	now_stage = 0;
	now_hp = 100;
	max_hp = now_hp;
	gameover_count = 0;
	movie_use = 0;
	for (int i = 0; i < 2; i++) {
		weapon_rereas[i] = 0;
	}
	bullet_number[0] = 20;
	bullet_number[1] = 5;
	bullet_number[2] = 5;

	for (int i = 0; i < 3; i++) {
		bullet_max[i] = bullet_number[i];
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 100; j++) {
			read_scenario[i][j] = 0;
		}
	}
}