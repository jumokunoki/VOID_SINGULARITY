/*****************************************************************//**
 * \file   SceneTestStaging.cpp
 * \brief  ゲーム本編の描画関連演出
 *
 * \author 奈良充樹、齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#include "SceneTest.h"
#include "DxLib.h"
#include "main.h"
#include "gamemain.h"
#include "mydraw.h"

void SceneTest::Staging() {
	// ステージ中に描画される描画のカウントなどの管理
	// ダメージの演出カウント
	if(_player.GetD_judge() == true) {
		_stacnt[0] = 60;
	}
	if(_stacnt[0] > 0) {
		_stacnt[0]--;
	}
	if(_stacnt[0] < 60) {
		_player.SetD_judge();
	}
	if(_stacnt[0] < 0) {
		_stacnt[0] = 0;
	}

	// ヒールの演出カウント
	if(_stajudge[1] == true) {
		_stacnt[1] = 60;
	}
	if(_stacnt[1] > 0) {
		_stacnt[1]--;
	}
	if(_stacnt[1] < 60) {
		_stajudge[1] = false;
	}
	if(_stacnt[1] < 0) {
		_stacnt[1] = 0;
	}
	// アンチマターの演出カウント
	if(_stajudge[2] == true) {
		_stacnt[2] = 60;
	}
	if(_stacnt[2] > 0) {
		_stacnt[2]--;
	}
	if(_stacnt[2] < 60) {
		_stajudge[2] = false;
	}
	if(_stacnt[2] < 0) {
		_stacnt[2] = 0;
	}
	//　弾薬箱の演出カウント
	if (_stajudge[5] == true) {
		_stacnt[5] = 60;
	}
	if (_stacnt[5] > 0) {
		_stacnt[5]--;
	}
	if (_stacnt[5] < 60) {
		_stajudge[5] = false;
	}
	if (_stacnt[5] < 0) {
		_stacnt[5] = 0;
	}

	// 弾薬増加;;
	if(_stajudge[10] == true) {
		_stacnt[10] = 120;
	}
	if(_stacnt[10] > 0) {
		_stacnt[10]--;
	}
	if(_stacnt[10] < 120) {
		_stajudge[10] = false;
	}
	if(_stacnt[10] < 0) {
		_stacnt[10] = 0;
	}

	// ドア解錠;;
	if(_stajudge[11] == true) {
		_stacnt[11] = 120;
	}
	if(_stacnt[11] > 0) {
		_stacnt[11]--;
	}
	if(_stacnt[11] < 120) {
		_stajudge[11] = false;
	}
	if(_stacnt[11] < 0) {
		_stacnt[11] = 0;
	}

	// HP100回復;;
	if(_stajudge[12] == true) {
		_stacnt[12] = 120;
	}
	if(_stacnt[12] > 0) {
		_stacnt[12]--;
	}
	if(_stacnt[12] < 120) {
		_stajudge[12] = false;
	}
	if(_stacnt[12] < 0) {
		_stacnt[12] = 0;
	}

	// HP上限増加;;
	if(_stajudge[13] == true) {
		_stacnt[13] = 120;
	}
	if(_stacnt[13] > 0) {
		_stacnt[13]--;
	}
	if(_stacnt[13] < 120) {
		_stajudge[13] = false;
	}
	if(_stacnt[13] < 0) {
		_stacnt[13] = 0;
	}

	// ポータル弾増加;;
	if(_stajudge[14] == true) {
		_stacnt[14] = 120;
	}
	if(_stacnt[14] > 0) {
		_stacnt[14]--;
	}
	if(_stacnt[14] < 120) {
		_stajudge[14] = false;
	}
	if(_stacnt[14] < 0) {
		_stacnt[14] = 0;
	}

	// 敵反物質化;;
	if(_stajudge[15] == true) {
		_stacnt[15] = 120;
	}
	if(_stacnt[15] > 0) {
		_stacnt[15]--;
	}
	if(_stacnt[15] < 120) {
		_stajudge[15] = false;
	}
	if(_stacnt[15] < 0) {
		_stacnt[15] = 0;
	}

	// 黒弾増加;;
	if(_stajudge[16] == true) {
		_stacnt[16] = 120;
	}
	if(_stacnt[16] > 0) {
		_stacnt[16]--;
	}
	if(_stacnt[16] < 120) {
		_stajudge[16] = false;
	}
	if(_stacnt[16] < 0) {
		_stacnt[16] = 0;
	}

	// 貫通増加;;
	if(_stajudge[17] == true) {
		_stacnt[17] = 120;
	}
	if(_stacnt[17] > 0) {
		_stacnt[17]--;
	}
	if(_stacnt[17] < 120) {
		_stajudge[17] = false;
	}
	if(_stacnt[17] < 0) {
		_stacnt[17] = 0;
	}

	// 反射増加;;
	if(_stajudge[18] == true) {
		_stacnt[18] = 120;
	}
	if(_stacnt[18] > 0) {
		_stacnt[18]--;
	}
	if(_stacnt[18] < 120) {
		_stajudge[18] = false;
	}
	if(_stacnt[18] < 0) {
		_stacnt[18] = 0;
	}
} 

void   SceneTest::StartMovie() {
	if(_start_movie_use == 0 && GetMovieStateToGraph(_image->GetStart_Movie()) == 0) {
		SeekMovieToGraph(_image->GetStart_Movie(),0);
		PlayMovieToGraph(_image->GetStart_Movie());
		_start_movie_use = 1;
		_Save->SetMovieUse();
	}
	else {
		if(gPad._gTrg[0] & PAD_INPUT_12) {
			if(GetMovieStateToGraph(_image->GetStart_Movie()) == 1) {
				PauseMovieToGraph(_image->GetStart_Movie());
			}
		}
	}
}

void SceneTest::MovieDraw() {
	if(GetMovieStateToGraph(_image->GetStart_Movie()) == 1) {
		DrawGraph(0, 0, _image->GetStart_Movie(), true);
		DrawGraph(0, 0, _image->GetSkip(), true);
	}
}

void SceneTest::GameOver() {
	if(_player.GetHp() <= 0 && _stock <= 0) {
		_Fade->FadeSet(1, 0, 180, 2);
		_music->MakeVoice(DEAD_VOICE, RANDAM_TWO);
		for(int i = 0; i < 8; i++) {
			if(CheckSoundMem(_image->Bgm[i]) == 1) {
				int volum = _Fade->Fade._FadeIn;
				if(volum >= gauge[1]) {
					volum = gauge[1];
				}
				ChangeVolumeSoundMem(volum, _image->Bgm[i]);
			}
		}
		if(_Fade->Fade.scene_change == 2) {
			for(int i = 0; i < 8; i++) {
				if(CheckSoundMem(_image->Bgm[i]) == 1) {
					StopSoundMem(_image->Bgm[i]);
				}
			}
			_Fade->SetSceneChange(0);
			_Fade->SetType(0);
			//_image->SetLoadComplet(0);
			_FadeSound->change_volume.clear();
			_Save->SetGameovercount();
			SceneBase* gScene = new SceneGameOver;
			ChangeScene(gScene);
		}
	}
};

void SceneTest::SinarioDraw() {
	if (_talk.GetScenario() == 1 && _talk.GetTalkScene() != 10 || _Fade->Fade.hang == -1 && _talk.GetScenario() == 1 && _talk.GetTalkScene() == 10) {
		int i = 0;
		switch (_mapData.GetFloorNum()) {
		case 0:
		case 1:
		case 2:
		case 3: {
			i = 1;
			break;
		}
		case 4:
		case 5: {
			i = 2;
			break;
		}
		case 6:
		case 7:
		case 8:
		case 9: {
			i = 3;
			break;
		}
		case 10:
		case 11:
		case 12: {
			i = 4;
			break;
		}
		case 13:
		case 14:
		case 15:
		{
			i = 0;
			break;
		}
		case 16:
		{
			i = 0;
			break;
		}
		}
		DrawGraph(0, 0, _image->GetBlur(i), true);
	}
	_talk.Draw(_Fade->Fade.scene_change);
}

void SceneTest::BgmProcess() {
	if (_talk.GetScenario() == 0) {
		switch (_mapData.GetFloorNum()) {
		case 0:
		case 1: {
			if (CheckSoundMem(_image->Bgm[0]) == 0) {
				_music->MakeBgm(_image->Bgm[0]);
				bgm_count = 0;
			}
			break;
		}
		case 2:
		case 3: {
			if (CheckSoundMem(_image->Bgm[1]) == 0) {
				_music->MakeBgm(_image->Bgm[1]);
				bgm_count = 1;
			}
			break;
		}
		case 4:
		case 5: {
			if (CheckSoundMem(_image->Bgm[2]) == 0) {
				_music->MakeBgm(_image->Bgm[2]);
				bgm_count = 2;
			}
			break;
		}
		case 6:
		case 7:
		case 8:
		case 9: {
			if (CheckSoundMem(_image->Bgm[3]) == 0) {
				_music->MakeBgm(_image->Bgm[3]);
				bgm_count = 3;
			}
			break;
		}
		case 10:
		case 11:
		case 12: {
			if (CheckSoundMem(_image->Bgm[4]) == 0) {
				_music->MakeBgm(_image->Bgm[4]);
				bgm_count = 4;
			}
			break;
		}
		case 13:
		case 14: {
			if (CheckSoundMem(_image->Bgm[5]) == 0) {
				_music->MakeBgm(_image->Bgm[5]);
				_FadeSound->SetFadeBgm(&_image->Bgm[5], gauge[1], 120, 1);
				bgm_count = 5;
			}
			break;
		}
		case 15: {
			if (CheckSoundMem(_image->Bgm[6]) == 0) {
				_music->MakeBgm(_image->Bgm[6]);
				bgm_count = 6;
			}
			break;
		}
		case 16: {
			if (CheckSoundMem(_image->Bgm[7]) == 0) {
				_music->MakeBgm(_image->Bgm[7]);
				if (bgm_count != 7) {
					_music->MakeSe(_image->Se[5]);
				}
				bgm_count = 7;
			}
			break;
		}
		}
		if (CheckSoundMem(_image->Bgm[bgm_count + 1]) == 1) {
			_music->StopBgm(_image->Bgm[bgm_count + 1]);
		}

		if (bgm_count - 1 >= 0) {
			if (CheckSoundMem(_image->Bgm[bgm_count - 1]) == 1) {
				_music->StopBgm(_image->Bgm[bgm_count - 1]);
			}
		}
	}
	if (_talk.GetScenario() == 1) {
		if (_talk.GetTalkScene() == 0) {
			//ステージbgmが鳴っていたら止める
			for (int i = 0; i < 8; i++) {
				if (CheckSoundMem(_image->Bgm[i]) == 0) {
					_music->StopBgm(_image->Bgm[i]);
				}
			}
			if (CheckSoundMem(_image->scenario_Bgm[0]) == 0) {
				_music->SetBgmVolume(_image->scenario_Bgm[0]);
				_music->MakeBgm(_image->scenario_Bgm[0]);
			}
		}
		else if (_talk.GetTalkScene() == 2) {
			for (int i = 0; i < 8; i++) {
				if (CheckSoundMem(_image->Bgm[i]) == 1 && i != 1) {
					_music->StopBgm(_image->Bgm[i]);
				}
			}
			if (CheckSoundMem(_image->Bgm[1]) == 0) {
				_music->MakeBgm(_image->Bgm[1]);
				bgm_count = 1;
			}
		}
		else if (_talk.GetTalkScene() == 7) {
			for (int i = 0; i < 8; i++) {
				if (CheckSoundMem(_image->Bgm[i]) == 1 && i != 4) {
					_music->StopBgm(_image->Bgm[i]);
				}
			}
			if (CheckSoundMem(_image->Bgm[4]) == 0) {
				_music->MakeBgm(_image->Bgm[4]);
				bgm_count = 4;
			}
		}
		else if (_talk.GetTalkScene() == 10) {
			for (int i = 0; i < 8; i++) {
				if (CheckSoundMem(_image->Bgm[i]) == 1) {
					_music->StopBgm(_image->Bgm[i]);
				}
			}
			if (CheckSoundMem(_image->scenario_Bgm[3]) == 0) {
				_music->MakeBgm(_image->scenario_Bgm[3]);
			}
		}
	}
	else {
		if (CheckSoundMem(_image->scenario_Bgm[0]) == 1) {
			_music->StopBgm(_image->scenario_Bgm[0]);
		}
	}
}

void SceneTest::VolumProcess() {

	_music->MusicProcess();

	for (int i = 0; i < 8; i++) {
		_music->SetBgmVolume(_image->Bgm[i]);
	}
	for (int i = 0; i < 31; i++) {
		_music->SetSeVolume(_image->Se[i]);
	}
	for (int i = 0; i < 16; i++) {
		_music->SetVoiceVolume(_image->chara_voice[i]);
	}

	_FadeSound->FadeBgmProcess();
}

void SceneTest::BgProcess() {
	//背景の画像番号
	switch(_mapData.GetFloorNum()) {
	case 0:
	case 1:
	case 2:
	case 3: {
		_stageNum = 0;
		break;
	}
	case 4: {
		_stageNum = 1;
		break;
	}
	case 5:
	{
		_stageNum = 2;
		break;
	}
	case 6:
	case 7:
	case 8:
	case 9:
	{
		_stageNum = 3;
		break;
	}
	case 10:
	case 11:
	case 12:
	{
		_stageNum = 4;
		break;
	}
	case 13:
	case 14:
	case 15:
	case 16:
	{
		_stageNum = 5;
		break;
	}
	}
}

void SceneTest::ArrowDraw(MATRIX mView) {
	// ステージ中の方向表示の矢印
	if (_mapData.GetFloorNum() == 4) {
		VECTOR AL = VGet(3480 + 100, 1860 + 100, 0);
		_arrowcnt++;
		if (_arrowcnt >= 105) {
			_arrowcnt = 0;
		}
		MyDrawModiGraph(mView, AL, 1.0f, 4.7f, 200, 200, _image->Get_Gra_arrow(_arrowcnt / 3));
	}
	if (_mapData.GetFloorNum() == 5) {
		VECTOR AL = VGet(3420 + 100, 960 + 100, 0);
		VECTOR AL_s = VGet(3480 + 100, 1860 + 100, 0);
		_arrowcnt++;
		if (_arrowcnt >= 105) {
			_arrowcnt = 0;
		}
		MyDrawModiGraph(mView, AL, 1.0f, 4.7f, 200, 200, _image->Get_Gra_arrow(_arrowcnt / 3));
		MyDrawModiGraph(mView, AL_s, 1.0f, 4.7f, 200, 200, _image->Get_Gra_arrow(_arrowcnt / 3));
	}
	if(_mapData.GetFloorNum() == 11) {
		VECTOR AL = VGet(180 + 100, 1860 + 100, 0);
		VECTOR AL_s = VGet(1860 + 100, 1860 + 100, 0);
		_arrowcnt++;
		if(_arrowcnt >= 105) {
			_arrowcnt = 0;
		}
		MyDrawModiGraph(mView, AL, 1.0f, 0.0f, 200, 200, _image->Get_Gra_arrow(_arrowcnt/3));
		MyDrawModiGraph(mView, AL_s, 1.0f, 0.0f, 200, 200, _image->Get_Gra_arrow(_arrowcnt/3));
	}
	if(_mapData.GetFloorNum() == 12) {
		VECTOR AL = VGet(180+100, 1860+100, 0);
		_arrowcnt++;
		if(_arrowcnt >= 105) {
			_arrowcnt = 0;
		}
		MyDrawModiGraph(mView, AL, 1.0f, 0.0f, 200, 200, _image->Get_Gra_arrow(_arrowcnt/3));
	}
}

void SceneTest::StagingDraw() {
	if(_stacnt[0] > 0) {
		int suba = 0;
		suba = 255 / 60 * _stacnt[0];
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, suba);
		DrawGraph(0, 0, _image->GetScreen_Effect(0), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if(_stacnt[1] > 0) {
		int subb = 0;
		subb = 255 / 60 * _stacnt[1];
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, subb);
		DrawGraph(0, 0, _image->GetScreen_Effect(1), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if(_stacnt[2] > 0) {
		int subc = 0;
		subc = 255 / 60 * _stacnt[2];
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, subc);
		DrawGraph(0, 0, _image->GetScreen_Effect(2), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if (_stacnt[5] > 0) {
		int subd = 0;
		subd = 255 / 60 * _stacnt[5];
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, subd);
		DrawGraph(0, 0, _image->GetScreen_Effect(3), TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	// アイテムログ用
	int log = 0;
	for(int i = 10; i < 19; i++) {
		if(_stacnt[i] > 0) {
			if(log == 0) {
				log = i;
			}
			if(log != 0) {
				if(_stacnt[i] > _stacnt[log]) {
					log = i;
				}
			}
		}
	}
	if(log >= 10) {
		if(_stacnt[log] > 0) {
			int subd = 0;
			if(_stacnt[log] > 60) {
				subd = 255;
			}
			else if(_stacnt[log] <= 60) {
				subd = 255 / 60 * _stacnt[log];
			}
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, subd);
			DrawGraph(0, 0, _image->Get_Item_log(log - 10), TRUE);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
	}

}

void SceneTest::B_Out_Entry() {
	// 画面遷移時の画面暗転
	_stajudge[3] = true;
	if(_stajudge[3] == true) {
		_stacnt[3]++;
	}
}

void SceneTest::B_Out_Cancel() {
	// 画面遷移時の画面明け
	if(_stajudge[4] == true) {
		_stacnt[3]--;
	}
	if(_stacnt[3] <= 0) {
		_stajudge[4] = false;
	}
}

void SceneTest::B_OutBox() {
	// 暗転に使用する黒い矩形
	int alpha = 0;
	alpha = 255 / 60 * _stacnt[3];
	if(alpha >= 255) {
		alpha = 255;
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
    DrawBox(0, 0, SCREEN_W, SCREEN_H, GetColor(0, 0, 0), TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}