//*-------------------------------------------------------------------------------*
//							�Q�[���̃V�[�����Ǘ�
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃w�b�_�t�@�C��
#include GAME_SCENE_HPP
using namespace n_game_scene;
//		����w�b�_�t�@�C��
#include AUDIO_MULT_HPP
using namespace n_audio_mult;
#include KEYBOARD_HPP
using namespace n_keyboard;
#include MOUSE_HPP
using namespace n_mouse;
//		�W���t�@�C��
#include <math.h>
using namespace std;
//		�l�[��
using namespace n_img;
using namespace n_img_div;
using namespace n_audio;
using namespace n_img_coll;
using namespace n_img_div;

//�w�b�_�Ŏg�p����const
//const int SHOT_MAX = 40;
//const int ENEMY_KIND = 7;
//const int ENEMY_MAX = 10;


//*--------------------------------------------------------------------------------*
//								�V���O���g������
//*--------------------------------------------------------------------------------*

//�V���O���g����GameStateManager�N���X�̃I�u�W�F�N�g
ClGameScene* ClGameScene::m_ins = nullptr;

const string ENEMY_PATHS[ENEMY_KIND] = {
	"teki_blue.png",
	"teki_gray.png",
	"teki_green.png",
	"teki_mizu.png",
	"teki_purple.png",
	"teki_red.png",
	"teki_yellow.png"
};

ClGameScene::SHOT::SHOT(){
	coll_img = ClImgDivColl();
	start_pos = n_xy::ClXY();
	degree = 0.0f;
	radius = 0.0f;
}
ClGameScene::SHOT::~SHOT() { return; }

const float TIME_START = 0.0f;

