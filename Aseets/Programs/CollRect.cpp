//*--------------------------------------------------------------------------------*
//								��`�����蔻��
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include COLL_RECT_HPP
using namespace n_coll_rect;
//		�l�[��
using namespace n_xy;
using namespace n_rect;

//*--------------------------------------------------------------------------------*
//								��`�����蔻��
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		�R���X�g���N�^
//*------------------------------------------------*

ClCollRect::ClCollRect() {
	m_coll = ClRect(); 
	m_size = ClXY();
}
ClCollRect::~ClCollRect() { return; }

//*------------------------------------------------*
//		�v���p�e�B
//*------------------------------------------------*

//�����蔻��͈͂��Q��
ClRect ClCollRect::GetColl() { return m_coll; }

////�����蔻�肪�쓮���Ă��邩���Q��
//BOOL ClCollRect::GetIsColl() { return m_is_coll; }

/// <summary>
/// �����蔻��͈͂�ݒ�(is_coll=FALSE�ł��\)
/// </summary>
/// <param name="left">���[</param>
/// <param name="top">��[</param>
/// <param name="right">�E�[</param>
/// <param name="bottom">���[</param>
VOID ClCollRect::SetColl(int pos_x, int pos_y, int size_x, int size_y) {
	m_coll.SetRect(pos_x, pos_y, pos_x + size_x, pos_y + size_y);
	m_size.SetXY(size_x, size_y);
}

///// <summary>
///// �����蔻����쓮�����邩
///// </summary>
///// <param name="is_coll">TRUE�ō쓮</param>
//VOID ClCollRect::SetIsColl(BOOL is_coll) { m_is_coll = is_coll; }

//*------------------------------------------------*
//		�֐�
//*------------------------------------------------*

