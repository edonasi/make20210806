//*--------------------------------------------------------------------------------*
//								カウンタ
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include CNT_HPP
using namespace n_cnt;

//*--------------------------------------------------------------------------------*
//								全体で使う定数
//*--------------------------------------------------------------------------------*

const int CNT_MIN = 0;			//カウンタの初期変数
const int CNT_ADD = 1;			//カウンタ加算変数
const float SEC_MIN = 0.0f;		//タイマーの初期変数

//*--------------------------------------------------------------------------------*
//								コンストラクタ、デストラクタ、変数の初期化
//*--------------------------------------------------------------------------------*

ClCntArySec::ClCntArySec(){
	//すべて初期化
	m_is_over = FALSE;
	m_is_stop = FALSE;
	m_after_type = n_cnt::CNT_AFTER_TYPE::STOP;
	m_index = CNT_MIN;
	m_index_max = CNT_MIN;
	m_timer_start = SEC_MIN;
	m_timer_sec_start = SEC_MIN;
	m_timer = SEC_MIN;
	m_sec_all = SEC_MIN;
	m_sec_max = SEC_MIN;
}

ClCntArySec::~ClCntArySec() { return; }

//*--------------------------------------------------------------------------------*
//								プロパティ
//*--------------------------------------------------------------------------------*

const int INDEX_OVER_BLOCK = 1;	//配列あふれを防ぐ

//最大値まで行ったか返す
BOOL ClCntArySec::GetIsOver() { return m_is_over; }	

//カウンタがストップしたか
BOOL ClCntArySec::GetIsStop() { return m_is_stop; }

//現在のカウンタ(配列要素数)を返す
int ClCntArySec::GetIndex() { return m_index >= m_index_max == TRUE ? m_index_max - INDEX_OVER_BLOCK : m_index; }

//現在の反対のカウンタ(配列要素数)を返す
int ClCntArySec::GetReverseIndex() { return m_index_max - m_index - INDEX_OVER_BLOCK; }

//タイマー開始からの時間
float ClCntArySec::MmGetTimerSub() { return m_timer - m_timer_start; }

//毎秒毎経過時間
float ClCntArySec::MmGetTimerSecSub() { return m_timer - m_timer_sec_start; }

//カウンタを停止させる
VOID ClCntArySec::SetIsStop() {
	m_is_stop = TRUE;
	m_is_over = FALSE;
	m_index = CNT_MIN;
	m_timer_start = SEC_MIN;
	m_timer_sec_start = SEC_MIN;
	m_timer = SEC_MIN;
}

//カウンタと現在の秒数を初期化
VOID ClCntArySec::SetCnt() {
	//max系以外初期化
	m_is_over = FALSE;
	m_is_stop = FALSE;
	m_index = CNT_MIN;
	m_timer_start = SEC_MIN;
	m_timer_sec_start = SEC_MIN;
	m_timer = SEC_MIN;
}		

/// <summary>
/// カウンタを設定、初期化
/// </summary>
/// <param name="cnt_size">配列の要素数(例：a[5]ならSetCnt(5, , )と入力)</param>
/// <param name="all_sec">カウント0までかかる時間(秒)</param>
/// <param name="after_type">カウント0到達後の挙動</param>
VOID ClCntArySec::SetCnt(int cnt_size, float all_sec, n_cnt::CNT_AFTER_TYPE after_type) {
	//すべて初期化
	m_is_over = FALSE;
	m_is_stop = FALSE;
	m_after_type = after_type;
	m_index = CNT_MIN;
	m_index_max = cnt_size;
	m_timer_start = SEC_MIN;
	m_timer_sec_start = SEC_MIN;
	m_timer = SEC_MIN;
	m_sec_all = all_sec;
	m_sec_max = all_sec / static_cast<float>(cnt_size);
}

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

//カウンタの更新(この関数は1つしか使わないこと)
VOID ClCntArySec::Proc() {
	//停止後はカウントをストップ
	if (m_is_stop == TRUE) { m_is_over = FALSE; return; }

	//カウンタ最大値まで行ったフラグを初期化
	if (m_is_over == TRUE) { m_is_over = FALSE; }

	//タイマーの加算
	m_timer += ClFps::GetIns()->GetDeltaTime();

	//カウンタの更新
	if (MmGetTimerSecSub() >= m_sec_max && m_index < m_index_max) {
		m_index = static_cast<int>(
			static_cast<float>(m_index_max - INDEX_OVER_BLOCK) * (MmGetTimerSub() / m_sec_all)
			) + INDEX_OVER_BLOCK;
		m_timer_sec_start = m_timer;
	}

	//カウンタ最大値まで行った
	if (MmIsIndexOver() == TRUE) { m_is_over = TRUE; }

	//カウンタが最大値まで行った後の処理
	if (m_is_over == FALSE) { return; }
	switch (m_after_type){
		//カウンタと開始時間を初期化
	case n_cnt::LOOP:MmSetCnt(); break;

		//処理を停止させるフラグを立てる
	default:m_is_stop = TRUE; break;
	}
}


//要素数が最大数を超えたか
BOOL ClCntArySec::MmIsIndexOver() { return m_index >= m_index_max ? TRUE : FALSE; }

const float TIMER_MAX = 1.70141183460469E+38f;	//timerがfloatの最大値を超えないようにする対策

//カウンタと開始時間を初期化
VOID ClCntArySec::MmSetCnt() {
	m_index = CNT_MIN;
	if (m_timer > TIMER_MAX) { m_timer = SEC_MIN; }
	m_timer_start = m_timer;
	m_timer_sec_start = m_timer;
}