/// <summary>
/// �R���X�g���N�^�A������
/// </summary>
ClGameScene::ClGameScene() { 
	m_scene = n_game_scene::GAME_SCENE::TITLE;
	m_next_scene = n_game_scene::GAME_SCENE::TITLE;
	m_back_scene = n_game_scene::BACK_GAME_SCENE::NONE;
	m_is_change_secne = FALSE;
	m_fade = n_fade::ClFade();
	//�������~�߂邩
	m_is_end_proc_stop = FALSE;
	m_is_title_proc_stop = FALSE;
	m_is_play_proc_stop = FALSE;
	//�V�[�����ꂼ��̐i�s��
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::START;
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::SCENE_END;
	m_end_state = n_game_scene::ClGameScene::SCENE_STATE::SCENE_END;
	//�ϐ�
	m_score = 0;
	m_back_move_abs_speed = 1;
	m_back_move_speed = 1;

	//�摜
	m_title_back_img = ClImg();
	m_title_logo_img = ClImg();
	m_play_back_img_start = ClImg();
	m_play_back_img_up = ClImg();
	m_end_back_img = ClImg();
	m_end_logo_img = ClImg();
	//�@�̉摜
	m_player = ClImgColl();
	for (int i = 0; i < ENEMY_KIND; i++) {
		m_enemy_base[i] = ClImgCollCircle();
	}
	for (int i = 0; i < ENEMY_MAX; i++) {
		m_enemy_use[i] = ClImgCollCircle();
	}
	m_enemy_drop_interval = TIME_START;
	m_enemy_drop_interval_max = 2.0f;
	//�e�摜
	m_shot_base = ClImgDivColl();
	//for (int i = 0; i < SHOT_MAX; i++) {
	//	m_shot_use[i] = SHOT();
	//}
	m_shot_div_x = 4;
	m_shot_div_y = 1;
	m_shot_div_max = m_shot_div_x * m_shot_div_y;
	m_shot_interval = TIME_START;
	m_shot_interval_max = 0.2f;
	//���y
	m_title_audio = ClAudio();
	m_play_audio = ClAudio();
	m_end_audio = ClAudio();

	return; 
}

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
ClGameScene::ClGameScene(const ClGameScene& src) {
	//�A�h���X���R�s�[���Ă���
	m_ins = src.m_ins;
}

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
/// <returns>���̃C���X�^���X�̃A�h���X</returns>
ClGameScene& ClGameScene::operator=(const ClGameScene& src) {
	//�A�h���X���R�s�[���Ă���
	m_ins = src.m_ins;
	return *this;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ClGameScene::~ClGameScene() { return; }

/// <summary>
/// �C���X�^���X�擾(���߂ĎQ�Ƃ���Ƃ��̓C���X�^���X�𐶐�)
/// </summary>
/// <returns><�V���O���g���ȃC���X�^���X/returns>
ClGameScene* ClGameScene::GetIns() {
	//���߂Ď擾���鎞�A���̃I�u�W�F�N�g�𐶐��𐶐�
	if (m_ins == nullptr)
	{
		//�������̊m��
		m_ins = new ClGameScene();
	}

	return m_ins;
}

/// <summary>
/// �I�u�W�F�N�g�̔j��
/// </summary>
VOID ClGameScene::Destroy() {
	//�������̔j��
	delete m_ins;
	m_ins = nullptr;
}

//*--------------------------------------------------------------------------------*
//								�v���p�e�B
//*--------------------------------------------------------------------------------*

//�^�C�g����ʂɐ؂�ւ�
VOID ClGameScene::ChangeSceneTitle() { MmChangeScene(GAME_SCENE::TITLE); }

//�v���C��ʂɐ؂�ւ�
VOID ClGameScene::ChangeScenePlay() { MmChangeScene(GAME_SCENE::PLAY); }

//�G���h��ʂɐ؂�ւ�
VOID ClGameScene::ChangeSceneEnd() { MmChangeScene(GAME_SCENE::END); }

const float FADE_TIME = 0.25f;	//�t�F�[�h���鎞��
//const float FADE_TIME = 2.0f;	//�t�F�[�h���鎞��

/// <summary>
/// �V�[���ύX�J�n����
/// </summary>
/// <param name="next_scene">���̃V�[��</param>
VOID ClGameScene::MmChangeScene(GAME_SCENE next_scene) {
	//�V�[���ύX���͕ύX�ς����Ȃ�
	if (m_is_change_secne == TRUE) { return; }

	//�t�F�[�h�A�E�g���鏀��
	m_next_scene = next_scene;
	m_is_change_secne = TRUE;
	m_back_scene = n_game_scene::BACK_GAME_SCENE::BACK_LOAD;
	m_fade.FadeUpStart(FADE_TIME);
	ClAudioMult::GetIns()->SetFadeDownStart(FADE_TIME);

	//�t�F�[�h�O�̃V�[���̕`��ȊO�̏������~������
	MmSetProcStopState(m_scene, TRUE);

	//�t�F�[�h��̃V�[���̕`��ȊO�̏������~������
	MmSetProcStopState(m_next_scene, TRUE);

	//�J�n������������
	MmSetSceneState(m_next_scene, n_game_scene::ClGameScene::SCENE_STATE::START);

	//�t�F�[�h�A�b�v�J�n�n�_�����J�n�̃t���O�𗧂Ă�
	MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START);
}

/// <summary>
/// �`��ȊO�̏������~������t���O�̐ݒ�
/// </summary>
/// <param name="scene">�Q�Ƃ���Q�[���V�[��</param>
/// <param name="is_stop">��~�����邩</param>
VOID ClGameScene::MmSetProcStopState(GAME_SCENE scene, BOOL is_stop) {
	switch (scene){
		//�^�C�g����ʎ�
	case n_game_scene::TITLE:
		m_is_title_proc_stop = is_stop;
		break;

		//�v���C��ʎ�
	case n_game_scene::PLAY:
		m_is_play_proc_stop = is_stop;
		break;

		//�G���h��ʎ�
	case n_game_scene::END:
		m_is_end_proc_stop = is_stop;
		break;

	default:break;
	}
}

/// <summary>
/// �Q�ƃV�[���̐i�s��Ԃ�ύX����
/// </summary>
/// <param name="scene">�Q�ƃV�[��</param>
/// <param name="set_state">�i�s��ԁA�ύX��</param>
VOID ClGameScene::MmSetSceneState(GAME_SCENE scene, SCENE_STATE set_state) {
	switch (scene){
	case n_game_scene::TITLE:
		m_title_state = set_state;
		break;
	case n_game_scene::PLAY:
		m_play_state = set_state;
		break;
	case n_game_scene::END:
		m_end_state = set_state;
		break;
	default:
		break;
	}
}