/// <summary>
/// �����蔻����X�V(is_coll=FALSE���͍쓮���Ȃ�)
/// </summary>
/// <param name="left">���[</param>
/// <param name="top">��[</param>
/// <param name="right">�E�[</param>
/// <param name="bottom">���[</param>
VOID ClCollRect::Update(int x,int y) {
	if (m_is_coll == FALSE) { return; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�
	m_coll.SetRect(x, y, x + m_size.x, y + m_size.y);
}

BOOL ClCollRect::IsStay(ClXY point) {
	if (MmIsStay(m_coll, point) == TRUE) { return TRUE; }
	return FALSE;
}

//
//BOOL ClCollRect::IsStay(ClCollPoint point, n_com::IF_CASE_WHICH if_case) {
//	switch (if_case)
//	{
//	case n_com::EQUAL_OUT:
//		if (MmIsCollPointEqualOut(point) == TRUE) { return TRUE; }
//		break;
//	case n_com::EQUAL_IN:
//		if (MmIsCollPointEqualIn(point) == TRUE) { return TRUE; }
//		break;
//	default:
//		break;
//	}
//	return FALSE;
//}
//
//BOOL ClCollRect::MmIsCollPointEqualOut(ClCollPoint point) {
//	//�����蔻�肪�쓮���ĂȂ��Ȃ珈�����I��
//	if (m_is_coll == FALSE) { return FALSE; }
//	if (point.aGetIsColl() == FALSE) { return FALSE; }
//
//	//�����蔻������ǂ���
//	if (m_coll.left < point.aGetColl().x
//		&& m_coll.right > point.aGetColl().x
//		&& m_coll.top < point.aGetColl().y
//		&& m_coll.bottom > point.aGetColl().y) {
//		return TRUE;
//	}
//
//	return FALSE;
//}
//
//BOOL ClCollRect::MmIsCollPointEqualIn(ClCollPoint point) {
//	//�����蔻�肪�쓮���ĂȂ��Ȃ珈�����I��
//	if (m_is_coll == FALSE) { return FALSE; }
//	if (point.aGetIsColl() == FALSE) { return FALSE; }
//
//	//�����蔻������ǂ���
//	if (m_coll.left <= point.aGetColl().x
//		&& m_coll.right >= point.aGetColl().x
//		&& m_coll.top <= point.aGetColl().y
//		&& m_coll.bottom >= point.aGetColl().y) {
//		return TRUE;
//	}
//
//	return FALSE;
//}

/// <summary>
/// ����̓����蔻��ɐG��Ă���Ƃ�TRUE(�͈͈ȏ�A�ȉ�)
/// </summary>
/// <param name="rect">����̋�`������͈�</param>
/// <returns>TRUE�ő���Ɠ������Ă���</returns>
BOOL ClCollRect::IsStay(ClRect rect) {
	if (MmIsStay(m_coll,rect) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClCollRect::IsStay(n_circle::ClCircle circle) {
	if (MmIsStay(m_coll, circle) == TRUE) { return TRUE; }
	return FALSE;
}

///// <summary>
///// ����̓����蔻��ɐG��Ă���Ƃ�TRUE
///// </summary>
///// <param name="rect">����̋�`������͈�</param>
///// <param name="if_case">�����蔻�肪(�������A����)��(�ȏ�A�ȉ�)</param>
///// <returns>TRUE�ő���Ɠ������Ă���</returns>
//BOOL ClCollRect::IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case) {
//	switch (if_case) {
//		//�������A����
//	case n_com::EQUAL_OUT:
//		if (MmIsCollRectEqualOut(rect) == TRUE) { return TRUE; }
//		break;
//
//		//�ȏ�A�ȉ�
//	case n_com::EQUAL_IN:
//		if (MmIsCollRectEqualIn(rect) == TRUE) { return TRUE; }
//		break;
//	default:
//		break;
//	}
//
//
//	return FALSE;
//}

////�����蔻��(�������A����)
//BOOL ClCollRect::MmIsCollRectEqualOut(ClCollRect rect) {
//	//�����蔻�肪�쓮���ĂȂ��Ȃ珈�����I��
//	if (m_is_coll == FALSE) { return FALSE; }
//	if (rect.GetIsColl() == FALSE) { return FALSE; }
//
//	//�����蔻������ǂ���
//	if (m_coll.left < rect.GetColl().right
//		&& m_coll.right > rect.GetColl().left
//		&& m_coll.top < rect.GetColl().bottom
//		&& m_coll.bottom > rect.GetColl().top) {
//		return TRUE;
//	}
//
//	return FALSE;
//}
//
////�����蔻��(�ȏ�A�ȉ�)
//BOOL ClCollRect::MmIsCollRectEqualIn(ClCollRect rect) {
//	//�����蔻�肪�쓮���ĂȂ��Ȃ珈�����I��
//	if (m_is_coll == FALSE) { return FALSE; }
//	if (rect.GetIsColl() == FALSE) { return FALSE; }
//
//	//�����蔻��Ȃ����ǂ���
//	if (m_coll.left <= rect.GetColl().right
//		&& m_coll.right >= rect.GetColl().left
//		&& m_coll.top <= rect.GetColl().bottom
//		&& m_coll.bottom >= rect.GetColl().top) {
//		return TRUE;
//	}
//
//	return FALSE;
//}

//*------------------------------------------------*
//		�����蔻���`��
//*------------------------------------------------*

const int DEFULT_LINE_THICK = 1;	//�f�t�H���g�̐��̑���

//��ʂƔ��ΐF�œ����蔻���`��
VOID ClCollRect::DrawDebug() { DrawDebug(ClCom().GetFlipColor(), DEFULT_LINE_THICK); }

/// <summary>
/// �F���w�肵�ē����蔻���`��
/// </summary>
/// <param name="color">�w��F</param>
VOID ClCollRect::DrawDebug(unsigned int color) { DrawDebug(color, DEFULT_LINE_THICK); }

/// <summary>
/// �F�Ɛ��̑������w�肵�ē������œ����蔻���`��
/// </summary>
/// <param name="color">�w��F</param>
/// <param name="thick">���̑���</param>
VOID ClCollRect::DrawDebug(unsigned int color, int thick) {
	//�����蔻�肪�쓮���ĂȂ��Ȃ珈�����I��
	if (ClWin().GetIsDebug() == FALSE) { return; }
	if (m_is_coll == FALSE) { return; }

	//�����蔻���`��
	for (int i = 0; i < thick; i++) {
		DrawBox(m_coll.left + i, m_coll.top + i, m_coll.right - i, m_coll.bottom - i, color, FALSE);
	}
	DrawLine(m_coll.left + thick, m_coll.top + thick, m_coll.right - thick, m_coll.bottom - thick, color, thick);
	DrawLine(m_coll.right - thick, m_coll.top + thick, m_coll.left + thick, m_coll.bottom - thick, color, thick);
}