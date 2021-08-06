//*--------------------------------------------------------------------------------*
//								�J�E���^
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include CNT_HPP
using namespace n_cnt;

//*--------------------------------------------------------------------------------*
//								�S�̂Ŏg���萔
//*--------------------------------------------------------------------------------*

const int CNT_MIN = 0;			//�J�E���^�̏����ϐ�
const int CNT_ADD = 1;			//�J�E���^���Z�ϐ�
const float SEC_MIN = 0.0f;		//�^�C�}�[�̏����ϐ�

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^�A�f�X�g���N�^�A�ϐ��̏�����
//*--------------------------------------------------------------------------------*

ClCntArySec::ClCntArySec(){
	//���ׂď�����
	m_is_over = FALSE;
	m_is_stop = FALSE;
	m_after_type = n_cnt::CNT_AFTER_TYPE::STOP;
	m_index = CNT_MIN;
	m_index_max = CNT_MIN;
	m_timer_start = SEC_MIN;
	m_timer_sec_start = SEC_MIN;
	m_timer = SEC_MIN;
	m_sec_all = SEC_MIN;
	m_sec_max = SEC_MIN;
}

ClCntArySec::~ClCntArySec() { return; }

//*--------------------------------------------------------------------------------*
//								�v���p�e�B
//*--------------------------------------------------------------------------------*

const int INDEX_OVER_BLOCK = 1;	//�z�񂠂ӂ��h��

//�ő�l�܂ōs�������Ԃ�
BOOL ClCntArySec::GetIsOver() { return m_is_over; }	

//�J�E���^���X�g�b�v������
BOOL ClCntArySec::GetIsStop() { return m_is_stop; }

//���݂̃J�E���^(�z��v�f��)��Ԃ�
int ClCntArySec::GetIndex() { return m_index >= m_index_max == TRUE ? m_index_max - INDEX_OVER_BLOCK : m_index; }

//���݂̔��΂̃J�E���^(�z��v�f��)��Ԃ�
int ClCntArySec::GetReverseIndex() { return m_index_max - m_index - INDEX_OVER_BLOCK; }

//�^�C�}�[�J�n����̎���
float ClCntArySec::MmGetTimerSub() { return m_timer - m_timer_start; }

//���b���o�ߎ���
float ClCntArySec::MmGetTimerSecSub() { return m_timer - m_timer_sec_start; }

//�J�E���^���~������
VOID ClCntArySec::SetIsStop() {
	m_is_stop = TRUE;
	m_is_over = FALSE;
	m_index = CNT_MIN;
	m_timer_start = SEC_MIN;
	m_timer_sec_start = SEC_MIN;
	m_timer = SEC_MIN;
}

//�J�E���^�ƌ��݂̕b����������
VOID ClCntArySec::SetCnt() {
	//max�n�ȊO������
	m_is_over = FALSE;
	m_is_stop = FALSE;
	m_index = CNT_MIN;
	m_timer_start = SEC_MIN;
	m_timer_sec_start = SEC_MIN;
	m_timer = SEC_MIN;
}		

/// <summary>
/// �J�E���^��ݒ�A������
/// </summary>
/// <param name="cnt_size">�z��̗v�f��(��Fa[5]�Ȃ�SetCnt(5, , )�Ɠ���)</param>
/// <param name="all_sec">�J�E���g0�܂ł����鎞��(�b)</param>
/// <param name="after_type">�J�E���g0���B��̋���</param>
VOID ClCntArySec::SetCnt(int cnt_size, float all_sec, n_cnt::CNT_AFTER_TYPE after_type) {
	//���ׂď�����
	m_is_over = FALSE;
	m_is_stop = FALSE;
	m_after_type = after_type;
	m_index = CNT_MIN;
	m_index_max = cnt_size;
	m_timer_start = SEC_MIN;
	m_timer_sec_start = SEC_MIN;
	m_timer = SEC_MIN;
	m_sec_all = all_sec;
	m_sec_max = all_sec / static_cast<float>(cnt_size);
}

//*--------------------------------------------------------------------------------*
//								�֐�
//*--------------------------------------------------------------------------------*

//�J�E���^�̍X�V(���̊֐���1�����g��Ȃ�����)
VOID ClCntArySec::Proc() {
	//��~��̓J�E���g���X�g�b�v
	if (m_is_stop == TRUE) { m_is_over = FALSE; return; }

	//�J�E���^�ő�l�܂ōs�����t���O��������
	if (m_is_over == TRUE) { m_is_over = FALSE; }

	//�^�C�}�[�̉��Z
	m_timer += ClFps::GetIns()->GetDeltaTime();

	//�J�E���^�̍X�V
	if (MmGetTimerSecSub() >= m_sec_max && m_index < m_index_max) {
		m_index = static_cast<int>(
			static_cast<float>(m_index_max - INDEX_OVER_BLOCK) * (MmGetTimerSub() / m_sec_all)
			) + INDEX_OVER_BLOCK;
		m_timer_sec_start = m_timer;
	}

	//�J�E���^�ő�l�܂ōs����
	if (MmIsIndexOver() == TRUE) { m_is_over = TRUE; }

	//�J�E���^���ő�l�܂ōs������̏���
	if (m_is_over == FALSE) { return; }
	switch (m_after_type){
		//�J�E���^�ƊJ�n���Ԃ�������
	case n_cnt::LOOP:MmSetCnt(); break;

		//�������~������t���O�𗧂Ă�
	default:m_is_stop = TRUE; break;
	}
}


//�v�f�����ő吔�𒴂�����
BOOL ClCntArySec::MmIsIndexOver() { return m_index >= m_index_max ? TRUE : FALSE; }

const float TIMER_MAX = 1.70141183460469E+38f;	//timer��float�̍ő�l�𒴂��Ȃ��悤�ɂ���΍�

//�J�E���^�ƊJ�n���Ԃ�������
VOID ClCntArySec::MmSetCnt() {
	m_index = CNT_MIN;
	if (m_timer > TIMER_MAX) { m_timer = SEC_MIN; }
	m_timer_start = m_timer;
	m_timer_sec_start = m_timer;
}

