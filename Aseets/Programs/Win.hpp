#pragma once
//		インクルードファイル
#include "XY.hpp"	//XYなどを使用

namespace n_win{
	//		enum
	//背景の色の種類
	enum BACK_COLOR_TYPE {
		BLACK,	//黒
		WHITE,	//白
		OTHER	//その他
	};

	//Windowの初期化を行う
	class ClWin{
		//*----------------------------------------------------------------------------*
		//							publicここから
		//*----------------------------------------------------------------------------*

	public:
		//		コンストラクタ
		ClWin();	
		~ClWin();

		//		プロパティここから	
		n_xy::ClXY GetWinPivot();						//左上端を取得
		n_xy::ClXY GetWinPivot(n_xy::PIVOT pivot);	//指定した枢軸の座標を取得
		//片側のpivot取得
		int GetWinPivotX(n_xy::ONE_PIVOT pivot_x);
		int GetWinPivotY(n_xy::ONE_PIVOT pivot_y);
		int GetWinHeight();		//ゲームの縦幅を参照する
		int GetWinWidth();		//ゲームの横幅を参照する
		n_xy::ClXY GetWinSize();	//ゲームの画面サイズを取得
		int GetWinColor();		//ゲームの解像度を参照する
		BOOL GetIsDebug();		//デバックモードか	参照
		BACK_COLOR_TYPE GetBackColorType();//背景色の種類を参照

		//		プロトタイプ宣言ここから
		int Init();					//ゲームの初期化
		VOID BeforeInit();			//Init前のゲーム初期化
		VOID AfterInit();			//Init後のゲーム初期化

	//*----------------------------------------------------------------------------*
	//							privateここから
	//*----------------------------------------------------------------------------*

	private:
		//		メンバ関数
		VOID MmSetBackColorType();			//背景色の種類を設定
		BOOL MmIsNoChroma(int lightness);	//無彩色か
		BACK_COLOR_TYPE M_BACK_COLOR_TYPE;	//背景色の種類

		//		メンバ変数
		n_xy::ClXY m_size;
	};
}