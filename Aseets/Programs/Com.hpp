#pragma once

namespace n_com {

	//enum�����
	//�E����enum��Singleton�݂̂Ŏg���邩�ǂ���
	//�@Singleton�ł̂ݎg����Ȃ�Com�ō쐬�\

	//�����̎��
	enum IF_CASE_TYPE {
		OVER,		//������(>)
		ABOVE,		//�ȏ�(>=)
		EQUAL,		//����(==)
		IN_UNDER,	//�ȉ�(<=)
		LESS_THAN	//����(<)
	};

	//�����͂ǂ�����
	enum IF_CASE_WHICH{
		EQUAL_OUT,	//������(>),����(<)
		EQUAL_IN	//�ȏ�(>=)�A�ȉ�(<=)
	};

	//�N���X�����
	//�ECom�t�@�C���ȊO�ō쐬�N���X��߂�l�Ƃ���
	//�@�֐�����邩�ǂ���(���ꍇ��Com�ȊO�ŃN���X���쐬����)

	//���ʂ��Ďg���ϐ��⏈��������
	class ClCom {

		//*----------------------------------------------------------------------------*
		//							public��������
		//*----------------------------------------------------------------------------*
	public:
		//�R���X�g���N�^
		ClCom();
		~ClCom();

		//		�v���p�e�B��������
		VOID VirtualError();	//virtual�̊֐����O���ȂǂŎg�p���ꂽ�Ƃ��G���[���b�Z�[�W���o��
		// 0�`255�̍ő�l�A���Ԓl�A�ŏ��l
		int GetUnCharMax();	//255
		int GetUnCharHalf();//128
		int GetUnCharMin();	//0
		//�ݏ�
		int GetPowerNumPlas(int index);				//2��index���Ԃ�
		int GetPowerNumPlas(int radix, int index);	//radix��index���Ԃ�
		//�b���~��
		int GetMilliMult();			//1�b��1000�~���b
		//�F
		unsigned int GetBlack();	//���F
		unsigned int GetGray();		//�D�F
		unsigned int GetWhite();	//���F
		unsigned int GetSameColor();//�w�i�F�Ɠ����F
		unsigned int GetFlipColor();//�w�i�F�Ɣ��ΐF
		unsigned int GetRed();		//�ԐF
		unsigned int GetGreen();	//�ΐF
		unsigned int GetBlue();		//�F
		unsigned int GetYellow();	//���F
		unsigned int GetCyan();		//�V�A��
		unsigned int GetMagenta();	//�}�[���_
		unsigned int GetOrange();	//��F
		unsigned int GetYellowGreen();//����
		unsigned int GetBlueGreen();//��
		unsigned int GetSkyColor();	//��F
		unsigned int GetRedPurple();//�Ԏ�
		unsigned int GetBluePurple();//��
		//		�n���h���̃G���[�l
		int GetHandleError();
		//		�t�@�C���p�X
		//.\\Aseets/
		string GetAseetsPath();
		//.\\Aseets/Audios/
		string GetAudiosPath();
		//.\\Aseets/Images/
		string GetImagesPath();
		//.\\Aseets/Movies/
		string GetMoviesPath();
		//�f�t�H���g�̃t�H���g�T�C�Y
		int GetDefalutFontSize();

	//*----------------------------------------------------------------------------*
	//							private��������
	//*----------------------------------------------------------------------------*
	private:
	};
}