//*--------------------------------------------------------------------------------*
//								��`
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include RECT_HPP
using namespace n_rect;
//		�l�[��
using namespace n_xy;

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^
//*--------------------------------------------------------------------------------*

//(0,0,0,0)�ŏ�����
ClRect::ClRect(){
	left = 0;
	top = 0;
	right = 0;
	bottom = 0;
}
ClRect::~ClRect() { return; }

//*--------------------------------------------------------------------------------*
//								�v���p�e�B
//*--------------------------------------------------------------------------------*

ClXY ClRect::GetPivot(PIVOT pivot) {
	ClXY xy = ClXY();

	switch (pivot){
	case n_xy::TOP_LEFT:
		xy.SetXY(left, top);
		break;
	case n_xy::TOP_CENTER:
		xy.SetXY((right - left) / 2, top);
		break;
	case n_xy::TOP_RIGHT:
		xy.SetXY(right, top);
		break;
	case n_xy::CENTER_LEFT:
		xy.SetXY(left, (bottom - top) / 2);
		break;
	case n_xy::CENTER_CENTER:
		xy.SetXY((right - left) / 2, (bottom - top) / 2);
		break;
	case n_xy::CENTER_RIGHT:
		xy.SetXY(right, (bottom - top) / 2);
		break;
	case n_xy::BUTTOM_LEFT:
		xy.SetXY(left, bottom);
		break;
	case n_xy::BUTTOM_CENTER:
		xy.SetXY((right - left) / 2, bottom);
		break;
	case n_xy::BUTTOM_RIGHT:
		xy.SetXY(right, bottom);
		break;
	default:
		break;
	}

	return xy;
}

/// <summary>
/// �ϐ����w�肵�ď�����
/// </summary>
/// <param name="left_in">���[</param>
/// <param name="top_in">��[</param>
/// <param name="right_in">�E�[</param>
/// <param name="bottom_in">���[</param>
VOID ClRect::SetRect(int left_in, int top_in, int right_in, int bottom_in) {
	left = left_in;
	top = top_in;
	right = right_in;
	bottom = bottom_in;
}