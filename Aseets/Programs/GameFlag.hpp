#pragma once

namespace n_game_flag{
	//ゲーム続行のフラグを管理する
	class ClGameFlag{
		//*----------------------------------------------------------------------------*
		//							publicここから
		//*----------------------------------------------------------------------------*

	public:
		//		シングルトン実装
		//インスタンス取得(初めて参照するときはインスタンスを生成)
		static ClGameFlag* GetIns();
		//オブジェクトの破棄
		VOID Destroy();

		//		プロパティここから
		//ゲーム続行のフラグをおろす
		VOID SetEndPlay();
		//ゲームを行っているのか参照する
		BOOL GetIsPlay();

		//*----------------------------------------------------------------------------*
		//							privateここから
		//*----------------------------------------------------------------------------*

	private:
		//		シングルトン実装
		//シングルトンなインスタンス
		static ClGameFlag* m_ins;
		//コンストラクタ、初期化
		ClGameFlag();
		//コピーコンストラクタ
		ClGameFlag(const ClGameFlag& src);
		ClGameFlag& operator=(const ClGameFlag& src);
		//デストラクタ、オブジェクトの破棄
		virtual ~ClGameFlag();

		//		メンバ変数ここから
		//ゲームを行っているか
		BOOL m_is_play;
	};
}