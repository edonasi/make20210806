//*--------------------------------------------------------------------------------*
//								���ʂ��Ďg���ϐ��⏈��������
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^��������
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		Com�N���X
//*------------------------------------------------*

ClCom::ClCom() { return; }
ClCom::~ClCom() { return; }

//*--------------------------------------------------------------------------------*
//								�v���p�e�B��������
//*--------------------------------------------------------------------------------*

//virtual�̊֐����O���ȂǂŎg�p���ꂽ�Ƃ��G���[���b�Z�[�W���o��
VOID ClCom::VirtualError() {
	//�G���[���b�Z�[�W
	string error_title = "virtual�g�p�֎~";
	string error_msg = "�O���g�p���֎~���邽�ߎg�p�ł��܂���";

	MessageBox(
		GetMainWindowHandle(), error_msg.c_str(),
		error_title.c_str(), MB_OK
	);
}

//*------------------------------------------------*
//		0�`255�̍ő�l�A���Ԓl�A�ŏ��l
//*------------------------------------------------*

//0�`255�̍ő�l(255)
int ClCom::GetUnCharMax() { return 255; }

//0�`255�̍ő�l(128)
int ClCom::GetUnCharHalf() { return 128; }

//0�`255�̍ő�l(0)
int ClCom::GetUnCharMin() { return 0; }

//*------------------------------------------------*
//		�ݏ�
//*------------------------------------------------*

/// <summary>
/// 2�̐��̗ݏ�𓾂�(���w�����}�C�i�X�̂Ƃ��� 1 �ɂȂ�)
/// </summary>
/// <param name="index">�w��</param>
/// <returns>2��(�w��)��</returns>
int ClCom::GetPowerNumPlas(int index) {
	int num = 1;
	if (index <= 0) { return num; }	//�w����0�Ȃ�1

	//2�̗ݏ���v�Z
	int radix2 = 2;	//2�̊
	for (int i = 0; i < index; i++) {
		num *= radix2;
	}
	return num;
}

/// <summary>
/// radix�̐��̗ݏ�𓾂�
/// </summary>
/// <param name="radix">�</param>
/// <param name="index">�w��</param>
/// <returns>radix�̗ݏ�</returns>
int ClCom::GetPowerNumPlas(int radix, int index) {
	int num = 1;
	if (index <= 0) { return num; }	//�w����0�Ȃ�1

	//�ݏ���v�Z
	for (int i = 0; i < index; i++) {
		num *= radix;
	}
	return num;
}

//*------------------------------------------------*
//		�b���~��
//*------------------------------------------------*

//1�b��1000�~���b
int ClCom::GetMilliMult() { return 1000; }

//*------------------------------------------------*
//		�F
//*------------------------------------------------*

//�F�̒����l
const int MIN_COLOR = 0;
const int HALF_COLOR = 128;
const int MAX_COLOR = 255;

//���F
unsigned int ClCom::GetBlack() {
	return GetColor(MIN_COLOR, MIN_COLOR, MIN_COLOR);
}

//�D�F
unsigned int ClCom::GetGray() {
	return GetColor(HALF_COLOR, HALF_COLOR, HALF_COLOR);
}

//���F
unsigned int ClCom::GetWhite() {
	return GetColor(MAX_COLOR, MAX_COLOR, MAX_COLOR);
}

//�w�i�F�Ɠ���
unsigned int ClCom::GetSameColor() {
	switch (ClWin().GetBackColorType()){
		//�w�i�F�����Ȃ獕�ɐݒ�
	case n_win::BACK_COLOR_TYPE::BLACK:
		return GetColor(MIN_COLOR, MIN_COLOR, MIN_COLOR);
		break;

		//�w�i�F�����Ȃ甒�ɐݒ�
	case n_win::BACK_COLOR_TYPE::WHITE:
		return GetColor(MAX_COLOR, MAX_COLOR, MAX_COLOR);
		break;

		//�f�t�H���g�͔�
	default:
		return GetColor(MAX_COLOR, MAX_COLOR, MAX_COLOR);
		break;
	}

	return GetColor(MAX_COLOR, MAX_COLOR, MAX_COLOR);
}

