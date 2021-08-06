//*--------------------------------------------------------------------------------*
//								FPS���Ǘ�����
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"

//*--------------------------------------------------------------------------------*
//								�V���O���g������
//*--------------------------------------------------------------------------------*

ClFps* ClFps::m_ins = nullptr;		//�V���O���g���ȃC���X�^���X

//�C���X�^���X�擾
ClFps* ClFps::GetIns() {

	//���߂Ď擾���鎞�A���̃I�u�W�F�N�g�𐶐�
	if (m_ins == nullptr)
	{
		//�������̊m��
		m_ins = new ClFps();
	}

	return m_ins;
}

//�R���X�g���N�^
ClFps::ClFps() {

	MmMemberVarInit();		//�����o�ϐ��̏�����

	return;
}

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
ClFps::ClFps(const ClFps& src) {

	//�A�h���X���R�s�[���Ă���
	m_ins = src.m_ins;
}

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
/// <returns>���̃C���X�^���X�̃A�h���X</returns>
ClFps& ClFps::operator=(const ClFps& src) {

	//�A�h���X���R�s�[���Ă���
	m_ins = src.m_ins;
	return *this;
}

//�f�X�g���N�^
ClFps::~ClFps() { return; }

//*--------------------------------------------------------------------------------*
//								�v���p�e�B��������
//*--------------------------------------------------------------------------------*

//�����o�ϐ��̏�������const�ϐ�
const int GAME_FPS_NORMAL = 60;		//FPS�W��
const int GAME_FPS_MAX = 240;		//FPS�ő�
const int GAME_FPS_MIN = 60;		//FPS�ŏ�
const float OVER_MIN = 1.0f;

//FPS�l(int)���擾
int ClFps::GetFpsIntValue() { return m_int_value; }

/// <summary>
/// speed��fps�ɍ��킹�Ē���
/// </summary>
/// <param name="speed">�Q�Ƃ���X�s�[�h</param>
/// <param name="over">�X�s�[�h�]��l</param>
/// <returns>fps�ɍ��킹���X�s�[�h</returns>
int ClFps::GetFpsIntFix(int speed, float* over) {
	if (speed == 0) { return 0; }		//speed��0�Ȃ珈�����I��

	//fps�ɍ��킹���X�s�[�h���v�Z
	float mult
		= static_cast<float>(GAME_FPS_NORMAL) / m_float_value;
	float speed_float = speed * mult;

	//�����_�ȉ����擾
	int speed_int = static_cast<int>(speed_float);	//int�l
	float over_float								//�����_�ȉ�
		= speed_float - static_cast<float>(static_cast<int>(speed_float));

	//�����_�ȉ������Z
	*over += over_float;

	//�����_�ȉ��̌덷�𒲐�
	int add = 0;
	//speed_float��0���傫�����ɂ���ĕ���
	if (speed_float > 0.0f) {
		if (*over >= OVER_MIN) {
			add = static_cast<int>(*over);
			//over��1.0f�����ɂ���
			*over = *over - static_cast<float>(add);
		}
	}
	else {
		if (*over <= OVER_MIN) {
			add = static_cast<int>(*over);
			//over��-1.0f����ɂ���
			*over = *over - static_cast<float>(add);
		}
	}

	return speed_int + add;
}

//FPS�l(float)���擾
float ClFps::GetFpsFloatValue() { return m_float_value; }

//deltaTime���Q��
float ClFps::GetDeltaTime() {
	//�l�����肦�Ȃ����炢�傫���Ƃ��C��
	if (m_delta_time < 1000.0f/*=���肦�Ȃ����炢�傫���Ƃ�*/) {
		return m_delta_time;
	}
	else {
		return 0.015f;	//���ϓI��delta_time�ɐݒ�
	}
}

//*--------------------------------------------------------------------------------*
//								�֐���������
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		�����o�ϐ��̏�����
//*------------------------------------------------*

//�����o�ϐ��̏�����
VOID ClFps::MmMemberVarInit() {

	//*------------------------------------------------*
	//		Fps�l�̊Ǘ�
	//*------------------------------------------------*
	m_is_init = FALSE;				//�ŏ��̑���J�n�t���O
	m_start_time = 0;				//�J�n�J�n����
	m_now_time = 0;					//���݂̎���
	m_old_time = 0;					//�ȑO�̎���
	m_int_value = GAME_FPS_NORMAL;	//FPS�̒l
	m_float_value = GAME_FPS_NORMAL;//�v�Z���ʂ�`��
	m_delta_time					//�o�ߎ���
		= static_cast<float>(0.000001);
	m_cnt = 1;					//���݂̃t���[����
	m_sample_rote = GAME_FPS_NORMAL;//���ς����T���v���l
}

//*------------------------------------------------*
//		�C���X�^���X�̔j��
//*------------------------------------------------*

//�C���X�^���X�̔j��
VOID ClFps::Destroy() {

	delete m_ins;
	m_ins = nullptr;
}

//*------------------------------------------------*
//		Fps�l�̊Ǘ�
//*------------------------------------------------*

//FPS�̊Ǘ���const�ϐ�
const float DIV_DELETA_TIME = 1000000.0f;		//deltaTime�����鐔(1000000.0f)