//*--------------------------------------------------------------------------------*
//								�֐�
//*--------------------------------------------------------------------------------*

const string CPP_NAME = "GameScene";

//�Q�[�����J�n�O�̏���
VOID ClGameScene::GameInit() {

	//*---------- �������珈�� ----------*
	

	//�ǂݍ���
	//�w�i�摜�ǂݍ���
	//�^�C�g��
	m_title_back_img.Load(
		"TitleBack.png", 0, TRUE,
		CPP_NAME, "m_title_back_img");
	//�v���C
	m_play_back_img_start.Load(
		"PlayBackStart.jpg", m_back_move_abs_speed, TRUE,
		CPP_NAME, "m_play_back_start_img");
	m_play_back_img_up.Load(
		"PlayBackUp.jpg", m_back_move_abs_speed, TRUE,
		CPP_NAME, "m_play_back_up_img");
	m_play_back_img_up.SetPos(
		n_xy::TOP_CENTER, n_xy::BUTTOM_CENTER);
	//�G���h
	m_end_back_img.Load(
		"EndBack.jpg", 0, TRUE,
		CPP_NAME, "m_end_back_img");

	//���S�̓ǂݍ���
	m_title_logo_img.Load(
		"TitleLogo.png", 0, TRUE,
		CPP_NAME, "m_title_logo_img");
	m_title_logo_img.SetPos(n_xy::CENTER_CENTER, n_xy::CENTER_CENTER);
	m_end_logo_img.Load(
		"EndLogo.png", 0, TRUE,
		CPP_NAME, "m_end_logo_img");
	m_end_logo_img.SetPos(n_xy::CENTER_CENTER, n_xy::CENTER_CENTER);

	//�@�̉摜�̓ǂݍ���
	m_player.Load("Player.png", CPP_NAME, "m_player");

	//�G�摜�̓ǂݍ���
	for (int i = 0; i < ENEMY_KIND; i++) {
		m_enemy_base[i].Load(ENEMY_PATHS[i], CPP_NAME, "m_enemy");
		m_enemy_base[i].SetAbsSpeed(1);
	}

	//�e�摜�̓ǂݍ���
	m_shot_base.Load("ShotRed.png",
		m_shot_div_x, m_shot_div_y, m_shot_div_max,
		CPP_NAME, "m_shot");
	m_shot_base.SetAbsSpeed(2);
	for (int i = 0; i < SHOT_MAX; i++) {
		m_shot_use[i].coll_img = m_shot_base;
	}
	
	//Bgm�ǂݍ���
	m_title_audio.BgmLoad(
		"TitleBgm.mp3", CPP_NAME, "m_title_audio");
	m_play_audio.BgmLoad(
		"PlayBgm.mp3", CPP_NAME, "m_play_audio");
	m_end_audio.BgmLoad(
		"EndBgm.mp3", CPP_NAME, "m_end_audio");

}

//���݂̃Q�[���V�[���ɂ���ď�����ς���
VOID ClGameScene::GameSceneSwitch() {
	
	switch (m_scene){
		//�^�C�g�����
	case n_game_scene::TITLE:
		MmTitleProc();	//����
		MmTitleDraw();	//�`��
		break;

		//�v���C���
	case n_game_scene::PLAY:
		MmPlayProc();	//����
		MmPlayDraw();	//�`��
		break;

		//�G���h���
	case n_game_scene::END:
		MmEndProc();	//����
		MmEndDraw();	//�`��
		break;


	default:break;
	}

	//���ǂݍ��݂��s����
	switch (m_back_scene){
		//�Ȃɂ��s��Ȃ�
	case n_game_scene::BACK_GAME_SCENE::NONE:
		MmBackNoneDebug();	//�f�o�b�N
		break;

		//�����[�h���s��
	case n_game_scene::BACK_LOAD:
		MmBackLoadProc();	//����
		MmBackLoadDebug();	//�f�o�b�N
		break;

	default:break;
	}
}

