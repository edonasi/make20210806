//*--------------------------------------------------------------------------------*
//								XY�֌W�Ǘ�
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include XY_HPP
using namespace n_xy;

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^�A�f�X�g���N�^�A�ϐ��̏�����
//*--------------------------------------------------------------------------------*

const int POS_MIN = 0;	//���W�̍ŏ��l

//xy(0,0)�ŏ�����
ClXY::ClXY() {
	x = POS_MIN;
	y = POS_MIN;
}
//�����ŏ�����
ClXY::ClXY(int x_in, int y_in) {
	x = x_in;
	y = y_in;
}
ClXY::~ClXY() { return; }

//*--------------------------------------------------------------------------------*
//								�v���p�e�B
//*--------------------------------------------------------------------------------*

//x��ݒ�
VOID ClXY::SetX(int x_in) { x = x_in; }		

//y��ݒ�
VOID ClXY::SetY(int y_in) { y = y_in; }

//xy��ݒ�
VOID ClXY::SetXY(int x_in, int y_in) {
	x = x_in;
	y = y_in;
}

//*--------------------------------------------------------------------------------*
//								�֐�
//*--------------------------------------------------------------------------------*

//����[(0, 0)���擾
ClXY ClXY::GetPivot() {
	ClXY xy = ClXY();
	return xy;
}

/// <summary>
/// �w�肵�������̍��W���擾
/// </summary>
/// <param name="pivot"></param>
/// <returns></returns>
ClXY ClXY::GetPivot(PIVOT pivot) {
	//����[�̍��W
	ClXY xy = ClXY();

	//X���W�̌v�Z
	switch (pivot){
		//����[�������珈���I��
	case n_xy::TOP_LEFT:return xy;break;

	case n_xy::TOP_CENTER:
	case n_xy::CENTER_CENTER:
	case n_xy::BUTTOM_CENTER:
		xy.x = x / 2;
		break;

	case n_xy::TOP_RIGHT:
	case n_xy::CENTER_RIGHT:
	case n_xy::BUTTOM_RIGHT:
		xy.x = x;
		break;

	default:break;
	}

	//Y���W�̌v�Z
	switch (pivot){
	case n_xy::CENTER_LEFT:
	case n_xy::CENTER_CENTER:
	case n_xy::CENTER_RIGHT:
		xy.y = y / 2;
		break;

	case n_xy::BUTTOM_LEFT:
	case n_xy::BUTTOM_CENTER:
	case n_xy::BUTTOM_RIGHT:
		xy.y = y;
		break;

	default:break;
	}

	return xy;
}



//X���W���擾
int ClXY::GetPivotX(ONE_PIVOT pivot_x) {
	switch (pivot_x){

	case n_xy::HALF:
		return x / 2;
		break;

	case n_xy::MAX:
		return x;
		break;

	default:
		return POS_MIN;
		break;
	}
}

//Y���W���擾
int ClXY::GetPivotY(ONE_PIVOT pivot_y) {
	switch (pivot_y){
	case n_xy::HALF:
		return y / 2;
		break;
	case n_xy::MAX:
		return y;
		break;
	default:
		return POS_MIN;
		break;
	}
}