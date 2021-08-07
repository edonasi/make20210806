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
#include KEYBOARD_HPP
using namespace n_keyboard;
#include MOUSE_HPP
using namespace n_mouse;
//		標準ファイル
#include <math.h>
using namespace std;
//		ネーム
using namespace n_img;
using namespace n_img_div;
using namespace n_audio;
using namespace n_img_coll;
using namespace n_img_div;

//ヘッダで使用するconst
//const int SHOT_MAX = 40;
//const int ENEMY_KIND = 7;
//const int ENEMY_MAX = 10;


//*--------------------------------------------------------------------------------*
//								シングルトン実装
//*--------------------------------------------------------------------------------*

//シングルトンなGameStateManagerクラスのオブジェクト
ClGameScene* ClGameScene::m_ins = nullptr;

const string ENEMY_PATHS[ENEMY_KIND] = {
	"teki_blue.png",
	"teki_gray.png",
	"teki_green.png",
	"teki_mizu.png",
	"teki_purple.png",
	"teki_red.png",
	"teki_yellow.png"
};

ClGameScene::SHOT::SHOT(){
	coll_img = ClImgDivColl();
	start_pos = n_xy::ClXY();
	degree = 0.0f;
	radius = 0.0f;
}
ClGameScene::SHOT::~SHOT() { return; }

const float TIME_START = 0.0f;

/// <summary>
/// コンストラクタ、初期化
/// </summary>
ClGameScene::ClGameScene() { 
	m_scene = n_game_scene::GAME_SCENE::TITLE;
	m_next_scene = n_game_scene::GAME_SCENE::TITLE;
	m_back_scene = n_game_scene::BACK_GAME_SCENE::NONE;
	m_is_change_secne = FALSE;
	m_fade = n_fade::ClFade();
	//処理を止めるか
	m_is_end_proc_stop = FALSE;
	m_is_title_proc_stop = FALSE;
	m_is_play_proc_stop = FALSE;
	//シーンそれぞれの進行状況
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::START;
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::SCENE_END;
	m_end_state = n_game_scene::ClGameScene::SCENE_STATE::SCENE_END;
	//変数
	m_score = 0;
	m_back_move_abs_speed = 1;
	m_back_move_speed = 1;

	//画像
	m_title_back_img = ClImg();
	m_title_logo_img = ClImg();
	m_play_back_img_start = ClImg();
	m_play_back_img_up = ClImg();
	m_end_back_img = ClImg();
	m_end_logo_img = ClImg();
	//機体画像
	m_player = ClImgColl();
	for (int i = 0; i < ENEMY_KIND; i++) {
		m_enemy_base[i] = ClImgCollCircle();
	}
	for (int i = 0; i < ENEMY_MAX; i++) {
		m_enemy_use[i] = ClImgCollCircle();
	}
	m_enemy_drop_interval = TIME_START;
	m_enemy_drop_interval_max = 2.0f;
	//弾画像
	m_shot_base = ClImgDivColl();
	//for (int i = 0; i < SHOT_MAX; i++) {
	//	m_shot_use[i] = SHOT();
	//}
	m_shot_div_x = 4;
	m_shot_div_y = 1;
	m_shot_div_max = m_shot_div_x * m_shot_div_y;
	m_shot_interval = TIME_START;
	m_shot_interval_max = 0.2f;
	//音楽
	m_title_audio = ClAudio();
	m_play_audio = ClAudio();
	m_end_audio = ClAudio();

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

//タイトル画面に切り替え
VOID ClGameScene::ChangeSceneTitle() { MmChangeScene(GAME_SCENE::TITLE); }

//プレイ画面に切り替え
VOID ClGameScene::ChangeScenePlay() { MmChangeScene(GAME_SCENE::PLAY); }

//エンド画面に切り替え
VOID ClGameScene::ChangeSceneEnd() { MmChangeScene(GAME_SCENE::END); }

const float FADE_TIME = 0.25f;	//フェードする時間
//const float FADE_TIME = 2.0f;	//フェードする時間

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
		//タイトル画面時
	case n_game_scene::TITLE:
		m_is_title_proc_stop = is_stop;
		break;

		//プレイ画面時
	case n_game_scene::PLAY:
		m_is_play_proc_stop = is_stop;
		break;

		//エンド画面時
	case n_game_scene::END:
		m_is_end_proc_stop = is_stop;
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
	case n_game_scene::TITLE:
		m_title_state = set_state;
		break;
	case n_game_scene::PLAY:
		m_play_state = set_state;
		break;
	case n_game_scene::END:
		m_end_state = set_state;
		break;
	default:
		break;
	}
}

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

