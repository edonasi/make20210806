//*--------------------------------------------------------------------------------*
//								映像管理クラス
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*

//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include MOVIE_HPP
using namespace n_movie;

//*--------------------------------------------------------------------------------*
//								コンストラクタ
//*--------------------------------------------------------------------------------*

const int START_TIME = 0;	//再生地点の最初の地点

ClMovie::ClMovie(){
	m_time = START_TIME;
}
ClMovie::~ClMovie() { return; }

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

const int MOVIE_STATE_STOP = 0;	//映像が再生中のとき

//映像を描画
VOID ClMovie::Draw() {
	//描画フラグが立っていないなら描画しない
	if (m_is_draw == FALSE) { return; }

	//再生されていないなら開始時間を0にする
	if (GetMovieStateToGraph(m_handle) == MOVIE_STATE_STOP) {
		//再生地点を最初に戻す
		SeekMovieToGraph(m_handle, START_TIME);
		PlayMovieToGraph(m_handle);
	}

	//動画を描画
	DrawGraph(m_pos.x, m_pos.y, m_handle, TRUE);
}	

//画面サイズに合わせて描画
VOID ClMovie::WinDraw() {
	//描画フラグが立っていないなら描画しない
	if (m_is_draw == FALSE) { return; }

	//再生されていないなら開始時間を0にする
	if (GetMovieStateToGraph(m_handle) == MOVIE_STATE_STOP) {
		//再生地点を最初に戻す
		SeekMovieToGraph(m_handle, START_TIME);
		PlayMovieToGraph(m_handle);
	}

	//動画を描画
	DrawExtendGraph(
		ClWin().GetWinPivot().x, ClWin().GetWinPivot().y,
		ClWin().GetWinWidth(), ClWin().GetWinHeight(),
		m_handle, TRUE);
}

/// <summary>
/// 画像読み込み共通関数
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="cpp_name">cpp名_引数</param>
/// <param name="ins_name">インスタンス名_引数</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClMovie::MmLoad(string path, string cpp_name, string ins_name) {
	//画像の読み込み
	string all_path = ClCom().GetMoviesPath() + path;
	m_handle = LoadGraph(all_path.c_str());
	m_path = all_path;						//パスをコピー

	//読み込み失敗
	if (m_handle == ClCom().GetHandleError()) {
		//エラーメッセージ
		string error_meg
			= cpp_name + ".cpp : " + ins_name + " : " + "映像読み込みエラー";

		MessageBox(
			GetMainWindowHandle(), all_path.c_str(),
			error_meg.c_str(), MB_OK
		);
		return FALSE;
	}

	//画像の幅と高さを取得
	GetGraphSize(m_handle, &m_size.x, &m_size.y);

	return TRUE;	//読み込み成功
}


