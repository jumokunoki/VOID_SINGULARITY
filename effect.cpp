/*****************************************************************//**
 * \file   effect.cpp
 * \brief  エフェクト
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#include "effect.h"
#include "dxlib.h"
#include "mymath.h"
#include "mydraw.h"

Effect::Effect() {
	EffectInit();
	rifflect_cooltime = 0;
};

Effect::~Effect(){
	
};



void Effect::EffectInit() {
	//初期化
	for(int i = 0; i < EFFECT_MAX; i++) {
		effect[i].use = 0;
		effect[i].Cnt = 0;
		effect[i].cx = 0;
		effect[i].cy = 0;
		effect[i].direction = 0;
		effect[i].chara_type = 0;
	}
};

void Effect::SetEffect( int x, int y, int type, float direction, int aiming, int arrow , int portal, int size,int chara_type) {
	//エフェクトを使うときの設定
	for(int i = 0; i < EFFECT_MAX; i++) {
		
		if(effect[i].use == 0) {
			effect[i].use = 1;
			effect[i].pos = VGet(x , y, 0);
			effect[i].cx = 100;
			effect[i].cy = 100;
			effect[i].direction = direction;
			effect[i].type = type;
			effect[i].chara_type = chara_type;
			VECTOR effect_size = VGet(0,0,0) ;
			int bullet_size = 0;
			//プレイヤーから出るときの位置の調整
			switch(type) {
			case 0: {
				switch(portal) {
				case 0:
					effect[i].type = EFFECT_TYPE_BULLET_NOLMAR;
					effect_size = VGet(50,50,0);
					bullet_size = 7;
					break;
				case 1:
					effect[i].type = EFFECT_TYPE_BULLET_BRACK;
					effect_size = VGet(50, 50, 0);
					break;
				}
				break;
			}
			case 1: {
				effect[i].type = EFFECT_TYPE_BULLET_RIFLECT;
				effect_size = VGet(50, 50, 0);
				break;
			}
			case 2: {
				effect[i].type = EFFECT_TYPE_BULLET_TRUST;
				effect_size = VGet(50, 50, 0); 
				break;
			}
			}
			switch(arrow) {//左
			case 1: {
				switch(aiming) {
				case 0: {//横
					effect[i].pos = VGet(x - effect_size.x + bullet_size, y, 0);
					break;
				}
				case 1: {//斜め上
					effect[i].pos = VGet(x - effect_size.x - bullet_size, y + effect_size.y - bullet_size, 0);
					break;
				}
				case 2: {//斜め下
					effect[i].pos = VGet(x - effect_size.x - bullet_size, y - effect_size.y - bullet_size, 0);
					break;
				}
				case 3: {//上
					effect[i].pos = VGet(x, y + effect_size.y + bullet_size, 0);
					break;
				}
				case 4: {//下
					effect[i].pos = VGet(x, y - effect_size.y + bullet_size, 0);
					break;
				}
				}

			}
				  break;
			case -1: {
				switch(aiming) {
				case 0: {
					effect[i].pos = VGet(x + effect_size.x + bullet_size, y, 0);
					break;
				}
				case 1: {
					effect[i].pos = VGet(x + effect_size.x - bullet_size, y + effect_size.y - bullet_size, 0);
					break;
				}
				case 2: {
					effect[i].pos = VGet(x + effect_size.x - bullet_size, y - effect_size.y - bullet_size, 0);
					break;
				}
				case 3: {
					effect[i].pos = VGet(x, y + effect_size.y + bullet_size, 0);
					break;
				}
				case 4: {
					effect[i].pos = VGet(x, y - effect_size.y + bullet_size, 0);
					break;
				}
				}

			}
			}
			//弾のエフェクトのサイズやタイプの設定
			switch(effect[i].type)
			{
			case EFFECT_TYPE_BULLET_NOLMAR:
				effect[i].sheets = 10;
				effect[i].speed = 1;
				effect[i].cx = 100 * size;
				effect[i].cy = 100 * size;
				break;
			case EFFECT_TYPE_BULLET_RIFLECT:
				effect[i].sheets = 10;
				effect[i].speed = 1;
				effect[i].cx = 100 * size;
				effect[i].cy = 100 * size;
				break;
			case EFFECT_TYPE_BULLET_TRUST:
				effect[i].sheets = 10;
				effect[i].speed = 1;
				effect[i].cx = 100 * size;
				effect[i].cy = 100 * size;
				break;
			case EFFECT_TYPE_BULLET_BRACK:
				effect[i].sheets = 13;
				effect[i].speed = 1;
				effect[i].cx = 100 * size;
				effect[i].cy = 100 * size;
				break;
			case EFFECT_TYPE_BULLET_BPORTAL:
				effect[i].sheets = 20;
				effect[i].speed = 1;
				effect[i].cx = 200 * size;
				effect[i].cy = 200 * size;
				break;
			case EFFECT_TYPE_BULLET_WPORTAL:
				effect[i].sheets = 20;
				effect[i].speed = 1;
				effect[i].cx = 200 * size;
				effect[i].cy = 200 * size;
				break;
			case EFFECT_TYPE_BULLET_ANNIHILAT:
				effect[i].sheets = 15;
				effect[i].speed = 4;
				effect[i].cx = 200 * size;
				effect[i].cy = 200 * size;
				break;
			case EFFECT_TYPE_RIFFLECT_WALL:
				effect[i].sheets = 11;
				effect[i].speed = 1;
				effect[i].cx = 50 * size;
				effect[i].cy = 50 * size;
				break;
			case EFFECT_TYPE_NORMAL_WALL:
				effect[i].sheets = 11;
				effect[i].speed = 1;
				effect[i].cx = 100 * size;
				effect[i].cy = 100 * size;
				break;
			case EFFECT_TYPE_NORMAL_SHOT:
				effect[i].sheets = 11;
				effect[i].speed = 1;
				effect[i].cx = 50 * size;
				effect[i].cy = 50 * size;
				break;
			case EFFECT_TYPE_RIFLECT_BOOST:
				effect[i].sheets = 1;
				effect[i].speed = 15;
				effect[i].cx = 100 * size;
				effect[i].cy = 100 * size;
				break;
			case EFFECT_TYPE_BLACK_BOOST:
				effect[i].sheets = 1;
				effect[i].speed = 15;
				effect[i].cx = 100 * size;
				effect[i].cy = 100 * size;
				break;
			case EFFECT_TYPE_BOMBER:
				effect[i].sheets = 17;
				effect[i].speed  = 2 * size;
				effect[i].cx = 400 * size;
				effect[i].cy = 400 * size;
			}
			//ボスの時、弾から出るエフェクトの位置調整
			if (effect[i].chara_type == EFFECT_BOSS) {
				effect[i].pos = VGet(x - (effect[i].cx / 2) * cos(DegToRad(effect[i].direction)), y - (effect[i].cy / 2) * sin(DegToRad(effect[i].direction)), 0);
			}
			break;
		}
	}
};


VECTOR Effect::AngreProcess(int direction) {
	//プレイヤーの向きの位置調整
	int x = 0;
	int y = 0;
	int effect_size = 50;
	int bullet_size = 7;
	VECTOR re = VGet(0, 0, 0);
	switch((int)direction) {
	case 0: {
		re = VGet(x - effect_size - bullet_size, y, 0);
		break;
	}
	case 45: {
		re = VGet(x - effect_size + bullet_size, y - effect_size + bullet_size, 0);
		break;
	}
	case 90: {
		re = VGet(x, y - effect_size - bullet_size, 0);
		break;
	}
	case 135: {
		re = VGet(x + effect_size - bullet_size, y - effect_size + bullet_size, 0);
		break;
	}
	case 180: {
		re = VGet(x + effect_size + bullet_size, y, 0);
		break;
	}
	case 225: {
		re = VGet(x + effect_size - bullet_size, y + effect_size - bullet_size, 0);
		break;
	}
	case 270: {
		re = VGet(x, y + effect_size + bullet_size, 0);
		break;
	}
	case 315: {
		re = VGet(x - effect_size + bullet_size, y + effect_size - bullet_size, 0);
		break;
	}
	}
	return re;
}
void Effect::CountEffect() {
	for(int i = 0; i < EFFECT_MAX; i++) {
		if(effect[i].use == 1) {
			effect[i].Cnt++;
		}
	}
	if(rifflect_cooltime > 0) {
		rifflect_cooltime--;
	}
}

void Effect::DoEffect() {
	//エフェクトが使われているとき動かす
	for(int i = 0; i < EFFECT_MAX; i++) {
		if(effect[i].use == 1) {
			if(effect[i].Cnt > effect[i].speed * effect[i].sheets - 1) {
				//初期化
				effect[i].Cnt = 0;
				effect[i].use = 0;
				effect[i].direction = 0;
				effect[i].type = -1;
				effect[i].chara_type = 0;
			}
		}
	}
};

void Effect::ShootDraw(MATRIX mview, int plx, int ply, int arrow, int aiming) {
	//弾を打った時の爆発エフェクト
	const int point = 70;
	const int BULLET_SHOT_POINT = 125;
	VECTOR pos = VGet(0, 0, 0);
	for(int i = 0; i < EFFECT_MAX; i++) {
		if(effect[i].type == EFFECT_TYPE_NORMAL_SHOT) {
			switch(arrow) {
			case 1: {
				switch(aiming) {
				case 0: {
					pos.x = (plx + BULLET_SHOT_POINT) + 50 + point * cos(0);
					pos.y = (ply + BULLET_SHOT_POINT)      + point * sin(0);
					break;
				}
				case 1: {
					pos.x = (plx + BULLET_SHOT_POINT) + 30 + point * cos(DegToRad(315));
					pos.y = (ply + BULLET_SHOT_POINT) - 10 + point * sin(DegToRad(315));
					break;
				}
				case 2: {
					pos.x = (plx + BULLET_SHOT_POINT) +35 + point  * cos(DegToRad(45));
					pos.y = (ply + BULLET_SHOT_POINT) +15 + point  * sin(DegToRad(45));
					break;
				}
				case 3: {
					pos.y = (ply + BULLET_SHOT_POINT) + -90 + point * sin(270);
					pos.x = (plx + BULLET_SHOT_POINT) + -70 + point * cos(270);
					break;
				}
				case 4: {
					pos.x = (plx + BULLET_SHOT_POINT) + 45 + point * cos(90);
					pos.y = (ply + BULLET_SHOT_POINT)      + point * sin(90);
					break;
				}
				}
				break;
			case -1: {
				switch(aiming) {
				case 0: {
					pos.x = (plx + BULLET_SHOT_POINT) - 20 + point * cos(180);
					pos.y = (ply + BULLET_SHOT_POINT) + 30 + point * sin(180);
					break;
				}
				case 1: {
					pos.x = (plx + BULLET_SHOT_POINT) + 20 + point * cos(DegToRad(225));
					pos.y = (ply + BULLET_SHOT_POINT) - 30 + point * sin(DegToRad(225));
					break;
				}
				case 2: {
					pos.x = (plx + BULLET_SHOT_POINT) +10 + point  * cos(DegToRad(135));
					pos.y = (ply + BULLET_SHOT_POINT)     + point  * sin(DegToRad(135));
					break;
				}
				case 3: {
					pos.x = (plx + BULLET_SHOT_POINT) - 20 + point * cos(270);
					pos.y = (ply + BULLET_SHOT_POINT) - 100 + point * sin(270);
					break;
				}
				case 4: {
					pos.x = (plx + BULLET_SHOT_POINT) + 45 + point * cos(90);
					pos.y = (ply + BULLET_SHOT_POINT)      + point * sin(90);
					break;
				}
				}
			}
			}
			}
			MyDrawModiGraph(mview, pos, 1.f, DegToRad(effect[i].direction), effect[i].cx, effect[i].cy, _image->GetCgEffect(effect[i].type,(effect[i].Cnt / effect[i].speed) % effect[i].sheets));
		}
	}
}

void Effect::Draw(MATRIX mview) {
	//ほとんどのエフェクトの描画
	for(int i = 0; i < EFFECT_MAX; i++) {
		if(effect[i].use == 1) {
			if(effect[i].type != -1) {
				if(effect[i].type != EFFECT_TYPE_BULLET_NOLMAR && effect[i].type != EFFECT_TYPE_NORMAL_SHOT && effect[i].type != EFFECT_TYPE_BULLET_RIFLECT  ) {
					MyDrawModiGraph(mview, effect[i].pos, 1.f, DegToRad(effect[i].direction), effect[i].cx, effect[i].cy, _image->GetCgEffect(effect[i].type,(effect[i].Cnt / effect[i].speed) % effect[i].sheets));
				}
				else if(effect[i].type == EFFECT_TYPE_BULLET_RIFLECT) {
					MyDrawModiGraph(mview, effect[i].pos, 1.f, DegToRad(effect[i].direction), effect[i].cx, effect[i].cy, _image->GetCgEffect(effect[i].type,(effect[i].Cnt / effect[i].speed) % effect[i].sheets));
				}
			}
		}
	}
}

void Effect::NormalDraw(MATRIX mview, VECTOR vector,float direction) {
	//通常弾は常に弾の後ろにあるのでその位置におく
	for(int i = 0; i < EFFECT_MAX; i++) {
		if(effect[i].use == 1 ) {
			if(effect[i].type == EFFECT_TYPE_BULLET_NOLMAR) {

				VECTOR a = AngreProcess((int)direction);
			
				VECTOR vec = VAdd(vector, a);

				MyDrawModiGraph(mview, vec, 1.f, DegToRad(direction), effect[i].cx, effect[i].cy, _image->GetCgEffect(effect[i].type,(effect[i].Cnt / effect[i].speed) % effect[i].sheets));

			}
		}
	}
}

