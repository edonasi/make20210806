#pragma once

#include COLL_HPP

#include XY_HPP
//当たり判定範囲に使用
#include RECT_HPP
#include CIRCLE_HPP

namespace n_coll_circle {
	class ClCollCircle:public n_coll::ClColl{
	public:
		ClCollCircle();
		~ClCollCircle();

		//		プロパティ
		int GetRadius();
		n_circle::ClCircle GetColl();		//当たり判定範囲を参照
		VOID SetColl(int x, int y, int radius);//当たり判定範囲を設定(is_coll=FALSEでも可能)

		//		関数
		VOID Update(int x, int y);		//当たり判定を更新
		//円と点
		BOOL IsStay(n_xy::ClXY point);
		//BOOL IsStay(n_coll_point::ClCollPoint point, n_com::IF_CASE_WHICH if_case);
		//円と矩形
		BOOL IsStay(n_rect::ClRect rect);		//当たり判定がその中に入ったか
		//BOOL IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case);		//当たり判定がその中に入ったか
		//円と円
		BOOL IsStay(n_circle::ClCircle circle);
		//デバック描画
		VOID DrawDebug();
		VOID DrawDebug(unsigned int color);
		VOID DrawDebug(unsigned int color, int thick);

	private:
		//		メンバ変数
		n_circle::ClCircle m_coll;
	};

	
}