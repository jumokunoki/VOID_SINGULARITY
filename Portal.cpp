/*****************************************************************//**
 * \file   Portal.cpp
 * \brief  ポータル
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/

#include "Portal.h"
#include "Character.h"
#include "PlayerBullet.h"
#include "mydraw.h"

Portal::Portal() {
	portB = port_NONE;
	portW = port_NONE;
	FixportB = port_NONE;
	FixportW = port_NONE;

	portal_count = 0;

	for (int i = 0; i < 4; i++) {
		portal_effect_count[i] = 0;
	}

}

Portal::~Portal() {

}

void Portal::PortalGenerate(int portBW, int x, int y) {
	// ポータルの生成処理
	if(portBW == WPORTAL_BULLET) {
		portW = { White_Hole, x - _cx, y - _cy, PORT_W, PORT_H, 0, 0, 0 };
	}
	if(portBW == BPORTAL_BULLET) {
		portB = { Black_Hole, x - _cx, y - _cy, PORT_W, PORT_H, 0, 0, 0 };
	}
	if(portBW == Fix_White_Hole) {
		FixportW = { Fix_White_Hole, x - _cx, y - _cy, PORT_W, PORT_H, 0, 0, 0 };
	}
	if(portBW == Fix_Black_Hole) {
		FixportB = { Fix_Black_Hole, x - _cx, y - _cy, PORT_W, PORT_H, 0, 0, 0 };
	}
}

void Portal::PortalProcess() {
	int speed = 4;
	if(portal_count <= 20 * speed) {
		portal_count++;
	}
	else {
		portal_count = 0;
	}

	for (int i = 0; i < 4; i++) {
		if (portal_effect_count[i] <= 41 * speed -1) {
			portal_effect_count[i]++;
		}
		else {
			portal_effect_count[i] = 19 * speed;
		}
	}

};

void Portal::PortalDraw(MATRIX mview) {
	int speed = 4;
	int sheet_max = 41;

	VECTOR portB_pos = VGet(portB.x + portB.w / 2, portB.y + portB.h / 2, 0);
	VECTOR portW_pos = VGet(portW.x + portW.w / 2, portW.y + portW.h / 2, 0);
	VECTOR FixportB_pos = VGet(FixportB.x + FixportB.w / 2, FixportB.y + FixportB.h / 2, 0);
	VECTOR FixportW_pos = VGet(FixportW.x + FixportW.w / 2, FixportW.y + FixportW.h / 2, 0);

	if (portB_pos.x == 0) {
		portal_effect_count[0] = 0;
	}
	if (portW_pos.x == 0) {
		portal_effect_count[1] = 0;
	}
	
	if(portB_pos.x != 0) {
		MyDrawModiGraph(mview, portB_pos, 1.0f, 0.0f, 200, 200, _image->GetBlack_Portal_Handle((portal_count / speed)% SHEET_MAX));
		MyDrawModiGraph(mview, portB_pos, 1.0f, 0.0f, 200, 200, _image->GetBlack_Portal_Effect_Handle((portal_effect_count[0] / speed) % sheet_max));
	}
	if(portW_pos.x != 0) {
		MyDrawModiGraph(mview, portW_pos, 1.0f, 0.0f, 200, 200, _image->GetWhite_Portal_Handle((portal_count / speed)% SHEET_MAX));
		MyDrawModiGraph(mview, portW_pos, 1.0f, 0.0f, 200, 200, _image->GetWhite_Portal_Effect_Handle((portal_effect_count[1] / speed) % sheet_max));
	}
	if(FixportB_pos.x != 0) {
		MyDrawModiGraph(mview, FixportB_pos, 1.0f, 0.0f, 200, 200, _image->GetBlack_Portal_Handle((portal_count / speed) % SHEET_MAX));
		MyDrawModiGraph(mview, FixportB_pos, 1.0f, 0.0f, 200, 200, _image->GetBlack_Portal_Effect_Handle((portal_effect_count[2] / speed) % sheet_max));
	}
	if(FixportW_pos.x != 0) {
		MyDrawModiGraph(mview, FixportW_pos, 1.0f, 0.0f, 200, 200, _image->GetWhite_Portal_Handle((portal_count / speed) % SHEET_MAX));
		MyDrawModiGraph(mview, FixportW_pos, 1.0f, 0.0f, 200, 200, _image->GetWhite_Portal_Effect_Handle((portal_effect_count[3] / speed) % sheet_max));
	}
}