//*------------------------------------------------*
//		�^�C�g�����
//*------------------------------------------------*

//�^�C�g������
VOID ClGameScene::MmTitleProc() {
	if (MmIsTitleProcDo() == FALSE) { return; }		//���̐�̏����͍s��Ȃ�

	//*---------- ����������s���� ----------*

	

	//�V�[���؂�ւ�
	if (ClKeyboard::GetIns()->GetIsKeyDown(KEY_INPUT_SPACE) == TRUE) {
		ChangeScenePlay();
	}

	
}

//�^�C�g���������s����
BOOL ClGameScene::MmIsTitleProcDo() {
	MmSceneChangeProc();				//�V�[���ύX
	MmTitleStart();						//�V�[���؂�ւ���ŏ��̏���
	MmTitleProcEnd();					//�t�F�[�h�A�E�g�J�n�n�_����
	MmTitleEnd();						//�t�F�[�h�A�E�g�����n�_����
	if (m_is_title_proc_stop == TRUE) {	//���̐�̏����͍s��Ȃ�
		return FALSE;
	}
	MmTitleProcStart();					//�t�F�[�h�C����̍ŏ��̏���

	return TRUE;
}

//�^�C�g���V�[���J�n����(m_scene���ύX�����Ƃ���1�x�̂�)
VOID ClGameScene::MmTitleStart() {
	//1�x�݂̂̏���
	if (m_title_state != n_game_scene::ClGameScene::SCENE_STATE::START) { return; }
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::START_AFTER;

	//*---------- ��������J�n���� ----------*
	//�}�E�X��\��
	SetMouseDispFlag(TRUE);
	 
	//Bgm�Đ�
	m_title_audio.Sound();


}

//�^�C�g���V�[�������J�n����(�t�F�[�h�C���I�������1�x�̂�)
VOID ClGameScene::MmTitleProcStart() {
	//1�x�݂̂̏���
	if (m_title_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END) { return; }
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END_AFTER;

	//*---------- ��������J�n���� ----------*
	
}

//�t�F�[�h�A�E�g�����J�n�n�_����
VOID ClGameScene::MmTitleProcEnd() {
	//1�x�݂̂̏���
	if (m_title_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START) { return; }
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START_AFTER;

	//*---------- ��������J�n���� ----------*
	
}

//�V�[���I���n�_����
VOID ClGameScene::MmTitleEnd() {
	if (m_title_state != n_game_scene::ClGameScene::SCENE_STATE::SCENE_END) { return; }
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::NEXT_SCENE;

	MmEnd(&m_title_state);		//�V�[���I���n�_�J�n�O����

	//*---------- ��������J�n���� ----------*
	//
	//���y���~
	m_title_audio.Stop();
}

//�^�C�g���`��
VOID ClGameScene::MmTitleDraw() {

	//�^�C�g���̉摜��`��
	m_title_back_img.Draw();
	m_title_logo_img.Draw();

	//*---------- ���`�揈���͏�ɏ����� ----------*
	//�t�F�[�h����
	if (m_is_change_secne == TRUE) { m_fade.FadeSameDraw(); }

	if (ClWin().GetIsDebug() == FALSE) { return; }	//�f�o�b�N��Ԃł͂Ȃ��Ȃ珈�����s��Ȃ�
	//*---------- ��������f�o�b�N���� ----------*

	

	//���݂̉�ʏ�Ԃ�\��
	DrawString(ClWin().GetWinPivot().x, ClWin().GetWinPivot().y, "Title", ClCom().GetFlipColor());

}

//*------------------------------------------------*
//		�v���C���
//*------------------------------------------------*

