#pragma once

//		インクルードファイル
#include XY_HPP
#include RECT_HPP
#include CIRCLE_HPP

namespace n_coll {
	//Collの共通項目
	class ClColl{
	public:
		//		コンストラクタ
		ClColl();
		~ClColl();

		//		プロパティ
		BOOL GetIsColl();				//当たり判定が作動しているかを参照
		VOID SetIsColl(BOOL is_coll);	//当たり判定を作動させるか

	protected:
		

		//		関数
		BOOL MmIsStay(n_xy::ClXY m_point, n_xy::ClXY point);
		BOOL MmIsStay(n_xy::ClXY m_point, n_rect::ClRect rect);
		BOOL MmIsStay(n_xy::ClXY m_point, n_circle::ClCircle circle);
		BOOL MmIsStay(n_rect::ClRect m_rect, n_rect::ClRect rect);
		BOOL MmIsStay(n_rect::ClRect m_rect, n_xy::ClXY point);
		BOOL MmIsStay(n_rect::ClRect m_rect, n_circle::ClCircle circle);
		BOOL MmIsStay(n_circle::ClCircle m_circle, n_circle::ClCircle circle);
		BOOL MmIsStay(n_circle::ClCircle m_circle, n_xy::ClXY point);
		BOOL MmIsStay(n_circle::ClCircle m_circle, n_rect::ClRect rect);
		

		//		プロテクト変数
		BOOL m_is_coll;		//当たり判定を動作させるか

	private:
		//		メンバ関数
		BOOL MmIsCollEqualOut(n_xy::ClXY m_point, n_rect::ClRect rect);
		BOOL MmIsCollEqualIn(n_xy::ClXY m_point, n_rect::ClRect rect);

		BOOL MmIsCollEqualIn(n_xy::ClXY m_point, n_circle::ClCircle circle);
		BOOL MmIsCollEqualOut(n_rect::ClRect m_rect, n_rect::ClRect rect);
		BOOL MmIsCollEqualIn(n_rect::ClRect m_rect, n_rect::ClRect rect);
		BOOL MmIsCollEqualOut(n_rect::ClRect m_rect, n_xy::ClXY point);
		BOOL MmIsCollEqualIn(n_rect::ClRect m_rect, n_xy::ClXY point);

		BOOL MmIsCollEqualIn(n_rect::ClRect m_rect, n_circle::ClCircle circle);

		BOOL MmIsCollEqualIn(n_circle::ClCircle m_circle, n_circle::ClCircle circle);

		BOOL MmIsCollEqualIn(n_circle::ClCircle m_circle, n_xy::ClXY point);

		BOOL MmIsCollEqualIn(n_circle::ClCircle m_circle, n_rect::ClRect rect);
	};
}

//
////		インクルードファイル
//
////Circle時使用
//#include CIRCLE_HPP
////Rect時使用
//#include RECT_HPP
////XY使用
//#include XY_HPP
//
//namespace n_coll {
//	//点当たり判定
//	class ClCollPoint{
//	public:
//		//		コンストラクタ
//		ClCollPoint();
//		~ClCollPoint();
//
//		//		プロパティ
//		n_xy::ClXY GetColl();			//当たり判定位置を参照
//		BOOL GetIsColl();				//当たり判定が作動しているかを参照
//		VOID SetColl(int x, int y);		//当たり判定位置を設定(is_coll=FALSEでも可能)
//		VOID SetIsColl(BOOL is_coll);	//当たり判定を作動させるか
//		
//		//		関数
//		//当たり判定を更新
//		VOID Update(int x, int y);
//		//点と点
//		BOOL IsStay(ClCollPoint point);
//		//点と矩形
//		BOOL IsStay(ClCollRect rect);		
//		BOOL IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case);
//		//デバック描画
//		VOID DrawDebug();
//		VOID DrawDebug(unsigned int color);
//		VOID DrawDebug(unsigned int color, int thick);
//
//	private:
//		//		メンバ関数
//		//		メンバ関数
//		BOOL MmIsCollRectEqualOut(ClCollRect rect);
//		BOOL MmIsCollRectEqualIn(ClCollRect rect);
//
//		//		メンバ変数
//		n_xy::ClXY m_coll;		//当たり判定範囲
//		BOOL m_is_coll;			//当たり判定を動作させるか
//	};
//
//	//矩形当たり判定
//	class ClCollRect{
//	public:
//		//		コンストラクタ
//		ClCollRect();
//		~ClCollRect();
//
//		//		プロパティ
//		n_rect::ClRect GetColl();		//当たり判定範囲を参照
//		BOOL GetIsColl();				//当たり判定が作動しているかを参照
//		VOID SetColl(					//当たり判定範囲を設定(is_coll=FALSEでも可能)
//			int left, int top, int right, int bottom);
//		VOID SetIsColl(BOOL is_coll);	//当たり判定を作動させるか
//
//		//		関数
//		VOID Update(int left, int top, int right, int bottom);		//当たり判定を更新
//		//矩形と点
//		BOOL IsStay(ClCollPoint point);
//		BOOL IsStay(ClCollPoint point, n_com::IF_CASE_WHICH if_case);
//		//矩形と矩形
//		BOOL IsStay(ClCollRect rect);		//当たり判定がその中に入ったか
//		BOOL IsStay(ClCollRect rect,n_com::IF_CASE_WHICH if_case);		//当たり判定がその中に入ったか
//		//デバック描画
//		VOID DrawDebug();
//		VOID DrawDebug(unsigned int color);
//		VOID DrawDebug(unsigned int color, int thick);
//		
//
//	private:
//		//		メンバ関数
//		BOOL MmIsCollRectEqualOut(ClCollRect rect);
//		BOOL MmIsCollRectEqualIn(ClCollRect rect);
//
//		//		メンバ変数
//		n_rect::ClRect m_coll;	//当たり判定範囲
//		BOOL m_is_coll;			//当たり判定を動作させるか
//	};
//
//	
//
//	//class ClCollCircle{
//	//public:
//	//	ClCollCircle();
//	//	~ClCollCircle();
//
//	//	//		プロパティ
//	//	n_circle::ClCircle GetColl();
//
//	//private:
//	//	n_circle::ClCircle m_coll;
//	//};
//
//	
//}