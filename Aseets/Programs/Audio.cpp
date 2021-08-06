//*--------------------------------------------------------------------------------*
//								���y�̊Ǘ�
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include AUDIO_HPP
using namespace n_audio;
//		Singleton�t�@�C��
#include AUDIO_MULT_HPP
using namespace n_audio_mult;


//�������ĂȂ����ƃ���
//�ESe�̍Đ��ŉ����d�Ȃ��čĐ����Đ����ԃC���^�[�o����b�����w��

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^�A�f�X�g���N�^�A�ϐ��̏�����
//*--------------------------------------------------------------------------------*

ClAudio::ClAudio() {
	//�ϐ��̏�����
	m_handle = ClCom().GetHandleError();
	m_product_volume = ClCom().GetUnCharHalf();
	m_play_type = -1;
	m_se_type = SE_TYPE::BGM;
}

//�R�s�[�R���X�g���N�^
ClAudio::ClAudio(const ClAudio &src) { 
	m_handle = src.m_handle;
	m_path = src.m_path;
	m_product_volume = src.m_product_volume;
	m_play_type = src.m_play_type;
	m_se_type = src.m_se_type;
	return; 
}
ClAudio &ClAudio::operator=(const ClAudio &src) { 
	if (this != &src) { ClAudio::operator=(src); }
	return (*this);
}
ClAudio::~ClAudio() { return; }

//*--------------------------------------------------------------------------------*
//								�v���p�e�B
//*--------------------------------------------------------------------------------*

//�n���h�����擾
int ClAudio::GetAudioHandle() { return m_handle; }
//����(����Ғ����p)���擾
int ClAudio::GetProductVolume() { return m_product_volume; }
//���y�̎�ނ��擾
SE_TYPE ClAudio::GetSeType() { return m_se_type; }

//*--------------------------------------------------------------------------------*
//								�֐�
//*--------------------------------------------------------------------------------*