//�v���C����
VOID ClGameScene::MmPlayProc() {
	if (MmIsPlayProcDo() == FALSE) { return; }		//���̐�̏����͍s��Ȃ�

	//*---------- ����������s���� ----------*

	//�w�i�摜���ړ�
	m_play_back_img_start.Move(0, m_back_move_speed);
	m_play_back_img_up.Move(0, m_back_move_speed);
	if (m_play_back_img_start.GetPos().y > ClWin().GetWinHeight()) {
		m_play_back_img_start.SetPos(
			n_xy::TOP_CENTER, n_xy::BUTTOM_CENTER, 0, 1);
	}
	if (m_play_back_img_up.GetPos().y > ClWin().GetWinHeight()) {
		m_play_back_img_up.SetPos(
			n_xy::TOP_CENTER, n_xy::BUTTOM_CENTER, 0, 1);
	}

	//�v���C���[�̈ړ�
	m_player.SetMove(
		ClMouse::GetIns()->GetPos().x - m_player.GetSize().x / 2,
		ClMouse::GetIns()->GetPos().y - m_player.GetSize().y / 2);

	//�e�̏���
	//�e�̔��ˑ҂�
	if (m_shot_interval != TIME_START && m_shot_interval < m_shot_interval_max) {
		m_shot_interval += ClFps::GetIns()->GetDeltaTime();
		DrawString(100, 100, "IIIIII", ClCom().GetRed());
	}
	else {
		DrawString(100, 100, "AAAA", ClCom().GetRed());
		m_shot_interval = TIME_START;
	}

	//�e�̔���
	if (ClMouse::GetIns()->GetIsButton(MOUSE_INPUT_LEFT) == TRUE
		&& m_shot_interval == TIME_START) {
		
		for (int i = 0; i < SHOT_MAX; i++) {
			if (m_shot_use[i].coll_img.GetIsDraw() == FALSE) {
				m_shot_interval += ClFps::GetIns()->GetDeltaTime();
				m_shot_use[i].coll_img.SetIsDraw();

				//�e�̈ʒu
				m_shot_use[i].start_pos.x 
					= m_player.GetPos().x + m_player.GetSize().x / 2 
					- m_shot_use[i].coll_img.GetRadius();
				m_shot_use[i].start_pos.y = m_player.GetPos().y;

				m_shot_use[i].coll_img.SetMove(
					m_shot_use[i].start_pos.x,
					m_shot_use[i].start_pos.y);

				m_shot_use[i].degree = 270.0f;
				m_shot_use[i].radius = 0.0f;
			}
		}
	}

	//�e���΂�
	for (int i = 0; i < SHOT_MAX; i++) {
		if (m_shot_use[i].coll_img.GetIsDraw() == TRUE) {
			//���a�𑫂�
			m_shot_use[i].radius += m_shot_use[i].coll_img.GetAbsSpeed();

			//�e�̈ʒu���C��
			//���S�ʒu�{��΂��p�x����΂��������v�Z������
			m_shot_use[i].coll_img.SetMove(
				m_shot_use[i].start_pos.x
				+ cos(m_shot_use[i].degree * DX_PI / 180.0f)
				* m_shot_use[i].radius,
				m_shot_use[i].start_pos.y
				+ sin(m_shot_use[i].degree * DX_PI / 180.0f)
				* m_shot_use[i].radius
				);

			//��ʊO�ɏo����`�悵�Ȃ�
			if (m_shot_use[i].coll_img.GetPos().y
				+ m_shot_use[i].coll_img.GetSize().y
				< ClWin().GetWinPivot().y
				||
				m_shot_use[i].coll_img.GetPos().y>ClWin().GetWinHeight()
				||
				m_shot_use[i].coll_img.GetPos().x
				+ m_shot_use[i].coll_img.GetSize().x
				< ClWin().GetWinPivot().x
				||
				m_shot_use[i].coll_img.GetPos().x>ClWin().GetWinWidth()){
				m_shot_use[i].coll_img.SetIsDraw(FALSE);
			}
		}
	}

	//�G�̐���
	if (m_enemy_drop_interval < m_enemy_drop_interval_max) {
		m_enemy_drop_interval += ClFps::GetIns()->GetDeltaTime();
	}
	else {
		//�G�̃C���^�[�o����������
		m_enemy_drop_interval = TIME_START;
		//�G�𐶐�
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (m_enemy_use[i].GetIsDraw() == FALSE) {
				if (m_score < 1000) {
					m_enemy_use[i] = m_enemy_base[0];
				}
				else if (m_score > 2000) {
					m_enemy_use[i] = m_enemy_base[1];
				}
				else {
					m_enemy_use[i] = m_enemy_base[GetRand(ENEMY_MAX - 1)];
				}

				//m_enemy_use[i] = m_enemy_base[i];
				m_enemy_use[i].SetIsDraw(TRUE);
				m_enemy_use[i].SetMove(
					GetRand(ENEMY_MAX - 1) * ClWin().GetWinWidth() / 4,
					-m_enemy_use[i].GetRadius()
				);
				
				break;
			}
		}
	}

	//�G�̏���
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (m_enemy_use[i].GetIsDraw() == TRUE) {
			m_enemy_use[i].Move(0, 1);

			if (m_enemy_use[i].GetPos().y > ClWin().GetWinHeight()) {
				m_enemy_use[i].SetIsDraw(FALSE);
				return;
			}

			for (int j = 0; j < SHOT_MAX; j++) {
				if (m_enemy_use[i].IsStay(m_shot_use[j].coll_img.GetColl(),m_shot_use[j].coll_img.GetIsColl()) == TRUE) {
					m_enemy_use[i].SetIsDraw(FALSE);
					m_shot_use[j].coll_img.SetIsDraw(FALSE);
					m_score += 100;
				}
			}
		}
	}

	//�V�[���؂�ւ�
	if (m_score>=200) {
		ChangeSceneEnd();
	}
}

