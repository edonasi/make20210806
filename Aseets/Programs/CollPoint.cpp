//*--------------------------------------------------------------------------------*
//								点当たり判定
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include COLL_POINT_HPP
using namespace n_coll_point;
//		ネーム
using namespace n_xy;
using namespace n_rect;
using namespace n_circle;
//using namespace n_coll_rect;

//*--------------------------------------------------------------------------------*
//								点当たり判定
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		コンストラクタ
//*------------------------------------------------*

ClCollPoint::ClCollPoint() { m_coll = ClXY(); }
ClCollPoint::~ClCollPoint() { return; }

//*------------------------------------------------*
//		プロパティ
//*------------------------------------------------*

//当たり判定位置を参照
ClXY ClCollPoint::GetColl() { return m_coll; }

//当たり判定位置を設定(is_coll=FALSEでも可能)
VOID ClCollPoint::SetColl(int x, int y) { m_coll.SetXY(x, y); }

//*------------------------------------------------*
//		関数
//*------------------------------------------------*

//当たり判定を更新
VOID ClCollPoint::Update(int x, int y) {
	if (m_is_coll == FALSE) { return; }		//当たり判定が作動していないなら更新しない
	m_coll.SetXY(x, y);
}

//*------------------------------------------------*
//		当たり判定
//*------------------------------------------------*

BOOL ClCollPoint::IsStay(ClXY point) {
	//当たり判定
	if (MmIsStay(m_coll, point) == TRUE) { return TRUE; }
	return FALSE;
}



//当たり判定が矩形当たり判定範囲内に入ったか
BOOL ClCollPoint::IsStay(ClRect rect) {
	if (MmIsStay(m_coll,rect) == TRUE) { return TRUE; }
	return FALSE;
}

//当たり判定が矩形当たり判定範囲内に入ったか
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
////当たり判定(超えた、未満)
//BOOL ClCollPoint::aMmIsCollRectEqualOut(ClCollRect rect) {
//	//当たり判定が作動してないなら処理を終了
//	if (am_is_coll == FALSE) { return FALSE; }
//	if (rect.GetIsColl() == FALSE) { return FALSE; }
//
//	//当たり判定内かどうか
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
////当たり判定(以上、以下)
//BOOL ClCollPoint::aMmIsCollRectEqualIn(ClCollRect rect) {
//	//当たり判定が作動してないなら処理を終了
//	if (am_is_coll == FALSE) { return FALSE; }
//	if (rect.GetIsColl() == FALSE) { return FALSE; }
//
//	//当たり判定ないかどうか
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
//		デバック描画
//*------------------------------------------------*

const int DEFULT_LINE_THICK = 1;	//デフォルトの線の太さ

//デバック描画
VOID ClCollPoint::DrawDebug() { DrawDebug(ClCom().GetFlipColor(), DEFULT_LINE_THICK); }

VOID ClCollPoint::DrawDebug(unsigned int color) { DrawDebug(color, DEFULT_LINE_THICK); }

VOID ClCollPoint::DrawDebug(unsigned int color, int thick) {
	//当たり判定が作動してないなら処理を終了
	if (ClWin().GetIsDebug() == FALSE) { return; }
	if (m_is_coll == FALSE) { return; }

	//線の位置を計算
	int cross_half_size = ClWin().GetWinColor() / ClCom().GetPowerNumPlas(2);
	ClRect cr = ClRect();
	cr.SetRect(
		m_coll.x - cross_half_size, m_coll.y - cross_half_size,
		m_coll.x + cross_half_size, m_coll.y + cross_half_size
	);

	//描画
	DrawLine(cr.left, cr.top, cr.right, cr.bottom, color,thick);
	DrawLine(cr.right, cr.top , cr.left, cr.bottom, color,thick);
}
