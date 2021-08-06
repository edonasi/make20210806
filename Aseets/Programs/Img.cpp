//*--------------------------------------------------------------------------------*
//								画像管理の基底クラス
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include IMG_HPP
using namespace n_img;
//		ネーム
using namespace n_xy;

//*--------------------------------------------------------------------------------*
//								コンストラクタ、デストラクタ、変数の初期化
//*--------------------------------------------------------------------------------*

ClImg::ClImg() {
	m_handle = ClCom().GetHandleError();
	m_pos = ClXY();			//位置
	m_size = ClXY();			//サイズ
	m_abs_speed = 0;		//移動スピード
	m_over_speed = 0.0f;	//移動スピードの小数点以下
	m_is_draw = FALSE;		//描画するか
}
ClImg::~ClImg() { return; }

//*--------------------------------------------------------------------------------*
//									プロパティ
//*--------------------------------------------------------------------------------*

ClXY ClImg::GetPos() { return m_pos; }

//画像を表示状態にする
VOID ClImg::SetIsDraw() { m_is_draw = TRUE; }

/// <summary>
/// 画像を表示/非表示状態にする
/// </summary>
/// <param name="is_draw">TRUEで表示状態</param>
VOID ClImg::SetIsDraw(BOOL is_draw) { m_is_draw = is_draw; }

/// <summary>
/// 移動スピードの絶対値を代入(-のときは+に変換して代入)
/// </summary>
/// <param name="abs_speed">移動スピードの絶対値</param>
VOID ClImg::SetAbsSpeed(int abs_speed) { m_abs_speed = std::abs(abs_speed); }

//*------------------------------------------------*
//		画像読み込み
//*------------------------------------------------*

/// <summary>
/// 画像読み込み
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImg::Load(string path, string cpp_name, string ins_name) {
	//FALSEなら読み込み失敗
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	return TRUE;	//読み込み成功
}

/// <summary>
/// 移動スピードを指定して画像読み込み
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="abs_speed">移動スピード</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImg::Load(string path, int abs_speed, string cpp_name, string ins_name) {
	//FALSEなら読み込み失敗
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	SetAbsSpeed(abs_speed);	//移動速度を代入

	return TRUE;	//読み込み成功
}

/// <summary>
/// 移動スピードと表示非表示を指定して画像読み込み
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="abs_speed">移動スピード</param>
/// <param name="is_draw">表示非表示</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImg::Load(string path, int abs_speed, BOOL is_draw, string cpp_name, string ins_name) {
	//FALSEなら読み込み失敗
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	SetAbsSpeed(abs_speed);		//移動速度を代入
	SetIsDraw(is_draw);			//表示非表示を代入

	return TRUE;	//読み込み成功
}

/// <summary>
/// 移動スピードと表示非表示を指定して画像読み込み
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <param name="is_draw">表示非表示</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImg::Load(string path, string cpp_name, string ins_name, BOOL is_draw) {
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	SetIsDraw(is_draw);			//表示非表示を代入

	return TRUE;	//読み込み成功
}

/// <summary>
/// 画像読み込み共通関数
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="cpp_name">cpp名_引数</param>
/// <param name="ins_name">インスタンス名_引数</param>
/// <returns>TRUEで読み込み成功</returns>
BOOL ClImg::MmLoad(string path, string cpp_name, string ins_name) {
	//画像の読み込み
	string all_path = ClCom().GetImagesPath() + path;
	m_handle = LoadGraph(all_path.c_str());
	m_path = all_path;						//パスをコピー

	//読み込み失敗
	if (m_handle == ClCom().GetHandleError()) {
		//エラーメッセージ
		string error_meg
			= cpp_name + ".cpp : " + ins_name + " : " + "画像読み込みエラー";

		MessageBox(
			GetMainWindowHandle(), all_path.c_str(),
			error_meg.c_str(), MB_OK
		);
		return FALSE;
	}

	//画像の幅と高さを取得
	GetGraphSize(m_handle, &m_size.x, &m_size.y);

	return TRUE;	//読み込み成功
}

