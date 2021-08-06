#pragma once

namespace n_game_flag{
	//�Q�[�����s�̃t���O���Ǘ�����
	class ClGameFlag{
		//*----------------------------------------------------------------------------*
		//							public��������
		//*----------------------------------------------------------------------------*

	public:
		//		�V���O���g������
		//�C���X�^���X�擾(���߂ĎQ�Ƃ���Ƃ��̓C���X�^���X�𐶐�)
		static ClGameFlag* GetIns();
		//�I�u�W�F�N�g�̔j��
		VOID Destroy();

		//		�v���p�e�B��������
		//�Q�[�����s�̃t���O�����낷
		VOID SetEndPlay();
		//�Q�[�����s���Ă���̂��Q�Ƃ���
		BOOL GetIsPlay();

		//*----------------------------------------------------------------------------*
		//							private��������
		//*----------------------------------------------------------------------------*

	private:
		//		�V���O���g������
		//�V���O���g���ȃC���X�^���X
		static ClGameFlag* m_ins;
		//�R���X�g���N�^�A������
		ClGameFlag();
		//�R�s�[�R���X�g���N�^
		ClGameFlag(const ClGameFlag& src);
		ClGameFlag& operator=(const ClGameFlag& src);
		//�f�X�g���N�^�A�I�u�W�F�N�g�̔j��
		virtual ~ClGameFlag();

		//		�����o�ϐ���������
		//�Q�[�����s���Ă��邩
		BOOL m_is_play;
	};
}