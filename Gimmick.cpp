/*****************************************************************//**
 * \file   Gimmick.cpp
 * \brief  ギミック、アイテム
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#include "Gimmick.h"
#include "mydraw.h"
#include "mymath.h"
#include "gamemain.h"

Gimmick::Gimmick() {

	_door.motaddcount = 0;
	_door.motcount = 0;
	_door.motspeed = 2; 
	_door.motseet = 50;
	Fade = 255;
	hang = -1;

	for(int i = 0; i < GIMMAX; i++) {
		direction[i] = 0;
		_ExistGim[i] = false;
		_state[i] = 0;
		_Possible[i] = true;
		GimHit[i] = Gim_NONE;
	}
}

Gimmick::~Gimmick() {
	
}
void Gimmick::GimInit() {
	for(int i = 0; i < GIMMAX; i++) {
		_ExistGim[i] = false;
		_state[i] = 0;
		_Possible[i] = true;
		GimHit[i] = Gim_NONE;
	}
}
void Gimmick::GeneGimmick(int type, int x, int y, int TreContent) {
	// ギミックの生成
	switch(type) {
	case ITEM_TYPE_AMMO: {
		for(int i = 0; i < PARTI_TB; i++) {
			if(_ExistGim[i] != true) {
				_ExistGim[i] = true;
				GimHit[i].type = type;
				GimHit[i].x = x;
				GimHit[i].y = y;
				GimHit[i].w = GIM_W;
				GimHit[i].h = GIM_H;
				_state[i] = TreContent;
				break;
			}
		}
		break;
	}
	case ITEM_TYPE_TRE: {
		for(int i = PARTI_TB; i < PARTI_HC; i++) {
			if(_ExistGim[i] != true) {
				_ExistGim[i] = true;
				GimHit[i].type = type;
				GimHit[i].x = x;
				GimHit[i].y = y;
				GimHit[i].w = GIM_W;
				GimHit[i].h = GIM_H;
				_state[i] = TreContent;
				break;
			}
		}
		break;
	}
	case ITEM_TYPE_HEAL: {
		for(int i = PARTI_HC; i < PARTI_AMB; i++) {
			if(_ExistGim[i] != true) {
				_ExistGim[i] = true;
				GimHit[i].type = type;
				GimHit[i].x = x;
				GimHit[i].y = y;
				GimHit[i].w = GIM_W;
				GimHit[i].h = GIM_H;
				_state[i] = TreContent;
				break;
			}
		}
		break;
	}
	case ITEM_TYPE_A_MATTER: {
		for(int i = PARTI_AMB; i < PARTI_SL; i++) {
			if(_ExistGim[i] != true) {
				_ExistGim[i] = true;
				GimHit[i].type = type;
				GimHit[i].x = x;
				GimHit[i].y = y;
				GimHit[i].w = GIM_W;
				GimHit[i].h = GIM_H;
				_state[i] = TreContent;
				break;
			}
		}
		break;
	}
	case ITEM_TYPE_LEVER: {
		for(int i = PARTI_SL; i < PARTI_DOOR; i++) {
			if(_ExistGim[i] != true) {
				_ExistGim[i] = true;
				GimHit[i].type = type;
				GimHit[i].x = x;
				GimHit[i].y = y;
				GimHit[i].w = GIM_W;
				GimHit[i].h = GIM_H;
				// 0,1のみ
				_state[i] = TreContent;
				break;
			}
		}
		break;
	}
	case OBJ_TYPE_DOOR: {
		for(int i = PARTI_DOOR; i < GIMMAX; i++) {
			if(_ExistGim[i] != true) {
				_ExistGim[i] = true;
				GimHit[i].type = type;
				GimHit[i].x = x;
				GimHit[i].y = y;
				GimHit[i].w = DOOR_W;
				GimHit[i].h = DOOR_H;
	            GimHit[i].index = i;
				// 0,1のみ
				_state[i] = TreContent;
				break;
			}
		}
		break;
	}
	}
}

void Gimmick::GeneLeverDoor(int LX, int LY, int DX, int DY) {
// 対になるレバーとドアの生成
	GeneGimmick(ITEM_TYPE_LEVER, LX, LY, 0);

	GeneGimmick(OBJ_TYPE_DOOR, DX, DY, 1);
}

void Gimmick::Save(int Floor_Num) {
	// マップを超えて保持するアイテム情報
	for(int i = 0; i < GIMMAX; i++) {
		if(GimHit[i].type == ITEM_TYPE_LEVER || GimHit[i].type == OBJ_TYPE_DOOR || _state[i] != 0) {
			for(int j = 0; j < SAVE_MAX; j++) {
				if(_G_save[Floor_Num].info[j].type != 0) {
					continue;
				}
				_G_save[Floor_Num].info[j] = GimHit[i];
				_G_save[Floor_Num].state[j] = _state[i];
				break;
			}
		}
	}
}

void Gimmick::Load(int FloorNum) {
	// 戻ってきたときにとらなかったアイテムを復活させる
	for(int i = 0; i < SAVE_MAX; i++) {
		switch(_G_save[FloorNum].info[i].type) {
		case 0: {
			break;
		}
		case ITEM_TYPE_AMMO:
		case ITEM_TYPE_TRE:
		case ITEM_TYPE_HEAL:
		case ITEM_TYPE_A_MATTER:
		case ITEM_TYPE_LEVER:
		case OBJ_TYPE_DOOR: {
			GeneGimmick(_G_save[FloorNum].info[i].type, _G_save[FloorNum].info[i].x, _G_save[FloorNum].info[i].y, _G_save[FloorNum].state[i]);
			_G_save[FloorNum].info[i] = Gim_NONE;
			_G_save[FloorNum].state[i] = 0;
			break;
		}
		}
	}
}

void Gimmick::MotProcess() {

	_door.motcount++;
	if(_door.motcount >= _door.motspeed) {
		_door.motcount = 0;
		_door.motaddcount++;
	}
	if(_door.motaddcount * _door.motspeed > ( _door.motseet - 1 ) * _door.motspeed ) {
		_door.motcount = 0;
		_door.motaddcount = 0;
	}
	for(int i = 0; i < GIMMAX; i++) {
		if(GimHit[i].type == ITEM_TYPE_A_MATTER || GimHit[i].type == ITEM_TYPE_HEAL) {
			direction[i] += 2;
			if(direction[i] >= 360) {
				direction[i] = 0;
			}
		}
	}

	Fade += 2.0f * hang;

	if(Fade >= 255 || Fade <= 92.5) {
		hang *= -1;
		if(Fade >= 255) {
			Fade = 254;
		}
		else {
			Fade = 93.5;
		}
	}
}

int Gimmick::Process(HITSLIDE hit) {
	int index = hit.slide_x;
	int done = 0;
	if(hit.hit == ITEM_TYPE_LEVER) {
		if(_state[index] == 0) {
			if(gPad._gTrg[0] & PAD_INPUT_4) {
				_music->MakeSe(_image->Se[15]);//レバーを下げる音
				_state[index] = 1;
				done = 1;
			}
		}
		if(_state[index] == 1) {
			_state[index + SLMAX] = 0;
		}
		if(_state[index + SLMAX] == 0) {
			_Possible[index + SLMAX] = false;
			GimHit[index + SLMAX] = Gim_NONE;
		}
	}
	for(int i = 0; i < GIMMAX; i++) {
		if(_Possible[i] == false) {
			GimHit[i] = Gim_NONE;
		}
	}

	return done;
}

void Gimmick::Draw(MATRIX mview) {
// ギミックの描画
	VECTOR GIMMICK[GIMMAX];
	VECTOR DOOR[GIMMAX];
	for(int i = 0; i < GIMMAX; i++) {
		GIMMICK[i] = VGet(GimHit[i].x + 60,( GimHit[i].y + 60)+ 10*sin(DegToRad(direction[i])), 0);
		DOOR[i] = VGet(GimHit[i].x + 30, GimHit[i].y + 180, 0);

		switch(GimHit[i].type) {
		case ITEM_TYPE_AMMO: {
			if(_ExistGim[i] == true && _Possible[i] == true) {
				for(int j = 0; j < 2; j++) {
					if(j == 0) {
						MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graAmmo(j));
					}
					else {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fade);
						MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graAmmo(j));
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					}
				}
			}
			break;
		}
		case ITEM_TYPE_TRE: {
			if(_ExistGim[i] == true && _Possible[i] == true) {
				SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fade);
				MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graTre(5));
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
				switch(_state[i]) {
				case 1: {
					MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graTre(0));
					break;
				}
				case 2: {
					MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graTre(1));
					break;
				}
				case 3: {
					MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graTre(2));
					break;
				}
				case 4: {
					MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graTre(3));
					break;
				}
				case 5: {
					MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graTre(4));
					break;
				}
				}
			}
			break;
		}
		case ITEM_TYPE_HEAL: {
			if(_ExistGim[i] == true && _Possible[i] == true) {
				for(int j = 0; j < 2; j++) {
					if(j == 0) {
						MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graHeal(j));
					}
					else {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fade);
						MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graHeal(j));
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					}
				}
			}
			break;
		}
		case ITEM_TYPE_A_MATTER: {
			if(_ExistGim[i] == true && _Possible[i] == true) {
				for(int j = 0; j < 2; j++) {
					if(j == 0) {
						MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graA_Matter(j));
					}
					else {
						SetDrawBlendMode(DX_BLENDMODE_ALPHA, Fade);
						MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graA_Matter(j));
						SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
					}
				}
			}
			break;
		}
		case ITEM_TYPE_LEVER: {
			if(_ExistGim[i] == true && _Possible[i] == true) {
				if(_state[i] == 0) {
					MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graSwitch(0));
				}
				else if(_state[i] == 1) {
					MyDrawModiGraph(mview, GIMMICK[i], 1.f, 0.f, GimHit[i].w, GimHit[i].h, _image->Get_graSwitch(1));
				}
			}
			break;
		}
		case OBJ_TYPE_DOOR: {
			if(_ExistGim[i] == true && _Possible[i] == true) {
				MyDrawModiGraph(mview, DOOR[i], 1.f, 0.f, DOOR_W, DOOR_H, _image->Get_graDoor(_door.motaddcount));
			}
			break;
		}
		}
	}
}
