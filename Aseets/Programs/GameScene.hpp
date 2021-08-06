#pragma once

//		自作ファイル
#include FADE_HPP	//画面切り替え時、フェードを使用
#include IMG_HPP	//画像読み込み
#include IMG_DIV_HPP
#include IMG_COLL_HPP
#include AUDIO_HPP

#define SHOT_MAX 40
#define ENEMY_KIND 7
#define ENEMY_MAX 10

namespace n_game_scene{

	//		enum
	//ゲームシーン
	enum GAME_SCENE {
		END,		//終わり
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
			SCENE_END,
			NEXT_SCENE
		};

		//		プロパティ
		VOID ChangeSceneEnd();		//ロードシーンに遷移
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
		//エンド
		BOOL MmIsEndProcDo();	//処理を行うか
		VOID MmEndProc();		//処理
		VOID MmEndStart();		//シーン開始処理
		VOID MmEndProcStart();	//処理開始処理
		VOID MmEndProcEnd();	//フェードアウト開始地点処理
		VOID MmEndEnd();		//フェードアウト完了地点処理
		VOID MmEndDraw();		//描画
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
		BOOL m_is_title_proc_stop;
		BOOL m_is_play_proc_stop;
		BOOL m_is_end_proc_stop;
		//シーンそれぞれの進行状況
		SCENE_STATE m_title_state;
		SCENE_STATE m_play_state;
		SCENE_STATE m_end_state;

		//		変数
		int m_score;
		int m_back_move_abs_speed;
		int m_back_move_speed;

		//		読み込むもの
		//画像
		//背景画像
		n_img::ClImg m_title_back_img;
		n_img::ClImg m_play_back_img_start;
		n_img::ClImg m_play_back_img_up;
		n_img::ClImg m_end_back_img;
		//ロゴ
		n_img::ClImg m_title_logo_img;
		n_img::ClImg m_end_logo_img;
		//機体画像
		n_img_coll::ClImgColl m_player;
		n_img_coll::ClImgCollCircle m_enemy_base[ENEMY_KIND];
		n_img_coll::ClImgCollCircle m_enemy_use[ENEMY_MAX];
		float m_enemy_drop_interval;
		float m_enemy_drop_interval_max;
		//弾画像
		n_img_div::ClImgDivColl m_shot_base;
		
		class SHOT
		{
		public:
			SHOT();
			~SHOT();
			n_img_div::ClImgDivColl coll_img;
			n_xy::ClXY start_pos;
			float degree;
			float radius;

		private:

		};
		SHOT m_shot_use[SHOT_MAX];
		
		int m_shot_div_x;
		int m_shot_div_y;
		int m_shot_div_max;
		float m_shot_interval;
		float m_shot_interval_max;

		//音楽
		n_audio::ClAudio m_title_audio;
		n_audio::ClAudio m_play_audio;
		n_audio::ClAudio m_end_audio;
	};
}