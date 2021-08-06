#pragma once

//		インクルードファイル
//XY使用
#include XY_HPP

namespace n_circle {
	//丸
	class ClCircle{
	public:
		//		コンストラクタ
		ClCircle();
		~ClCircle();

		//		プロパティ
		VOID SetPos(int x,int y);
		VOID SetRadius(int radius_in);
		VOID SetCircle(int x,int y,int radius_in);

		//		変数
		n_xy::ClXY center;
		int radius;
	};
}