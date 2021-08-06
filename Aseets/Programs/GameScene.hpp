#pragma once

//		����t�@�C��
#include FADE_HPP	//��ʐ؂�ւ����A�t�F�[�h���g�p
#include IMG_HPP	//�摜�ǂݍ���
#include IMG_DIV_HPP
#include IMG_COLL_HPP
#include AUDIO_HPP

#define SHOT_MAX 40
#define ENEMY_KIND 7
#define ENEMY_MAX 10

namespace n_game_scene{

	//		enum
	//�Q�[���V�[��
	enum GAME_SCENE {
		END,		//�I���
		TITLE,		//�^�C�g��
		PLAY,		//�Q�[���V�[��
	};

	//���V�[����ǉ������Ƃ��ɕK�v�Ȓǉ��ϐ�
		// 1.�����o�ϐ� > �V�[�����ꂼ��̐i�s�󋵂ɐV�KGAME_STATE��ǉ��A�R���X�g���N�^�ŏ�����
		// 2.MmSetProcStopState()��switch�ǉ�
		// 3.MmSetSceneState()��switch�ǉ�
		// 4.GameSceneSwitch()��switch�ǉ�
		// 5.�����o�֐� > �V�[���ɂ���Ă̏�����ǉ�
		// 6.�v���p�e�B > �V�[���ύX������ǉ�

	//���̃Q�[���V�[��
	enum BACK_GAME_SCENE {
		NONE,		//���ɂȂ�
		BACK_LOAD	//���ǂݍ��ݒ�
	};

	

	//�Q�[���̃V�[�����Ǘ�
	class ClGameScene{
		//*----------------------------------------------------------------------------*
		//							public��������
		//*----------------------------------------------------------------------------*

	public:
		//		�V���O���g������
		//�C���X�^���X�擾(���߂ĎQ�Ƃ���Ƃ��̓C���X�^���X�𐶐�)
		static ClGameScene* GetIns();
		//�I�u�W�F�N�g�̔j��
		VOID Destroy();

		//		enum
		//�V�[���i�s��
		enum SCENE_STATE {
			START,
			START_AFTER,
			FADE_DOWN_END,
			FADE_DOWN_END_AFTER,
			FADE_UP_START,
			FADE_UP_START_AFTER,
			SCENE_END,
			NEXT_SCENE
		};

		//		�v���p�e�B
		VOID ChangeSceneEnd();		//���[�h�V�[���ɑJ��
		VOID ChangeSceneTitle();	//�^�C�g���V�[���ɑJ��
		VOID ChangeScenePlay();		//�v���C�V�[���ɑJ��

		//		�֐�
		VOID GameInit();		//�Q�[���J�n�O�̏���
		VOID GameSceneSwitch();		//�Q�[���̃V�[���ɂ���ď����𕪊�

		//*----------------------------------------------------------------------------*
		//							private��������
		//*----------------------------------------------------------------------------*

	private:
		//		�V���O���g������
		//�V���O���g���ȃC���X�^���X
		static ClGameScene* m_ins;
		//�R���X�g���N�^�A������
		ClGameScene();
		//�R�s�[�R���X�g���N�^
		ClGameScene(const ClGameScene& src);
		ClGameScene& operator=(const ClGameScene& src);
		//�f�X�g���N�^�A�I�u�W�F�N�g�̔j��
		virtual ~ClGameScene();

		//		�����o�֐�
		//�V�[���ɂ���Ă̏���
		//�^�C�g��
		BOOL MmIsTitleProcDo();	//�������s����
		VOID MmTitleProc();		//����
		VOID MmTitleStart();	//�V�[���J�n����
		VOID MmTitleProcStart();//�����J�n����
		VOID MmTitleProcEnd();	//�t�F�[�h�A�E�g�����J�n�n�_����
		VOID MmTitleEnd();		//�V�[���I���n�_����
		VOID MmTitleDraw();		//�`��
		//�v���C
		BOOL MmIsPlayProcDo();	//�������s����
		VOID MmPlayProc();		//����
		VOID MmPlayStart();		//�V�[���J�n����
		VOID MmPlayProcStart();	//�����J�n����
		VOID MmPlayProcEnd();	//�t�F�[�h�A�E�g�����J�n�n�_����
		VOID MmPlayEnd();		//�V�[���I���n�_����
		VOID MmPlayDraw();		//�`��
		//�G���h
		BOOL MmIsEndProcDo();	//�������s����
		VOID MmEndProc();		//����
		VOID MmEndStart();		//�V�[���J�n����
		VOID MmEndProcStart();	//�����J�n����
		VOID MmEndProcEnd();	//�t�F�[�h�A�E�g�J�n�n�_����
		VOID MmEndEnd();		//�t�F�[�h�A�E�g�����n�_����
		VOID MmEndDraw();		//�`��
		//
		VOID MmSceneChangeProc();	//�V�[���ύX�̏���
		VOID MmEnd(SCENE_STATE* scene_state);
		//������
		VOID MmBackNoneDebug();		//�f�o�b�N
		VOID MmBackLoadProc();		//����
		VOID MmBackLoadDebug();		//�f�o�b�N
		//
		VOID MmChangeScene(GAME_SCENE next_scene);	//�V�[���ύX�J�n����
		VOID MmSetProcStopState(					//�`��ȊO�̏������~������t���O�̐ݒ�
			GAME_SCENE scene, BOOL is_stop);
		VOID MmSetSceneState(						//�Q�ƃV�[���̐i�s��Ԃ�ύX����
			GAME_SCENE scene, SCENE_STATE set_state);


		//		�����o�ϐ�
		GAME_SCENE m_scene;
		GAME_SCENE m_next_scene;
		BACK_GAME_SCENE m_back_scene;
		BOOL m_is_change_secne;
		n_fade::ClFade m_fade;
		//�������~�߂邩
		BOOL m_is_title_proc_stop;
		BOOL m_is_play_proc_stop;
		BOOL m_is_end_proc_stop;
		//�V�[�����ꂼ��̐i�s��
		SCENE_STATE m_title_state;
		SCENE_STATE m_play_state;
		SCENE_STATE m_end_state;

		//		�ϐ�
		int m_score;
		int m_back_move_abs_speed;
		int m_back_move_speed;

		//		�ǂݍ��ނ���
		//�摜
		//�w�i�摜
		n_img::ClImg m_title_back_img;
		n_img::ClImg m_play_back_img_start;
		n_img::ClImg m_play_back_img_up;
		n_img::ClImg m_end_back_img;
		//���S
		n_img::ClImg m_title_logo_img;
		n_img::ClImg m_end_logo_img;
		//�@�̉摜
		n_img_coll::ClImgColl m_player;
		n_img_coll::ClImgCollCircle m_enemy_base[ENEMY_KIND];
		n_img_coll::ClImgCollCircle m_enemy_use[ENEMY_MAX];
		float m_enemy_drop_interval;
		float m_enemy_drop_interval_max;
		//�e�摜
		n_img_div::ClImgDivColl m_shot_base;
		
		class SHOT
		{
		public:
			SHOT();
			~SHOT();
			n_img_div::ClImgDivColl coll_img;
			n_xy::ClXY start_pos;
			float degree;
			float radius;

		private:

		};
		SHOT m_shot_use[SHOT_MAX];
		
		int m_shot_div_x;
		int m_shot_div_y;
		int m_shot_div_max;
		float m_shot_interval;
		float m_shot_interval_max;

		//���y
		n_audio::ClAudio m_title_audio;
		n_audio::ClAudio m_play_audio;
		n_audio::ClAudio m_end_audio;
	};
}