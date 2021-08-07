//*--------------------------------------------------------------------------------*
//								�����蔻��
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include COLL_HPP
using namespace n_coll;
//		�W���t�@�C��
#include <math.h>
using namespace std;

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^
//*--------------------------------------------------------------------------------*

ClColl::ClColl() { m_is_coll = FALSE; }
ClColl::~ClColl() { return; }

//*--------------------------------------------------------------------------------*
//								�v���p�e�B
//*--------------------------------------------------------------------------------*

//�����蔻�肪�쓮���Ă��邩���Q��
BOOL ClColl::GetIsColl() { return m_is_coll; }

//�����蔻����쓮�����邩
VOID ClColl::SetIsColl(BOOL is_coll) { m_is_coll = is_coll; }

//*--------------------------------------------------------------------------------*
//								�֐�
//*--------------------------------------------------------------------------------*

//�_�Ɠ_�̓����蔻��
BOOL ClColl::MmIsStay(n_xy::ClXY m_point, n_xy::ClXY point) {
	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�

	if (m_point.x == point.x && m_point.y == point.y) { return TRUE; }
	return FALSE;
}

//�_�Ƌ�`�̓����蔻��(In)
BOOL ClColl::MmIsStay(n_xy::ClXY m_point, n_rect::ClRect rect) {
	if (MmIsCollEqualIn(m_point, rect) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualOut(n_xy::ClXY m_point, n_rect::ClRect rect) {
	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�

	//�����蔻��
	if (m_point.x<rect.right
		&& m_point.x > rect.left
		&& m_point.y<rect.bottom
		&& m_point.y>rect.top) {
		return TRUE;
	}
	return FALSE;
}
BOOL ClColl::MmIsCollEqualIn(n_xy::ClXY m_point, n_rect::ClRect rect) {
	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�

	//�����蔻��
	if (m_point.x <= rect.right
		&& m_point.x >= rect.left
		&& m_point.y <= rect.bottom
		&& m_point.y >= rect.top) {
		return TRUE;
	}
	return FALSE;
}

//�_�Ɖ~�̓����蔻��(In)
BOOL ClColl::MmIsStay(n_xy::ClXY m_point, n_circle::ClCircle circle) {
	if (MmIsCollEqualIn(m_point, circle) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualIn(n_xy::ClXY m_point, n_circle::ClCircle circle) {
	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�

	float bm = m_point.x - circle.center.x;		//�O�p�`�̒�ӂ̒��������߂�
	float ht = m_point.y - circle.center.y;		//�O�p�`�̍����̒��������߂�
	float sq = sqrtf(bm * bm + ht * ht);		//�O�p�`�̎Εӂ̒��������߂�(sqrt=������)

	//�Εӂ̒������A�~�̔��a�����Z���Ȃ�΁A�~�̒��ɂ���
	return (sq <= circle.radius) ? TRUE : FALSE;
}

//��`�Ƌ�`�̓����蔻��(In)
BOOL ClColl::MmIsStay(n_rect::ClRect m_rect, n_rect::ClRect rect) {
	if (MmIsCollEqualIn(m_rect, rect) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualOut(n_rect::ClRect m_rect, n_rect::ClRect rect) {
	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�

	//�����蔻��
	if (m_rect.left < rect.right
		&& m_rect.right > rect.left
		&& m_rect.top < rect.bottom
		&& m_rect.bottom > rect.top) {
		return TRUE;
	}
	return FALSE;
}

BOOL ClColl::MmIsCollEqualIn(n_rect::ClRect m_rect, n_rect::ClRect rect) {
	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�

	//�����蔻��
	if (m_rect.left <= rect.right
		&& m_rect.right >= rect.left
		&& m_rect.top <= rect.bottom
		&& m_rect.bottom >= rect.top) {
		return TRUE;
	}
	return FALSE;
}

//��`�Ɠ_�̓����蔻��(In)
BOOL ClColl::MmIsStay(n_rect::ClRect m_rect, n_xy::ClXY point) {
	if (MmIsCollEqualIn(m_rect, point) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualOut(n_rect::ClRect m_rect, n_xy::ClXY point) {
	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�

	//�����蔻��
	if (m_rect.left < point.x
		&& m_rect.right > point.x
		&& m_rect.top < point.y
		&& m_rect.bottom > point.y) {
		return TRUE;
	}
	return FALSE;
}

BOOL ClColl::MmIsCollEqualIn(n_rect::ClRect m_rect, n_xy::ClXY point) {
	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�

	//�����蔻��
	if (m_rect.left <= point.x
		&& m_rect.right >= point.x
		&& m_rect.top <= point.y
		&& m_rect.bottom >= point.y) {
		return TRUE;
	}
	return FALSE;
}

//��`�Ɖ~
BOOL ClColl::MmIsStay(n_rect::ClRect m_rect, n_circle::ClCircle circle) {
	if (MmIsCollEqualIn(m_rect, circle) == TRUE) { return TRUE; }
	return FALSE;
}

//���Ԉ���Ă���\������
BOOL ClColl::MmIsCollEqualIn(n_rect::ClRect m_rect, n_circle::ClCircle circle) {
	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�

	//�����蔻��
	if (m_rect.left <= circle.center.x
		&& m_rect.right >= circle.center.x
		&& m_rect.top <= circle.center.y + circle.radius
		&& m_rect.bottom >= circle.center.y - circle.radius) {
		return TRUE;
	}

	if (m_rect.left <= circle.center.x + circle.radius
		&& m_rect.right >= circle.center.x - circle.radius
		&& m_rect.top <= circle.center.y
		&& m_rect.bottom >= circle.center.y) {
		return TRUE;
	}

	if (MmIsCollEqualIn(m_rect.GetPivot(n_xy::TOP_LEFT), circle) == TRUE
		|| MmIsCollEqualIn(m_rect.GetPivot(n_xy::TOP_RIGHT), circle) == TRUE
		|| MmIsCollEqualIn(m_rect.GetPivot(n_xy::BUTTOM_LEFT), circle) == TRUE
		|| MmIsCollEqualIn(m_rect.GetPivot(n_xy::BUTTOM_RIGHT), circle) == TRUE) {
		return TRUE;
	}

	return FALSE;
}

//�~�Ɖ~
BOOL ClColl::MmIsStay(n_circle::ClCircle m_circle, n_circle::ClCircle circle) {
	if (MmIsCollEqualIn(m_circle, circle) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualIn(n_circle::ClCircle m_circle, n_circle::ClCircle circle) {
	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�

	float bm = m_circle.center.x - circle.center.x;		//�O�p�`�̒�ӂ̒��������߂�
	float ht = m_circle.center.y - circle.center.y;		//�O�p�`�̍����̒��������߂�
	float sq = sqrtf(bm * bm + ht * ht);		//�O�p�`�̎Εӂ̒��������߂�(sqrt=������)

	//�Εӂ̒������A�~�̔��a�����Z���Ȃ�΁A�~�̒��ɂ���
	return (sq <= m_circle.radius) ? TRUE : FALSE;
}

//�~�Ɠ_
BOOL ClColl::MmIsStay(n_circle::ClCircle m_circle, n_xy::ClXY point) {
	if (MmIsCollEqualIn(m_circle, point) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualIn(n_circle::ClCircle m_circle, n_xy::ClXY point) {
	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�

	float bm = m_circle.center.x - point.x;		//�O�p�`�̒�ӂ̒��������߂�
	float ht = m_circle.center.y - point.y;		//�O�p�`�̍����̒��������߂�
	float sq = sqrtf(bm * bm + ht * ht);		//�O�p�`�̎Εӂ̒��������߂�(sqrt=������)

	//�Εӂ̒������A�~�̔��a�����Z���Ȃ�΁A�~�̒��ɂ���
	return (sq <= m_circle.radius) ? TRUE : FALSE;
}

//�~�Ƌ�`
BOOL ClColl::MmIsStay(n_circle::ClCircle m_circle, n_rect::ClRect rect) {
	if (MmIsCollEqualIn(rect, m_circle) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualIn(n_circle::ClCircle m_circle, n_rect::ClRect rect) {
	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�

	//�����蔻��
	if (m_circle.center.x <= rect.left
		&& m_circle.center.x >= rect.right
		&& m_circle.center.y + m_circle.radius <= rect.top
		&& m_circle.center.y - m_circle.radius >= rect.bottom) {
		return TRUE;
	}

	if (rect.left <= m_circle.center.x + m_circle.radius
		&& rect.right >= m_circle.center.x - m_circle.radius
		&& rect.top <= m_circle.center.y
		&& rect.bottom >= m_circle.center.y) {
		return TRUE;
	}

	if (MmIsCollEqualIn( m_circle, rect.GetPivot(n_xy::TOP_LEFT)) == TRUE
		|| MmIsCollEqualIn( m_circle, rect.GetPivot(n_xy::TOP_RIGHT)) == TRUE
		|| MmIsCollEqualIn( m_circle, rect.GetPivot(n_xy::BUTTOM_LEFT)) == TRUE
		|| MmIsCollEqualIn( m_circle, rect.GetPivot(n_xy::BUTTOM_RIGHT)) == TRUE) {
		return TRUE;
	}

	return FALSE;
}

////*--------------------------------------------------------------------------------*
////								�����蔻��
////*--------------------------------------------------------------------------------*
//
////*--------------------------------------------------------------------------------*
////								�w�b�_�t�@�C���ǂݍ���
////*--------------------------------------------------------------------------------*
////		CommonUse�t�@�C��
//#include "IncludeFile.hpp"
////		���g�̃t�@�C��
//#include COLL_HPP
//using namespace n_coll;
////		�l�[��
//using namespace n_rect;
//using namespace n_xy;
//
//const int DEFULT_LINE_THICK = 1;	//�f�t�H���g�̐��̑���
//
////*--------------------------------------------------------------------------------*
////								�_�����蔻��
////*--------------------------------------------------------------------------------*
//
////*------------------------------------------------*
////		�R���X�g���N�^
////*------------------------------------------------*
//
//ClCollPoint::ClCollPoint() { 
//	m_coll = ClXY(); 
//	m_is_coll = FALSE;
//}
//ClCollPoint::~ClCollPoint() { return; }
//
////*------------------------------------------------*
////		�v���p�e�B
////*------------------------------------------------*
//
////�����蔻��ʒu���Q��
//ClXY ClCollPoint::GetColl() { return m_coll; }
//
////�����蔻�肪�쓮���Ă��邩���Q��
//BOOL ClCollPoint::GetIsColl() { return m_is_coll; }
//
////�����蔻��ʒu��ݒ�(is_coll=FALSE�ł��\)
//VOID ClCollPoint::SetColl(int x, int y) { m_coll.SetXY(x, y); }
//
////�����蔻����쓮�����邩
//VOID ClCollPoint::SetIsColl(BOOL is_coll) { m_is_coll = is_coll; }
//
////*------------------------------------------------*
////		�֐�
////*------------------------------------------------*
//
////�����蔻����X�V
//VOID ClCollPoint::Update(int x, int y) {
//	if (m_is_coll == FALSE) { return; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�
//	m_coll.SetXY(x, y);
//}
//
////*------------------------------------------------*
////		�����蔻��
////*------------------------------------------------*
//
//BOOL ClCollPoint::IsStay(ClCollPoint point) {
//	if (m_is_coll == FALSE) { return FALSE; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�
//
//	if (m_coll.x == point.GetColl().x && m_coll.y == point.GetColl().y) { return TRUE; }
//	return FALSE;
//}
//
////�����蔻�肪��`�����蔻��͈͓��ɓ�������
//BOOL ClCollPoint::IsStay(ClCollRect rect) {
//	if (m_is_coll == FALSE) { return; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�
//}
//
//BOOL IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case);
//
////*------------------------------------------------*
////		�f�o�b�N�`��
////*------------------------------------------------*
//
////�f�o�b�N�`��
//VOID ClCollPoint::DrawDebug() { DrawDebug(ClCom().GetFlipColor(), DEFULT_LINE_THICK); }
//
//VOID ClCollPoint::DrawDebug(unsigned int color) { DrawDebug(color, DEFULT_LINE_THICK); }
//
//VOID ClCollPoint::DrawDebug(unsigned int color, int thick){
//	//�����蔻�肪�쓮���ĂȂ��Ȃ珈�����I��
//	if (ClWin().GetIsDebug() == FALSE) { return; }
//	if (m_is_coll == FALSE) { return; }		
//}
//
////*--------------------------------------------------------------------------------*
////								��`�����蔻��
////*--------------------------------------------------------------------------------*
//
////*------------------------------------------------*
////		�R���X�g���N�^
////*------------------------------------------------*
//
//ClCollRect::ClCollRect() { 
//	m_coll = ClRect();
//	m_is_coll = FALSE;
//}
//ClCollRect::~ClCollRect() { return; }
//
////*------------------------------------------------*
////		�v���p�e�B
////*------------------------------------------------*
//
////�����蔻��͈͂��Q��
//ClRect ClCollRect::GetColl() { return m_coll; }
//
////�����蔻�肪�쓮���Ă��邩���Q��
//BOOL ClCollRect::GetIsColl() { return m_is_coll; }
//
///// <summary>
///// �����蔻��͈͂�ݒ�(is_coll=FALSE�ł��\)
///// </summary>
///// <param name="left">���[</param>
///// <param name="top">��[</param>
///// <param name="right">�E�[</param>
///// <param name="bottom">���[</param>
//VOID ClCollRect::SetColl(int left, int top, int right, int bottom) { m_coll.SetRect(left, top, right, bottom); }
//
///// <summary>
///// �����蔻����쓮�����邩
///// </summary>
///// <param name="is_coll">TRUE�ō쓮</param>
//VOID ClCollRect::SetIsColl(BOOL is_coll) { m_is_coll = is_coll; }
//
////*------------------------------------------------*
////		�֐�
////*------------------------------------------------*
//
///// <summary>
///// �����蔻����X�V(is_coll=FALSE���͍쓮���Ȃ�)
///// </summary>
///// <param name="left">���[</param>
///// <param name="top">��[</param>
///// <param name="right">�E�[</param>
///// <param name="bottom">���[</param>
//VOID ClCollRect::Update(int left, int top, int right, int bottom) { 
//	if (m_is_coll == FALSE) { return; }		//�����蔻�肪�쓮���Ă��Ȃ��Ȃ�X�V���Ȃ�
//	m_coll.SetRect(left, top, right, bottom);
//}
//
///// <summary>
///// ����̓����蔻��ɐG��Ă���Ƃ�TRUE(�͈͈ȏ�A�ȉ�)
///// </summary>
///// <param name="rect">����̋�`������͈�</param>
///// <returns>TRUE�ő���Ɠ������Ă���</returns>
//BOOL ClCollRect::IsStay(ClCollRect rect) {
//	if (MmIsCollRectEqualIn(rect) == TRUE) { return TRUE; }
//	return FALSE;
//}
//
///// <summary>
///// ����̓����蔻��ɐG��Ă���Ƃ�TRUE
///// </summary>
///// <param name="rect">����̋�`������͈�</param>
///// <param name="if_case">�����蔻�肪(�������A����)��(�ȏ�A�ȉ�)</param>
///// <returns>TRUE�ő���Ɠ������Ă���</returns>
//BOOL ClCollRect::IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case) {
//	switch (if_case){
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
//
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
//
////*------------------------------------------------*
////		�����蔻���`��
////*------------------------------------------------*
//
////��ʂƔ��ΐF�œ����蔻���`��
//VOID ClCollRect::DrawDebug() { DrawDebug(ClCom().GetFlipColor(), DEFULT_LINE_THICK); }
//
///// <summary>
///// �F���w�肵�ē����蔻���`��
///// </summary>
///// <param name="color">�w��F</param>
//VOID ClCollRect::DrawDebug(unsigned int color) { DrawDebug(color, DEFULT_LINE_THICK); }
//
///// <summary>
///// �F�Ɛ��̑������w�肵�ē������œ����蔻���`��
///// </summary>
///// <param name="color">�w��F</param>
///// <param name="thick">���̑���</param>
//VOID ClCollRect::DrawDebug(unsigned int color, int thick) {
//	//�����蔻�肪�쓮���ĂȂ��Ȃ珈�����I��
//	if (ClWin().GetIsDebug() == FALSE) { return; }
//	if (m_is_coll == FALSE) { return; }
//
//	//�����蔻���`��
//	for (int i = 0; i < thick; i++) {
//		DrawBox(m_coll.left + i, m_coll.top + i, m_coll.right - i, m_coll.bottom - i, color, FALSE);
//	}
//	DrawLine(m_coll.left + thick, m_coll.top + thick, m_coll.right - thick, m_coll.bottom - thick, color, thick);
//	DrawLine(m_coll.right - thick, m_coll.top + thick, m_coll.left + thick, m_coll.bottom - thick, color, thick);
//}
//
//
//
////*--------------------------------------------------------------------------------*
////								�ۓ����蔻��
////*--------------------------------------------------------------------------------*
//
////ClCollCircle::ClCollCircle()
////{
////}
////
////ClCollCircle::~ClCollCircle()
////{
////}