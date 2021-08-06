#pragma once

namespace n_com {

	//enumを作る基準
	//・そのenumがSingletonのみで使われるかどうか
	//　Singletonでのみ使われるならComで作成可能

	//条件の種類
	enum IF_CASE_TYPE {
		OVER,		//超えた(>)
		ABOVE,		//以上(>=)
		EQUAL,		//同等(==)
		IN_UNDER,	//以下(<=)
		LESS_THAN	//未満(<)
	};

	//条件はどっちか
	enum IF_CASE_WHICH{
		EQUAL_OUT,	//超えた(>),未満(<)
		EQUAL_IN	//以上(>=)、以下(<=)
	};

	//クラスを作る基準
	//・Comファイル以外で作成クラスを戻り値とする
	//　関数を作るかどうか(作る場合はCom以外でクラスを作成する)

	//共通して使う変数や処理を扱う
	class ClCom {

		//*----------------------------------------------------------------------------*
		//							publicここから
		//*----------------------------------------------------------------------------*
	public:
		//コンストラクタ
		ClCom();
		~ClCom();

		//		プロパティここから
		VOID VirtualError();	//virtualの関数を外部などで使用されたときエラーメッセージを出す
		// 0～255の最大値、中間値、最小値
		int GetUnCharMax();	//255
		int GetUnCharHalf();//128
		int GetUnCharMin();	//0
		//累乗
		int GetPowerNumPlas(int index);				//2のindex乗を返す
		int GetPowerNumPlas(int radix, int index);	//radixのindex乗を返す
		//秒数ミリ
		int GetMilliMult();			//1秒は1000ミリ秒
		//色
		unsigned int GetBlack();	//黒色
		unsigned int GetGray();		//灰色
		unsigned int GetWhite();	//白色
		unsigned int GetSameColor();//背景色と同じ色
		unsigned int GetFlipColor();//背景色と反対色
		unsigned int GetRed();		//赤色
		unsigned int GetGreen();	//緑色
		unsigned int GetBlue();		//青色
		unsigned int GetYellow();	//黄色
		unsigned int GetCyan();		//シアン
		unsigned int GetMagenta();	//マゼンダ
		unsigned int GetOrange();	//橙色
		unsigned int GetYellowGreen();//黄緑
		unsigned int GetBlueGreen();//青緑
		unsigned int GetSkyColor();	//空色
		unsigned int GetRedPurple();//赤紫
		unsigned int GetBluePurple();//青紫
		//		ハンドルのエラー値
		int GetHandleError();
		//		ファイルパス
		//.\\Aseets/
		string GetAseetsPath();
		//.\\Aseets/Audios/
		string GetAudiosPath();
		//.\\Aseets/Images/
		string GetImagesPath();
		//.\\Aseets/Movies/
		string GetMoviesPath();
		//デフォルトのフォントサイズ
		int GetDefalutFontSize();

	//*----------------------------------------------------------------------------*
	//							privateここから
	//*----------------------------------------------------------------------------*
	private:
	};
}