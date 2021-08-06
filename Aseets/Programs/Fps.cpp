//*--------------------------------------------------------------------------------*
//								FPSを管理する
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"

//*--------------------------------------------------------------------------------*
//								シングルトン実装
//*--------------------------------------------------------------------------------*

ClFps* ClFps::m_ins = nullptr;		//シングルトンなインスタンス

//インスタンス取得
ClFps* ClFps::GetIns() {

	//初めて取得する時、そのオブジェクトを生成
	if (m_ins == nullptr)
	{
		//メモリの確保
		m_ins = new ClFps();
	}

	return m_ins;
}

//コンストラクタ
ClFps::ClFps() {

	MmMemberVarInit();		//メンバ変数の初期化

	return;
}

/// <summary>
/// コピーコンストラクタ
/// </summary>
/// <param name="src">コピー元アドレス</param>
ClFps::ClFps(const ClFps& src) {

	//アドレスをコピーしておく
	m_ins = src.m_ins;
}

/// <summary>
/// コピーコンストラクタ
/// </summary>
/// <param name="src">コピー元アドレス</param>
/// <returns>このインスタンスのアドレス</returns>
ClFps& ClFps::operator=(const ClFps& src) {

	//アドレスをコピーしておく
	m_ins = src.m_ins;
	return *this;
}

//デストラクタ
ClFps::~ClFps() { return; }

//*--------------------------------------------------------------------------------*
//								プロパティここから
//*--------------------------------------------------------------------------------*

//メンバ変数の初期化のconst変数
const int GAME_FPS_NORMAL = 60;		//FPS標準
const int GAME_FPS_MAX = 240;		//FPS最大
const int GAME_FPS_MIN = 60;		//FPS最小
const float OVER_MIN = 1.0f;

//FPS値(int)を取得
int ClFps::GetFpsIntValue() { return m_int_value; }

/// <summary>
/// speedをfpsに合わせて調整
/// </summary>
/// <param name="speed">参照するスピード</param>
/// <param name="over">スピード余り値</param>
/// <returns>fpsに合わせたスピード</returns>
int ClFps::GetFpsIntFix(int speed, float* over) {
	if (speed == 0) { return 0; }		//speedが0なら処理を終了

	//fpsに合わせたスピードを計算
	float mult
		= static_cast<float>(GAME_FPS_NORMAL) / m_float_value;
	float speed_float = speed * mult;

	//小数点以下を取得
	int speed_int = static_cast<int>(speed_float);	//int値
	float over_float								//小数点以下
		= speed_float - static_cast<float>(static_cast<int>(speed_float));

	//小数点以下を加算
	*over += over_float;

	//小数点以下の誤差を調整
	int add = 0;
	//speed_floatが0より大きいかによって分岐
	if (speed_float > 0.0f) {
		if (*over >= OVER_MIN) {
			add = static_cast<int>(*over);
			//overを1.0f未満にする
			*over = *over - static_cast<float>(add);
		}
	}
	else {
		if (*over <= OVER_MIN) {
			add = static_cast<int>(*over);
			//overを-1.0fより上にする
			*over = *over - static_cast<float>(add);
		}
	}

	return speed_int + add;
}

//FPS値(float)を取得
float ClFps::GetFpsFloatValue() { return m_float_value; }

//deltaTimeを参照
float ClFps::GetDeltaTime() {
	//値がありえないぐらい大きいとき修正
	if (m_delta_time < 1000.0f/*=ありえないくらい大きいとき*/) {
		return m_delta_time;
	}
	else {
		return 0.015f;	//平均的なdelta_timeに設定
	}
}

//*--------------------------------------------------------------------------------*
//								関数ここから
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		メンバ変数の初期化
//*------------------------------------------------*

//メンバ変数の初期化
VOID ClFps::MmMemberVarInit() {

	//*------------------------------------------------*
	//		Fps値の管理
	//*------------------------------------------------*
	m_is_init = FALSE;				//最初の測定開始フラグ
	m_start_time = 0;				//開始開始時刻
	m_now_time = 0;					//現在の時刻
	m_old_time = 0;					//以前の時刻
	m_int_value = GAME_FPS_NORMAL;	//FPSの値
	m_float_value = GAME_FPS_NORMAL;//計算結果を描画
	m_delta_time					//経過時間
		= static_cast<float>(0.000001);
	m_cnt = 1;					//現在のフレーム数
	m_sample_rote = GAME_FPS_NORMAL;//平均を取るサンプル値
}

//*------------------------------------------------*
//		インスタンスの破棄
//*------------------------------------------------*

//インスタンスの破棄
VOID ClFps::Destroy() {

	delete m_ins;
	m_ins = nullptr;
}

//*------------------------------------------------*
//		Fps値の管理
//*------------------------------------------------*

//FPSの管理のconst変数
const float DIV_DELETA_TIME = 1000000.0f;		//deltaTimeを割る数(1000000.0f)