//�v���C�������s����
BOOL ClGameScene::MmIsPlayProcDo() {
	MmSceneChangeProc();				//�V�[���ύX
	MmPlayStart();						//�V�[���؂�ւ���ŏ��̏���
	MmPlayProcEnd();					//�t�F�[�h�A�E�g�J�n�n�_����
	MmPlayEnd();						//�t�F�[�h�A�E�g�����n�_����
	if (m_is_play_proc_stop == TRUE) {	//���̐�̏����͍s��Ȃ�
		return FALSE;
	}
	MmPlayProcStart();					//�t�F�[�h�C����̍ŏ��̏���

	return TRUE;
}

//�v���C�V�[���J�n����(m_scene���ύX�����Ƃ���1�x�̂�)
VOID ClGameScene::MmPlayStart() {
	//1�x�݂̂̏���
	if (m_play_state != n_game_scene::ClGameScene::SCENE_STATE::START) { return; }
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::START_AFTER;

	//*---------- ��������J�n���� ----------*
	//�}�E�X���\��
	SetMouseDispFlag(FALSE);

	//Bgm�Đ�
	m_play_audio.Sound();

	//�v���C���[�̉摜�`��t���O
	m_player.SetIsDraw(TRUE, FALSE);
	
}

//�v���C�V�[�������J�n����(�t�F�[�h�C���I�������1�x�̂�)
VOID ClGameScene::MmPlayProcStart() {
	//1�x�݂̂̏���
	if (m_play_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END) { return; }
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END_AFTER;

	//*---------- ��������J�n���� ----------*

	//�v���C���[�摜�̓����蔻��t���O
	m_player.SetIsDraw(TRUE, TRUE);
	
}

//�t�F�[�h�A�E�g�����J�n�n�_����
VOID ClGameScene::MmPlayProcEnd() {
	//1�x�݂̂̏���
	if (m_play_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START) { return; }
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START_AFTER;

	//*---------- ��������J�n���� ----------*
	
}

//�V�[���I���n�_����
VOID ClGameScene::MmPlayEnd() {
	if (m_play_state != n_game_scene::ClGameScene::SCENE_STATE::SCENE_END) { return; }
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::NEXT_SCENE;

	MmEnd(&m_play_state);		//�V�[���I���n�_�J�n�O����

	//*---------- ��������J�n���� ----------*
	
	//�G�̃C���^�[�o����������
	m_enemy_drop_interval = TIME_START;

	//Bgm��~
	m_play_audio.Stop();
}

