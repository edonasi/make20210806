#pragma once

namespace n_cnt {

	//		enum
		//カウントの仕方
	enum CNT_AFTER_TYPE {
		STOP,		//最大値まで行ったら0に初期化して停止する
		LOOP,			//最大値まで行ったら最初に戻ってカウント
	};

	//配列要素カウンタ、秒数でカウンタ加算(※ループを何回もすると秒数がずれるので注意)
	class ClCntArySec{
		//*----------------------------------------------------------------------------*
		//							publicここから
		//*----------------------------------------------------------------------------*
	public:
		//		コンストラクタ、デストラクタ、変数の初期化
		ClCntArySec();
		~ClCntArySec();

		//		プロパティ
		BOOL GetIsOver();		//最大値を超えたか
		BOOL GetIsStop();		//カウンタがストップしたか
		int GetIndex();			//カウンタ取得
		int GetReverseIndex();	//反転したカウンタを取得
		VOID SetIsStop();		//カウンタを停止させる
		VOID SetCnt();			//カウンタと現在の秒数を初期化
		VOID SetCnt(			//カウンタの設定
			int cnt_size, float all_sec, n_cnt::CNT_AFTER_TYPE after_type);

		//		関数
		VOID Proc();			//カウンタの更新

		//*----------------------------------------------------------------------------*
		//							privateここから
		//*----------------------------------------------------------------------------*
	private:
		//		メンバ関数
		BOOL MmIsIndexOver();		//要素数が最大数を超えたか
		float MmGetTimerSub();		//タイマー開始からの時間
		float MmGetTimerSecSub();	//毎秒毎経過時間
		VOID MmSetCnt();			//カウンタと開始時間を初期化

		//		メンバ変数
		BOOL m_is_over;				//最大値を超えたか
		BOOL m_is_stop;				//カウントを停止するか
		n_cnt::CNT_AFTER_TYPE m_after_type;
		int m_index;				//現在のカウンタ
		int m_index_max;			//カウンタの最大値
		float m_timer_start;		//計測開始地点
		float m_timer_sec_start;	//秒数毎開始地点
		float m_timer;				//現在の計測時間
		float m_sec_all;			//カウント0までにかかる時間
		float m_sec_max;			//秒数毎値
	};

	
}
