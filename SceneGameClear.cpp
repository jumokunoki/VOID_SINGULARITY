/*****************************************************************//**
 * \file   SceneGameClear.h
 * \brief  ゲームクリア
 *
 * \author 齋藤 瑚羽
 * \date   August 2023
 *********************************************************************/
#include "SceneGameClear.h"
#include "SceneTitle.h"
SceneGameClear::SceneGameClear() {
	

	voice[0] = LoadSoundMem("res/voice/ending_voice/vcA18.wav");
	voice[1] = LoadSoundMem("res/voice/ending_voice/vcA19_1.wav");
	voice[2] = LoadSoundMem("res/voice/ending_voice/vcA26.wav");
	voice[3] = LoadSoundMem("res/voice/ending_voice/vcA27.wav");


	SeekMovieToGraph(_image->GetStaff_Roll(), 0);

	flow_count = 0;
	handle_count = 0;
	movie_flag = 0;
	for(int i = 0; i < 5; i++) {
		_Fade[i] = 0;
		 hang[i] = 1;
	}
	hang[3] = -1;
	stop = 0;
	stop_order = 1;
	voice_num = 0;

};

SceneGameClear::~SceneGameClear() {

};

void SceneGameClear::Process() {

	if(GetMovieStateToGraph(_image->GetStaff_Roll()) != 1 && stop == 0) {
		flow_count++;
	}

	Flow_Process(flow_count);

	StopProcess();

	if(_Fade[2] >= 255 && handle_count == 2) {
		if(gPad._gTrg[0] & PAD_INPUT_4) {
			hang[3] = 1;
		}
	}
	
	if(_Fade[3] >= 255) {
		SceneBase* gScene = new SceneTitle;
		ChangeScene(gScene);
	}
};

int SceneGameClear::CheckVoiceAll() {
	int check = 0;
	for (int i = 0; i < 4; i++) {
		if (CheckSoundMem(voice[i]) != 1) {
			check++;
		}
	}

	if (check >= 4) {
		return 1;
	}
	else {
		return 0;
	}

}

void SceneGameClear::StopProcess(){

	if (stop == stop_order) {

		int check = 0;

		for (int i = 0; i < 4; i++) {
			if (CheckSoundMem(voice[i]) != 1) {
				check++;
			}
		}

		if (check >= 4) {
			stop = 0;
			stop_order++;
		}

	}

};


void SceneGameClear::Flow_Process(int flow_count) {

	int min = 180;
	int old_flow_count = flow_count;
	float add_fade = (float)255 / min;
	int mul = 2;

	old_flow_count -= 120;

	if (old_flow_count >= 0) {
		if (_Fade[0] >= 0 && _Fade[0] <= 255 && stop == 0) {
			if (hang[0] == 1) {
				_Fade[0] += add_fade * hang[0];
				if (CheckSoundMem(voice[0]) == 0 && voice_num == 0) {
					PlaySoundMem(voice[0], DX_PLAYTYPE_BACK);
					voice_num++;
				}
			}
			else {
				_Fade[0] += (add_fade * mul) * hang[0];
			}
		}
	}

	old_flow_count -= min;


	if (old_flow_count >= 0) {
		if (stop_order == 1) {
			stop = 1;
		}
		hang[0] = -1;

	}

	old_flow_count -= min;

	if (old_flow_count >= 0) {
		hang[0] = 1;
		handle_count = 1;
	}

	old_flow_count -= 60;

	if (CheckSoundMem(voice[1]) == 0 && voice_num == 1 && old_flow_count >= 0) {
		PlaySoundMem(voice[1], DX_PLAYTYPE_BACK);
		voice_num++;
	}


	old_flow_count -= min;

	if(old_flow_count >= 0) {
		if (stop_order == 2) {
			stop = 2;
		}
		hang[0] = -1;
	}

	old_flow_count -= min;

	if(old_flow_count >= 0) {
		if(movie_flag == 0 && GetMovieStateToGraph(_image->GetStaff_Roll()) != 1){
			PlayMovieToGraph(_image->GetStaff_Roll());
			movie_flag = 1;
			
		}
		handle_count = 0;
	}
	
	old_flow_count -= 1;

	if(old_flow_count >= 0) {
		if(_Fade[1] >= 0 && _Fade[1] <= 255 && stop == 0) {
			if(hang[1] == 1) {
				_Fade[1] += add_fade * hang[1];
			}
			else {
				_Fade[1] += (add_fade * mul) * hang[1];
			}
		}
	}

	old_flow_count -= min * 2;

	if(old_flow_count >= 0) {
		if(_Fade[2] >= 0 && _Fade[2] <= 255 && stop == 0) {
			if(hang[2] == 1) {
				_Fade[2] += add_fade * hang[2];
				if (CheckSoundMem(voice[2]) == 0 && voice_num == 2) {
					PlaySoundMem(voice[2], DX_PLAYTYPE_BACK);
					voice_num++;
				}
			}
			else {
				_Fade[2] += (add_fade * mul) * hang[2];
			}
		}
	}

    old_flow_count -= min * 2;

	if(old_flow_count >= 0) {
		if (stop_order == 3) {
			stop = 3;
		}
		hang[2] = -1;
	}

	old_flow_count -= min;

	if(old_flow_count >= 0) {
		hang[2] = 1;
		handle_count = 1;
		if (CheckSoundMem(voice[3]) == 0 && voice_num == 3) {
			PlaySoundMem(voice[3], DX_PLAYTYPE_BACK);
			voice_num++;
		}
	}
	

	old_flow_count -= min * 2;

	if(old_flow_count >= 0) {
		if (stop_order == 4) {
			stop = 4;
		}
		hang[2] = -1;
	}

	old_flow_count -= (float)min/2;

	if(old_flow_count >= 0) {
		hang[2] = 1;
		handle_count = 2;
	}

	if(old_flow_count >= 0) {
		if(_Fade[3] >= 0 && _Fade[3] <= 255) {
			_Fade[3] += add_fade * hang[3];
		}
	}



	for(int i = 0; i < 4; i++) {
		if(_Fade[i] <= 0) {
			_Fade[i] = 0;
		}
		else if(_Fade[i] >= 255) {
			_Fade[i] = 255;
		}
	}
}

void SceneGameClear::Draw() {

	//初めのフォント
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _Fade[0]);
	DrawGraph(0, 0, _image->GetClear_Font_Target(handle_count), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, _Fade[0]);

	//スタッフロール
	if(GetMovieStateToGraph(_image->GetStaff_Roll()) != 0) {
		DrawGraph(0, 0, _image->GetStaff_Roll(), true);
	}

	//二人の絵
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _Fade[1]);
	if(movie_flag == 1 && GetMovieStateToGraph(_image->GetStaff_Roll()) != 1) {
		DrawGraph(0, 0, _image->GetClear_Cg(), true);
	}
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _Fade[1]);
	//フォント
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _Fade[2]);
	DrawGraph(0, 0, _image->GetAfter_Clear_Font(handle_count), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, _Fade[2]);

	//フェードアウト用のどろーぼっくす
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, _Fade[3]);
	DrawBox(0, 0, 1920, 1080, GetColor(0, 0, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, _Fade[3]);

};