//*--------------------------------------------------------------------------------*
//								Windowの初期化を行う
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		ネーム
using namespace n_xy;

//*--------------------------------------------------------------------------------*
//								コンストラクタここから
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		Windowの初期設定const変数
//*------------------------------------------------*

//ゲームタイトル
const string GAME_TITLE = "ゲームタイトル";
//ゲームの縦横幅、解像度
const int GAME_HEIGHT = 720;
const int GAME_WIDTH = 1280;
const int GAME_COLOR = 32;
//ゲームの背景色(red,green,blue)
const int GANE_WINDOW_RED = 0;
const int GANE_WINDOW_GREEN = 0;
const int GANE_WINDOW_BLUE = 0;
//ウィンドウバーの状態
const unsigned char GANE_WINDOW_BAR = 0;
//ゲームのアイコンのID
//const int GAME_ICON_ID = 333;
//デバックモード
const BOOL IS_GAME_DEBUG = TRUE;

//*------------------------------------------------*

//*------------------------------------------------*
//		コンストラクタ
//*------------------------------------------------*

ClWin::ClWin() {
	MmSetBackColorType();	//背景色の種類を設定
	m_size = ClXY(GAME_WIDTH, GAME_HEIGHT);
	return; 
}

//*------------------------------------------------*
//		背景色の種類を設定
//*------------------------------------------------*

const int BLACK_LIGHTNESS = 0;	//黒色の明度
const int WHITE_LIGHTNESS = 255;//白色の明度

//背景色の種類を設定
VOID ClWin::MmSetBackColorType() {
	//背景色の種類を黒に設定
	if (MmIsNoChroma(BLACK_LIGHTNESS) == TRUE) {
		M_BACK_COLOR_TYPE = BACK_COLOR_TYPE::BLACK; return;
	}
	//背景色の種類を白に設定
	else if (MmIsNoChroma(WHITE_LIGHTNESS) == TRUE) {
		M_BACK_COLOR_TYPE = BACK_COLOR_TYPE::WHITE; return;
	}
	//背景色の種類をその他に設定
	else {
		M_BACK_COLOR_TYPE = BACK_COLOR_TYPE::OTHER; return;
	}
}

/// <summary>
/// 背景色が指定した明度の無彩色かどうか
/// </summary>
/// <param name="lightness">明度</param>
/// <returns>TRUEなら指定した明度の無彩色</returns>
BOOL ClWin::MmIsNoChroma(int lightness) {
	if (GANE_WINDOW_RED != lightness) { return FALSE; }
	if (GANE_WINDOW_GREEN != lightness) { return FALSE; }
	if (GANE_WINDOW_BLUE != lightness) { return FALSE; }

	return TRUE;
}

//*------------------------------------------------*
//		デストラクタ
//*------------------------------------------------*

ClWin::~ClWin() { return; }

//*------------------------------------------------*
//		プロパティ
//*------------------------------------------------*

//左上端を取得
ClXY ClWin::GetWinPivot() { return m_size.GetPivot(); }

//指定した枢軸の座標を取得
ClXY ClWin::GetWinPivot(n_xy::PIVOT pivot) { return m_size.GetPivot(pivot); }

//枢軸Xサイズ取得
int ClWin::GetWinPivotX(n_xy::ONE_PIVOT pivot_x) { return m_size.GetPivotX(pivot_x); }

//枢軸Yサイズ取得
int ClWin::GetWinPivotY(n_xy::ONE_PIVOT pivot_y) { return m_size.GetPivotY(pivot_y); }

//ゲームの縦幅を参照する
int ClWin::GetWinHeight() { return GAME_HEIGHT; }

//ゲームの横幅を参照する
int ClWin::GetWinWidth() { return GAME_WIDTH; }

//画面のサイズを取得
ClXY ClWin::GetWinSize() { return m_size; }

//ゲームの解像度を参照する
int ClWin::GetWinColor() { return GAME_COLOR; }

//デバックモードか	参照
BOOL ClWin::GetIsDebug() { return IS_GAME_DEBUG; }

//背景色の種類を参照
BACK_COLOR_TYPE ClWin::GetBackColorType() { return M_BACK_COLOR_TYPE; }

//*--------------------------------------------------------------------------------*
//								関数ここから
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		DXライブラリの初期化
//*------------------------------------------------*

///<summary >
	/// Init前のゲーム初期化
	///</summary >
VOID ClWin::BeforeInit() {

	//Log.txtを出力しない(GitHubで管理するため、現在必要ない)
	SetOutApplicationLogValidFlag(FALSE);
	//ウィンドウモードに設定
	ChangeWindowMode(TRUE);
	//ゲームタイトルの設定
	SetMainWindowText(GAME_TITLE.c_str());
	//ゲームウィンドウ解像度設定
	SetGraphMode(GetWinWidth(), GetWinHeight(), GAME_COLOR);
	//ウィンドウのサイズを設定
	SetWindowSize(GAME_WIDTH, GAME_HEIGHT);
	//背景色の設定
	SetBackgroundColor(
		GANE_WINDOW_RED,
		GANE_WINDOW_GREEN,
		GANE_WINDOW_BLUE
	);
	//ゲームのICONを設定
	//SetWindowIconID(GAME_ICON_ID);
	//ウィンドウバーの状態
	SetWindowStyleMode(GANE_WINDOW_BAR);
	//ウィンドウの垂直同期を有効にする(ディスプレイの能力を制限して、フレームレート(fps)を一定に保つ)=FALSEはフレームレートを管理しなければならない
	SetWaitVSyncFlag(TRUE);
	//非アクティブでも実行する
	SetAlwaysRunFlag(TRUE);
}

/// <summary>
/// ゲームの初期化
/// </summary>
/// <returns>エラーが起きたら-1</returns>
int ClWin::Init() {

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		// エラーが起きたら直ちに終了
		return -1;
	}

	//エラーではないなら終了させない
	return 0;
}

/// <summary>
/// Init後のゲーム初期化
/// </summary>
VOID ClWin::AfterInit() {

	//ダブルバッファリング有効化
	SetDrawScreen(DX_SCREEN_BACK);
}

