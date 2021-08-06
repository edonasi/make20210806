#pragma once

//PIVOT時に使用
#include XY_HPP

namespace n_rect {
	//矩形
	class ClRect{
	public:
		//コンストラクタ
		ClRect();
		~ClRect();

		//プロパティ
		n_xy::ClXY GetPivot(n_xy::PIVOT pivot);
		VOID SetRect(int left_in, int top_in, int right_in, int bottom_in);

		//		変数
		int left;
		int top;
		int right;
		int bottom;
	};
}