const string CPP_NAME = "GameScene";

//ゲームが開始前の処理
VOID ClGameScene::GameInit() {

	//*---------- ここから処理 ----------*
	

	//読み込み
	//背景画像読み込み
	//タイトル
	m_title_back_img.Load(
		"TitleBack.png", 0, TRUE,
		CPP_NAME, "m_title_back_img");
	//プレイ
	m_play_back_img_start.Load(
		"PlayBackStart.jpg", m_back_move_abs_speed, TRUE,
		CPP_NAME, "m_play_back_start_img");
	m_play_back_img_up.Load(
		"PlayBackUp.jpg", m_back_move_abs_speed, TRUE,
		CPP_NAME, "m_play_back_up_img");
	m_play_back_img_up.SetPos(
		n_xy::TOP_CENTER, n_xy::BUTTOM_CENTER);
	//エンド
	m_end_back_img.Load(
		"EndBack.jpg", 0, TRUE,
		CPP_NAME, "m_end_back_img");

	//ロゴの読み込み
	m_title_logo_img.Load(
		"TitleLogo.png", 0, TRUE,
		CPP_NAME, "m_title_logo_img");
	m_title_logo_img.SetPos(n_xy::CENTER_CENTER, n_xy::CENTER_CENTER);
	m_end_logo_img.Load(
		"EndLogo.png", 0, TRUE,
		CPP_NAME, "m_end_logo_img");
	m_end_logo_img.SetPos(n_xy::CENTER_CENTER, n_xy::CENTER_CENTER);

	//機体画像の読み込み
	m_player.Load("Player.png", CPP_NAME, "m_player");

	//敵画像の読み込み
	for (int i = 0; i < ENEMY_KIND; i++) {
		m_enemy_base[i].Load(ENEMY_PATHS[i], CPP_NAME, "m_enemy");
		m_enemy_base[i].SetAbsSpeed(1);
	}

	//弾画像の読み込み
	m_shot_base.Load("ShotRed.png",
		m_shot_div_x, m_shot_div_y, m_shot_div_max,
		CPP_NAME, "m_shot");
	m_shot_base.SetAbsSpeed(2);
	for (int i = 0; i < SHOT_MAX; i++) {
		m_shot_use[i].coll_img = m_shot_base;
	}
	
	//Bgm読み込み
	m_title_audio.BgmLoad(
		"TitleBgm.mp3", CPP_NAME, "m_title_audio");
	m_play_audio.BgmLoad(
		"PlayBgm.mp3", CPP_NAME, "m_play_audio");
	m_end_audio.BgmLoad(
		"EndBgm.mp3", CPP_NAME, "m_end_audio");

}

