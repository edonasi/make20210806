//*-------------------------------------------------------------------------------*
//							ゲームのシーンを管理
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のヘッダファイル
#include GAME_SCENE_HPP
using namespace n_game_scene;
//		自作ヘッダファイル
#include AUDIO_MULT_HPP
using namespace n_audio_mult;

//*--------------------------------------------------------------------------------*
//								シングルトン実装
//*--------------------------------------------------------------------------------*

//シングルトンなGameStateManagerクラスのオブジェクト
ClGameScene* ClGameScene::m_ins = nullptr;

/// <summary>
/// コンストラクタ、初期化
/// </summary>
ClGameScene::ClGameScene() { 
	m_scene = n_game_scene::GAME_SCENE::LOAD;
	m_next_scene = n_game_scene::GAME_SCENE::LOAD;
	m_back_scene = n_game_scene::BACK_GAME_SCENE::NONE;
	m_is_change_secne = FALSE;
	m_fade = n_fade::ClFade();
	//処理を止めるか
	m_is_load_proc_stop = FALSE;
	m_is_title_proc_stop = FALSE;
	m_is_play_proc_stop = FALSE;
	//シーンそれぞれの進行状況
	m_load_state = n_game_scene::ClGameScene::SCENE_STATE::START;
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::END;
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::END;
	return; 
}

/// <summary>
/// コピーコンストラクタ
/// </summary>
/// <param name="src">コピー元アドレス</param>
ClGameScene::ClGameScene(const ClGameScene& src) {
	//アドレスをコピーしておく
	m_ins = src.m_ins;
}

/// <summary>
/// コピーコンストラクタ
/// </summary>
/// <param name="src">コピー元アドレス</param>
/// <returns>このインスタンスのアドレス</returns>
ClGameScene& ClGameScene::operator=(const ClGameScene& src) {
	//アドレスをコピーしておく
	m_ins = src.m_ins;
	return *this;
}


/// <summary>
/// デストラクタ
/// </summary>
ClGameScene::~ClGameScene() { return; }

/// <summary>
/// インスタンス取得(初めて参照するときはインスタンスを生成)
/// </summary>
/// <returns><シングルトンなインスタンス/returns>
ClGameScene* ClGameScene::GetIns() {
	//初めて取得する時、そのオブジェクトを生成を生成
	if (m_ins == nullptr)
	{
		//メモリの確保
		m_ins = new ClGameScene();
	}

	return m_ins;
}

/// <summary>
/// オブジェクトの破棄
/// </summary>
VOID ClGameScene::Destroy() {
	//メモリの破棄
	delete m_ins;
	m_ins = nullptr;
}

//*--------------------------------------------------------------------------------*
//								プロパティ
//*--------------------------------------------------------------------------------*

//ロード画面に切り替え
VOID ClGameScene::ChangeSceneLoad() { MmChangeScene(GAME_SCENE::LOAD); }

//タイトル画面に切り替え
VOID ClGameScene::ChangeSceneTitle() { MmChangeScene(GAME_SCENE::TITLE); }

//プレイ画面に切り替え
VOID ClGameScene::ChangeScenePlay() { MmChangeScene(GAME_SCENE::PLAY); }

//const float FADE_TIME = 0.25f;	//フェードする時間
const float FADE_TIME = 2.0f;	//フェードする時間

/// <summary>
/// シーン変更開始処理
/// </summary>
/// <param name="next_scene">次のシーン</param>
VOID ClGameScene::MmChangeScene(GAME_SCENE next_scene) {
	//シーン変更中は変更変えしない
	if (m_is_change_secne == TRUE) { return; }

	//フェードアウトする準備
	m_next_scene = next_scene;
	m_is_change_secne = TRUE;
	m_back_scene = n_game_scene::BACK_GAME_SCENE::BACK_LOAD;
	m_fade.FadeUpStart(FADE_TIME);
	ClAudioMult::GetIns()->SetFadeDownStart(FADE_TIME);

	//フェード前のシーンの描画以外の処理を停止させる
	MmSetProcStopState(m_scene, TRUE);

	//フェード後のシーンの描画以外の処理を停止させる
	MmSetProcStopState(m_next_scene, TRUE);

	//開始処理を初期化
	MmSetSceneState(m_next_scene, n_game_scene::ClGameScene::SCENE_STATE::START);

	//フェードアップ開始地点処理開始のフラグを立てる
	MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START);
}

