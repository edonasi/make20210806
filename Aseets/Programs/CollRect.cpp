//*--------------------------------------------------------------------------------*
//								矩形当たり判定
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include COLL_RECT_HPP
using namespace n_coll_rect;
//		ネーム
using namespace n_xy;
using namespace n_rect;

//*--------------------------------------------------------------------------------*
//								矩形当たり判定
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		コンストラクタ
//*------------------------------------------------*

ClCollRect::ClCollRect() {
	m_coll = ClRect(); 
	m_size = ClXY();
}
ClCollRect::~ClCollRect() { return; }

//*------------------------------------------------*
//		プロパティ
//*------------------------------------------------*

//当たり判定範囲を参照
ClRect ClCollRect::GetColl() { return m_coll; }

////当たり判定が作動しているかを参照
//BOOL ClCollRect::GetIsColl() { return m_is_coll; }

/// <summary>
/// 当たり判定範囲を設定(is_coll=FALSEでも可能)
/// </summary>
/// <param name="left">左端</param>
/// <param name="top">上端</param>
/// <param name="right">右端</param>
/// <param name="bottom">下端</param>
VOID ClCollRect::SetColl(int pos_x, int pos_y, int size_x, int size_y) {
	m_coll.SetRect(pos_x, pos_y, pos_x + size_x, pos_y + size_y);
	m_size.SetXY(size_x, size_y);
}

///// <summary>
///// 当たり判定を作動させるか
///// </summary>
///// <param name="is_coll">TRUEで作動</param>
//VOID ClCollRect::SetIsColl(BOOL is_coll) { m_is_coll = is_coll; }

//*------------------------------------------------*
//		関数
//*------------------------------------------------*

/// <summary>
/// 当たり判定を更新(is_coll=FALSE時は作動しない)
/// </summary>
/// <param name="left">左端</param>
/// <param name="top">上端</param>
/// <param name="right">右端</param>
/// <param name="bottom">下端</param>
VOID ClCollRect::Update(int x,int y) {
	if (m_is_coll == FALSE) { return; }		//当たり判定が作動していないなら更新しない
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
//	//当たり判定が作動してないなら処理を終了
//	if (m_is_coll == FALSE) { return FALSE; }
//	if (point.aGetIsColl() == FALSE) { return FALSE; }
//
//	//当たり判定内かどうか
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
//	//当たり判定が作動してないなら処理を終了
//	if (m_is_coll == FALSE) { return FALSE; }
//	if (point.aGetIsColl() == FALSE) { return FALSE; }
//
//	//当たり判定内かどうか
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
/// 相手の当たり判定に触れているときTRUE(範囲以上、以下)
/// </summary>
/// <param name="rect">相手の矩形当たり範囲</param>
/// <returns>TRUEで相手と当たっている</returns>
BOOL ClCollRect::IsStay(ClRect rect) {
	if (MmIsStay(m_coll,rect) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClCollRect::IsStay(n_circle::ClCircle circle) {
	if (MmIsStay(m_coll, circle) == TRUE) { return TRUE; }
	return FALSE;
}

///// <summary>
///// 相手の当たり判定に触れているときTRUE
///// </summary>
///// <param name="rect">相手の矩形当たり範囲</param>
///// <param name="if_case">当たり判定が(超えた、未満)か(以上、以下)</param>
///// <returns>TRUEで相手と当たっている</returns>
//BOOL ClCollRect::IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case) {
//	switch (if_case) {
//		//超えた、未満
//	case n_com::EQUAL_OUT:
//		if (MmIsCollRectEqualOut(rect) == TRUE) { return TRUE; }
//		break;
//
//		//以上、以下
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

////当たり判定(超えた、未満)
//BOOL ClCollRect::MmIsCollRectEqualOut(ClCollRect rect) {
//	//当たり判定が作動してないなら処理を終了
//	if (m_is_coll == FALSE) { return FALSE; }
//	if (rect.GetIsColl() == FALSE) { return FALSE; }
//
//	//当たり判定内かどうか
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
////当たり判定(以上、以下)
//BOOL ClCollRect::MmIsCollRectEqualIn(ClCollRect rect) {
//	//当たり判定が作動してないなら処理を終了
//	if (m_is_coll == FALSE) { return FALSE; }
//	if (rect.GetIsColl() == FALSE) { return FALSE; }
//
//	//当たり判定ないかどうか
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
//		当たり判定を描画
//*------------------------------------------------*

const int DEFULT_LINE_THICK = 1;	//デフォルトの線の太さ

//画面と反対色で当たり判定を描画
VOID ClCollRect::DrawDebug() { DrawDebug(ClCom().GetFlipColor(), DEFULT_LINE_THICK); }

/// <summary>
/// 色を指定して当たり判定を描画
/// </summary>
/// <param name="color">指定色</param>
VOID ClCollRect::DrawDebug(unsigned int color) { DrawDebug(color, DEFULT_LINE_THICK); }

/// <summary>
/// 色と線の太さを指定して内側線で当たり判定を描画
/// </summary>
/// <param name="color">指定色</param>
/// <param name="thick">線の太さ</param>
VOID ClCollRect::DrawDebug(unsigned int color, int thick) {
	//当たり判定が作動してないなら処理を終了
	if (ClWin().GetIsDebug() == FALSE) { return; }
	if (m_is_coll == FALSE) { return; }

	//当たり判定を描画
	for (int i = 0; i < thick; i++) {
		DrawBox(m_coll.left + i, m_coll.top + i, m_coll.right - i, m_coll.bottom - i, color, FALSE);
	}
	DrawLine(m_coll.left + thick, m_coll.top + thick, m_coll.right - thick, m_coll.bottom - thick, color, thick);
	DrawLine(m_coll.right - thick, m_coll.top + thick, m_coll.left + thick, m_coll.bottom - thick, color, thick);
}