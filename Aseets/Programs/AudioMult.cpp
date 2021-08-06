//*--------------------------------------------------------------------------------*
//								Audio�̉��ʂ��Ǘ�
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include AUDIO_MULT_HPP
using namespace n_audio_mult;

//*--------------------------------------------------------------------------------*
//								�V���O���g������
//*--------------------------------------------------------------------------------*

ClAudioMult* ClAudioMult::m_ins = nullptr;		//�V���O���g���ȃC���X�^���X

//�C���X�^���X�擾
ClAudioMult* ClAudioMult::GetIns() {

	//���߂Ď擾���鎞�A���̃I�u�W�F�N�g�𐶐�
	if (m_ins == nullptr)
	{
		//�������̊m��
		m_ins = new ClAudioMult();
	}

	return m_ins;
}

//�R���X�g���N�^
ClAudioMult::ClAudioMult() { 

	m_is_audio_mute = FALSE;	//���y���������
	//�{�����[�������l��ݒ�
	m_bgm_volume = ClCom().GetUnCharHalf();
	m_se_system_volume = ClCom().GetUnCharHalf();
	m_se_play_volume = ClCom().GetUnCharHalf();
	m_fade = n_fade::ClFade();

	return;
}

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
ClAudioMult::ClAudioMult(const ClAudioMult& src) {

	//�A�h���X���R�s�[���Ă���
	m_ins = src.m_ins;
}

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
/// <returns>���̃C���X�^���X�̃A�h���X</returns>
ClAudioMult& ClAudioMult::operator=(const ClAudioMult& src) {

	//�A�h���X���R�s�[���Ă���
	m_ins = src.m_ins;
	return *this;
}

//�f�X�g���N�^
ClAudioMult::~ClAudioMult() { return; }

//*------------------------------------------------*
//		�C���X�^���X�̔j��
//*------------------------------------------------*

//�C���X�^���X�̔j��
VOID ClAudioMult::Destroy() {

	delete m_ins;
	m_ins = nullptr;
}

//*--------------------------------------------------------------------------------*
//								�v���p�e�B
//*--------------------------------------------------------------------------------*

//�ǂݍ��񂾉��y�̐�
int ClAudioMult::GetVecSize() { return m_load_audio.size(); }

//*------------------------------------------------*
//		����(0.0�`1.0)
//*------------------------------------------------*

//bgm���ʂ̊���(0.0�`1.0)��Ԃ�
float ClAudioMult::GetBgmDecimalPar() { return MmGetAudioParcent(m_bgm_volume); }

//se��system���ʂ̏���������Ԃ�
float ClAudioMult::GetSeSystemDecimalPar() { return MmGetAudioParcent(m_se_system_volume); }

//se��play	���ʂ̏���������Ԃ�
float ClAudioMult::GetSePlayDecimalPar() { return MmGetAudioParcent(m_se_play_volume); }

//*------------------------------------------------*
//		����(0%�`100%)
//*------------------------------------------------*

//bgm���ʂ̊���(0%�`100%)��Ԃ�
int ClAudioMult::GetBgmIntPar() { return static_cast<int>(MmGetAudioParcent(m_bgm_volume) * 100); }

//se��system���ʂ̊���(0%�`100%)��Ԃ�
int ClAudioMult::GetSeSystemIntPar() { return static_cast<int>(MmGetAudioParcent(m_se_system_volume) * 100); }

//se��play	���ʂ̊���(0%�`100%)��Ԃ�
int ClAudioMult::GetSePlayIntPar() { return static_cast<int>(MmGetAudioParcent(m_se_play_volume) * 100); }

//*------------------------------------------------*
//		���ʊ֐�
//*------------------------------------------------*

/// <summary>
/// ���ʂ̊���(0.0�`1.0)��Ԃ�
/// </summary>
/// <param name="m_volume">���ʂ̎��</param>
/// <returns>���ʂ̊���(0.0�`1.0)</returns>
float ClAudioMult::MmGetAudioParcent(int m_volume) {
	float bgm_float = static_cast<float>(m_volume);
	float max_float = static_cast<float>(ClCom().GetUnCharMax());
	return  bgm_float / max_float;
}

