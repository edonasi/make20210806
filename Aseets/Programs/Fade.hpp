#pragma once

//�w�b�_�t�@�C���C���N���[�h
#include CNT_HPP

namespace n_fade {
	//		enum
	enum FADE_TYPE {
		FADE_UP_DOWN_TYPE,
		FADE_DOWN_UP_TYPE,
		FADE_UP_TYPE,
		FADE_DOWN_TYPE,
	};
	//�t�F�[�h�̏��
	enum FADE_STATE {
		NONE,
		FADE_UP,
		FADE_DOWN
	};

	//�t�F�[�h�_�E���t�F�[�h�A�b�v�̃C�����X�^���X
	class ClFade{
		//*----------------------------------------------------------------------------*
		//							public��������
		//*----------------------------------------------------------------------------*

	public:
		//		�R���X�g���N�^�A�f�X�g���N�^�A�ϐ��̏�����
		ClFade();
		~ClFade();

		//		�v���p�e�B
		FADE_TYPE GetFadeType();	//�t�F�[�h�̎��
		BOOL GetIsFadeNone();		//�t�F�[�h���s���Ă��Ȃ���
		BOOL GetIsFadeStop();		//�t�F�[�h���I��������
		float GetFadeDecimalPar();	//�t�F�[�h�̊���(0.0f�`1.0f)

		//		�֐�
		//�J�n����
		VOID FadeUpDownStart(float all_time);	//�t�F�[�h�A�b�v�_�E��
		VOID FadeDownUpStart(float all_time);	//�t�F�[�h�_�E���A�b�v
		VOID FadeUpStart(float all_time);		//�t�F�[�h�A�b�v
		VOID FadeDownStart(float all_time);		//�t�F�[�h�_�E��
		//update����
		VOID FadeProc();		//�X�V����
		//�t�F�[�h�`��
		VOID FadeSameDraw();	
		VOID FadeBlackDraw();	
		VOID FadeWhiteDraw();	
		

		//*----------------------------------------------------------------------------*
		//							private��������
		//*----------------------------------------------------------------------------*

	private:
		//		�����o�֐�
		VOID MmFadeDraw(unsigned int color);	//�t�F�[�h�`��

		//		�����o�ϐ�
		BOOL m_is_start;			//�J�n������
		BOOL m_next_in;				//���̓t�F�[�h�_�E�����邩
		FADE_TYPE m_fade_type;		//�t�F�[�h�̎��
		FADE_STATE m_fade_state;	//�t�F�[�h�̏��
		n_cnt::ClCntArySec m_cnt;	//�J�E���^
	};
}
