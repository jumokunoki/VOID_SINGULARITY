/*****************************************************************//**
 * \file   Portal.h
 * \brief  ポータル
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#pragma once

#include "DxLib.h"
#include "mymath.h"

const int PORT_W = 179;
const int PORT_H = 179;

class Portal
{
public:
	Portal();
	virtual ~Portal();

	void PortalGenerate(int portBW, int x, int y);
	void PortalProcess();
	void PortalDraw(MATRIX mview);


	int GetPosBX() { return portB.x; }
	int GetPosBY() { return portB.y; }
	int GetPosWX() { return portW.x; }
	int GetPosWY() { return portW.y; }
	int GetPortTypeB() { return portB.type; }
	int GetPortTypeW() { return portW.type; }


	void  AddPosBX(int x) { portB.x += x; }
	void  AddPosBY(int y) { portB.y += y; }
	void  AddPosWX(int x) { portW.x += x; }
	void  AddPosWY(int y) { portW.y += y; }

	void  ResetPortB() { portB = port_NONE; }
	void  ResetPortW() { portW = port_NONE; }
	void  FixResetPortB() { FixportB = port_NONE; }
	void  FixResetPortW() { FixportW = port_NONE; }

	MYRECT_PLUS GetRectBlack() { return portB; }
	MYRECT_PLUS GetRectWhite() { return portW; }
	MYRECT_PLUS GetRectFixB() { return FixportB; }
	MYRECT_PLUS GetRectFixW() { return FixportW; }




protected:
#define SHEET_MAX 20
	// ポータルの当たり判定
	MYRECT_PLUS portB;
	MYRECT_PLUS portW;
	MYRECT_PLUS FixportB;
	MYRECT_PLUS FixportW;
	MYRECT_PLUS port_NONE = { 0,0,0,0,0,0,0,0 };
	int _cx = PORT_W / 2;
	int _cy = PORT_H / 2;
	int portal_count;
	int portal_effect_count[4];
};