//Fps値を測定し、値を更新する
VOID ClFps::FpsUpdate() {

	//一番最初の処理
	if (m_is_init == FALSE) {

		m_start_time						//測定開始時刻をマイクロ秒単位で取得
			= GetNowHiPerformanceCount();

		m_is_init = TRUE;					//最初の処理終了
	}

	m_now_time								//現在の時刻をμ秒単位で取得
		= GetNowHiPerformanceCount();

	m_delta_time							//前回取得した時間からの経過時間を秒に(小数)に変換してからセット
		= (m_now_time - m_old_time) / DIV_DELETA_TIME;

	m_old_time = m_now_time;				//今回取得した時間を保存

	//1フレーム目～FPS設定値まではカウントアップ
	if (m_cnt < m_sample_rote) {

		m_cnt++;							//カウンタを増やす
	}
	else {									//FPS設定値フレームで平均FPSを計算

		m_float_value						//現在の時刻から0フレームの時間をひきFPSの数値で割る
			= DIV_DELETA_TIME / ((m_now_time - m_start_time)
				/ static_cast<float>(m_sample_rote));

		m_start_time						//測定開始時刻をマイクロ秒単位で取得
			= GetNowHiPerformanceCount();

		m_cnt = 1;						//カウンタ初期化
	}
}

//FPSで処理を待つ
int ClFps::FpsWait() {

	LONGLONG resultTime					//現在の時刻-最初の時刻で、現在かかっている時刻を取得する
		= m_now_time - m_start_time;
	LONGLONG waitTime					//待つべきミリ秒数(1秒/FPS値＊現在のフレーム数)から、現在かかっている時刻を引く
		= static_cast<LONGLONG>(DIV_DELETA_TIME)
		/ static_cast<LONGLONG>(m_int_value * m_cnt - resultTime);
	//int millTime = 1000;				//ミリ秒に変換させる割る数

	waitTime /= ClCom().GetMilliMult();	//マイクロ秒からミリ秒に変換

	//処理が速かったら、処理を待つ
	if (waitTime > 0) {

		WaitTimer(static_cast<int>(waitTime));			//引数ミリ秒待つ(※WindowProcで停止するので途中でイベントが起きたときその処理を行う)
	}

	//垂直同期をOFFにしているか
	if (GetWaitVSyncFlag() == FALSE) {

		//FPSが最大値ではないとき
		if (m_int_value < GAME_FPS_MAX) {

			//1秒毎のFPS値よりも、待つ時間が小さいときは、もっとFPS値を上げてもよい
			//待つ時間10ミリ <= 1秒/60FPS=16.6666ミリ　もう少し早くできる
			if (waitTime > 0
				&& waitTime <= ClCom().GetMilliMult() / m_int_value) {

				m_int_value++;
			}
			else {

				//FPS値が追いついておらず、遅いときは、FPS値を下げる
				if (m_int_value > GAME_FPS_MIN) {

					m_int_value--;
				}
			}
		}
	}

	return 0;
}

//*------------------------------------------------*
//		Fps値の描画
//*------------------------------------------------*

//Fps値の描画のconst変数
const int FIX_HEIGHT = 16;		//FPS値を見えるように高さ調整

//デバック用の平均FPS値を黒色で画面左下に描画する
VOID ClFps::FpsDraw() {

	//デバックモードなら描画する
	if (ClWin().GetIsDebug() == TRUE) {

		//文字列を描画
		DrawFormatString(
			0, ClWin().GetWinHeight() - FIX_HEIGHT,
			ClCom().GetFlipColor(),
			"FPS : %.1f", m_float_value);
	}

	return;
}

//位置調整有のFps値の描画のconst変数
const int DRAW_X_MAX = ClWin().GetWinWidth() - 96;
const int DRAW_Y_MAX = ClWin().GetWinHeight() - FIX_HEIGHT;

/// <summary>
/// 位置を設定してデバック用の黒色で平均FPS値を描画する
/// </summary>
/// <param name="draw_x">描画するx位置</param>
/// <param name="draw_y">描画するy位置</param>
/// <param name="is_black_color">TRUEなら黒、FALSEなら白</param>
VOID ClFps::FpsDraw(int draw_x, int draw_y) {

	//デバックモードなら描画する
	if (ClWin().GetIsDebug() == TRUE) {

		//文字が画面外に出ているなら画面内に収まるようにする
		draw_x = MmFpsDrawPosLimit(draw_x, DRAW_X_MAX);
		draw_y = MmFpsDrawPosLimit(draw_y, DRAW_Y_MAX);

		//文字列を描画
		DrawFormatString(draw_x, draw_y, ClCom().GetFlipColor(),
			"FPS : %.1f", m_float_value);
	}

	return;
}

//Fps描画の位置調整
int ClFps::MmFpsDrawPosLimit(int num, int m_max) {	
	if (num < 0) { return 0; }			//返し値を最小値に設定
	else if (num > m_max) { return m_max; }	//返し値を最大値に設定
	return num;
}