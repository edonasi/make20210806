#pragma once

//		自作ファイル
#include FADE_HPP	//画面切り替え時、フェードを使用

namespace n_game_scene{

	//		enum
	//ゲームシーン
	enum GAME_SCENE {
		LOAD,		//読み込み中
		TITLE,		//タイトル
		PLAY,		//ゲームシーン
	};

	//※シーンを追加したときに必要な追加変数
		// 1.メンバ変数 > シーンそれぞれの進行状況に新規GAME_STATEを追加、コンストラクタで初期化
		// 2.MmSetProcStopState()のswitch追加
		// 3.MmSetSceneState()のswitch追加
		// 4.GameSceneSwitch()のswitch追加
		// 5.メンバ関数 > シーンによっての処理を追加
		// 6.プロパティ > シーン変更処理を追加

	//裏のゲームシーン
	enum BACK_GAME_SCENE {
		NONE,		//特になし
		BACK_LOAD	//裏読み込み中
	};

	//ゲームのシーンを管理
	class ClGameScene{
		//*----------------------------------------------------------------------------*
		//							publicここから
		//*----------------------------------------------------------------------------*

	public:
		//		シングルトン実装
		//インスタンス取得(初めて参照するときはインスタンスを生成)
		static ClGameScene* GetIns();
		//オブジェクトの破棄
		VOID Destroy();

		//		enum
		//シーン進行状況
		enum SCENE_STATE {
			START,
			START_AFTER,
			FADE_DOWN_END,
			FADE_DOWN_END_AFTER,
			FADE_UP_START,
			FADE_UP_START_AFTER,
			END,
			NEXT_SCENE
		};

		//		プロパティ
		VOID ChangeSceneLoad();		//ロードシーンに遷移
		VOID ChangeSceneTitle();	//タイトルシーンに遷移
		VOID ChangeScenePlay();		//プレイシーンに遷移

		//		関数
		VOID GameInit();		//ゲーム開始前の処理
		VOID GameSceneSwitch();		//ゲームのシーンによって処理を分岐

		//*----------------------------------------------------------------------------*
		//							privateここから
		//*----------------------------------------------------------------------------*

	private:
		//		シングルトン実装
		//シングルトンなインスタンス
		static ClGameScene* m_ins;
		//コンストラクタ、初期化
		ClGameScene();
		//コピーコンストラクタ
		ClGameScene(const ClGameScene& src);
		ClGameScene& operator=(const ClGameScene& src);
		//デストラクタ、オブジェクトの破棄
		virtual ~ClGameScene();

		//		メンバ関数
		//シーンによっての処理
		//ロード
		BOOL MmIsLoadProcDo();	//処理を行うか
		VOID MmLoadProc();		//処理
		VOID MmLoadStart();		//シーン開始処理
		VOID MmLoadProcStart();	//処理開始処理
		VOID MmLoadProcEnd();	//フェードアウト開始地点処理
		VOID MmLoadEnd();		//フェードアウト完了地点処理
		VOID MmLoadDraw();		//描画
		//タイトル
		BOOL MmIsTitleProcDo();	//処理を行うか
		VOID MmTitleProc();		//処理
		VOID MmTitleStart();	//シーン開始処理
		VOID MmTitleProcStart();//処理開始処理
		VOID MmTitleProcEnd();	//フェードアウト完了開始地点処理
		VOID MmTitleEnd();		//シーン終了地点処理
		VOID MmTitleDraw();		//描画
		//プレイ
		BOOL MmIsPlayProcDo();	//処理を行うか
		VOID MmPlayProc();		//処理
		VOID MmPlayStart();		//シーン開始処理
		VOID MmPlayProcStart();	//処理開始処理
		VOID MmPlayProcEnd();	//フェードアウト完了開始地点処理
		VOID MmPlayEnd();		//シーン終了地点処理
		VOID MmPlayDraw();		//描画
		//
		VOID MmSceneChangeProc();	//シーン変更の処理
		VOID MmEnd(SCENE_STATE* scene_state);
		//裏処理
		VOID MmBackNoneDebug();		//デバック
		VOID MmBackLoadProc();		//処理
		VOID MmBackLoadDebug();		//デバック
		//
		VOID MmChangeScene(GAME_SCENE next_scene);	//シーン変更開始処理
		VOID MmSetProcStopState(					//描画以外の処理を停止させるフラグの設定
			GAME_SCENE scene, BOOL is_stop);
		VOID MmSetSceneState(						//参照シーンの進行状態を変更する
			GAME_SCENE scene, SCENE_STATE set_state);


		//		メンバ変数
		GAME_SCENE m_scene;
		GAME_SCENE m_next_scene;
		BACK_GAME_SCENE m_back_scene;
		BOOL m_is_change_secne;
		n_fade::ClFade m_fade;
		//処理を止めるか
		BOOL m_is_load_proc_stop;
		BOOL m_is_title_proc_stop;
		BOOL m_is_play_proc_stop;
		//シーンそれぞれの進行状況
		SCENE_STATE m_load_state;
		SCENE_STATE m_title_state;
		SCENE_STATE m_play_state;
	};
}