//*------------------------------------------------*
//		
//*------------------------------------------------*

//画像を描画(※is_drawがTRUEのときのみ)
VOID ClImg::Draw() { if (m_is_draw == TRUE) { DrawGraph(m_pos.x, m_pos.y, m_handle, TRUE); } }

//画像をメモリから消去
VOID ClImg::Delete() { 
	DeleteGraph(m_handle); 
	m_is_draw = FALSE;
}

//*------------------------------------------------*
//		移動
//*------------------------------------------------*

/// <summary>
/// 直線移動
/// </summary>
/// <param name="move_type">どの方向に直線移動するか</param>
VOID ClImg::Move(MOVE_LINE_TYPE move_type) {
	//X移動の計算
	switch (move_type) {
		//STOPのときは処理を終了
	case n_img::STOP:return; break;

	case n_img::UP_LEFT:
	case n_img::LEFT:
	case n_img::DOWN_LEFT:
		m_pos.x += -ClFps::GetIns()->GetFpsIntFix(m_abs_speed, &m_over_speed);
		break;

	case n_img::UP_RIGHT:
	case n_img::RIGHT:
	case n_img::DOWN_RIGHT:
		m_pos.x += ClFps::GetIns()->GetFpsIntFix(m_abs_speed, &m_over_speed);
		break;

	default:break;
	}

	//Y移動の計算
	switch (move_type){
	case n_img::UP_LEFT:
	case n_img::UP:
	case n_img::UP_RIGHT:
		m_pos.y += -ClFps::GetIns()->GetFpsIntFix(m_abs_speed, &m_over_speed);
		break;

	case n_img::DOWN_LEFT:
	case n_img::DOWN:
	case n_img::DOWN_RIGHT:
		m_pos.y += ClFps::GetIns()->GetFpsIntFix(m_abs_speed, &m_over_speed);
		break;

	default:break;
	}
}

/// <summary>
/// deltaをかけて移動
/// </summary>
/// <param name="x_mult">+ で右方向、- で左方向に移動</param>
/// <param name="y_mult">+ で下方向、- で上方向に移動</param>
VOID ClImg::Move(int x_mult, int y_mult) {
	m_pos.x += ClFps::GetIns()->GetFpsIntFix(x_mult * m_abs_speed, &m_over_speed);
	m_pos.y += ClFps::GetIns()->GetFpsIntFix(y_mult * m_abs_speed, &m_over_speed);
}

/// <summary>
/// deltaをかけて移動するか掛けないで移動するか
/// </summary>
/// <param name="x_mult">+ で右方向、- で左方向に移動</param>
/// <param name="y_mult">+ で下方向、- で上方向に移動</param>
/// <param name="move_mult">係数の種類</param>
VOID ClImg::Move(int x_mult, int y_mult, n_img::MOVE_MULT move_mult) {
	switch (move_mult)
	{
	case n_img::ABS_SPEED:
		m_pos.x += x_mult * m_abs_speed, & m_over_speed;
		m_pos.y += y_mult * m_abs_speed, & m_over_speed;
		break;
	case n_img::DELTA:
		m_pos.x += ClFps::GetIns()->GetFpsIntFix(x_mult * m_abs_speed, &m_over_speed);
		m_pos.y += ClFps::GetIns()->GetFpsIntFix(y_mult * m_abs_speed, &m_over_speed);
		break;
	default:
		break;
	}
}

//*------------------------------------------------*
//		画面相対位置に画像の位置を設定
//*------------------------------------------------*

//画面左上端に画像の位置を設定
VOID ClImg::SetPos() {
	m_pos.x = ClWin().GetWinPivot().x;
	m_pos.y = ClWin().GetWinPivot().y;
}

/// <summary>
/// 画面左上端からmarginだけ離した位置に設定
/// </summary>
/// <param name="margin_x">離すx位置</param>
/// <param name="margin_y">離すy位置</param>
VOID ClImg::SetPos(int margin_x, int margin_y) {
	m_pos.x = ClWin().GetWinPivot().x + margin_x;
	m_pos.y = ClWin().GetWinPivot().y + margin_y;
}