//�w�i�F�Ɣ��ΐF
unsigned int ClCom::GetFlipColor() {

	switch (ClWin().GetBackColorType()){
		//�w�i�F�����Ȃ甒�ɐݒ�
		case n_win::BACK_COLOR_TYPE::BLACK:
			return GetColor(MAX_COLOR, MAX_COLOR, MAX_COLOR);
			break;

		//�w�i�F�����Ȃ獕�ɐݒ�
		case n_win::BACK_COLOR_TYPE::WHITE:
			return GetColor(MIN_COLOR, MIN_COLOR, MIN_COLOR);
			break;

		//�f�t�H���g�͍�
		default:
			return GetColor(MIN_COLOR, MIN_COLOR, MIN_COLOR);
			break;
	}

	return GetColor(MIN_COLOR, MIN_COLOR, MIN_COLOR);
}

//�ԐF
unsigned int ClCom::GetRed() {
	return GetColor(MAX_COLOR, MIN_COLOR, MIN_COLOR);
}

//�ΐF
unsigned int ClCom::GetGreen() {
	return GetColor(MIN_COLOR, MAX_COLOR, MIN_COLOR);
}

//�F
unsigned int ClCom::GetBlue() {
	return GetColor(MIN_COLOR, MIN_COLOR, MAX_COLOR);
}

//���F
unsigned int ClCom::GetYellow() {
	return GetColor(MAX_COLOR, MAX_COLOR, MIN_COLOR);
}

//�V�A��
unsigned int ClCom::GetCyan() {
	return GetColor(MIN_COLOR, MAX_COLOR, MAX_COLOR);
}

//�}�[���_
unsigned int ClCom::GetMagenta() {
	return GetColor(MAX_COLOR, MIN_COLOR, MAX_COLOR);
}

//��F
unsigned int ClCom::GetOrange() {
	return GetColor(MAX_COLOR, HALF_COLOR, MIN_COLOR);
}

//����
unsigned int ClCom::GetYellowGreen() {
	return GetColor(HALF_COLOR, MAX_COLOR, MIN_COLOR);
}

//��
unsigned int ClCom::GetBlueGreen() {
	return GetColor(MIN_COLOR, MAX_COLOR, HALF_COLOR);
}

//��F
unsigned int ClCom::GetSkyColor() {
	return GetColor(MIN_COLOR, HALF_COLOR, MAX_COLOR);
}

//�Ԏ�
unsigned int ClCom::GetRedPurple() {
	return GetColor(MAX_COLOR, MIN_COLOR, HALF_COLOR);
}

//��
unsigned int ClCom::GetBluePurple() {
	return GetColor(HALF_COLOR, MIN_COLOR, MAX_COLOR);
}

//*------------------------------------------------*
//		�n���h���̃G���[�l
//*------------------------------------------------*

/// <summary>
/// �n���h���̃G���[�l(-1)
/// </summary>
/// <returns>-1</returns>
int ClCom::GetHandleError() { return -1; }

//*------------------------------------------------*
//		�t�@�C���p�X
//*------------------------------------------------*

//.\\Aseets/
string ClCom::GetAseetsPath() { return ".\\Aseets/"; }

//.\\Aseets/Audios/
string ClCom::GetAudiosPath() { return GetAseetsPath() + "Audios/"; }

//.\\Aseets/Images/
string ClCom::GetImagesPath() { return GetAseetsPath() + "Images/"; }

//.\\Aseets/Movies/
string ClCom::GetMoviesPath() { return GetAseetsPath() + "Movies/"; }

//*------------------------------------------------*
//		�f�t�H���g�̃t�H���g�T�C�Y
//*------------------------------------------------*

//�f�t�H���g�̃t�H���g�T�C�Y(16)
int ClCom::GetDefalutFontSize() { return 16; }
