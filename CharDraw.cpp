/*****************************************************************//**
 * \file   CharDraw.cpp
 * \brief  �����`��
 *
 * \author �V�� ��H
 * \date  August 2023
 *********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include "CharDraw.h"
#include "SceneGameClear.h"
#include "dxlib.h"
#include "gamemain.h"
#include "mydraw.h"
#include "mymath.h"
#include "math.h"


CharDraw::CharDraw() {
	ChangeFont("���C���I");
	ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	SetFontSize(32);
	talk_scene = 0;
	process_stop = 0;
	scenario = 0;
	get_se = 0;
	count = 0;
	index = 0;
	line  = 0;
	for(int i = 0; i < TALK_SCENE_MAX; i++) {
		for(int j = 0; j < 100; j++) {
			read_stage_text[i][j] = _Save->GetScenario(i,j);
		}
	}

	for(int i = 0; i < 2; i++) {
		VoiceMem[i] = NULL;
	}

	sprintf(name,"�t�F���X");

	x = 176;
	y = 694;
	direction = 0;
};

CharDraw::~CharDraw() {

};


void CharDraw::NameProcess(int num) {
	//�`�悷�閼�O�̐ݒ�
	char size[128];
	switch(num) {
	case 0: {
		sprintf(size,"\n");
		break;
	}
	case 1: {
		sprintf(size, "�t�F���X");
		break;
	}
	case 2: {
		sprintf(size, "�A�g���A");
		break;
	}
	case 3: {
		sprintf(size, "�V���E�X");
		break;
	}
	case 4: {
		sprintf(size, "���i");
		break;
	}
	case 5: {
		sprintf(size, "�H�H�H");
		break;
	}
	}
	
	strcpy(name,size) ;
};

void CharDraw::Init() {
	//������
	scenario = 0;
	talk_scene = 0;
	line = 0;
	count = 0;
	index = 0;
	copy.clear();
	for (int i = 0; i < 2; i++) {
		VoiceMem[i] = NULL;
	}
}

void CharDraw::AllInit() {
	_Save->SaveInit();
	Init();
	_Fade->SetSceneChange(0);
	_Fade->SetType(0);
	_FadeSound->change_volume.clear();
}

void CharDraw::SetTutorial(int change) {

	if (change == 1) {
		//�Q�[���N���A���̃V�i���I�ւ̐؂�ւ�
		_music->StopBgm(_image->Bgm[7]);
		scenario   = 1;
		talk_scene = 10;
	}

	if (change == 4) {
		//�P�ڂ̃V�i���I��ǂ񂾂�`���[�g���A���Ɉړ�
		//---------------------------------
		_Fade->SetSceneChange(0);
		_Fade->SetType(0);
		//---------------------------------
		scenario = 2;
		talk_scene = 0;
	}

	//����𓾂��Ƃ��̉��̍Đ�
	if (scenario == 2 && talk_scene == 5) {
		if (get_se <= 1) {
			PlaySoundMem(_image->Se[26], DX_PLAYTYPE_BACK);
			get_se++;
		}
	}
	if (scenario == 2 && talk_scene == 6) {
		if (get_se <= 0) {
			PlaySoundMem(_image->Se[21], DX_PLAYTYPE_BACK);
			get_se++;
		}
	}
}

void CharDraw::Process(int change) {

	SetTutorial(change);

	if (scenario != 0) {
		if (talk_scene != 10 || change != 0) {

			if (scenario == 2) {//�`���[�g���A��

				if (tutorial[talk_scene][line].outline.next == -1 || read_stage_text[scenario][talk_scene] == 1) {
					read_stage_text[scenario][talk_scene] = 1;
					_Save->SetScenario(scenario, talk_scene);

					if (process_stop != 0) {
						process_stop = 0;
					}
					Init();
				}

				if (count == 0) {
					count = 1;
					PlaySoundMem(_image->Se[21], DX_PLAYTYPE_BACK);
				}

				if (gPad._gTrg[0] & PAD_INPUT_4) {
					line++;
					PlaySoundMem(_image->Se[21], DX_PLAYTYPE_BACK);
				}

			}

			//----------------------------------------------------------------------------

			if (scenario == 1) {
				direction += 3;
				if (direction >= 360) {
					direction = 0;
				}

				if (VoiceMem[1] == NULL) {
					VoiceMem[1] = LoadSoundMem(talk[talk_scene][line].contents.voice.c_str());
					PlaySoundMem(VoiceMem[1], DX_PLAYTYPE_BACK, TRUE);
					ChangeVolumeSoundMem(gauge[2], VoiceMem[1]);
					VoiceMem[0] = LoadSoundMem(talk[talk_scene][line + 1].contents.voice.c_str());
				}

				if ((count++ % 2) == 0) {
					if (index < talk[talk_scene][line].contents.text.length()) {
						if (SearchLetter(talk[talk_scene][line].contents.text, index) == 1) {
							index++;
						}
						else {
							index += 2;
						}
					}
				}

				if (index >= talk[talk_scene][line].contents.text.length()) {
					if (gPad._gTrg[0] & PAD_INPUT_4 && GetASyncLoadNum() <= 0) {
						count = 0;
						index = 0;
						line++;
						if (CheckSoundMem(VoiceMem[1]) == 1) {
							StopSoundMem(VoiceMem[1]);
						}
						VoiceMem[1] = VoiceMem[0];
						ChangeVolumeSoundMem(gauge[2], VoiceMem[1]);
						PlaySoundMem(VoiceMem[1], DX_PLAYTYPE_BACK, TRUE);
						SetUseASyncLoadFlag(TRUE);
						VoiceMem[0] = LoadSoundMem(talk[talk_scene][line + 1].contents.voice.c_str());
						SetUseASyncLoadFlag(FALSE);
					}
				}

				copy.clear();


				if (talk[talk_scene][line].contents.left_chara == -1 || read_stage_text[scenario][talk_scene] == 1 || gPad._gTrg[0] & PAD_INPUT_12 && talk_scene != 10) {
					read_stage_text[scenario][talk_scene] = 1;
					_Save->SetScenario(scenario, talk_scene);
					if (talk_scene > 3) {
						NameProcess(talk[talk_scene][line].contents.name);
						Init();
					}
					//�V�i���I����`���[�g���A���Ɉړ�����Ƃ��̐ݒ�
					else if (talk_scene == 0) {
						if (_Save->GetGameovercount() == 0) {
						_Fade->FadeSet(1, 1, 120, 3);
						line = 14;
						index = 15;
						if (change == 3) {
							read_stage_text[scenario][talk_scene] = 1;
							talk[talk_scene][line].contents.name = 4;
							NameProcess(talk[talk_scene][line].contents.name);
							Init();
						}
					}
						else {
							if (CheckSoundMem(VoiceMem[1]) == 1) {
								StopSoundMem(VoiceMem[1]);
							}
							process_stop = 0;
							NameProcess(talk[talk_scene][line].contents.name);
							Init();
						}
					}
					else if (talk_scene == 1) {
						read_stage_text[scenario][talk_scene] = 1;
						Init();
						if (read_stage_text[2][1] != 1) {
							scenario = 2;
							talk_scene = 1;
							PlaySoundMem(_image->Se[21], DX_PLAYTYPE_BACK);
						}
					}
					else if (talk_scene == 2) {
						read_stage_text[scenario][talk_scene] = 1;
						Init();
						if (read_stage_text[2][2] != 1) {
							scenario = 2;
							talk_scene = 2;
							PlaySoundMem(_image->Se[21], DX_PLAYTYPE_BACK);
						}
					}
					else if (talk_scene == 3) {
						read_stage_text[scenario][talk_scene] = 1;
						Init();
						if (read_stage_text[2][4] != 1) {
							scenario = 2;
							talk_scene = 4;
							PlaySoundMem(_image->Se[26], DX_PLAYTYPE_BACK);
						}
					}
				}
				else if (talk[talk_scene][line].contents.left_chara == -2) {
					//�Q�[���N���A���̃V�[���؂�ւ�
					AllInit();
					StopSoundMem(_image->scenario_Bgm[3]);
					SceneBase* gScene = new SceneGameClear;
					ChangeScene(gScene);
				}

				if (scenario == 1) {
					//�e�L�X�g�̐ݒ�
					copy = talk[talk_scene][line].contents.text.substr(0, index);
					//���O�̐ݒ�
					NameProcess(talk[talk_scene][line].contents.name);
				}

			}

			
		}
	}
};

void CharDraw::Draw(int clear) {
	int light  = 100;
	int font_x = 400;
	int font_y = 850;
	int left_x = -100;
	int right_x = 800;
	//�����̓v���Z�X�ŏ����Ȃ��Ƃ����Ȃ����ǃt�F�[�h�C���̎��A�����~�߂Ă�̂ł����ɏ��������v�����Ȃ������ł��@��ϐ\���󂲂����܂���B
	if (read_stage_text[scenario][talk_scene] == 1) {
		if (talk_scene != 0) {
			scenario = 0;
		}
		else {
			if (_Save->GetGameovercount() != 0) {
				if (CheckSoundMem(VoiceMem[1]) == 1) {
					StopSoundMem(VoiceMem[1]);
	}
				process_stop = 0;
				NameProcess(talk[talk_scene][line].contents.name);
				Init();
			}
		}
	}



	if (scenario == 1) {
		//�V�i���I�̕`��
		
		if (talk_scene != 10 || clear == 1) {
			//
			if (talk_scene < 5 && talk_scene != 1 || talk_scene == 6) {
				//--------------------------------------------------------------------------
				//�����̗����G�̕`��
				if (talk[talk_scene][line].contents.left_chara_back != 0) {
					DrawTurnGraph(left_x, 100, _image->GetBodyHandle(13 + talk[talk_scene][line].contents.left_chara_back), true);
				}

				SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - light * talk[talk_scene][line].contents.left_light);
				DrawTurnGraph(left_x, 100, _image->GetBodyHandle(talk[talk_scene][line].contents.left_chara), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

				//--------------------------------------------------------------------------
				//�E���̗����G�̕`��
				if (talk[talk_scene][line].contents.right_chara_back != 0) {
					DrawGraph(right_x, 100, _image->GetBodyHandle(13 + talk[talk_scene][line].contents.right_chara_back), true);
				}

				SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - light * talk[talk_scene][line].contents.right_light);
				DrawGraph(right_x, 100, _image->GetBodyHandle(talk[talk_scene][line].contents.right_chara), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

				//--------------------------------------------------------------------------
			
				//�e�L�X�g�{�b�N�X�̕`��
				DrawGraph(x, y, _image->GetText_Handle(), true);
				//�e�L�X�g�{�b�N�X�̒��ɂ�����̕`��
				DrawGraph(x + 1368, (y + 236) + 5 * sin(DegToRad(direction)), _image->GetText_Arrow(), true);
				//���O�̕`��i���������j
				DrawPosString(1920 / 2, 765, 0, GetColor(255, 255, 255), name);
				//�e�L�X�g�̕`��
				DrawFormatString(font_x, font_y, GetColor(255, 255, 255), "%s", copy.c_str());
				if (talk_scene != 10) {
					//�X�L�b�v���邱�Ƃ�`����摜�̕`��
					DrawGraph(0, 0, _image->GetSkip(), true);
				}
			}
			else {
				//��l�Řb���Ă���Ƃ��̃V�i���I
				//�L�����̕`��i�����j
				if (talk[talk_scene][line].contents.right_chara_back != 0) {
					DrawGraph(right_x - 400, 100, _image->GetBodyHandle(13 + talk[talk_scene][line].contents.right_chara_back), true);
				}

				SetDrawBlendMode(DX_BLENDMODE_ADD, 255 - light * talk[talk_scene][line].contents.right_light);
				DrawGraph(right_x - 400, 100, _image->GetBodyHandle(talk[talk_scene][line].contents.right_chara), true);
				SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

				//--------------------------------------------------------------------------
		
				//�e�L�X�g�{�b�N�X�̕`��
				DrawGraph(x, y, _image->GetText_Handle(), true);
				//�e�L�X�g�{�b�N�X�̒��ɂ�����̕`��
				DrawGraph(x + 1368, (y + 236) + 5 * sin(DegToRad(direction)), _image->GetText_Arrow(), true);
				//���O�̕`��
				DrawPosString(1920 / 2, 765, 0, GetColor(255, 255, 255), name);
				//�e�L�X�g�̕`��
				DrawFormatString(font_x, font_y, GetColor(255, 255, 255), "%s", copy.c_str());
				if (talk_scene != 10) {
					//�X�L�b�v���邱�Ƃ�`����摜�̕`��
					DrawGraph(0, 0, _image->GetSkip(), true);
				}
			}
		}
	}

	if(scenario == 2) {
		//�`���[�g���A���摜�̕`��
		DrawGraph(0, 0, _image->GetTutorial_Handle(tutorial[talk_scene][line].outline.handle), true);
	}

};

int CharDraw::SearchLetter(std::string text, int byte) {
	if (text.at(byte) >= 65 && text.at(byte) <= 122 || text.at(byte) == ' ' || text.at(byte) == '\n' || text.at(byte) == '�c') { // 65(A) ~ 122(z) ���� ASCII�R�[�h�\���m�F���Ă�������
		return 1;
	}
	else {
		return 0;
	}
}
