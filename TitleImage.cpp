/*****************************************************************//**
 * \file   TitleImage.cpp
 * \brief  タイトル画像
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS

#include "dxlib.h"
#include "SceneTitle.h"
#include "stdio.h"

//タイトルで使う画像

void SceneTitle::ImageInit() {
	

	_cgBg = LoadGraph("res/UI_TI/Title_BG.png");
	
	title_handle = LoadGraph("res/UI_TI/TITLE_LOGO_FIX.png");

	character_handle = LoadGraph("res/UI_TI_character.png");

	controle_Handle = LoadGraph("res/Controller_Setting.png");

	start_handle[0] = LoadGraph("res/UI_TI/UI_TI_START_1.png");
	start_handle[1] = LoadGraph("res/UI_TI/UI_TI_START_2.png");
	start_handle[2] = LoadGraph("res/UI_TI/UI_TI_START_3.png");

	copy_light_handle = LoadGraph("res/copylight.png");

	command_handle[0][0] = LoadGraph("res/UI_TI/UI_TI_New_Game_1.png");
	command_handle[0][1] = LoadGraph("res/UI_TI/UI_TI_New_Game_2.png");
	command_handle[0][2] = LoadGraph("res/UI_TI/UI_TI_New_Game_3.png");
	command_handle[1][0] = LoadGraph("res/UI_TI/UI_TI_Setting_1.png");
	command_handle[1][1] = LoadGraph("res/UI_TI/UI_TI_Setting_2.png");
	command_handle[1][2] = LoadGraph("res/UI_TI/UI_TI_Setting_3.png");
	command_handle[2][0] = LoadGraph("res/UI_TI/UI_TI_Control_1.png");
	command_handle[2][1] = LoadGraph("res/UI_TI/UI_TI_Control_2.png");
	command_handle[2][2] = LoadGraph("res/UI_TI/UI_TI_Control_3.png");
	command_handle[3][0] = LoadGraph("res/UI_TI/UI_TI_Extra_1.png");
	command_handle[3][1] = LoadGraph("res/UI_TI/UI_TI_Extra_2.png");
	command_handle[3][2] = LoadGraph("res/UI_TI/UI_TI_Extra_3.png");
	command_handle[4][0] = LoadGraph("res/UI_TI/UI_TI_Exit_1.png");
	command_handle[4][1] = LoadGraph("res/UI_TI/UI_TI_Exit_2.png");
	command_handle[4][2] = LoadGraph("res/UI_TI/UI_TI_Exit_3.png");
	command_handle[5][0] = LoadGraph("res/UI_TI/UI_TI_Movie_1.png");
	command_handle[5][1] = LoadGraph("res/UI_TI/UI_TI_Movie_2.png");
	command_handle[5][2] = LoadGraph("res/UI_TI/UI_TI_Movie_3.png");
	command_handle[6][0] = LoadGraph("res/UI_TI/UI_TI_Credit_1.png");
	command_handle[6][1] = LoadGraph("res/UI_TI/UI_TI_Credit_2.png");
	command_handle[6][2] = LoadGraph("res/UI_TI/UI_TI_Credit_3.png");
	
	

}

void SceneTitle::SoundInit() {

 Bgm = LoadSoundMem("res/BGM/Paper_City.mp3");

 Se[0] = LoadSoundMem("res/SE/SE_SELECT.mp3");//セレクト音
 Se[1] = LoadSoundMem("res/SE/SE_SELECT_ENTER1.mp3"); //決定音
 Se[2] = LoadSoundMem("res/SE/SE_SELECT_BACK1.mp3");//キャンセル音
 Se[3] = LoadSoundMem("res/SE/SE_TITLE_BG.mp3");//環境音

}