/// <summary>
/// 描画以外の処理を停止させるフラグの設定
/// </summary>
/// <param name="scene">参照するゲームシーン</param>
/// <param name="is_stop">停止させるか</param>
VOID ClGameScene::MmSetProcStopState(GAME_SCENE scene, BOOL is_stop) {
	switch (scene){
		//ロード画面時
	case n_game_scene::LOAD:
		m_is_load_proc_stop = is_stop;
		break;

		//タイトル画面時
	case n_game_scene::TITLE:
		m_is_title_proc_stop = is_stop;
		break;

		//プレイ画面時
	case n_game_scene::PLAY:
		m_is_play_proc_stop = is_stop;
		break;

	default:break;
	}
}

/// <summary>
/// 参照シーンの進行状態を変更する
/// </summary>
/// <param name="scene">参照シーン</param>
/// <param name="set_state">進行状態、変更先</param>
VOID ClGameScene::MmSetSceneState(GAME_SCENE scene, SCENE_STATE set_state) {
	switch (scene){
	case n_game_scene::LOAD:
		m_load_state = set_state;
		break;
	case n_game_scene::TITLE:
		m_title_state = set_state;
		break;
	case n_game_scene::PLAY:
		m_play_state = set_state;
		break;
	default:
		break;
	}
}

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

//ゲームが開始前の処理
VOID ClGameScene::GameInit() {

	//*---------- ここから処理 ----------*

}

//現在のゲームシーンによって処理を変える
VOID ClGameScene::GameSceneSwitch() {
	switch (m_scene){
		//ロード画面
	case n_game_scene::LOAD:
		MmLoadProc();	//処理
		MmLoadDraw();	//描画
		break;

		//タイトル画面
	case n_game_scene::TITLE:
		MmTitleProc();	//処理
		MmTitleDraw();	//描画
		break;

		//プレイ画面
	case n_game_scene::PLAY:
		MmPlayProc();	//処理
		MmPlayDraw();	//描画
		break;

	default:break;
	}

	//裏読み込みを行うか
	switch (m_back_scene){
		//なにも行わない
	case n_game_scene::BACK_GAME_SCENE::NONE:
		MmBackNoneDebug();	//デバック
		break;

		//裏ロードを行う
	case n_game_scene::BACK_LOAD:
		MmBackLoadProc();	//処理
		MmBackLoadDebug();	//デバック
		break;

	default:break;
	}
}

//*------------------------------------------------*
//		ロード画面
//*------------------------------------------------*

#include IMG_COLL_HPP
using namespace n_img_coll;
ClImgColl img_coll1 = ClImgColl();
ClImgCollCircle img_coll_circle = ClImgCollCircle();
//ClImgColl img_coll2 = ClImgColl();

#include MOUSE_HPP
using namespace n_mouse;

//#include COLL_CIRCLE_HPP
//using namespace n_coll_circle;
//ClCollCircle coll_circle = ClCollCircle();