//現在のゲームシーンによって処理を変える
VOID ClGameScene::GameSceneSwitch() {
	
	switch (m_scene){
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

		//エンド画面
	case n_game_scene::END:
		MmEndProc();	//処理
		MmEndDraw();	//描画
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
//		タイトル画面
//*------------------------------------------------*

//タイトル処理
VOID ClGameScene::MmTitleProc() {
	if (MmIsTitleProcDo() == FALSE) { return; }		//この先の処理は行わない

	//*---------- ここから実行処理 ----------*

	

	//シーン切り替え
	if (ClKeyboard::GetIns()->GetIsKeyDown(KEY_INPUT_SPACE) == TRUE) {
		ChangeScenePlay();
	}

	
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
	//マウスを表示
	SetMouseDispFlag(TRUE);
	 
	//Bgm再生
	m_title_audio.Sound();


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
	if (m_title_state != n_game_scene::ClGameScene::SCENE_STATE::SCENE_END) { return; }
	m_title_state = n_game_scene::ClGameScene::SCENE_STATE::NEXT_SCENE;

	MmEnd(&m_title_state);		//シーン終了地点開始前処理

	//*---------- ここから開始処理 ----------*
	//
	//音楽を停止
	m_title_audio.Stop();
}

//タイトル描画
VOID ClGameScene::MmTitleDraw() {

	//タイトルの画像を描画
	m_title_back_img.Draw();
	m_title_logo_img.Draw();

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

	//背景画像を移動
	m_play_back_img_start.Move(0, m_back_move_speed);
	m_play_back_img_up.Move(0, m_back_move_speed);
	if (m_play_back_img_start.GetPos().y > ClWin().GetWinHeight()) {
		m_play_back_img_start.SetPos(
			n_xy::TOP_CENTER, n_xy::BUTTOM_CENTER, 0, 1);
	}
	if (m_play_back_img_up.GetPos().y > ClWin().GetWinHeight()) {
		m_play_back_img_up.SetPos(
			n_xy::TOP_CENTER, n_xy::BUTTOM_CENTER, 0, 1);
	}

	//プレイヤーの移動
	m_player.SetMove(
		ClMouse::GetIns()->GetPos().x - m_player.GetSize().x / 2,
		ClMouse::GetIns()->GetPos().y - m_player.GetSize().y / 2);

	//弾の処理
	//弾の発射待ち
	if (m_shot_interval != TIME_START && m_shot_interval < m_shot_interval_max) {
		m_shot_interval += ClFps::GetIns()->GetDeltaTime();
		DrawString(100, 100, "IIIIII", ClCom().GetRed());
	}
	else {
		DrawString(100, 100, "AAAA", ClCom().GetRed());
		m_shot_interval = TIME_START;
	}

	//弾の発射
	if (ClMouse::GetIns()->GetIsButton(MOUSE_INPUT_LEFT) == TRUE
		&& m_shot_interval == TIME_START) {
		
		for (int i = 0; i < SHOT_MAX; i++) {
			if (m_shot_use[i].coll_img.GetIsDraw() == FALSE) {
				m_shot_interval += ClFps::GetIns()->GetDeltaTime();
				m_shot_use[i].coll_img.SetIsDraw();

				//弾の位置
				m_shot_use[i].start_pos.x 
					= m_player.GetPos().x + m_player.GetSize().x / 2 
					- m_shot_use[i].coll_img.GetRadius();
				m_shot_use[i].start_pos.y = m_player.GetPos().y;

				m_shot_use[i].coll_img.SetMove(
					m_shot_use[i].start_pos.x,
					m_shot_use[i].start_pos.y);

				m_shot_use[i].degree = 270.0f;
				m_shot_use[i].radius = 0.0f;
			}
		}
	}

	//弾を飛ばす
	for (int i = 0; i < SHOT_MAX; i++) {
		if (m_shot_use[i].coll_img.GetIsDraw() == TRUE) {
			//半径を足す
			m_shot_use[i].radius += m_shot_use[i].coll_img.GetAbsSpeed();

			//弾の位置を修正
			//中心位置＋飛ばす角度→飛ばす距離を計算＊距離
			m_shot_use[i].coll_img.SetMove(
				m_shot_use[i].start_pos.x
				+ cos(m_shot_use[i].degree * DX_PI / 180.0f)
				* m_shot_use[i].radius,
				m_shot_use[i].start_pos.y
				+ sin(m_shot_use[i].degree * DX_PI / 180.0f)
				* m_shot_use[i].radius
				);

			//画面外に出たら描画しない
			if (m_shot_use[i].coll_img.GetPos().y
				+ m_shot_use[i].coll_img.GetSize().y
				< ClWin().GetWinPivot().y
				||
				m_shot_use[i].coll_img.GetPos().y>ClWin().GetWinHeight()
				||
				m_shot_use[i].coll_img.GetPos().x
				+ m_shot_use[i].coll_img.GetSize().x
				< ClWin().GetWinPivot().x
				||
				m_shot_use[i].coll_img.GetPos().x>ClWin().GetWinWidth()){
				m_shot_use[i].coll_img.SetIsDraw(FALSE);
			}
		}
	}

	//敵の生成
	if (m_enemy_drop_interval < m_enemy_drop_interval_max) {
		m_enemy_drop_interval += ClFps::GetIns()->GetDeltaTime();
	}
	else {
		//敵のインターバルを初期化
		m_enemy_drop_interval = TIME_START;
		//敵を生成
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (m_enemy_use[i].GetIsDraw() == FALSE) {
				if (m_score < 1000) {
					m_enemy_use[i] = m_enemy_base[0];
				}
				else if (m_score > 2000) {
					m_enemy_use[i] = m_enemy_base[1];
				}
				else {
					m_enemy_use[i] = m_enemy_base[GetRand(ENEMY_MAX - 1)];
				}

				//m_enemy_use[i] = m_enemy_base[i];
				m_enemy_use[i].SetIsDraw(TRUE);
				m_enemy_use[i].SetMove(
					GetRand(ENEMY_MAX - 1) * ClWin().GetWinWidth() / 4,
					-m_enemy_use[i].GetRadius()
				);
				
				break;
			}
		}
	}

	//敵の処理
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (m_enemy_use[i].GetIsDraw() == TRUE) {
			m_enemy_use[i].Move(0, 1);

			if (m_enemy_use[i].GetPos().y > ClWin().GetWinHeight()) {
				m_enemy_use[i].SetIsDraw(FALSE);
				return;
			}

			for (int j = 0; j < SHOT_MAX; j++) {
				if (m_enemy_use[i].IsStay(m_shot_use[j].coll_img.GetColl(),m_shot_use[j].coll_img.GetIsColl()) == TRUE) {
					m_enemy_use[i].SetIsDraw(FALSE);
					m_shot_use[j].coll_img.SetIsDraw(FALSE);
					m_score += 100;
				}
			}
		}
	}

	//シーン切り替え
	if (m_score>=200) {
		ChangeSceneEnd();
	}
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
	//マウスを非表示
	SetMouseDispFlag(FALSE);

	//Bgm再生
	m_play_audio.Sound();

	//プレイヤーの画像描画フラグ
	m_player.SetIsDraw(TRUE, FALSE);
	
}

