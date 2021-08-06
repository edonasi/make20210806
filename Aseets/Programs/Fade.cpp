//*--------------------------------------------------------------------------------*
//								�t�F�[�h�_�E���t�F�[�h�A�b�v�̃C�����X�^���X
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include FADE_HPP
using namespace n_fade;

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^�A�f�X�g���N�^�A�ϐ��̏�����
//*--------------------------------------------------------------------------------*

ClFade::ClFade() {
	m_is_start = FALSE;
	m_next_in = FALSE;
	m_fade_state = FADE_STATE::NONE;
	m_fade_type = FADE_TYPE::FADE_UP_TYPE;
	m_cnt = n_cnt::ClCntArySec();
}
ClFade::~ClFade() { return; }

//*--------------------------------------------------------------------------------*
//								�v���p�e�B
//*--------------------------------------------------------------------------------*

//�t�F�[�h�̎��
FADE_TYPE ClFade::GetFadeType() { return m_fade_type; }	

//�t�F�[�h���s���Ă��Ȃ���
BOOL ClFade::GetIsFadeNone() { return (m_fade_state == n_fade::FADE_STATE::NONE) ? TRUE : FALSE; }

//�t�F�[�h���I��������
BOOL ClFade::GetIsFadeStop() { return m_cnt.GetIsStop(); }

const int NUM_256_INDEX = 8;	//256�̗ݏ搔

//�t�F�[�h�̊���(0.0f�`1.0f)
float ClFade::GetFadeDecimalPar() {
	//���݂̃J�E���g
	float index_float;
	switch (m_fade_state){
	case n_fade::FADE_DOWN:
		index_float = static_cast<float>(m_cnt.GetReverseIndex());
		break;
	default:
		index_float = static_cast<float>(m_cnt.GetIndex());
		break;
	}
	//�S�̂̃J�E���g
	float index_all_float = static_cast<float>(ClCom().GetPowerNumPlas(NUM_256_INDEX));
	return index_float / index_all_float;
}

//*--------------------------------------------------------------------------------*
//								�֐�
//*--------------------------------------------------------------------------------*

const float DIV_HALF = 2.0f;	//�t�F�[�h(�A�b�v/�_�E��)�̓J�E���g��2��J��Ԃ�����

/// <summary>
/// �t�F�[�h�A�b�v�_�E���J�n����
/// </summary>
/// <param name="all_time">�t�F�[�h�A�b�v�_�E������������܂łɂ����鎞��(�b)</param>
VOID ClFade::FadeUpDownStart(float all_time) {
	if (m_is_start == TRUE) { return; }	//�t�F�[�h���J�n���Ă���Ȃ珈�������Ȃ�

	m_cnt.SetCnt(ClCom().GetPowerNumPlas(NUM_256_INDEX), all_time / DIV_HALF, n_cnt::CNT_AFTER_TYPE::STOP);
	m_fade_state = FADE_STATE::FADE_UP;
	m_fade_type = FADE_TYPE::FADE_UP_DOWN_TYPE;
	m_next_in = TRUE;
	m_is_start = TRUE;		//�J�n
}

/// <summary>
/// �t�F�[�h�_�E���A�b�v�J�n����
/// </summary>
/// <param name="all_time">�t�F�[�h�_�E���A�b�v����������܂łɂ����鎞��(�b)</param>
VOID ClFade::FadeDownUpStart(float all_time) {
	if (m_is_start == TRUE) { return; }	//�t�F�[�h���J�n���Ă���Ȃ珈�������Ȃ�

	m_cnt.SetCnt(ClCom().GetPowerNumPlas(NUM_256_INDEX), all_time / DIV_HALF, n_cnt::CNT_AFTER_TYPE::STOP);
	m_fade_state = FADE_STATE::FADE_DOWN;
	m_fade_type = FADE_TYPE::FADE_DOWN_UP_TYPE;
	m_next_in = TRUE;
	m_is_start = TRUE;		//�J�n
}

