//*--------------------------------------------------------------------------------*
//								Window�̏��������s��
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		�l�[��
using namespace n_xy;

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^��������
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		Window�̏����ݒ�const�ϐ�
//*------------------------------------------------*

//�Q�[���^�C�g��
const string GAME_TITLE = "�Q�[���^�C�g��";
//�Q�[���̏c�����A�𑜓x
const int GAME_HEIGHT = 720;
const int GAME_WIDTH = 1280;
const int GAME_COLOR = 32;
//�Q�[���̔w�i�F(red,green,blue)
const int GANE_WINDOW_RED = 0;
const int GANE_WINDOW_GREEN = 0;
const int GANE_WINDOW_BLUE = 0;
//�E�B���h�E�o�[�̏��
const unsigned char GANE_WINDOW_BAR = 0;
//�Q�[���̃A�C�R����ID
//const int GAME_ICON_ID = 333;
//�f�o�b�N���[�h
const BOOL IS_GAME_DEBUG = TRUE;

//*------------------------------------------------*

//*------------------------------------------------*
//		�R���X�g���N�^
//*------------------------------------------------*

ClWin::ClWin() {
	MmSetBackColorType();	//�w�i�F�̎�ނ�ݒ�
	m_size = ClXY(GAME_WIDTH, GAME_HEIGHT);
	return; 
}

//*------------------------------------------------*
//		�w�i�F�̎�ނ�ݒ�
//*------------------------------------------------*

const int BLACK_LIGHTNESS = 0;	//���F�̖��x
const int WHITE_LIGHTNESS = 255;//���F�̖��x

//�w�i�F�̎�ނ�ݒ�
VOID ClWin::MmSetBackColorType() {
	//�w�i�F�̎�ނ����ɐݒ�
	if (MmIsNoChroma(BLACK_LIGHTNESS) == TRUE) {
		M_BACK_COLOR_TYPE = BACK_COLOR_TYPE::BLACK; return;
	}
	//�w�i�F�̎�ނ𔒂ɐݒ�
	else if (MmIsNoChroma(WHITE_LIGHTNESS) == TRUE) {
		M_BACK_COLOR_TYPE = BACK_COLOR_TYPE::WHITE; return;
	}
	//�w�i�F�̎�ނ����̑��ɐݒ�
	else {
		M_BACK_COLOR_TYPE = BACK_COLOR_TYPE::OTHER; return;
	}
}

/// <summary>
/// �w�i�F���w�肵�����x�̖��ʐF���ǂ���
/// </summary>
/// <param name="lightness">���x</param>
/// <returns>TRUE�Ȃ�w�肵�����x�̖��ʐF</returns>
BOOL ClWin::MmIsNoChroma(int lightness) {
	if (GANE_WINDOW_RED != lightness) { return FALSE; }
	if (GANE_WINDOW_GREEN != lightness) { return FALSE; }
	if (GANE_WINDOW_BLUE != lightness) { return FALSE; }

	return TRUE;
}

//*------------------------------------------------*
//		�f�X�g���N�^
//*------------------------------------------------*

ClWin::~ClWin() { return; }

//*------------------------------------------------*
//		�v���p�e�B
//*------------------------------------------------*

//����[���擾
ClXY ClWin::GetWinPivot() { return m_size.GetPivot(); }

//�w�肵�������̍��W���擾
ClXY ClWin::GetWinPivot(n_xy::PIVOT pivot) { return m_size.GetPivot(pivot); }

//����X�T�C�Y�擾
int ClWin::GetWinPivotX(n_xy::ONE_PIVOT pivot_x) { return m_size.GetPivotX(pivot_x); }

//����Y�T�C�Y�擾
int ClWin::GetWinPivotY(n_xy::ONE_PIVOT pivot_y) { return m_size.GetPivotY(pivot_y); }

//�Q�[���̏c�����Q�Ƃ���
int ClWin::GetWinHeight() { return GAME_HEIGHT; }

//�Q�[���̉������Q�Ƃ���
int ClWin::GetWinWidth() { return GAME_WIDTH; }

//��ʂ̃T�C�Y���擾
ClXY ClWin::GetWinSize() { return m_size; }

//�Q�[���̉𑜓x���Q�Ƃ���
int ClWin::GetWinColor() { return GAME_COLOR; }

//�f�o�b�N���[�h��	�Q��
BOOL ClWin::GetIsDebug() { return IS_GAME_DEBUG; }

//�w�i�F�̎�ނ��Q��
BACK_COLOR_TYPE ClWin::GetBackColorType() { return M_BACK_COLOR_TYPE; }

//*--------------------------------------------------------------------------------*
//								�֐���������
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		DX���C�u�����̏�����
//*------------------------------------------------*

///<summary >
	/// Init�O�̃Q�[��������
	///</summary >
VOID ClWin::BeforeInit() {

	//Log.txt���o�͂��Ȃ�(GitHub�ŊǗ����邽�߁A���ݕK�v�Ȃ�)
	SetOutApplicationLogValidFlag(FALSE);
	//�E�B���h�E���[�h�ɐݒ�
	ChangeWindowMode(TRUE);
	//�Q�[���^�C�g���̐ݒ�
	SetMainWindowText(GAME_TITLE.c_str());
	//�Q�[���E�B���h�E�𑜓x�ݒ�
	SetGraphMode(GetWinWidth(), GetWinHeight(), GAME_COLOR);
	//�E�B���h�E�̃T�C�Y��ݒ�
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);
	//�w�i�F�̐ݒ�
	SetBackgroundColor(
		GANE_WINDOW_RED,
		GANE_WINDOW_GREEN,
		GANE_WINDOW_BLUE
	);
	//�Q�[����ICON��ݒ�
	//SetWindowIconID(GAME_ICON_ID);
	//�E�B���h�E�o�[�̏��
	SetWindowStyleMode(GANE_WINDOW_BAR);
	//�E�B���h�E�̐���������L���ɂ���(�f�B�X�v���C�̔\�͂𐧌����āA�t���[�����[�g(fps)�����ɕۂ�)=FALSE�̓t���[�����[�g���Ǘ����Ȃ���΂Ȃ�Ȃ�
	SetWaitVSyncFlag(TRUE);
	//��A�N�e�B�u�ł����s����
	SetAlwaysRunFlag(TRUE);
}

/// <summary>
/// �Q�[���̏�����
/// </summary>
/// <returns>�G���[���N������-1</returns>
int ClWin::Init() {

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		// �G���[���N�����璼���ɏI��
		return -1;
	}

	//�G���[�ł͂Ȃ��Ȃ�I�������Ȃ�
	return 0;
}

/// <summary>
/// Init��̃Q�[��������
/// </summary>
VOID ClWin::AfterInit() {

	//�_�u���o�b�t�@�����O�L����
	SetDrawScreen(DX_SCREEN_BACK);
}

