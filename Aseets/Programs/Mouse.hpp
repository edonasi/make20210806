#pragma once

//		インクルードファイル
//XY使用
#include XY_HPP

//元々のキーの数
#define MOUSE_BUTTON_CODE 129
#define BUTTON_TIME_INPUT_NUM 5

namespace n_mouse{
	//キーボードの入力を管理する
	class ClMouse{
		//*----------------------------------------------------------------------------*
		//							publicここから
		//*----------------------------------------------------------------------------*

	public:
		//		シングルトン実装		
		//インスタンス取得(初めて参照するときはインスタンスを生成)
		static ClMouse* GetIns();
		//オブジェクトの破棄
		VOID Destroy();

		//		プロパティ
		n_xy::ClXY GetPos();

		//		関数
		//*------------------------------------------------*
		//		マウスの更新
		//*------------------------------------------------*
		int MouseUpdate();		//マウスの更新
		//*------------------------------------------------*
		//		当たり判定なしクリック判定
		//*------------------------------------------------*
		//ボタンの入力時間を返す
		int GetButtonCnt(int mouse_input_);
		//ボタンが押されている状態か(押されている状態ならTRUE)
		BOOL GetIsButton(int mouse_input_);
		//ボタンが押された瞬間か(押された瞬間ならTRUE)
		BOOL GetIsButtonDown(int mouse_input_);
		//ボタンが離された瞬間か(離された瞬間ならTRUE)
		BOOL GetIsButtonUp(int mouse_input_);
		//ボタンを離している状態か(離されているならTRUE)
		BOOL GetIsButtonAway(int mouse_input_);
		//指定時間押されたか
		BOOL GetIsButtonTimeInput(int mouse_input_, float time);
		//指定時間(ミリ秒)(を超えた / 以上 / と同等 / 以下 / 未満)ボタンが押されたか(基本：を超えた)
		BOOL GetIsButtonTimeInput(int mouse_input_, float time, n_com::IF_CASE_TYPE mouse_case_type);
		//*------------------------------------------------*
		//		デバック
		//*------------------------------------------------*
		VOID MousePosDraw();	//マウスの位置情報を描画する

		//*----------------------------------------------------------------------------*
		//							privateここから
		//*----------------------------------------------------------------------------*

	private:
		//		シングルトン実装
		//シングルトンなインスタンス
		static ClMouse* m_ins;
		//コンストラクタ、キーの状態を初期化
		ClMouse();
		//コピーコンストラクタ
		ClMouse(const ClMouse& src);
		ClMouse& operator=(const ClMouse& src);
		//デストラクタ
		virtual ~ClMouse();

		//		メンバ変数
		int m_input_value;		//GetMouseInputの値
		int m_wheel_value;		//マウスホイールの回転量(奥＋　手前－)
		n_xy::ClXY m_point;		//プレイ画面上のマウスの位置
		int m_button[MOUSE_BUTTON_CODE];	//マウスカウンタ
		//指定秒数押された判定後か
		BOOL m_is_time_input_button_after[MOUSE_BUTTON_CODE][BUTTON_TIME_INPUT_NUM];

		//		関数
		//マウスコードに対応したボタンが押されているかチェック
		VOID MmMouseCheck(int mouse_input_);	
	};
}