//ロード処理
VOID ClGameScene::MmLoadProc() {
	if (MmIsLoadProcDo() == FALSE) { return; }	//この先の処理は行わない

	//*---------- ここから実行処理 ----------*

	//img_coll1.Move(1, 1);
	img_coll_circle.SetMove(ClMouse::GetIns()->GetPos().x, ClMouse::GetIns()->GetPos().y);
	if (img_coll_circle.IsStay(img_coll1.GetCollRect()) == TRUE) { DrawString(600, 0, "aaa", ClCom().GetFlipColor()); }
	//img_coll2.Move(-1, -1);
	//if (img_coll1.IsStay(img_coll2.GetCollRect()) == TRUE) { DrawString(600, 600, "aaa",ClCom().GetFlipColor()); }

	//if (img_coll1.IsStay(coll_circle.GetColl()) == TRUE) { DrawString(600, 0, "aaa", ClCom().GetFlipColor()); }
	//if (img.GetPos().y > ClWin().GetWinHeight()) { img.SetPos(n_xy::TOP_CENTER,n_xy::BUTTOM_CENTER,0,1); }
	//if (img_up.GetPos().y > ClWin().GetWinHeight()) { img_up.SetPos(n_xy::TOP_CENTER,n_xy::BUTTOM_CENTER,0,1); }
}

//ロード処理を行うか
BOOL ClGameScene::MmIsLoadProcDo() {
	MmSceneChangeProc();				//シーン変更
	MmLoadStart();						//シーン切り替わり後最初の処理
	MmLoadProcEnd();					//フェードアウト開始地点処理
	MmLoadEnd();						//フェードアウト完了地点処理
	if (m_is_load_proc_stop == TRUE) {	//この先の処理は行わない
		return FALSE; 
	}
	MmLoadProcStart();					//フェードイン後の最初の処理

	return TRUE;
}

//ロードシーン開始処理(m_sceneが変更したときに1度のみ)
VOID ClGameScene::MmLoadStart() {
	//1度のみの処理
	if (m_load_state != n_game_scene::ClGameScene::SCENE_STATE::START) { return; }
	m_load_state = n_game_scene::ClGameScene::SCENE_STATE::START_AFTER;

	//*---------- ここから開始処理 ----------*



	//coll_circle.SetColl(700, 600, 100);
	//coll_circle.SetIsColl(TRUE);

	img_coll1.Load("test.jpeg", "", "");
	img_coll1.SetIsDraw();
	img_coll1.SetAbsSpeed(1);

	img_coll_circle.Load("test.jpeg", "", "");
	img_coll_circle.SetIsDraw();
	img_coll_circle.SetAbsSpeed(1);
	img_coll_circle.SetPos(n_xy::CENTER_CENTER, n_xy::CENTER_CENTER);
	//img_coll2.Load("test.jpeg", "", "");
	//img_coll2.SetIsDraw();
	//img_coll2.SetAbsSpeed(1);

}		

//ロード処理開始処理(フェードイン終わった後1度のみ)
VOID ClGameScene::MmLoadProcStart() {
	//1度のみの処理
	if (m_load_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END) { return; }
	m_load_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END_AFTER;

	//*---------- ここから開始処理 ----------*
}

//フェードアウト開始地点処理(フェードアウト開始時1度のみ)
VOID ClGameScene::MmLoadProcEnd() {
	//1度のみの処理
	if (m_load_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START) { return; }
	m_load_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START_AFTER;

	//*---------- ここから開始処理 ----------*
}

//フェードアウト完了地点処理(フェードアウト完了時1度のみ)
VOID ClGameScene::MmLoadEnd() {
	MmEnd(&m_load_state);		//シーン終了地点開始前処理

	//*---------- ここから開始処理 ----------*

}

//ロード描画
VOID ClGameScene::MmLoadDraw() {

	img_coll1.Draw();
	img_coll_circle.Draw();
	//img_coll2.Draw();



	//*---------- ↑描画処理は上に書く↑ ----------*
	//フェード処理
	if (m_is_change_secne == TRUE) { m_fade.FadeSameDraw(); }

	if (ClWin().GetIsDebug() == FALSE) { return; }	//デバック状態ではないなら処理を行わない
	//*---------- ここからデバック処理 ----------*

	//coll_circle.DrawDebug(ClCom().GetRed());
	
	//現在の画面状態を表示
	DrawString(ClWin().GetWinPivot().x, ClWin().GetWinPivot().y, "Load", ClCom().GetFlipColor());
}