//Fps�l�𑪒肵�A�l���X�V����
VOID ClFps::FpsUpdate() {

	//��ԍŏ��̏���
	if (m_is_init == FALSE) {

		m_start_time						//����J�n�������}�C�N���b�P�ʂŎ擾
			= GetNowHiPerformanceCount();

		m_is_init = TRUE;					//�ŏ��̏����I��
	}

	m_now_time								//���݂̎������ʕb�P�ʂŎ擾
		= GetNowHiPerformanceCount();

	m_delta_time							//�O��擾�������Ԃ���̌o�ߎ��Ԃ�b��(����)�ɕϊ����Ă���Z�b�g
		= (m_now_time - m_old_time) / DIV_DELETA_TIME;

	m_old_time = m_now_time;				//����擾�������Ԃ�ۑ�

	//1�t���[���ځ`FPS�ݒ�l�܂ł̓J�E���g�A�b�v
	if (m_cnt < m_sample_rote) {

		m_cnt++;							//�J�E���^�𑝂₷
	}
	else {									//FPS�ݒ�l�t���[���ŕ���FPS���v�Z

		m_float_value						//���݂̎�������0�t���[���̎��Ԃ��Ђ�FPS�̐��l�Ŋ���
			= DIV_DELETA_TIME / ((m_now_time - m_start_time)
				/ static_cast<float>(m_sample_rote));

		m_start_time						//����J�n�������}�C�N���b�P�ʂŎ擾
			= GetNowHiPerformanceCount();

		m_cnt = 1;						//�J�E���^������
	}
}

//FPS�ŏ�����҂�
int ClFps::FpsWait() {

	LONGLONG resultTime					//���݂̎���-�ŏ��̎����ŁA���݂������Ă��鎞�����擾����
		= m_now_time - m_start_time;
	LONGLONG waitTime					//�҂ׂ��~���b��(1�b/FPS�l�����݂̃t���[����)����A���݂������Ă��鎞��������
		= static_cast<LONGLONG>(DIV_DELETA_TIME)
		/ static_cast<LONGLONG>(m_int_value * m_cnt - resultTime);
	//int millTime = 1000;				//�~���b�ɕϊ������銄�鐔

	waitTime /= ClCom().GetMilliMult();	//�}�C�N���b����~���b�ɕϊ�

	//����������������A������҂�
	if (waitTime > 0) {

		WaitTimer(static_cast<int>(waitTime));			//�����~���b�҂�(��WindowProc�Œ�~����̂œr���ŃC�x���g���N�����Ƃ����̏������s��)
	}

	//����������OFF�ɂ��Ă��邩
	if (GetWaitVSyncFlag() == FALSE) {

		//FPS���ő�l�ł͂Ȃ��Ƃ�
		if (m_int_value < GAME_FPS_MAX) {

			//1�b����FPS�l�����A�҂��Ԃ��������Ƃ��́A������FPS�l���グ�Ă��悢
			//�҂���10�~�� <= 1�b/60FPS=16.6666�~���@�������������ł���
			if (waitTime > 0
				&& waitTime <= ClCom().GetMilliMult() / m_int_value) {

				m_int_value++;
			}
			else {

				//FPS�l���ǂ����Ă��炸�A�x���Ƃ��́AFPS�l��������
				if (m_int_value > GAME_FPS_MIN) {

					m_int_value--;
				}
			}
		}
	}

	return 0;
}

//*------------------------------------------------*
//		Fps�l�̕`��
//*------------------------------------------------*

//Fps�l�̕`���const�ϐ�
const int FIX_HEIGHT = 16;		//FPS�l��������悤�ɍ�������

//�f�o�b�N�p�̕���FPS�l�����F�ŉ�ʍ����ɕ`�悷��
VOID ClFps::FpsDraw() {

	//�f�o�b�N���[�h�Ȃ�`�悷��
	if (ClWin().GetIsDebug() == TRUE) {

		//�������`��
		DrawFormatString(
			0, ClWin().GetWinHeight() - FIX_HEIGHT,
			ClCom().GetFlipColor(),
			"FPS : %.1f", m_float_value);
	}

	return;
}

//�ʒu�����L��Fps�l�̕`���const�ϐ�
const int DRAW_X_MAX = ClWin().GetWinWidth() - 96;
const int DRAW_Y_MAX = ClWin().GetWinHeight() - FIX_HEIGHT;

/// <summary>
/// �ʒu��ݒ肵�ăf�o�b�N�p�̍��F�ŕ���FPS�l��`�悷��
/// </summary>
/// <param name="draw_x">�`�悷��x�ʒu</param>
/// <param name="draw_y">�`�悷��y�ʒu</param>
/// <param name="is_black_color">TRUE�Ȃ獕�AFALSE�Ȃ甒</param>
VOID ClFps::FpsDraw(int draw_x, int draw_y) {

	//�f�o�b�N���[�h�Ȃ�`�悷��
	if (ClWin().GetIsDebug() == TRUE) {

		//��������ʊO�ɏo�Ă���Ȃ��ʓ��Ɏ��܂�悤�ɂ���
		draw_x = MmFpsDrawPosLimit(draw_x, DRAW_X_MAX);
		draw_y = MmFpsDrawPosLimit(draw_y, DRAW_Y_MAX);

		//�������`��
		DrawFormatString(draw_x, draw_y, ClCom().GetFlipColor(),
			"FPS : %.1f", m_float_value);
	}

	return;
}

//Fps�`��̈ʒu����
int ClFps::MmFpsDrawPosLimit(int num, int m_max) {	
	if (num < 0) { return 0; }			//�Ԃ��l���ŏ��l�ɐݒ�
	else if (num > m_max) { return m_max; }	//�Ԃ��l���ő�l�ɐݒ�
	return num;
}