/// <summary>
/// 画面上の枢軸を基点にして相対位置に設定する
/// </summary>
/// <param name="win_pivot">XYの枢軸</param>
/// <param name="img_pivot">XYの枢軸</param>
VOID ClImg::SetPos(PIVOT win_pivot, PIVOT img_pivot) {
	m_pos.x = ClWin().GetWinPivot(win_pivot).x - m_size.GetPivot(img_pivot).x;
	m_pos.y = ClWin().GetWinPivot(win_pivot).y - m_size.GetPivot(img_pivot).y;
}

/// <summary>
/// 画面pivotを基点に画像pivotに対応した位置からmargin離した位置にする
/// </summary>
/// <param name="win_pivot">画面のpivot</param>
/// <param name="img_pivot">この画像のpivot</param>
/// <param name="margin_x">+ で右方向、- で左方向に離す</param>
/// <param name="margin_y">+ で下方向、- で上方向に離す</param>
VOID ClImg::SetPos(
	PIVOT win_pivot, PIVOT img_pivot,
	int margin_x, int margin_y) {
	m_pos.x = ClWin().GetWinPivot(win_pivot).x - m_size.GetPivot(img_pivot).x + margin_x;
	m_pos.y = ClWin().GetWinPivot(win_pivot).y - m_size.GetPivot(img_pivot).y + margin_y;
}

//*------------------------------------------------*
//		基点画像の相対位置に画像の位置を設定
//*------------------------------------------------*

/// <summary>
/// 基点画像の左上端の位置にこのインスタンスの画像の位置を設定
/// </summary>
/// <param name="base_img">基点画像</param>
VOID ClImg::SetPos(ClImg base_img) {
	m_pos.x = base_img.m_pos.x;
	m_pos.y = base_img.m_pos.y;
}

/// <summary>
/// 基点画像の左上端の位置からmarginだけ離した位置にこのインスタンスの画像の位置を設定
/// </summary>
/// <param name="base_img">基点画像</param>
/// <param name="margin_x">基点画像左上端から離すX位置</param>
/// <param name="margin_y">基点画像左上端から離すY位置</param>
VOID ClImg::SetPos(ClImg base_img, int margin_x, int margin_y) {
	m_pos.x = base_img.m_pos.x + margin_x;
	m_pos.y = base_img.m_pos.y + margin_y;
}

/// <summary>
/// 基点画像のpivot位置にこのインスタンスのpivot位置を設定
/// </summary>
/// <param name="base_img">基点画像</param>
/// <param name="base_pivot">基点画像の枢軸</param>
/// <param name="this_pivot">このインスタンス画像の枢軸</param>
VOID ClImg::SetPos(ClImg base_img,
	PIVOT base_pivot, PIVOT this_pivot) {
	m_pos.x = base_img.m_pos.x + base_img.m_size.GetPivot(base_pivot).x - m_size.GetPivot(this_pivot).x;
	m_pos.y = base_img.m_pos.y + base_img.m_size.GetPivot(base_pivot).y - m_size.GetPivot(this_pivot).y;
}

/// <summary>
/// 基点画像のpivot位置にこのインスタンスのpivot+margin位置を設定
/// </summary>
/// <param name="base_img">基点画像</param>
/// <param name="base_pivot">基点画像の枢軸</param>
/// <param name="this_pivot">このインスタンス画像の枢軸</param>
/// <param name="margin_x">基点画像左上端から離すX位置</param>
/// <param name="margin_y">基点画像左上端から離すY位置</param>
VOID ClImg::SetPos(ClImg base_img,
	PIVOT base_pivot, PIVOT this_pivot,
	int margin_x, int margin_y) {
	m_pos.x = base_img.m_pos.x + base_img.m_size.GetPivot(base_pivot).x - m_size.GetPivot(this_pivot).x + margin_x;
	m_pos.y = base_img.m_pos.y + base_img.m_size.GetPivot(base_pivot).y - m_size.GetPivot(this_pivot).y + margin_y;
}