//*------------------------------------------------*
//		タイトル画面
//*------------------------------------------------*

//タイトル処理
VOID ClGameScene::MmTitleProc() {
	if (MmIsTitleProcDo() == FALSE) { return; }		//この先の処理は行わない

	//*---------- ここから実行処理 ----------*

	
}

//タイトル処理を行うか
BOOL ClGameScene::MmIsTitleProcDo() {
	MmSceneChangeProc();				//シーン変更
	MmTitleStart();						//シーン切り替わり後最初の処理
	MmTitleProcEnd();					//フェードアウト開始地点処理
	MmTitleEnd();						//フェードアウト完了地点処理
	if (m_is_title_proc_stop == TRUE) {	//この先の処理は行わない
		return FALSE;
	}
	MmTitleProcStart();					//フェードイン後の最初の処理

	return TRUE;
}

//タイトルシーン開始処理(m_sceneが変更したときに1度のみ)
VOID ClGameScene::MmTitleStart() {
	//1度のみの処理
	if (m_title_state != n_game_scene::ClGameScene::SCENE_STATE::START) { return; }
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::START_AFTER;

	//*---------- ここから開始処理 ----------*

}

//タイトルシーン処理開始処理(フェードイン終わった後1度のみ)
VOID ClGameScene::MmTitleProcStart() {
	//1度のみの処理
	if (m_title_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END) { return; }
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END_AFTER;

	//*---------- ここから開始処理 ----------*
}

//フェードアウト完了開始地点処理
VOID ClGameScene::MmTitleProcEnd() {
	//1度のみの処理
	if (m_title_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START) { return; }
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START_AFTER;

	//*---------- ここから開始処理 ----------*
}

//シーン終了地点処理
VOID ClGameScene::MmTitleEnd() {
	MmEnd(&m_title_state);		//シーン終了地点開始前処理

	//*---------- ここから開始処理 ----------*
}

//タイトル描画
VOID ClGameScene::MmTitleDraw() {

	//*---------- ↑描画処理は上に書く↑ ----------*
	//フェード処理
	if (m_is_change_secne == TRUE) { m_fade.FadeSameDraw(); }

	if (ClWin().GetIsDebug() == FALSE) { return; }	//デバック状態ではないなら処理を行わない
	//*---------- ここからデバック処理 ----------*

	

	//現在の画面状態を表示
	DrawString(ClWin().GetWinPivot().x, ClWin().GetWinPivot().y, "Title", ClCom().GetFlipColor());
}

//*------------------------------------------------*
//		プレイ画面
//*------------------------------------------------*

//プレイ処理
VOID ClGameScene::MmPlayProc() {
	if (MmIsPlayProcDo() == FALSE) { return; }		//この先の処理は行わない

	//*---------- ここから実行処理 ----------*
}

//プレイ処理を行うか
BOOL ClGameScene::MmIsPlayProcDo() {
	MmSceneChangeProc();				//シーン変更
	MmPlayStart();						//シーン切り替わり後最初の処理
	MmPlayProcEnd();					//フェードアウト開始地点処理
	MmPlayEnd();						//フェードアウト完了地点処理
	if (m_is_play_proc_stop == TRUE) {	//この先の処理は行わない
		return FALSE;
	}
	MmPlayProcStart();					//フェードイン後の最初の処理

	return TRUE;
}

//プレイシーン開始処理(m_sceneが変更したときに1度のみ)
VOID ClGameScene::MmPlayStart() {
	//1度のみの処理
	if (m_play_state != n_game_scene::ClGameScene::SCENE_STATE::START) { return; }
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::START_AFTER;

	//*---------- ここから開始処理 ----------*
}

//プレイシーン処理開始処理(フェードイン終わった後1度のみ)
VOID ClGameScene::MmPlayProcStart() {
	//1度のみの処理
	if (m_play_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END) { return; }
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END_AFTER;

	//*---------- ここから開始処理 ----------*
}