//*--------------------------------------------------------------------------------*
//								�֐�
//*--------------------------------------------------------------------------------*

/// <summary>
/// ���[�h�������y���L�^
/// </summary>
/// <param name="audio">�L������ClAudio�|�C���^</param>
VOID ClAudioMult::VectorAudioEmplace(n_audio::ClAudio* audio) {
	m_load_audio.emplace_back(audio);
}

/// <summary>
/// �L���������y�̒�����1�̎w�肵�����y��T���ď���
/// </summary>
/// <param name="audio">���[�h�L�^���������y</param>
VOID ClAudioMult::VectorAudioFindErase(n_audio::ClAudio* audio) {
	auto itr = m_load_audio.begin();
	while (itr != m_load_audio.end()) {
		//�w�肵�����y��{������vector�������
		if (((*itr) == audio)) {
			itr = m_load_audio.erase(itr);
			return;
		}
		else { itr++; }
	}
}	

//�L���������y��S�폜(https://blog.dalt.me/666)
VOID ClAudioMult::VectorAudioAllErase() {
	auto itr = m_load_audio.begin();
	while (itr != m_load_audio.end()) { itr = m_load_audio.erase(itr); }
}

//
VOID ClAudioMult::VecSizeDraw() {
	DrawFormatString(0, 0, ClCom().GetFlipColor(), "%d", m_load_audio.size());
}

//*------------------------------------------------*
//		64�i�K�F�}�E�X�n���A�A�ˌn��
//*------------------------------------------------*

const int POWER_NUM_04_INDEX = 2;	//64�i�K�F�}�E�X�n��

/// <summary>
/// BGM�̉��ʂ�ύX(64�i�K)
/// </summary>
/// <param name="plas_volume">���ʕύX��(TRUE�ő傫���AFALSE�ŏ�����)</param>
VOID ClAudioMult::BgmVolumeChange64Step(BOOL is_up) {
	//�~���[�g��Ԃ̂Ƃ��͉��ʂ�ύX���Ȃ�(0�̂܂�)
	if (MmIsVolumeChange(POWER_NUM_04_INDEX, is_up, &m_bgm_volume) == FALSE) { return; }

	//���ʂ̕ύX
	MmVolumeChange(n_audio::SE_TYPE::BGM, GetBgmDecimalPar());
}

/// <summary>
/// Se��System���ʂ�ύX(64�i�K)
/// </summary>
/// <param name="is_up">���ʕύX��(TRUE�ő傫���AFALSE�ŏ�����)</param>
VOID ClAudioMult::SeSystemVolumeChange64Step(BOOL is_up) {
	//�~���[�g��Ԃ̂Ƃ��͉��ʂ�ύX���Ȃ�(0�̂܂�)
	if (MmIsVolumeChange(POWER_NUM_04_INDEX, is_up, &m_se_system_volume) == FALSE) { return; }

	//���ʂ̕ύX
	MmVolumeChange(n_audio::SE_TYPE::SYSTEM, GetSeSystemDecimalPar());
}	

/// <summary>
/// Se��Play���ʂ�ύX(64�i�K)
/// </summary>
/// <param name="is_up">���ʕύX��(TRUE�ő傫���AFALSE�ŏ�����)</param>
VOID ClAudioMult::SePlayVolumeChange64Step(BOOL is_up) {
	//�~���[�g��Ԃ̂Ƃ��͉��ʂ�ύX���Ȃ�(0�̂܂�)
	if (MmIsVolumeChange(POWER_NUM_04_INDEX, is_up, &m_se_play_volume) == FALSE) { return; }

	//���ʂ̕ύX
	MmVolumeChange(n_audio::SE_TYPE::PLAY, GetSePlayDecimalPar());
}