//プレイシーン処理開始処理(フェードイン終わった後1度のみ)
VOID ClGameScene::MmPlayProcStart() {
	//1度のみの処理
	if (m_play_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END) { return; }
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END_AFTER;

	//*---------- ここから開始処理 ----------*

	//プレイヤー画像の当たり判定フラグ
	m_player.SetIsDraw(TRUE, TRUE);
	
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
	if (m_play_state != n_game_scene::ClGameScene::SCENE_STATE::SCENE_END) { return; }
	m_play_state = n_game_scene::ClGameScene::SCENE_STATE::NEXT_SCENE;

	MmEnd(&m_play_state);		//シーン終了地点開始前処理

	//*---------- ここから開始処理 ----------*
	
	//敵のインターバルを初期化
	m_enemy_drop_interval = TIME_START;

	//Bgm停止
	m_play_audio.Stop();
}

//プレイ描画
VOID ClGameScene::MmPlayDraw() {

	//背景画像の描画
	m_play_back_img_start.Draw();
	m_play_back_img_up.Draw();

	//敵の描画
	for (int i = 0; i < ENEMY_MAX; i++) { m_enemy_use[i].Draw(); }

	//弾の描画
	for (int i = 0; i < SHOT_MAX; i++) { m_shot_use[i].coll_img.Draw(); }

	//プレイヤーの画像を描画
	m_player.Draw();

	DrawFormatString(0, 64, ClCom().GetFlipColor(), "SCORE : %d", m_score);

	//*---------- ↑描画処理は上に書く↑ ----------*
	//フェード処理
	if (m_is_change_secne == TRUE) { m_fade.FadeSameDraw(); }

	if (ClWin().GetIsDebug() == FALSE) { return; }	//デバック状態ではないなら処理を行わない
	//*---------- ここからデバック処理 ----------*

	

	//現在の画面状態を表示
	DrawString(ClWin().GetWinPivot().x, ClWin().GetWinPivot().y, "Play", ClCom().GetFlipColor());
}