/// <summary>
/// Bgm�̓ǂݍ���(�ǂݍ��ݕ��@��Se�Ɠ���)(��if(BgmLoad==FALSE){return FALSE;}�Ŏg�p)
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns>�ǂݍ��߂���TRUE</returns>
BOOL ClAudio::BgmLoad(string path, string cpp_name, string ins_name) {
	//���y�ǂݍ���
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	//�K�v�ȕϐ�����
	m_play_type = DX_PLAYTYPE_LOOP;			//�Đ�����
	m_se_type = SE_TYPE::BGM;	//���y�̎��
	MmLoadVolume(m_product_volume);			//���ʂ̓ǂݍ���

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// ���ʂ�ς���Bgm�̓ǂݍ���(�ǂݍ��ݕ��@��Se�Ɠ���)(��if(BgmLoad==FALSE){return FALSE;}�Ŏg�p)
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="volume">����(0~255)</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns>�ǂݍ��߂���TRUE</returns>
BOOL ClAudio::BgmLoad(string path, int volume, string cpp_name, string ins_name) {
	//���y�ǂݍ���
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	//�K�v�ȕϐ�����
	m_play_type = DX_PLAYTYPE_LOOP;			//�Đ�����
	m_se_type = SE_TYPE::BGM;	//���y�̎��
	m_product_volume = volume;				//���ʂ̕ύX
	MmLoadVolume(m_product_volume);			//���ʂ̓ǂݍ���

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// Se�̓ǂݍ���(�ǂݍ��ݕ��@��Bgm�Ɠ���)(��if(SeLoad==FALSE){return FALSE;}�Ŏg�p)
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="se_type">Se�̎��</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns></returns>
BOOL ClAudio::SeLoad(
	string path, SE_TYPE se_type,
	string cpp_name, string ins_name) {
	//���y�ǂݍ���
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	//�K�v�ȕϐ�����
	m_play_type = DX_PLAYTYPE_BACK;		//�Đ�����
	m_se_type = se_type;				//���y�̎��
	MmLoadVolume(m_product_volume);		//���ʂ̓ǂݍ���

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// ���y�ǂݍ���(��if(SeLoad==FALSE){return FALSE;}�Ŏg�p)
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="volume">����(0~255)</param>
/// <param name="se_type">���y�̎��(��BGM�Ȃ�BGM)</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns>�ǂݍ��߂���TRUE</returns>
BOOL ClAudio::SeLoad(
	string path, int volume, SE_TYPE se_type,
	string cpp_name,string ins_name) {
	//���y�ǂݍ���
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	//�K�v�ȕϐ�����
	m_play_type = DX_PLAYTYPE_BACK;	//�Đ�����
	m_se_type = se_type;			//���y�̎��
	m_product_volume = volume;		//���ʂ̕ύX
	MmLoadVolume(volume);			//���ʂ̓ǂݍ���
	
	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// ���y�ǂݍ��݋��ʊ֐�
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ_����</param>
/// <param name="cpp_name">cpp��_����</param>
/// <param name="ins_name">�C���X�^���X��_����</param>
/// <returns>�ǂݍ��߂���TRUE</returns>
BOOL ClAudio::MmLoad(string path, string cpp_name, string ins_name) {
	//���y�ǂݍ���
	string all_path = ClCom().GetAudiosPath() + path;
	m_handle = LoadSoundMem(all_path.c_str());	//���y�̓ǂݍ���
	m_path = all_path;							//�p�X���R�s�[

	//�ǂݍ��ݎ��s
	if (m_handle == ClCom().GetHandleError()) {
		//�G���[���b�Z�[�W
		string error_meg
			= cpp_name + ".cpp : " + ins_name + " : " + "���y�ǂݍ��݃G���[";

		MessageBox(
			GetMainWindowHandle(), all_path.c_str(),
			error_meg.c_str(), MB_OK
		);
		return FALSE;
	}

	//���ݎg�p���Ă��鉹�y��o�^
	ClAudioMult::GetIns()->VectorAudioEmplace(this);

	return TRUE;
}

/// <summary>
/// ���ʂ̓ǂݍ���(��m_se_type�̑���K�{)
/// </summary>
/// <param name="volume">Load�֐��̈���volume</param>
VOID ClAudio::MmLoadVolume(int volume) {
	if (volume > ClCom().GetUnCharMax()) { volume = ClCom().GetUnCharMax(); }
	if (volume < ClCom().GetUnCharMin()) { volume = ClCom().GetUnCharMin(); }
	m_product_volume = volume;

	//���ʂ𒲐�
	switch (m_se_type)
	{
	case n_audio::BGM:
		ChangeVolumeSoundMem(
			static_cast<int>(m_product_volume * ClAudioMult::GetIns()->GetBgmDecimalPar())
			, m_handle);
		break;
	case n_audio::SYSTEM:
		ChangeVolumeSoundMem(
			static_cast<int>(m_product_volume * ClAudioMult::GetIns()->GetSeSystemDecimalPar())
			, m_handle);
		break;
	case n_audio::PLAY:
		ChangeVolumeSoundMem(
			static_cast<int>(m_product_volume * ClAudioMult::GetIns()->GetSePlayDecimalPar())
			, m_handle);
		break;
	default:
		break;
	}
}

VOID ClAudio::Sound() {
	//�Đ�����Ă��Ȃ��Ȃ�Đ�
	if (CheckSoundMem(m_handle) == FALSE) {
		PlaySoundMem(m_handle, m_play_type);
	}
}

/// <summary>
/// ���y�̃���������
/// </summary>
/// <param name="is_vector_erase">TRUE�Ȃ烍�[�h�L�^������</param>
VOID ClAudio::Delete(BOOL is_vector_erase) {
	//�n���h������
	DeleteSoundMem(m_handle); 
	//���[�h�L�^������
	if (is_vector_erase == TRUE) { ClAudioMult::GetIns()->VectorAudioFindErase(this); }
}

