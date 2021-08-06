//*--------------------------------------------------------------------------------*
//								共通して使う変数や処理を扱う
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"

//*--------------------------------------------------------------------------------*
//								コンストラクタここから
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		Comクラス
//*------------------------------------------------*

ClCom::ClCom() { return; }
ClCom::~ClCom() { return; }

//*--------------------------------------------------------------------------------*
//								プロパティここから
//*--------------------------------------------------------------------------------*

//virtualの関数を外部などで使用されたときエラーメッセージを出す
VOID ClCom::VirtualError() {
	//エラーメッセージ
	string error_title = "virtual使用禁止";
	string error_msg = "外部使用を禁止するため使用できません";

	MessageBox(
		GetMainWindowHandle(), error_msg.c_str(),
		error_title.c_str(), MB_OK
	);
}

//*------------------------------------------------*
//		0～255の最大値、中間値、最小値
//*------------------------------------------------*

//0～255の最大値(255)
int ClCom::GetUnCharMax() { return 255; }

//0～255の最大値(128)
int ClCom::GetUnCharHalf() { return 128; }

//0～255の最大値(0)
int ClCom::GetUnCharMin() { return 0; }

//*------------------------------------------------*
//		累乗
//*------------------------------------------------*

/// <summary>
/// 2の正の累乗を得る(※指数がマイナスのときは 1 になる)
/// </summary>
/// <param name="index">指数</param>
/// <returns>2の(指数)乗</returns>
int ClCom::GetPowerNumPlas(int index) {
	int num = 1;
	if (index <= 0) { return num; }	//指数が0なら1

	//2の累乗を計算
	int radix2 = 2;	//2の基数
	for (int i = 0; i < index; i++) {
		num *= radix2;
	}
	return num;
}

/// <summary>
/// radixの正の累乗を得る
/// </summary>
/// <param name="radix">基数</param>
/// <param name="index">指数</param>
/// <returns>radixの累乗</returns>
int ClCom::GetPowerNumPlas(int radix, int index) {
	int num = 1;
	if (index <= 0) { return num; }	//指数が0なら1

	//累乗を計算
	for (int i = 0; i < index; i++) {
		num *= radix;
	}
	return num;
}

//*------------------------------------------------*
//		秒数ミリ
//*------------------------------------------------*

//1秒は1000ミリ秒
int ClCom::GetMilliMult() { return 1000; }

//*------------------------------------------------*
//		色
//*------------------------------------------------*

//色の調整値
const int MIN_COLOR = 0;
const int HALF_COLOR = 128;
const int MAX_COLOR = 255;

//黒色
unsigned int ClCom::GetBlack() {
	return GetColor(MIN_COLOR, MIN_COLOR, MIN_COLOR);
}

//灰色
unsigned int ClCom::GetGray() {
	return GetColor(HALF_COLOR, HALF_COLOR, HALF_COLOR);
}

//白色
unsigned int ClCom::GetWhite() {
	return GetColor(MAX_COLOR, MAX_COLOR, MAX_COLOR);
}

//背景色と同じ
unsigned int ClCom::GetSameColor() {
	switch (ClWin().GetBackColorType()){
		//背景色が黒なら黒に設定
	case n_win::BACK_COLOR_TYPE::BLACK:
		return GetColor(MIN_COLOR, MIN_COLOR, MIN_COLOR);
		break;

		//背景色が白なら白に設定
	case n_win::BACK_COLOR_TYPE::WHITE:
		return GetColor(MAX_COLOR, MAX_COLOR, MAX_COLOR);
		break;

		//デフォルトは白
	default:
		return GetColor(MAX_COLOR, MAX_COLOR, MAX_COLOR);
		break;
	}

	return GetColor(MAX_COLOR, MAX_COLOR, MAX_COLOR);
}

//背景色と反対色
unsigned int ClCom::GetFlipColor() {

	switch (ClWin().GetBackColorType()){
		//背景色が黒なら白に設定
		case n_win::BACK_COLOR_TYPE::BLACK:
			return GetColor(MAX_COLOR, MAX_COLOR, MAX_COLOR);
			break;

		//背景色が白なら黒に設定
		case n_win::BACK_COLOR_TYPE::WHITE:
			return GetColor(MIN_COLOR, MIN_COLOR, MIN_COLOR);
			break;

		//デフォルトは黒
		default:
			return GetColor(MIN_COLOR, MIN_COLOR, MIN_COLOR);
			break;
	}

	return GetColor(MIN_COLOR, MIN_COLOR, MIN_COLOR);
}

//赤色
unsigned int ClCom::GetRed() {
	return GetColor(MAX_COLOR, MIN_COLOR, MIN_COLOR);
}

//緑色
unsigned int ClCom::GetGreen() {
	return GetColor(MIN_COLOR, MAX_COLOR, MIN_COLOR);
}

//青色
unsigned int ClCom::GetBlue() {
	return GetColor(MIN_COLOR, MIN_COLOR, MAX_COLOR);
}

//黄色
unsigned int ClCom::GetYellow() {
	return GetColor(MAX_COLOR, MAX_COLOR, MIN_COLOR);
}

//シアン
unsigned int ClCom::GetCyan() {
	return GetColor(MIN_COLOR, MAX_COLOR, MAX_COLOR);
}

//マゼンダ
unsigned int ClCom::GetMagenta() {
	return GetColor(MAX_COLOR, MIN_COLOR, MAX_COLOR);
}

//橙色
unsigned int ClCom::GetOrange() {
	return GetColor(MAX_COLOR, HALF_COLOR, MIN_COLOR);
}

//黄緑
unsigned int ClCom::GetYellowGreen() {
	return GetColor(HALF_COLOR, MAX_COLOR, MIN_COLOR);
}

//青緑
unsigned int ClCom::GetBlueGreen() {
	return GetColor(MIN_COLOR, MAX_COLOR, HALF_COLOR);
}

//空色
unsigned int ClCom::GetSkyColor() {
	return GetColor(MIN_COLOR, HALF_COLOR, MAX_COLOR);
}

//赤紫
unsigned int ClCom::GetRedPurple() {
	return GetColor(MAX_COLOR, MIN_COLOR, HALF_COLOR);
}

//青紫
unsigned int ClCom::GetBluePurple() {
	return GetColor(HALF_COLOR, MIN_COLOR, MAX_COLOR);
}

//*------------------------------------------------*
//		ハンドルのエラー値
//*------------------------------------------------*

/// <summary>
/// ハンドルのエラー値(-1)
/// </summary>
/// <returns>-1</returns>
int ClCom::GetHandleError() { return -1; }

//*------------------------------------------------*
//		ファイルパス
//*------------------------------------------------*

//.\\Aseets/
string ClCom::GetAseetsPath() { return ".\\Aseets/"; }

//.\\Aseets/Audios/
string ClCom::GetAudiosPath() { return GetAseetsPath() + "Audios/"; }

//.\\Aseets/Images/
string ClCom::GetImagesPath() { return GetAseetsPath() + "Images/"; }

//.\\Aseets/Movies/
string ClCom::GetMoviesPath() { return GetAseetsPath() + "Movies/"; }

//*------------------------------------------------*
//		デフォルトのフォントサイズ
//*------------------------------------------------*

//デフォルトのフォントサイズ(16)
int ClCom::GetDefalutFontSize() { return 16; }
