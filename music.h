/*****************************************************************//**
 * \file   music.h
 * \brief  ‰¹Šy
 *
 * \author âV“¡ Œè‰H
 * \date   August 2023
 *********************************************************************/
#pragma once


class music
{
public:
	 music();
	 ~music();

	void MusicProcess();

	void SetSeVolume( int se);
	void SetBgmVolume( int bgm);
	void SetVoiceVolume( int voice);

	void MakeSe(int num);
	void MakeBgm(int num);
	void MakeVoice(int voice_num, int rand);

	int  CheckVoiceAll();

	void StopBgm(int Bgm);
	void StopSe(int Se);

	void SetCoolVoice();

protected:
#define SeMax 100
#define BgmMax 15
#define VoiceMax 100
	int cool_voice;

};

