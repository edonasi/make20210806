#pragma once

#include COLL_HPP

#include XY_HPP
//当たり判定範囲に使用
#include RECT_HPP
#include CIRCLE_HPP

namespace n_coll_rect {
	class ClCollRect:public n_coll::ClColl
	{
	public:
		//		コンストラクタ
		ClCollRect();
		~ClCollRect();

		//		プロパティ
		n_rect::ClRect GetColl();		//当たり判定範囲を参照
		VOID SetColl(					//当たり判定範囲を設定(is_coll=FALSEでも可能)
			int pos_x, int pos_y, int size_x, int size_y);

		//		関数
		VOID Update(int x, int y);		//当たり判定を更新
		//矩形と点
		BOOL IsStay(n_xy::ClXY point);
		//BOOL IsStay(n_coll_point::ClCollPoint point, n_com::IF_CASE_WHICH if_case);
		//矩形と矩形
		BOOL IsStay(n_rect::ClRect rect);		//当たり判定がその中に入ったか
		//矩形と円
		BOOL IsStay(n_circle::ClCircle circle);		//当たり判定がその中に入ったか
		//BOOL IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case);		//当たり判定がその中に入ったか
		//デバック描画
		VOID DrawDebug();
		VOID DrawDebug(unsigned int color);
		VOID DrawDebug(unsigned int color, int thick);

	private:
		//		メンバ変数
		n_rect::ClRect m_coll;	//当たり判定範囲
		n_xy::ClXY m_size;
	};
}

//namespace n_coll_rect {
//	//矩形当たり判定
//	class ClCollRect {
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
//		//BOOL IsStay(n_coll_point::ClCollPoint point);
//		//BOOL IsStay(n_coll_point::ClCollPoint point, n_com::IF_CASE_WHICH if_case);
//		//矩形と矩形
//		BOOL IsStay(ClCollRect rect);		//当たり判定がその中に入ったか
//		BOOL IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case);		//当たり判定がその中に入ったか
//		//デバック描画
//		VOID DrawDebug();
//		VOID DrawDebug(unsigned int color);
//		VOID DrawDebug(unsigned int color, int thick);
//
//
//	private:
//		//		メンバ関数
//		//BOOL MmIsCollPointEqualOut(n_coll_point::ClCollPoint point);
//		//BOOL MmIsCollPointEqualIn(n_coll_point::ClCollPoint point);
//		BOOL MmIsCollRectEqualOut(ClCollRect rect);
//		BOOL MmIsCollRectEqualIn(ClCollRect rect);
//
//		//		メンバ変数
//		n_rect::ClRect m_coll;	//当たり判定範囲
//		BOOL m_is_coll;			//当たり判定を動作させるか
//	};
//
//}