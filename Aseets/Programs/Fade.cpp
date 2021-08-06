//*--------------------------------------------------------------------------------*
//								フェードダウンフェードアップのインンスタンス
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include FADE_HPP
using namespace n_fade;

//*--------------------------------------------------------------------------------*
//								コンストラクタ、デストラクタ、変数の初期化
//*--------------------------------------------------------------------------------*

ClFade::ClFade() {
	m_is_start = FALSE;
	m_next_in = FALSE;
	m_fade_state = FADE_STATE::NONE;
	m_fade_type = FADE_TYPE::FADE_UP_TYPE;
	m_cnt = n_cnt::ClCntArySec();
}
ClFade::~ClFade() { return; }

//*--------------------------------------------------------------------------------*
//								プロパティ
//*--------------------------------------------------------------------------------*

//フェードの種類
FADE_TYPE ClFade::GetFadeType() { return m_fade_type; }	

//フェードを行っていないか
BOOL ClFade::GetIsFadeNone() { return (m_fade_state == n_fade::FADE_STATE::NONE) ? TRUE : FALSE; }

//フェードが終了したか
BOOL ClFade::GetIsFadeStop() { return m_cnt.GetIsStop(); }

const int NUM_256_INDEX = 8;	//256の累乗数

//フェードの割合(0.0f～1.0f)
float ClFade::GetFadeDecimalPar() {
	//現在のカウント
	float index_float;
	switch (m_fade_state){
	case n_fade::FADE_DOWN:
		index_float = static_cast<float>(m_cnt.GetReverseIndex());
		break;
	default:
		index_float = static_cast<float>(m_cnt.GetIndex());
		break;
	}
	//全体のカウント
	float index_all_float = static_cast<float>(ClCom().GetPowerNumPlas(NUM_256_INDEX));
	return index_float / index_all_float;
}

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

const float DIV_HALF = 2.0f;	//フェード(アップ/ダウン)はカウントを2回繰り返すため

/// <summary>
/// フェードアップダウン開始処理
/// </summary>
/// <param name="all_time">フェードアップダウンが完了するまでにかかる時間(秒)</param>
VOID ClFade::FadeUpDownStart(float all_time) {
	if (m_is_start == TRUE) { return; }	//フェードが開始しているなら処理をしない

	m_cnt.SetCnt(ClCom().GetPowerNumPlas(NUM_256_INDEX), all_time / DIV_HALF, n_cnt::CNT_AFTER_TYPE::STOP);
	m_fade_state = FADE_STATE::FADE_UP;
	m_fade_type = FADE_TYPE::FADE_UP_DOWN_TYPE;
	m_next_in = TRUE;
	m_is_start = TRUE;		//開始
}

/// <summary>
/// フェードダウンアップ開始処理
/// </summary>
/// <param name="all_time">フェードダウンアップが完了するまでにかかる時間(秒)</param>
VOID ClFade::FadeDownUpStart(float all_time) {
	if (m_is_start == TRUE) { return; }	//フェードが開始しているなら処理をしない

	m_cnt.SetCnt(ClCom().GetPowerNumPlas(NUM_256_INDEX), all_time / DIV_HALF, n_cnt::CNT_AFTER_TYPE::STOP);
	m_fade_state = FADE_STATE::FADE_DOWN;
	m_fade_type = FADE_TYPE::FADE_DOWN_UP_TYPE;
	m_next_in = TRUE;
	m_is_start = TRUE;		//開始
}

/// <summary>
/// フェードアップ開始処理
/// </summary>
/// <param name="all_time">フェードアップが完了するまでにかかる時間(秒)</param>
VOID ClFade::FadeUpStart(float all_time) {
	if (m_is_start == TRUE) { return; }	//フェードが開始しているなら処理をしない

	m_cnt.SetCnt(ClCom().GetPowerNumPlas(NUM_256_INDEX), all_time, n_cnt::CNT_AFTER_TYPE::STOP);
	m_fade_state = FADE_STATE::FADE_UP;
	m_fade_type = FADE_TYPE::FADE_UP_TYPE;
	m_next_in = FALSE;
	m_is_start = TRUE;		//開始
}

/// <summary>
/// フェードダウン開始処理
/// </summary>
/// <param name="all_time">フェードダウンが完了するまでにかかる時間(秒)</param>
VOID ClFade::FadeDownStart(float all_time) {
	if (m_is_start == TRUE) { return; }	//フェードが開始しているなら処理をしない

	m_cnt.SetCnt(ClCom().GetPowerNumPlas(NUM_256_INDEX), all_time, n_cnt::CNT_AFTER_TYPE::STOP);
	m_fade_state = FADE_STATE::FADE_DOWN;
	m_fade_type = FADE_TYPE::FADE_DOWN_TYPE;
	m_next_in = FALSE;
	m_is_start = TRUE;		//開始
}

//カウンタ更新
VOID ClFade::FadeProc(){
	//開始していないなら処理しない
	if (m_is_start == FALSE) { return; }
		
	//カウンタの更新
	m_cnt.Proc();

	//カウンタが最大になったとき
	if (m_cnt.GetIsOver() == FALSE) { return; }
	switch (m_fade_state){
	case n_fade::FADE_UP:
		//フェードダウンに移行
		if (m_next_in == TRUE) {
			m_next_in = FALSE;
			m_fade_state = n_fade::FADE_STATE::FADE_DOWN;
			m_cnt.SetCnt();
		}
		else {	//終了処理
			m_cnt.SetIsStop();
			m_fade_state = n_fade::FADE_STATE::NONE;
			m_is_start = FALSE;
		}
		break;

		//フェードダウンのときは終了
	case n_fade::FADE_DOWN:
		//フェードアップに移行
		if (m_next_in == TRUE) {
			m_next_in = FALSE;
			m_fade_state = n_fade::FADE_STATE::FADE_UP;
			m_cnt.SetCnt();
		}
		else {	//終了処理
			m_cnt.SetIsStop();
			m_fade_state = n_fade::FADE_STATE::NONE;
			m_is_start = FALSE;
		}
		break;

	default:break;
	}
}

//黒色フェード描画処理
VOID ClFade::FadeSameDraw() { MmFadeDraw(ClCom().GetSameColor()); }

//黒色フェード描画処理
VOID ClFade::FadeBlackDraw() { MmFadeDraw(ClCom().GetBlack()); }

//白色フェード描画処理
VOID ClFade::FadeWhiteDraw() { MmFadeDraw(ClCom().GetWhite()); }

/// <summary>
/// フェード描画共通処理
/// </summary>
/// <param name="color">フェードする色</param>
VOID ClFade::MmFadeDraw(unsigned int color) {
	//開始していないなら処理しない
	if (m_is_start == FALSE) { return; }

	//ブレンドモード設定
	switch (m_fade_state) {
	case n_fade::FADE_UP:
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_cnt.GetIndex());
		break;
	case n_fade::FADE_DOWN:
		SetDrawBlendMode(
			DX_BLENDMODE_ALPHA, m_cnt.GetReverseIndex()
		);
		break;
	default:return; break;
	}

	//画面全体に黒画面を描画
	DrawBox(
		ClWin().GetWinPivot().x, ClWin().GetWinPivot().y,
		ClWin().GetWinWidth(), ClWin().GetWinHeight(),
		color, TRUE
	);
	//ブレンドモード解除
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