//�v���C�`��
VOID ClGameScene::MmPlayDraw() {

	//�w�i�摜�̕`��
	m_play_back_img_start.Draw();
	m_play_back_img_up.Draw();

	//�G�̕`��
	for (int i = 0; i < ENEMY_MAX; i++) { m_enemy_use[i].Draw(); }

	//�e�̕`��
	for (int i = 0; i < SHOT_MAX; i++) { m_shot_use[i].coll_img.Draw(); }

	//�v���C���[�̉摜��`��
	m_player.Draw();

	DrawFormatString(0, 64, ClCom().GetFlipColor(), "SCORE : %d", m_score);

	//*---------- ���`�揈���͏�ɏ����� ----------*
	//�t�F�[�h����
	if (m_is_change_secne == TRUE) { m_fade.FadeSameDraw(); }

	if (ClWin().GetIsDebug() == FALSE) { return; }	//�f�o�b�N��Ԃł͂Ȃ��Ȃ珈�����s��Ȃ�
	//*---------- ��������f�o�b�N���� ----------*

	

	//���݂̉�ʏ�Ԃ�\��
	DrawString(ClWin().GetWinPivot().x, ClWin().GetWinPivot().y, "Play", ClCom().GetFlipColor());
}

VOID ClGameScene::MmEnd(SCENE_STATE* scene_state) {
	//if (*scene_state != n_game_scene::ClGameScene::SCENE_STATE::SCENE_END) { return; }
	//*scene_state = n_game_scene::ClGameScene::SCENE_STATE::NEXT_SCENE;

	m_scene = m_next_scene;	//���̃V�[����
	MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::START);

	m_fade.FadeDownStart(FADE_TIME);					//��ʃt�F�[�h�_�E���J�n
	ClAudioMult::GetIns()->SetFadeUpStart(FADE_TIME);	//���ʃt�F�[�h�A�b�v�J�n
}


//*------------------------------------------------*
//		�G���h���
//*------------------------------------------------*

//�G���h����
VOID ClGameScene::MmEndProc() {
	if (MmIsEndProcDo() == FALSE) { return; }	//���̐�̏����͍s��Ȃ�

	//*---------- ����������s���� ----------*
	//�V�[���؂�ւ�
	if (ClKeyboard::GetIns()->GetIsKeyDown(KEY_INPUT_SPACE) == TRUE) {
		ChangeSceneTitle();
	}
}

//�G���h�������s����
BOOL ClGameScene::MmIsEndProcDo() {
	MmSceneChangeProc();				//�V�[���ύX
	MmEndStart();						//�V�[���؂�ւ���ŏ��̏���
	MmEndProcEnd();					//�t�F�[�h�A�E�g�J�n�n�_����
	MmEndEnd();						//�t�F�[�h�A�E�g�����n�_����
	if (m_is_end_proc_stop == TRUE) {	//���̐�̏����͍s��Ȃ�
		return FALSE;
	}
	MmEndProcStart();					//�t�F�[�h�C����̍ŏ��̏���

	return TRUE;
}

//�G���h�V�[���J�n����(m_scene���ύX�����Ƃ���1�x�̂�)
VOID ClGameScene::MmEndStart() {
	//1�x�݂̂̏���
	if (m_end_state != n_game_scene::ClGameScene::SCENE_STATE::START) { return; }
	m_end_state = n_game_scene::ClGameScene::SCENE_STATE::START_AFTER;

	//*---------- ��������J�n���� ----------*
	//�}�E�X��\��
	SetMouseDispFlag(TRUE);

	//Bgm�Đ�
	m_end_audio.Sound();
}

//�G���h�����J�n����(�t�F�[�h�C���I�������1�x�̂�)
VOID ClGameScene::MmEndProcStart() {
	//1�x�݂̂̏���
	if (m_end_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END) { return; }
	m_end_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END_AFTER;

	//*---------- ��������J�n���� ----------*
	
}

//�t�F�[�h�A�E�g�J�n�n�_����(�t�F�[�h�A�E�g�J�n��1�x�̂�)
VOID ClGameScene::MmEndProcEnd() {
	//1�x�݂̂̏���
	if (m_end_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START) { return; }
	m_end_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START_AFTER;

	//*---------- ��������J�n���� ----------*
	
}

