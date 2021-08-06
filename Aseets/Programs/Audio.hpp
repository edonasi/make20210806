#pragma once

namespace n_audio{

	//		enum
	//���y�̎��
	enum SE_TYPE {
		BGM,		//bgm
		SYSTEM,		//�N���b�N���Ȃǂ̃V�X�e����
		PLAY,		//�U�����Ȃǂ̉�
	};

	//���y�̊Ǘ�
	class ClAudio{
		//*----------------------------------------------------------------------------*
		//							public��������
		//*----------------------------------------------------------------------------*

	public:
		//		�R���X�g���N�^�A�f�X�g���N�^�A�ϐ��̏�����
		ClAudio();
		/*ClAudio(const ClAudio& src);
		ClAudio& operator=(const ClAudio& src);*/
		~ClAudio();

		//		�v���p�e�B
		int GetAudioHandle();		//�n���h�����擾
		int GetProductVolume();		//����(����Ғ����p)���擾
		SE_TYPE GetSeType();		//���y�̎�ނ��擾

		//		�֐�
		//Bgm�ǂݍ���
		BOOL BgmLoad(string path, string cpp_name, string ins_name);
		BOOL BgmLoad(string path, int volume, string cpp_name, string ins_name);
		
		//Se �ǂݍ���
		BOOL SeLoad(
			string path,SE_TYPE se_type,
			string cpp_name, string ins_name);
		BOOL SeLoad(
			string path, int volume, SE_TYPE se_type,
			string cpp_name, string ins_name);

		VOID Sound();	//���y���Đ�
		VOID Stop();	//���y���~
		VOID Delete(BOOL is_vector_erase);	//���y�̃���������


		//*----------------------------------------------------------------------------*
		//							private��������
		//*----------------------------------------------------------------------------*

	private:
		//		�����o�֐�
		BOOL MmLoad(					//���y�ǂݍ��݋��ʊ֐�
			string path, string cpp_name, string ins_name);		
		VOID MmLoadVolume(int volume);	//���ʂ̓ǂݍ���

		//		�����o�ϐ�
		int m_handle;			//�n���h��
		string m_path;			//�p�X
		int m_product_volume;	//����(����Ғ����p)
		int m_play_type;		//�Đ�����
		SE_TYPE m_se_type;	//���y�̎��
	};
}
