#pragma once

namespace n_cnt {

	//		enum
		//�J�E���g�̎d��
	enum CNT_AFTER_TYPE {
		STOP,		//�ő�l�܂ōs������0�ɏ��������Ē�~����
		LOOP,			//�ő�l�܂ōs������ŏ��ɖ߂��ăJ�E���g
	};

	//�z��v�f�J�E���^�A�b���ŃJ�E���^���Z(�����[�v�����������ƕb���������̂Œ���)
	class ClCntArySec{
		//*----------------------------------------------------------------------------*
		//							public��������
		//*----------------------------------------------------------------------------*
	public:
		//		�R���X�g���N�^�A�f�X�g���N�^�A�ϐ��̏�����
		ClCntArySec();
		~ClCntArySec();

		//		�v���p�e�B
		BOOL GetIsOver();		//�ő�l�𒴂�����
		BOOL GetIsStop();		//�J�E���^���X�g�b�v������
		int GetIndex();			//�J�E���^�擾
		int GetReverseIndex();	//���]�����J�E���^���擾
		VOID SetIsStop();		//�J�E���^���~������
		VOID SetCnt();			//�J�E���^�ƌ��݂̕b����������
		VOID SetCnt(			//�J�E���^�̐ݒ�
			int cnt_size, float all_sec, n_cnt::CNT_AFTER_TYPE after_type);

		//		�֐�
		VOID Proc();			//�J�E���^�̍X�V

		//*----------------------------------------------------------------------------*
		//							private��������
		//*----------------------------------------------------------------------------*
	private:
		//		�����o�֐�
		BOOL MmIsIndexOver();		//�v�f�����ő吔�𒴂�����
		float MmGetTimerSub();		//�^�C�}�[�J�n����̎���
		float MmGetTimerSecSub();	//���b���o�ߎ���
		VOID MmSetCnt();			//�J�E���^�ƊJ�n���Ԃ�������

		//		�����o�ϐ�
		BOOL m_is_over;				//�ő�l�𒴂�����
		BOOL m_is_stop;				//�J�E���g���~���邩
		n_cnt::CNT_AFTER_TYPE m_after_type;
		int m_index;				//���݂̃J�E���^
		int m_index_max;			//�J�E���^�̍ő�l
		float m_timer_start;		//�v���J�n�n�_
		float m_timer_sec_start;	//�b�����J�n�n�_
		float m_timer;				//���݂̌v������
		float m_sec_all;			//�J�E���g0�܂łɂ����鎞��
		float m_sec_max;			//�b�����l
	};

	
}