//フェードアウト完了開始地点処理
VOID ClGameScene::MmPlayProcEnd() {
	//1度のみの処理
	if (m_play_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START) { return; }
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START_AFTER;

	//*---------- ここから開始処理 ----------*
}

//シーン終了地点処理
VOID ClGameScene::MmPlayEnd() {
	MmEnd(&m_play_state);		//シーン終了地点開始前処理

	//*---------- ここから開始処理 ----------*
}

//プレイ描画
VOID ClGameScene::MmPlayDraw() {

	//*---------- ↑描画処理は上に書く↑ ----------*
	//フェード処理
	if (m_is_change_secne == TRUE) { m_fade.FadeSameDraw(); }

	if (ClWin().GetIsDebug() == FALSE) { return; }	//デバック状態ではないなら処理を行わない
	//*---------- ここからデバック処理 ----------*

	

	//現在の画面状態を表示
	DrawString(ClWin().GetWinPivot().x, ClWin().GetWinPivot().y, "Play", ClCom().GetFlipColor());
}

VOID ClGameScene::MmEnd(SCENE_STATE* scene_state) {
	if (*scene_state != n_game_scene::ClGameScene::SCENE_STATE::END) { return; }
	*scene_state = n_game_scene::ClGameScene::SCENE_STATE::NEXT_SCENE;

	m_scene = m_next_scene;	//次のシーンへ
	MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::START);

	m_fade.FadeDownStart(FADE_TIME);					//画面フェードダウン開始
	ClAudioMult::GetIns()->SetFadeUpStart(FADE_TIME);	//音量フェードアップ開始
}

//*------------------------------------------------*
//		共通関数
//*------------------------------------------------*

//シーン変更処理
VOID ClGameScene::MmSceneChangeProc() {
	//シーン変更が行われないなら処理を行わない
	if (m_is_change_secne == FALSE) { return; }
		
	//フェードを更新
	m_fade.FadeProc();
	ClAudioMult::GetIns()->FadeProc();

	//フェードアウト処理が終了した時
	if (m_fade.GetIsFadeNone() == TRUE && m_fade.GetFadeType() == n_fade::FADE_TYPE::FADE_UP_TYPE) {
		//フェードアウト開始地点処理のフラグを立てる
		MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::END);
	}

	//フェードイン処理が終了した時
	if (m_fade.GetIsFadeNone() == TRUE && m_fade.GetFadeType() == n_fade::FADE_TYPE::FADE_DOWN_TYPE) {
		m_back_scene = n_game_scene::BACK_GAME_SCENE::NONE;	//裏ロードを解除

		//フェードイン終了後開始処理の状態にする
		MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END);

		m_is_change_secne = FALSE;			//シーン切り替えフラグを下す

		//シーンごとの処理を停止させるフラグを解除
		MmSetProcStopState(m_scene, FALSE);
	}
}

//*------------------------------------------------*
//		裏シーン
//*------------------------------------------------*

//裏シーンがないときのデバック処理
VOID ClGameScene::MmBackNoneDebug() {
	//デバック状態ではないなら処理を行わない
	if (ClWin().GetIsDebug() == FALSE) { return; }

	//現在の裏画面状態を表示
	DrawString(
		ClWin().GetWinPivot().x, ClWin().GetWinPivot().y + ClCom().GetDefalutFontSize(),
		"BackNone", ClCom().GetFlipColor()
	);
}

//裏ロード処理
VOID ClGameScene::MmBackLoadProc() {}

//裏ロードデバック処理
VOID ClGameScene::MmBackLoadDebug() {
	//デバック状態ではないなら処理を行わない
	if (ClWin().GetIsDebug() == FALSE) { return; }

	//現在の裏画面状態を表示
	DrawString(
		ClWin().GetWinPivot().x, ClWin().GetWinPivot().y + ClCom().GetDefalutFontSize(),
		"BackLoad", ClCom().GetFlipColor()
	);
}