//*------------------------------------------------*
//		16�i�K�F�L�[�{�[�h�n��
//*------------------------------------------------*

const int POWER_NUM_16_INDEX = 4;	//16�i�K�F�L�[�{�[�h�n��

/// <summary>
/// BGM�̉��ʂ�ύX(16�i�K)
/// </summary>
/// <param name="is_up">���ʕύX��(TRUE�ő傫���AFALSE�ŏ�����)</param>
VOID ClAudioMult::BgmVolumeChange16Step(BOOL is_up) {
	//�~���[�g��Ԃ̂Ƃ��͉��ʂ�ύX���Ȃ�(0�̂܂�)
	if (MmIsVolumeChange(POWER_NUM_16_INDEX, is_up, &m_bgm_volume) == FALSE) { return; }

	//���ʂ̕ύX
	MmVolumeChange(n_audio::SE_TYPE::BGM, GetBgmDecimalPar());
}

/// <summary>
/// Se��System���ʂ�ύX(16�i�K)
/// </summary>
/// <param name="is_up">���ʕύX��(TRUE�ő傫���AFALSE�ŏ�����)</param>
VOID ClAudioMult::SeSystemVolumeChange16Step(BOOL is_up) {
	//�~���[�g��Ԃ̂Ƃ��͉��ʂ�ύX���Ȃ�(0�̂܂�)
	if (MmIsVolumeChange(POWER_NUM_16_INDEX, is_up, &m_se_system_volume) == FALSE) { return; }

	//���ʂ̕ύX
	MmVolumeChange(n_audio::SE_TYPE::SYSTEM, GetSeSystemDecimalPar());
}	

/// <summary>
/// Se��Play���ʂ�ύX(16�i�K)
/// </summary>
/// <param name="is_up">���ʕύX��(TRUE�ő傫���AFALSE�ŏ�����)</param>
VOID ClAudioMult::SePlayVolumeChange16Step(BOOL is_up) {
	//�~���[�g��Ԃ̂Ƃ��͉��ʂ�ύX���Ȃ�(0�̂܂�)
	if (MmIsVolumeChange(POWER_NUM_16_INDEX, is_up, &m_se_play_volume) == FALSE) { return; }

	//���ʂ̕ύX
	MmVolumeChange(n_audio::SE_TYPE::PLAY, GetSePlayDecimalPar());
}

//*------------------------------------------------*
//		���ʊ֐�
//*------------------------------------------------*

const int ZERO = 0;		//0��菬������Ŏg�p
const int EVEN_FIX = 1;	//���ʂ�255(��̍ő�l)�̂Ƃ������ɐ�����

/// <summary>
/// ���̌㉹�ʂ̕ύX���s����
/// </summary>
/// <param name="POWER_NUM_">�ύX����ʂ�index</param>
/// <param name="is_up">�グ�邩�����邩�̈���</param>
/// <param name="m_change_volume">�ǂ̉��ʂ�ύX���邩</param>
/// <returns>���̌㉹�ʂ̕ύX���s���Ȃ�TRUE</returns>
BOOL ClAudioMult::MmIsVolumeChange(int POWER_NUM_, BOOL is_up, int* m_change_volume) {
	//�ύX���鉹�ʂ̗ʂ��v�Z
	int volume = ClCom().GetPowerNumPlas(POWER_NUM_);
	int plas_volume = (is_up == TRUE) ? volume : -volume;

	//���ʂ̕ύX
	if (*m_change_volume == ClCom().GetUnCharMax() && plas_volume < ZERO) {
		//���ʍő�l�̎��ŉ��ʂ�������ꍇ�̂Ƃ��͉��������ʂ������ɂȂ�悤�ɒ���
		*m_change_volume += plas_volume + EVEN_FIX;
	}
	else {
		*m_change_volume += plas_volume;
		//0�����A255����ɂȂ�Ȃ��悤�ɒ���
		if (*m_change_volume > ClCom().GetUnCharMax()) { *m_change_volume = ClCom().GetUnCharMax(); }
		if (*m_change_volume < ClCom().GetUnCharMin()) { *m_change_volume = ClCom().GetUnCharMin(); }
	}

	//�~���[�g��Ԃ̂Ƃ��͉��ʂ�ύX���Ȃ�(0�̂܂�)
	if (m_is_audio_mute == TRUE) { return FALSE; }

	//���ʂ̕ύX���s��
	return TRUE;
}

