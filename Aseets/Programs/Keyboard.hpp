#pragma once

//���X�̃L�[�̐�
#define DEFAULT_KEY_NUM 256
#define KEY_TIME_INPUT_NUM 5

namespace n_keyboard{
	//�L�[�{�[�h�̓��͂��Ǘ�����
	class ClKeyboard{
		//*----------------------------------------------------------------------------*
		//							public��������
		//*----------------------------------------------------------------------------*

	public:
		//		�V���O���g������		
		//�C���X�^���X�擾(���߂ĎQ�Ƃ���Ƃ��̓C���X�^���X�𐶐�)
		static ClKeyboard* GetIns();
		//�I�u�W�F�N�g�̔j��
		VOID Destroy();

		//�L�[���͏�Ԃ��X�V����
		int GpUpdateKey();
		//�L�[�̓��͎��Ԃ�Ԃ�
		int GetKeyCnt(int key_input_);
		//�L�[��������Ă����Ԃ�(������Ă����ԂȂ�TRUE)
		BOOL GetIsKey(int key_input_);
		//�L�[�������ꂽ�u�Ԃ�(�����ꂽ�u�ԂȂ�TRUE)
		BOOL GetIsKeyDown(int key_input_);
		//�L�[�������ꂽ�u�Ԃ�(�����ꂽ�u�ԂȂ�TRUE)
		BOOL GetIsKeyUp(int key_input_);
		//�L�[�𗣂��Ă����Ԃ�(������Ă���Ȃ�TRUE)
		BOOL GetIsKeyAway(int key_input_);
		//�w�莞�ԉ����ꂽ��
		BOOL GetIsKeyTimeInput(int key_input_, float time);
		//�w�莞��(�~���b)(�𒴂��� / �ȏ� / �Ɠ��� / �ȉ� / ����)�L�[�������ꂽ��(��{�F�𒴂���)
		BOOL GetIsKeyTimeInput(int key_input_, float time, n_com::IF_CASE_TYPE key_case_type);

		//*----------------------------------------------------------------------------*
		//							private��������
		//*----------------------------------------------------------------------------*


	private:
		//		�V���O���g������
		//�V���O���g���ȃC���X�^���X
		static ClKeyboard* m_ins;
		//�R���X�g���N�^�A�L�[�̏�Ԃ�������
		ClKeyboard();
		//�R�s�[�R���X�g���N�^
		ClKeyboard(const ClKeyboard& src);
		ClKeyboard& operator=(const ClKeyboard& src);

		//�f�X�g���N�^
		virtual ~ClKeyboard();

		//�L�[��������Ă���t���[�������i�[����
		int m_key_cnt[DEFAULT_KEY_NUM];
		//���Ԏw�菈���̂Ƃ���TRUE����ォ(2�d����ɂȂ�Ȃ��悤�ɂ���)
		BOOL m_is_time_input_after[DEFAULT_KEY_NUM][KEY_TIME_INPUT_NUM];
	};
}