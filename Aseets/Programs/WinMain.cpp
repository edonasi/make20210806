//*--------------------------------------------------------------------------------*
//								メイン処理
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								参考サイト
//*--------------------------------------------------------------------------------*
//・新・Ｃ言語～ゲームプログラミングの館[ＤＸライブラリ]
//https://dixq.net/g/
//・ＤＸライブラリ関数リファレンスページ
//https://dxlib.xsrv.jp/dxfunc.html
//C++におけるオブジェクトの取り扱い方[シングルトン]
//https://www.haljion.net/index.php/2019-11-13-03-27-18/119-2019-11-13-03-22-16/rx-62n/222-c*/

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		Singletonファイル
#include AUDIO_MULT_HPP
using namespace n_audio_mult;
#include KEYBOARD_HPP
using namespace n_keyboard;
#include MOUSE_HPP
using namespace n_mouse;
#include GAME_SCENE_HPP
using namespace n_game_scene;
#include GAME_FLAG_HPP
using namespace n_game_flag;

//*--------------------------------------------------------------------------------*
//								処理
//*--------------------------------------------------------------------------------*

//関数プロトタイプ宣言
VOID WinMainInit();			/// WinMainの初期化
BOOL IsGameWhile();			//ゲーム継続条件
VOID GameWhileDebugDraw();	//ゲームの継続デバック描画
VOID WinMainEnd();			// WinMain終了処理、シングルトンインスタンスを破棄

// プログラムは WinMain から始まります
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//WinMainの初期化
	WinMainInit();

	//ゲーム開始前の処理
	ClGameScene::GetIns()->GameInit();

	//繰り返し処理
	while (IsGameWhile() == TRUE) {
		ClGameScene::GetIns()->GameSceneSwitch();	//ゲームの処理
		GameWhileDebugDraw();						//継続デバック描画
	}

	//WinMain終了処理、シングルトンインスタンスを破棄
	WinMainEnd();

	// ソフトの終了
	return 0;
}

/// <summary>
/// WinMainの初期化
/// </summary>
VOID WinMainInit() {
	ClWin().BeforeInit();
	ClWin().Init();
	ClWin().AfterInit();
}

//ゲームの継続条件
BOOL IsGameWhile() {
	if (ProcessMessage() != 0) { return FALSE; }
	if (ClGameFlag::GetIns()->GetIsPlay() == FALSE) {	//ゲーム続行するか
		return FALSE;
	}
	if (ScreenFlip() != 0) { return FALSE; }			//画面反転
	if (ClearDrawScreen() != 0) { return FALSE; }		//画面の消去
	if (ClKeyboard::GetIns()->GpUpdateKey() != 0) {		//キーの更新
		return FALSE; 
	}
	if (ClMouse::GetIns()->MouseUpdate() != 0) {		//マウスの更新
		return FALSE; 
	}

	ClFps::GetIns()->FpsUpdate();	//fpsの更新
	
	return TRUE;
}

//継続デバック描画
VOID GameWhileDebugDraw() {
	ClFps::GetIns()->FpsDraw();			//fpsの描画
	ClMouse::GetIns()->MousePosDraw();	//マウスの位置情報を描画
}

/// <summary>
/// WinMain終了処理、シングルトンインスタンスを破棄
/// </summary>
VOID WinMainEnd() {
	//ComSingletonクラスを破棄
	ClFps::GetIns()->Destroy();

	//AnySingletonクラスを破棄
	ClAudioMult::GetIns()->Destroy();
	ClKeyboard::GetIns()->Destroy();
	ClMouse::GetIns()->Destroy();
	ClGameFlag::GetIns()->Destroy();
	ClGameScene::GetIns()->Destroy();

	// ＤＸライブラリ使用の終了処理準備(return 0でソフトが終了する)
	DxLib_End();
}