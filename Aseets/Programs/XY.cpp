//*--------------------------------------------------------------------------------*
//								XY関係管理
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include XY_HPP
using namespace n_xy;

//*--------------------------------------------------------------------------------*
//								コンストラクタ、デストラクタ、変数の初期化
//*--------------------------------------------------------------------------------*

const int POS_MIN = 0;	//座標の最小値

//xy(0,0)で初期化
ClXY::ClXY() {
	x = POS_MIN;
	y = POS_MIN;
}
//引数で初期化
ClXY::ClXY(int x_in, int y_in) {
	x = x_in;
	y = y_in;
}
ClXY::~ClXY() { return; }

//*--------------------------------------------------------------------------------*
//								プロパティ
//*--------------------------------------------------------------------------------*

//xを設定
VOID ClXY::SetX(int x_in) { x = x_in; }		

//yを設定
VOID ClXY::SetY(int y_in) { y = y_in; }

//xyを設定
VOID ClXY::SetXY(int x_in, int y_in) {
	x = x_in;
	y = y_in;
}

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

//左上端(0, 0)を取得
ClXY ClXY::GetPivot() {
	ClXY xy = ClXY();
	return xy;
}

/// <summary>
/// 指定した枢軸の座標を取得
/// </summary>
/// <param name="pivot"></param>
/// <returns></returns>
ClXY ClXY::GetPivot(PIVOT pivot) {
	//左上端の座標
	ClXY xy = ClXY();

	//X座標の計算
	switch (pivot){
		//左上端だったら処理終了
	case n_xy::TOP_LEFT:return xy;break;

	case n_xy::TOP_CENTER:
	case n_xy::CENTER_CENTER:
	case n_xy::BUTTOM_CENTER:
		xy.x = x / 2;
		break;

	case n_xy::TOP_RIGHT:
	case n_xy::CENTER_RIGHT:
	case n_xy::BUTTOM_RIGHT:
		xy.x = x;
		break;

	default:break;
	}

	//Y座標の計算
	switch (pivot){
	case n_xy::CENTER_LEFT:
	case n_xy::CENTER_CENTER:
	case n_xy::CENTER_RIGHT:
		xy.y = y / 2;
		break;

	case n_xy::BUTTOM_LEFT:
	case n_xy::BUTTOM_CENTER:
	case n_xy::BUTTOM_RIGHT:
		xy.y = y;
		break;

	default:break;
	}

	return xy;
}



//X座標を取得
int ClXY::GetPivotX(ONE_PIVOT pivot_x) {
	switch (pivot_x){

	case n_xy::HALF:
		return x / 2;
		break;

	case n_xy::MAX:
		return x;
		break;

	default:
		return POS_MIN;
		break;
	}
}

//Y座標を取得
int ClXY::GetPivotY(ONE_PIVOT pivot_y) {
	switch (pivot_y){
	case n_xy::HALF:
		return y / 2;
		break;
	case n_xy::MAX:
		return y;
		break;
	default:
		return POS_MIN;
		break;
	}
}