//�t�F�[�h�A�E�g�����n�_����(�t�F�[�h�A�E�g������1�x�̂�)
VOID ClGameScene::MmEndEnd() {
	if (m_end_state != n_game_scene::ClGameScene::SCENE_STATE::SCENE_END) { return; }
	m_end_state = n_game_scene::ClGameScene::SCENE_STATE::NEXT_SCENE;
	MmEnd(&m_end_state);		//�V�[���I���n�_�J�n�O����

	//*---------- ��������J�n���� ----------*
	

	//Bgm��~
	m_end_audio.Stop();
}

//�G���h�`��
VOID ClGameScene::MmEndDraw() {

	//�摜��`��
	m_end_back_img.Draw();
	m_end_logo_img.Draw();

	//*---------- ���`�揈���͏�ɏ����� ----------*
	//�t�F�[�h����
	if (m_is_change_secne == TRUE) { m_fade.FadeSameDraw(); }

	if (ClWin().GetIsDebug() == FALSE) { return; }	//�f�o�b�N��Ԃł͂Ȃ��Ȃ珈�����s��Ȃ�
	//*---------- ��������f�o�b�N���� ----------*

	//���݂̉�ʏ�Ԃ�\��
	DrawString(ClWin().GetWinPivot().x, ClWin().GetWinPivot().y, "End", ClCom().GetFlipColor());
}


//*------------------------------------------------*
//		���ʊ֐�
//*------------------------------------------------*

//�V�[���ύX����
VOID ClGameScene::MmSceneChangeProc() {
	//�V�[���ύX���s���Ȃ��Ȃ珈�����s��Ȃ�
	if (m_is_change_secne == FALSE) { return; }
		
	//�t�F�[�h���X�V
	m_fade.FadeProc();
	ClAudioMult::GetIns()->FadeProc();

	//�t�F�[�h�A�E�g�������I��������
	if (m_fade.GetIsFadeNone() == TRUE && m_fade.GetFadeType() == n_fade::FADE_TYPE::FADE_UP_TYPE) {
		//�t�F�[�h�A�E�g�J�n�n�_�����̃t���O�𗧂Ă�
		MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::SCENE_END);
	}

	//�t�F�[�h�C���������I��������
	if (m_fade.GetIsFadeNone() == TRUE && m_fade.GetFadeType() == n_fade::FADE_TYPE::FADE_DOWN_TYPE) {
		m_back_scene = n_game_scene::BACK_GAME_SCENE::NONE;	//�����[�h������

		//�t�F�[�h�C���I����J�n�����̏�Ԃɂ���
		MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END);

		m_is_change_secne = FALSE;			//�V�[���؂�ւ��t���O������

		//�V�[�����Ƃ̏������~������t���O������
		MmSetProcStopState(m_scene, FALSE);
	}
}

//*------------------------------------------------*
//		���V�[��
//*------------------------------------------------*

//���V�[�����Ȃ��Ƃ��̃f�o�b�N����
VOID ClGameScene::MmBackNoneDebug() {
	//�f�o�b�N��Ԃł͂Ȃ��Ȃ珈�����s��Ȃ�
	if (ClWin().GetIsDebug() == FALSE) { return; }

	//���݂̗���ʏ�Ԃ�\��
	DrawString(
		ClWin().GetWinPivot().x, ClWin().GetWinPivot().y + ClCom().GetDefalutFontSize(),
		"BackNone", ClCom().GetFlipColor()
	);
}

//�����[�h����
VOID ClGameScene::MmBackLoadProc() {}

//�����[�h�f�o�b�N����
VOID ClGameScene::MmBackLoadDebug() {
	//�f�o�b�N��Ԃł͂Ȃ��Ȃ珈�����s��Ȃ�
	if (ClWin().GetIsDebug() == FALSE) { return; }

	//���݂̗���ʏ�Ԃ�\��
	DrawString(
		ClWin().GetWinPivot().x, ClWin().GetWinPivot().y + ClCom().GetDefalutFontSize(),
		"BackLoad", ClCom().GetFlipColor()
	);
}
