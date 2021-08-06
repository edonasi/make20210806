#pragma once

//元々のキーの数
#define DEFAULT_KEY_NUM 256
#define KEY_TIME_INPUT_NUM 5

namespace n_keyboard{
	//キーボードの入力を管理する
	class ClKeyboard{
		//*----------------------------------------------------------------------------*
		//							publicここから
		//*----------------------------------------------------------------------------*

	public:
		//		シングルトン実装		
		//インスタンス取得(初めて参照するときはインスタンスを生成)
		static ClKeyboard* GetIns();
		//オブジェクトの破棄
		VOID Destroy();

		//キー入力状態を更新する
		int GpUpdateKey();
		//キーの入力時間を返す
		int GetKeyCnt(int key_input_);
		//キーが押されている状態か(押されている状態ならTRUE)
		BOOL GetIsKey(int key_input_);
		//キーが押された瞬間か(押された瞬間ならTRUE)
		BOOL GetIsKeyDown(int key_input_);
		//キーが離された瞬間か(離された瞬間ならTRUE)
		BOOL GetIsKeyUp(int key_input_);
		//キーを離している状態か(離されているならTRUE)
		BOOL GetIsKeyAway(int key_input_);
		//指定時間押されたか
		BOOL GetIsKeyTimeInput(int key_input_, float time);
		//指定時間(ミリ秒)(を超えた / 以上 / と同等 / 以下 / 未満)キーが押されたか(基本：を超えた)
		BOOL GetIsKeyTimeInput(int key_input_, float time, n_com::IF_CASE_TYPE key_case_type);

		//*----------------------------------------------------------------------------*
		//							privateここから
		//*----------------------------------------------------------------------------*


	private:
		//		シングルトン実装
		//シングルトンなインスタンス
		static ClKeyboard* m_ins;
		//コンストラクタ、キーの状態を初期化
		ClKeyboard();
		//コピーコンストラクタ
		ClKeyboard(const ClKeyboard& src);
		ClKeyboard& operator=(const ClKeyboard& src);

		//デストラクタ
		virtual ~ClKeyboard();

		//キーが押されているフレーム数を格納する
		int m_key_cnt[DEFAULT_KEY_NUM];
		//時間指定処理のときにTRUE判定後か(2重判定にならないようにする)
		BOOL m_is_time_input_after[DEFAULT_KEY_NUM][KEY_TIME_INPUT_NUM];
	};
}