VOID ClGameScene::MmEnd(SCENE_STATE* scene_state) {
	//if (*scene_state != n_game_scene::ClGameScene::SCENE_STATE::SCENE_END) { return; }
	//*scene_state = n_game_scene::ClGameScene::SCENE_STATE::NEXT_SCENE;

	m_scene = m_next_scene;	//次のシーンへ
	MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::START);

	m_fade.FadeDownStart(FADE_TIME);					//画面フェードダウン開始
	ClAudioMult::GetIns()->SetFadeUpStart(FADE_TIME);	//音量フェードアップ開始
}


//*------------------------------------------------*
//		エンド画面
//*------------------------------------------------*

//エンド処理
VOID ClGameScene::MmEndProc() {
	if (MmIsEndProcDo() == FALSE) { return; }	//この先の処理は行わない

	//*---------- ここから実行処理 ----------*
	//シーン切り替え
	if (ClKeyboard::GetIns()->GetIsKeyDown(KEY_INPUT_SPACE) == TRUE) {
		ChangeSceneTitle();
	}
}

//エンド処理を行うか
BOOL ClGameScene::MmIsEndProcDo() {
	MmSceneChangeProc();				//シーン変更
	MmEndStart();						//シーン切り替わり後最初の処理
	MmEndProcEnd();					//フェードアウト開始地点処理
	MmEndEnd();						//フェードアウト完了地点処理
	if (m_is_end_proc_stop == TRUE) {	//この先の処理は行わない
		return FALSE;
	}
	MmEndProcStart();					//フェードイン後の最初の処理

	return TRUE;
}

//エンドシーン開始処理(m_sceneが変更したときに1度のみ)
VOID ClGameScene::MmEndStart() {
	//1度のみの処理
	if (m_end_state != n_game_scene::ClGameScene::SCENE_STATE::START) { return; }
	m_end_state = n_game_scene::ClGameScene::SCENE_STATE::START_AFTER;

	//*---------- ここから開始処理 ----------*
	//マウスを表示
	SetMouseDispFlag(TRUE);

	//Bgm再生
	m_end_audio.Sound();
}

//エンド処理開始処理(フェードイン終わった後1度のみ)
VOID ClGameScene::MmEndProcStart() {
	//1度のみの処理
	if (m_end_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END) { return; }
	m_end_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_DOWN_END_AFTER;

	//*---------- ここから開始処理 ----------*
	
}

//フェードアウト開始地点処理(フェードアウト開始時1度のみ)
VOID ClGameScene::MmEndProcEnd() {
	//1度のみの処理
	if (m_end_state != n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START) { return; }
	m_end_state = n_game_scene::ClGameScene::SCENE_STATE::FADE_UP_START_AFTER;

	//*---------- ここから開始処理 ----------*
	
}

//フェードアウト完了地点処理(フェードアウト完了時1度のみ)
VOID ClGameScene::MmEndEnd() {
	if (m_end_state != n_game_scene::ClGameScene::SCENE_STATE::SCENE_END) { return; }
	m_end_state = n_game_scene::ClGameScene::SCENE_STATE::NEXT_SCENE;
	MmEnd(&m_end_state);		//シーン終了地点開始前処理

	//*---------- ここから開始処理 ----------*
	

	//Bgm停止
	m_end_audio.Stop();
}

//エンド描画
VOID ClGameScene::MmEndDraw() {

	//画像を描画
	m_end_back_img.Draw();
	m_end_logo_img.Draw();

	//*---------- ↑描画処理は上に書く↑ ----------*
	//フェード処理
	if (m_is_change_secne == TRUE) { m_fade.FadeSameDraw(); }

	if (ClWin().GetIsDebug() == FALSE) { return; }	//デバック状態ではないなら処理を行わない
	//*---------- ここからデバック処理 ----------*

	//現在の画面状態を表示
	DrawString(ClWin().GetWinPivot().x, ClWin().GetWinPivot().y, "End", ClCom().GetFlipColor());
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
		MmSetSceneState(m_scene, n_game_scene::ClGameScene::SCENE_STATE::SCENE_END);
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
