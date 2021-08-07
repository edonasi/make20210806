//*--------------------------------------------------------------------------------*
//								当たり判定
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include COLL_HPP
using namespace n_coll;
//		標準ファイル
#include <math.h>
using namespace std;

//*--------------------------------------------------------------------------------*
//								コンストラクタ
//*--------------------------------------------------------------------------------*

ClColl::ClColl() { m_is_coll = FALSE; }
ClColl::~ClColl() { return; }

//*--------------------------------------------------------------------------------*
//								プロパティ
//*--------------------------------------------------------------------------------*

//当たり判定が作動しているかを参照
BOOL ClColl::GetIsColl() { return m_is_coll; }

//当たり判定を作動させるか
VOID ClColl::SetIsColl(BOOL is_coll) { m_is_coll = is_coll; }

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

//点と点の当たり判定
BOOL ClColl::MmIsStay(n_xy::ClXY m_point, n_xy::ClXY point) {
	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない

	if (m_point.x == point.x && m_point.y == point.y) { return TRUE; }
	return FALSE;
}

//点と矩形の当たり判定(In)
BOOL ClColl::MmIsStay(n_xy::ClXY m_point, n_rect::ClRect rect) {
	if (MmIsCollEqualIn(m_point, rect) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualOut(n_xy::ClXY m_point, n_rect::ClRect rect) {
	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない

	//当たり判定
	if (m_point.x<rect.right
		&& m_point.x > rect.left
		&& m_point.y<rect.bottom
		&& m_point.y>rect.top) {
		return TRUE;
	}
	return FALSE;
}
BOOL ClColl::MmIsCollEqualIn(n_xy::ClXY m_point, n_rect::ClRect rect) {
	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない

	//当たり判定
	if (m_point.x <= rect.right
		&& m_point.x >= rect.left
		&& m_point.y <= rect.bottom
		&& m_point.y >= rect.top) {
		return TRUE;
	}
	return FALSE;
}

//点と円の当たり判定(In)
BOOL ClColl::MmIsStay(n_xy::ClXY m_point, n_circle::ClCircle circle) {
	if (MmIsCollEqualIn(m_point, circle) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualIn(n_xy::ClXY m_point, n_circle::ClCircle circle) {
	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない

	float bm = m_point.x - circle.center.x;		//三角形の底辺の長さを求める
	float ht = m_point.y - circle.center.y;		//三角形の高さの長さを求める
	float sq = sqrtf(bm * bm + ht * ht);		//三角形の斜辺の長さを求める(sqrt=平方根)

	//斜辺の長さが、円の半径よりも短いならば、円の中にいる
	return (sq <= circle.radius) ? TRUE : FALSE;
}

//矩形と矩形の当たり判定(In)
BOOL ClColl::MmIsStay(n_rect::ClRect m_rect, n_rect::ClRect rect) {
	if (MmIsCollEqualIn(m_rect, rect) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualOut(n_rect::ClRect m_rect, n_rect::ClRect rect) {
	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない

	//当たり判定
	if (m_rect.left < rect.right
		&& m_rect.right > rect.left
		&& m_rect.top < rect.bottom
		&& m_rect.bottom > rect.top) {
		return TRUE;
	}
	return FALSE;
}

BOOL ClColl::MmIsCollEqualIn(n_rect::ClRect m_rect, n_rect::ClRect rect) {
	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない

	//当たり判定
	if (m_rect.left <= rect.right
		&& m_rect.right >= rect.left
		&& m_rect.top <= rect.bottom
		&& m_rect.bottom >= rect.top) {
		return TRUE;
	}
	return FALSE;
}

//矩形と点の当たり判定(In)
BOOL ClColl::MmIsStay(n_rect::ClRect m_rect, n_xy::ClXY point) {
	if (MmIsCollEqualIn(m_rect, point) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualOut(n_rect::ClRect m_rect, n_xy::ClXY point) {
	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない

	//当たり判定
	if (m_rect.left < point.x
		&& m_rect.right > point.x
		&& m_rect.top < point.y
		&& m_rect.bottom > point.y) {
		return TRUE;
	}
	return FALSE;
}

BOOL ClColl::MmIsCollEqualIn(n_rect::ClRect m_rect, n_xy::ClXY point) {
	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない

	//当たり判定
	if (m_rect.left <= point.x
		&& m_rect.right >= point.x
		&& m_rect.top <= point.y
		&& m_rect.bottom >= point.y) {
		return TRUE;
	}
	return FALSE;
}

//矩形と円
BOOL ClColl::MmIsStay(n_rect::ClRect m_rect, n_circle::ClCircle circle) {
	if (MmIsCollEqualIn(m_rect, circle) == TRUE) { return TRUE; }
	return FALSE;
}

//※間違っている可能性あり
BOOL ClColl::MmIsCollEqualIn(n_rect::ClRect m_rect, n_circle::ClCircle circle) {
	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない

	//当たり判定
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

//円と円
BOOL ClColl::MmIsStay(n_circle::ClCircle m_circle, n_circle::ClCircle circle) {
	if (MmIsCollEqualIn(m_circle, circle) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualIn(n_circle::ClCircle m_circle, n_circle::ClCircle circle) {
	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない

	float bm = m_circle.center.x - circle.center.x;		//三角形の底辺の長さを求める
	float ht = m_circle.center.y - circle.center.y;		//三角形の高さの長さを求める
	float sq = sqrtf(bm * bm + ht * ht);		//三角形の斜辺の長さを求める(sqrt=平方根)

	//斜辺の長さが、円の半径よりも短いならば、円の中にいる
	return (sq <= m_circle.radius) ? TRUE : FALSE;
}

//円と点
BOOL ClColl::MmIsStay(n_circle::ClCircle m_circle, n_xy::ClXY point) {
	if (MmIsCollEqualIn(m_circle, point) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualIn(n_circle::ClCircle m_circle, n_xy::ClXY point) {
	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない

	float bm = m_circle.center.x - point.x;		//三角形の底辺の長さを求める
	float ht = m_circle.center.y - point.y;		//三角形の高さの長さを求める
	float sq = sqrtf(bm * bm + ht * ht);		//三角形の斜辺の長さを求める(sqrt=平方根)

	//斜辺の長さが、円の半径よりも短いならば、円の中にいる
	return (sq <= m_circle.radius) ? TRUE : FALSE;
}

//円と矩形
BOOL ClColl::MmIsStay(n_circle::ClCircle m_circle, n_rect::ClRect rect) {
	if (MmIsCollEqualIn(rect, m_circle) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClColl::MmIsCollEqualIn(n_circle::ClCircle m_circle, n_rect::ClRect rect) {
	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない

	//当たり判定
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
////								当たり判定
////*--------------------------------------------------------------------------------*
//
////*--------------------------------------------------------------------------------*
////								ヘッダファイル読み込み
////*--------------------------------------------------------------------------------*
////		CommonUseファイル
//#include "IncludeFile.hpp"
////		自身のファイル
//#include COLL_HPP
//using namespace n_coll;
////		ネーム
//using namespace n_rect;
//using namespace n_xy;
//
//const int DEFULT_LINE_THICK = 1;	//デフォルトの線の太さ
//
////*--------------------------------------------------------------------------------*
////								点当たり判定
////*--------------------------------------------------------------------------------*
//
////*------------------------------------------------*
////		コンストラクタ
////*------------------------------------------------*
//
//ClCollPoint::ClCollPoint() { 
//	m_coll = ClXY(); 
//	m_is_coll = FALSE;
//}
//ClCollPoint::~ClCollPoint() { return; }
//
////*------------------------------------------------*
////		プロパティ
////*------------------------------------------------*
//
////当たり判定位置を参照
//ClXY ClCollPoint::GetColl() { return m_coll; }
//
////当たり判定が作動しているかを参照
//BOOL ClCollPoint::GetIsColl() { return m_is_coll; }
//
////当たり判定位置を設定(is_coll=FALSEでも可能)
//VOID ClCollPoint::SetColl(int x, int y) { m_coll.SetXY(x, y); }
//
////当たり判定を作動させるか
//VOID ClCollPoint::SetIsColl(BOOL is_coll) { m_is_coll = is_coll; }
//
////*------------------------------------------------*
////		関数
////*------------------------------------------------*
//
////当たり判定を更新
//VOID ClCollPoint::Update(int x, int y) {
//	if (m_is_coll == FALSE) { return; }		//当たり判定が作動していないなら更新しない
//	m_coll.SetXY(x, y);
//}
//
////*------------------------------------------------*
////		当たり判定
////*------------------------------------------------*
//
//BOOL ClCollPoint::IsStay(ClCollPoint point) {
//	if (m_is_coll == FALSE) { return FALSE; }		//当たり判定が作動していないなら更新しない
//
//	if (m_coll.x == point.GetColl().x && m_coll.y == point.GetColl().y) { return TRUE; }
//	return FALSE;
//}
//
////当たり判定が矩形当たり判定範囲内に入ったか
//BOOL ClCollPoint::IsStay(ClCollRect rect) {
//	if (m_is_coll == FALSE) { return; }		//当たり判定が作動していないなら更新しない
//}
//
//BOOL IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case);
//
////*------------------------------------------------*
////		デバック描画
////*------------------------------------------------*
//
////デバック描画
//VOID ClCollPoint::DrawDebug() { DrawDebug(ClCom().GetFlipColor(), DEFULT_LINE_THICK); }
//
//VOID ClCollPoint::DrawDebug(unsigned int color) { DrawDebug(color, DEFULT_LINE_THICK); }
//
//VOID ClCollPoint::DrawDebug(unsigned int color, int thick){
//	//当たり判定が作動してないなら処理を終了
//	if (ClWin().GetIsDebug() == FALSE) { return; }
//	if (m_is_coll == FALSE) { return; }		
//}
//
////*--------------------------------------------------------------------------------*
////								矩形当たり判定
////*--------------------------------------------------------------------------------*
//
////*------------------------------------------------*
////		コンストラクタ
////*------------------------------------------------*
//
//ClCollRect::ClCollRect() { 
//	m_coll = ClRect();
//	m_is_coll = FALSE;
//}
//ClCollRect::~ClCollRect() { return; }
//
////*------------------------------------------------*
////		プロパティ
////*------------------------------------------------*
//
////当たり判定範囲を参照
//ClRect ClCollRect::GetColl() { return m_coll; }
//
////当たり判定が作動しているかを参照
//BOOL ClCollRect::GetIsColl() { return m_is_coll; }
//
///// <summary>
///// 当たり判定範囲を設定(is_coll=FALSEでも可能)
///// </summary>
///// <param name="left">左端</param>
///// <param name="top">上端</param>
///// <param name="right">右端</param>
///// <param name="bottom">下端</param>
//VOID ClCollRect::SetColl(int left, int top, int right, int bottom) { m_coll.SetRect(left, top, right, bottom); }
//
///// <summary>
///// 当たり判定を作動させるか
///// </summary>
///// <param name="is_coll">TRUEで作動</param>
//VOID ClCollRect::SetIsColl(BOOL is_coll) { m_is_coll = is_coll; }
//
////*------------------------------------------------*
////		関数
////*------------------------------------------------*
//
///// <summary>
///// 当たり判定を更新(is_coll=FALSE時は作動しない)
///// </summary>
///// <param name="left">左端</param>
///// <param name="top">上端</param>
///// <param name="right">右端</param>
///// <param name="bottom">下端</param>
//VOID ClCollRect::Update(int left, int top, int right, int bottom) { 
//	if (m_is_coll == FALSE) { return; }		//当たり判定が作動していないなら更新しない
//	m_coll.SetRect(left, top, right, bottom);
//}
//
///// <summary>
///// 相手の当たり判定に触れているときTRUE(範囲以上、以下)
///// </summary>
///// <param name="rect">相手の矩形当たり範囲</param>
///// <returns>TRUEで相手と当たっている</returns>
//BOOL ClCollRect::IsStay(ClCollRect rect) {
//	if (MmIsCollRectEqualIn(rect) == TRUE) { return TRUE; }
//	return FALSE;
//}
//
///// <summary>
///// 相手の当たり判定に触れているときTRUE
///// </summary>
///// <param name="rect">相手の矩形当たり範囲</param>
///// <param name="if_case">当たり判定が(超えた、未満)か(以上、以下)</param>
///// <returns>TRUEで相手と当たっている</returns>
//BOOL ClCollRect::IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case) {
//	switch (if_case){
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
//
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
//
////*------------------------------------------------*
////		当たり判定を描画
////*------------------------------------------------*
//
////画面と反対色で当たり判定を描画
//VOID ClCollRect::DrawDebug() { DrawDebug(ClCom().GetFlipColor(), DEFULT_LINE_THICK); }
//
///// <summary>
///// 色を指定して当たり判定を描画
///// </summary>
///// <param name="color">指定色</param>
//VOID ClCollRect::DrawDebug(unsigned int color) { DrawDebug(color, DEFULT_LINE_THICK); }
//
///// <summary>
///// 色と線の太さを指定して内側線で当たり判定を描画
///// </summary>
///// <param name="color">指定色</param>
///// <param name="thick">線の太さ</param>
//VOID ClCollRect::DrawDebug(unsigned int color, int thick) {
//	//当たり判定が作動してないなら処理を終了
//	if (ClWin().GetIsDebug() == FALSE) { return; }
//	if (m_is_coll == FALSE) { return; }
//
//	//当たり判定を描画
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
////								丸当たり判定
////*--------------------------------------------------------------------------------*
//
////ClCollCircle::ClCollCircle()
////{
////}
////
////ClCollCircle::~ClCollCircle()
////{
////}