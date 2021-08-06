//*--------------------------------------------------------------------------------*
//								�_�����蔻��
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include COLL_POINT_HPP
using namespace n_coll_point;
//		�l�[��
using namespace n_xy;
using namespace n_rect;
using namespace n_circle;
//using namespace n_coll_rect;

//*--------------------------------------------------------------------------------*
//								�_�����蔻��
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		�R���X�g���N�^
//*------------------------------------------------*

ClCollPoint::ClCollPoint() { m_coll = ClXY(); }
ClCollPoint::~ClCollPoint() { return; }

//*------------------------------------------------*
//		�v���p�e�B
//*------------------------------------------------*

//�����蔻��ʒu���Q��
ClXY ClCollPoint::GetColl() { return m_coll; }

//�����蔻��ʒu��ݒ�(is_coll=FALSE�ł��\)
VOID ClCollPoint::SetColl(int x, int y) { m_coll.SetXY(x, y); }

//*------------------------------------------------*
//		�֐�
//*------------------------------------------------*

//�����蔻����X�V
VOID ClCollPoint::Update(int x, int y) {
	if (m_is_coll == FALSE) { return; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�
	m_coll.SetXY(x, y);
}

//*------------------------------------------------*
//		�����蔻��
//*------------------------------------------------*

BOOL ClCollPoint::IsStay(ClXY point) {
	//�����蔻��
	if (MmIsStay(m_coll, point) == TRUE) { return TRUE; }
	return FALSE;
}



//�����蔻�肪��`�����蔻��͈͓��ɓ�������
BOOL ClCollPoint::IsStay(ClRect rect) {
	if (MmIsStay(m_coll,rect) == TRUE) { return TRUE; }
	return FALSE;
}

//�����蔻�肪��`�����蔻��͈͓��ɓ�������
BOOL ClCollPoint::IsStay(ClCircle circle) {
	if (MmIsStay(m_coll, circle) == TRUE) { return TRUE; }
	return FALSE;
}

//BOOL ClCollPoint::aIsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case) {
//	switch (if_case){
//	case n_com::EQUAL_OUT:
//		if (aMmIsCollRectEqualOut(rect) == TRUE) { return TRUE; }
//		break;
//	case n_com::EQUAL_IN:
//		if (aMmIsCollRectEqualIn(rect) == TRUE) { return TRUE; }
//		break;
//	default:
//		break;
//	}
//	return FALSE;
//}
//
////�����蔻��(�������A����)
//BOOL ClCollPoint::aMmIsCollRectEqualOut(ClCollRect rect) {
//	//�����蔻�肪�쓮���ĂȂ��Ȃ珈�����I��
//	if (am_is_coll == FALSE) { return FALSE; }
//	if (rect.GetIsColl() == FALSE) { return FALSE; }
//
//	//�����蔻������ǂ���
//	if (am_coll.x < rect.GetColl().right
//		&& am_coll.x  > rect.GetColl().left
//		&& am_coll.y < rect.GetColl().bottom
//		&& am_coll.y > rect.GetColl().top) {
//		return TRUE;
//	}
//
//	return FALSE;
//}
//
////�����蔻��(�ȏ�A�ȉ�)
//BOOL ClCollPoint::aMmIsCollRectEqualIn(ClCollRect rect) {
//	//�����蔻�肪�쓮���ĂȂ��Ȃ珈�����I��
//	if (am_is_coll == FALSE) { return FALSE; }
//	if (rect.GetIsColl() == FALSE) { return FALSE; }
//
//	//�����蔻��Ȃ����ǂ���
//	if (am_coll.x <= rect.GetColl().right
//		&& am_coll.x >= rect.GetColl().left
//		&& am_coll.y <= rect.GetColl().bottom
//		&& am_coll.y >= rect.GetColl().top) {
//		return TRUE;
//	}
//
//	return FALSE;
//}

//*------------------------------------------------*
//		�f�o�b�N�`��
//*------------------------------------------------*

const int DEFULT_LINE_THICK = 1;	//�f�t�H���g�̐��̑���

//�f�o�b�N�`��
VOID ClCollPoint::DrawDebug() { DrawDebug(ClCom().GetFlipColor(), DEFULT_LINE_THICK); }

VOID ClCollPoint::DrawDebug(unsigned int color) { DrawDebug(color, DEFULT_LINE_THICK); }

VOID ClCollPoint::DrawDebug(unsigned int color, int thick) {
	//�����蔻�肪�쓮���ĂȂ��Ȃ珈�����I��
	if (ClWin().GetIsDebug() == FALSE) { return; }
	if (m_is_coll == FALSE) { return; }

	//���̈ʒu���v�Z
	int cross_half_size = ClWin().GetWinColor() / ClCom().GetPowerNumPlas(2);
	ClRect cr = ClRect();
	cr.SetRect(
		m_coll.x - cross_half_size, m_coll.y - cross_half_size,
		m_coll.x + cross_half_size, m_coll.y + cross_half_size
	);

	//�`��
	DrawLine(cr.left, cr.top, cr.right, cr.bottom, color,thick);
	DrawLine(cr.right, cr.top , cr.left, cr.bottom, color,thick);
}