/// <summary>
/// �t�F�[�h�A�b�v�J�n����
/// </summary>
/// <param name="all_time">�t�F�[�h�A�b�v����������܂łɂ����鎞��(�b)</param>
VOID ClFade::FadeUpStart(float all_time) {
	if (m_is_start == TRUE) { return; }	//�t�F�[�h���J�n���Ă���Ȃ珈�������Ȃ�

	m_cnt.SetCnt(ClCom().GetPowerNumPlas(NUM_256_INDEX), all_time, n_cnt::CNT_AFTER_TYPE::STOP);
	m_fade_state = FADE_STATE::FADE_UP;
	m_fade_type = FADE_TYPE::FADE_UP_TYPE;
	m_next_in = FALSE;
	m_is_start = TRUE;		//�J�n
}

/// <summary>
/// �t�F�[�h�_�E���J�n����
/// </summary>
/// <param name="all_time">�t�F�[�h�_�E������������܂łɂ����鎞��(�b)</param>
VOID ClFade::FadeDownStart(float all_time) {
	if (m_is_start == TRUE) { return; }	//�t�F�[�h���J�n���Ă���Ȃ珈�������Ȃ�

	m_cnt.SetCnt(ClCom().GetPowerNumPlas(NUM_256_INDEX), all_time, n_cnt::CNT_AFTER_TYPE::STOP);
	m_fade_state = FADE_STATE::FADE_DOWN;
	m_fade_type = FADE_TYPE::FADE_DOWN_TYPE;
	m_next_in = FALSE;
	m_is_start = TRUE;		//�J�n
}

//�J�E���^�X�V
VOID ClFade::FadeProc(){
	//�J�n���Ă��Ȃ��Ȃ珈�����Ȃ�
	if (m_is_start == FALSE) { return; }
		
	//�J�E���^�̍X�V
	m_cnt.Proc();

	//�J�E���^���ő�ɂȂ����Ƃ�
	if (m_cnt.GetIsOver() == FALSE) { return; }
	switch (m_fade_state){
	case n_fade::FADE_UP:
		//�t�F�[�h�_�E���Ɉڍs
		if (m_next_in == TRUE) {
			m_next_in = FALSE;
			m_fade_state = n_fade::FADE_STATE::FADE_DOWN;
			m_cnt.SetCnt();
		}
		else {	//�I������
			m_cnt.SetIsStop();
			m_fade_state = n_fade::FADE_STATE::NONE;
			m_is_start = FALSE;
		}
		break;

		//�t�F�[�h�_�E���̂Ƃ��͏I��
	case n_fade::FADE_DOWN:
		//�t�F�[�h�A�b�v�Ɉڍs
		if (m_next_in == TRUE) {
			m_next_in = FALSE;
			m_fade_state = n_fade::FADE_STATE::FADE_UP;
			m_cnt.SetCnt();
		}
		else {	//�I������
			m_cnt.SetIsStop();
			m_fade_state = n_fade::FADE_STATE::NONE;
			m_is_start = FALSE;
		}
		break;

	default:break;
	}
}

//���F�t�F�[�h�`�揈��
VOID ClFade::FadeSameDraw() { MmFadeDraw(ClCom().GetSameColor()); }

//���F�t�F�[�h�`�揈��
VOID ClFade::FadeBlackDraw() { MmFadeDraw(ClCom().GetBlack()); }

//���F�t�F�[�h�`�揈��
VOID ClFade::FadeWhiteDraw() { MmFadeDraw(ClCom().GetWhite()); }

/// <summary>
/// �t�F�[�h�`�拤�ʏ���
/// </summary>
/// <param name="color">�t�F�[�h����F</param>
VOID ClFade::MmFadeDraw(unsigned int color) {
	//�J�n���Ă��Ȃ��Ȃ珈�����Ȃ�
	if (m_is_start == FALSE) { return; }

	//�u�����h���[�h�ݒ�
	switch (m_fade_state) {
	case n_fade::FADE_UP:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_cnt.GetIndex());
		break;
	case n_fade::FADE_DOWN:
		SetDrawBlendMode(
			DX_BLENDMODE_ALPHA, m_cnt.GetReverseIndex()
		);
		break;
	default:return; break;
	}

	//��ʑS�̂ɍ���ʂ�`��
	DrawBox(
		ClWin().GetWinPivot().x, ClWin().GetWinPivot().y,
		ClWin().GetWinWidth(), ClWin().GetWinHeight(),
		color, TRUE
	);
	//�u�����h���[�h����
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
