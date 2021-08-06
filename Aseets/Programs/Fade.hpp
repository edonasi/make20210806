#pragma once

//ヘッダファイルインクルード
#include CNT_HPP

namespace n_fade {
	//		enum
	enum FADE_TYPE {
		FADE_UP_DOWN_TYPE,
		FADE_DOWN_UP_TYPE,
		FADE_UP_TYPE,
		FADE_DOWN_TYPE,
	};
	//フェードの状態
	enum FADE_STATE {
		NONE,
		FADE_UP,
		FADE_DOWN
	};

	//フェードダウンフェードアップのインンスタンス
	class ClFade{
		//*----------------------------------------------------------------------------*
		//							publicここから
		//*----------------------------------------------------------------------------*

	public:
		//		コンストラクタ、デストラクタ、変数の初期化
		ClFade();
		~ClFade();

		//		プロパティ
		FADE_TYPE GetFadeType();	//フェードの種類
		BOOL GetIsFadeNone();		//フェードを行っていないか
		BOOL GetIsFadeStop();		//フェードが終了したか
		float GetFadeDecimalPar();	//フェードの割合(0.0f～1.0f)

		//		関数
		//開始処理
		VOID FadeUpDownStart(float all_time);	//フェードアップダウン
		VOID FadeDownUpStart(float all_time);	//フェードダウンアップ
		VOID FadeUpStart(float all_time);		//フェードアップ
		VOID FadeDownStart(float all_time);		//フェードダウン
		//update処理
		VOID FadeProc();		//更新処理
		//フェード描画
		VOID FadeSameDraw();	
		VOID FadeBlackDraw();	
		VOID FadeWhiteDraw();	
		

		//*----------------------------------------------------------------------------*
		//							privateここから
		//*----------------------------------------------------------------------------*

	private:
		//		メンバ関数
		VOID MmFadeDraw(unsigned int color);	//フェード描画

		//		メンバ変数
		BOOL m_is_start;			//開始したか
		BOOL m_next_in;				//次はフェードダウンするか
		FADE_TYPE m_fade_type;		//フェードの種類
		FADE_STATE m_fade_state;	//フェードの状態
		n_cnt::ClCntArySec m_cnt;	//カウンタ
	};
}