/// <summary>
/// ���ʂ̕ύX
/// </summary>
/// <param name="se_type">���ʂ̎��</param>
/// <param name="decimal_par">se_type�ɂ���Ă̌W��</param>
VOID ClAudioMult::MmVolumeChange(n_audio::SE_TYPE se_type, float decimal_par) {
	//se_type�̓ǂݍ��񂾉��ʂ�{��
	for (unsigned int i = 0; i < m_load_audio.size(); i++) {
		if (m_load_audio[i]->GetSeType() == se_type) {
			//���ʂ�ύX
			ChangeVolumeSoundMem(
				static_cast<int>(m_load_audio[i]->GetProductVolume() * decimal_par)
				, m_load_audio[i]->GetAudioHandle());
		}
	}
}

//*------------------------------------------------*
//		���y�S�̂��~���[�g
//*------------------------------------------------*

/// <summary>
/// ���y�S�̂��~���[�g�ɂ���
/// </summary>
VOID ClAudioMult::VecMute() {
	//�~���[�g��Ԃ̂Ƃ��̓~���[�g����
	if (m_is_audio_mute == TRUE) {
		for (unsigned int i = 0; i < m_load_audio.size(); i++) {
			//���y�̎�ނɂ���ĉ��ʂ̊������v�Z
			float decimal_par = MmGetDecimalPar(m_load_audio[i]->GetSeType());

			//���ʂ̕ύX
			ChangeVolumeSoundMem(
				static_cast<int>(m_load_audio[i]->GetProductVolume() * decimal_par)
				, m_load_audio[i]->GetAudioHandle());
		}
		//�~���[�g��Ԃł͂Ȃ��t���O
		m_is_audio_mute = FALSE;

	}	//�~���[�g��Ԃł͂Ȃ��Ƃ��͉��ʂ��[����
	else {
		for (unsigned int i = 0; i < m_load_audio.size(); i++) {
			ChangeVolumeSoundMem(0/*�������*/, m_load_audio[i]->GetAudioHandle());
		}
		//�~���[�g��ԃt���O
		m_is_audio_mute = TRUE;
	}
}

/// <summary>
/// SeType�ɂ���ĉ��ʂ̊�����Ԃ�(0.0f�`1.0f)
/// </summary>
/// <param name="se_type">���y�̎��</param>
/// <returns>SeType�ɂ���ĉ��ʂ̊���(0.0f�`1.0f)</returns>
float ClAudioMult::MmGetDecimalPar(n_audio::SE_TYPE se_type) {
	switch (se_type){
		//BGM
	case n_audio::SE_TYPE::BGM:
		return GetBgmDecimalPar();
		break;

		//�V�X�e����
	case n_audio::SE_TYPE::SYSTEM:
		return GetSeSystemDecimalPar();
		break;

		//�v���C���y
	case n_audio::SE_TYPE::PLAY:
		return GetSePlayDecimalPar();
		break;

	default:break;
	}
	return 0.0f;	//���ʂ��}�ɂł����Ȃ�Ȃ��悤��
}

//*------------------------------------------------*
//		���ʃt�F�[�h
//*------------------------------------------------*

/// <summary>
/// ���ʃt�F�[�h�A�b�v�J�n����(���y�̃���������������A���y�̍Đ���؂����肷�鏈���͕ʓr)
/// </summary>
/// <param name="all_time">�t�F�[�h�ɂ����鎞��</param>
VOID ClAudioMult::SetFadeUpStart(float all_time) {
	//�~���[�g�̂Ƃ��͍s��Ȃ�(�����ۂɂ͕K�v�Ȃ����y������)
	if (m_is_audio_mute == TRUE) { return; }

	//�J�n����
	m_fade.FadeUpStart(all_time);
}

