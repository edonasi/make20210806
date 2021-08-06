#pragma once

#include COLL_HPP
//XY使用
#include XY_HPP
//
#include RECT_HPP
#include CIRCLE_HPP


namespace n_coll_point {
	class ClCollPoint:public n_coll::ClColl{
	public:
		ClCollPoint();
		~ClCollPoint();

		//		プロパティ
		n_xy::ClXY GetColl();			//当たり判定位置を参照
		VOID SetColl(int x, int y);		//当たり判定位置を設定(is_coll=FALSEでも可能)

		//		関数
		//当たり判定を更新
		VOID Update(int x, int y);
		//点と点
		BOOL IsStay(n_xy::ClXY point);
		//点と矩形
		BOOL IsStay(n_rect::ClRect rect);
		//点と円
		BOOL IsStay(n_circle::ClCircle circle);
		//BOOL IsStay(n_rect::ClRect rect, n_com::IF_CASE_WHICH if_case);
		//デバック描画
		VOID DrawDebug();
		VOID DrawDebug(unsigned int color);
		VOID DrawDebug(unsigned int color, int thick);

	private:
		//		メンバ変数
		n_xy::ClXY m_coll;		//当たり判定範囲
	};
}

//namespace n_coll_point {
//	//点当たり判定
//	class ClCollPoint {
//	public:
//		//		コンストラクタ
//		ClCollPoint();
//		~ClCollPoint();
//
//		//		プロパティ
//		n_xy::ClXY aGetColl();			//当たり判定位置を参照
//		BOOL aGetIsColl();				//当たり判定が作動しているかを参照
//		VOID aSetColl(int x, int y);		//当たり判定位置を設定(is_coll=FALSEでも可能)
//		VOID aSetIsColl(BOOL is_coll);	//当たり判定を作動させるか
//
//		//		関数
//		//当たり判定を更新
//		VOID aUpdate(int x, int y);
//		//点と点
//		BOOL aIsStay(ClCollPoint point);
//		//点と矩形
//		//BOOL aIsStay(n_coll_rect::ClCollRect rect);
//		//BOOL aIsStay(n_coll_rect::ClCollRect rect, n_com::IF_CASE_WHICH if_case);
//		//デバック描画
//		VOID aDrawDebug();
//		VOID aDrawDebug(unsigned int color);
//		VOID aDrawDebug(unsigned int color, int thick);
//
//	private:
//		//		メンバ関数
//		//BOOL aMmIsCollRectEqualOut(n_coll_rect::ClCollRect rect);
//		//BOOL aMmIsCollRectEqualIn(n_coll_rect::ClCollRect rect);
//
//		//		メンバ変数
//		n_xy::ClXY am_coll;		//当たり判定範囲
//		BOOL am_is_coll;			//当たり判定を動作させるか
//	};
//}