/// <summary>
/// ���ʃt�F�[�h�_�E���J�n����(���y�̃���������������A���y�̍Đ���؂����肷�鏈���͕ʓr)
/// </summary>
/// <param name="all_time">�t�F�[�h�ɂ����鎞��</param>
VOID ClAudioMult::SetFadeDownStart(float all_time) {
	//�~���[�g�̂Ƃ��͍s��Ȃ�(�����ۂɂ͕K�v�Ȃ����y������)
	if (m_is_audio_mute == TRUE) { return; }

	//�J�n����
	m_fade.FadeDownStart(all_time);
}

/// <summary>
/// ���ʃt�F�[�h�_�E���A�b�v�J�n����(���y�̃���������������A���y�̍Đ���؂����肷�鏈���͕ʓr)
/// </summary>
/// <param name="all_time">�t�F�[�h�ɂ����鎞��</param>
VOID ClAudioMult::SetFadeDownUpStart(float all_time) {
	//�~���[�g�̂Ƃ��͍s��Ȃ�(�����ۂɂ͕K�v�Ȃ����y������)
	if (m_is_audio_mute == TRUE) { return; }

	//�J�n����
	m_fade.FadeDownUpStart(all_time);
}

//�t�F�[�h���I�������Ƃ��ɉ��؂ꂪ�N���Ȃ��悤�ɂ���
const float FADE_MIN_MULT = 0.0f;	
const float FADE_MAX_MULT = 1.0f;	

//���ʃt�F�[�h����(���y�̃���������������A���y�̍Đ���؂����肷�鏈���͕ʓr)
VOID ClAudioMult::FadeProc() {
	//�~���[�g�̂Ƃ��͍s��Ȃ�(�����ۂɂ͕K�v�Ȃ����y������)
	if (m_is_audio_mute == TRUE) { return; }
	//�t�F�[�h���s���Ă��Ȃ��Ȃ珈�����s��Ȃ�
	if (m_fade.GetIsFadeNone() == TRUE) { return; }

	//�t�F�[�h�J�E���^����
	m_fade.FadeProc();

	//���ʂ��t�F�[�h
	for (unsigned int i = 0; i < m_load_audio.size(); i++) {
		//���y�̎�ނɂ���ĉ��ʂ̊������v�Z
		float decimal_par = MmGetDecimalPar(m_load_audio[i]->GetSeType());

		//���ʂ�ύX
		if (m_fade.GetIsFadeStop() == FALSE) {
			ChangeVolumeSoundMem(
				static_cast<int>(m_load_audio[i]->GetProductVolume() * decimal_par * m_fade.GetFadeDecimalPar()),
				m_load_audio[i]->GetAudioHandle());
		}
		else {	
			//�I�������ʒ���
			switch (m_fade.GetFadeType()){
				//���ʊ�����1.0f��
			case n_fade::FADE_TYPE::FADE_DOWN_UP_TYPE:
			case n_fade::FADE_TYPE::FADE_UP_TYPE:
				ChangeVolumeSoundMem(
					static_cast<int>(m_load_audio[i]->GetProductVolume() * decimal_par * FADE_MAX_MULT),
					m_load_audio[i]->GetAudioHandle());
				break;

				//���ʊ�����0.0f��
			case n_fade::FADE_TYPE::FADE_UP_DOWN_TYPE:
			case n_fade::FADE_TYPE::FADE_DOWN_TYPE:
				ChangeVolumeSoundMem(
					static_cast<int>(m_load_audio[i]->GetProductVolume() * decimal_par * FADE_MIN_MULT),
					m_load_audio[i]->GetAudioHandle());
				break;
			default:break;
			}
			
		}
	}
}