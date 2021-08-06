//*--------------------------------------------------------------------------------*
//								マウスの入力
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include MOUSE_HPP
using namespace n_mouse;

//*--------------------------------------------------------------------------------*
//								シングルトン実装
//*--------------------------------------------------------------------------------*

//ボタンが離された瞬間、ボタン入力情報を-1に
const signed char UP_NUM = -1;
//ボタンが離されている状態(ボタンが離された瞬間を除く)、ボタン入力情報を0に
const signed char UPPING_NUM = 0;
//ボタンが押された瞬間
const signed char DOWN_NUM = 1;

/// <summary>
/// コンストラクタ、キーの状態を初期化
/// </summary>
ClMouse::ClMouse() { 
     //マウス変数の初期化
    m_input_value = 0;
    m_wheel_value = 0;
    m_point = n_xy::ClXY();
    //マウスカウンタの初期化
    for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { m_button[i] = UPPING_NUM; }

    //指定秒数押された判定後フラグの初期化
    for (int i = 0; i < MOUSE_BUTTON_CODE; i++) {
        for (int j = 0; j < BUTTON_TIME_INPUT_NUM; j++) {
            m_is_time_input_button_after[i][j] = FALSE;
        }
    }
    return; 
}

//シングルトンなKeyboardクラスのオブジェクト
ClMouse* ClMouse::m_ins = nullptr;

/// <summary>
/// コピーコンストラクタ
/// </summary>
/// <param name="src">コピー元アドレス</param>
ClMouse::ClMouse(const ClMouse& src) {

    //アドレスをコピーしておく
    m_ins = src.m_ins;
}

/// <summary>
/// コピーコンストラクタ
/// </summary>
/// <param name="src">コピー元アドレス</param>
/// <returns>このインスタンスのアドレス</returns>
ClMouse& ClMouse::operator=(const ClMouse& src) {

    //アドレスをコピーしておく
    m_ins = src.m_ins;
    return *this;
}

/// <summary>
/// デストラクタ
/// </summary>
ClMouse::~ClMouse() { return; }

/// <summary>
/// インスタンス取得(初めて参照するときはインスタンスを生成)
/// </summary>
/// <returns>シングルトンなインスタンス</returns>
ClMouse* ClMouse::GetIns() {

    //初めて取得する時Keyboardオブジェクトを生成
    if (m_ins == nullptr) {

        //メモリの確保
        m_ins = new ClMouse();
    }

    return m_ins;
}

//*--------------------------------------------------------------------------------*
//								関数ここから
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		オブジェクトの破棄
//*------------------------------------------------*

/// <summary>
/// オブジェクトの破棄
/// </summary>
VOID ClMouse::Destroy() {

    //メモリの破棄
    delete m_ins;
    m_ins = nullptr;
}

//*------------------------------------------------*
//		マウスの更新
//*------------------------------------------------*

n_xy::ClXY ClMouse::GetPos() { return m_point; }

//マウスの座標制限範囲
const RECT LIMIT_SCREEN = { 0,0,ClWin().GetWinWidth() ,ClWin().GetWinHeight() };
const BOOL IS_MOUSE_POS_LIMIT = TRUE;   //マウスの座標を画面内に制限するか

//マウスの更新
int ClMouse::MouseUpdate() {
    //マウスの座標を取得
    GetMousePoint(&m_point.x, &m_point.y);  
    
    //プレイ画面上のマウスの座標を画面内に制限する
    if (IS_MOUSE_POS_LIMIT == TRUE) {
        if (m_point.x < LIMIT_SCREEN.left) { m_point.x = LIMIT_SCREEN.left; }
        if (m_point.x > LIMIT_SCREEN.right) { m_point.x = LIMIT_SCREEN.right; }
        if (m_point.y < LIMIT_SCREEN.top) { m_point.y = LIMIT_SCREEN.top; }
        if (m_point.y > LIMIT_SCREEN.bottom) { m_point.y = LIMIT_SCREEN.bottom; }
    }

    //マウスの押しているボタンを取得
    m_input_value = GetMouseInput();

    //マウスコードに対応したボタンが押されているかチェック
    MmMouseCheck(MOUSE_INPUT_LEFT);       //左
    MmMouseCheck(MOUSE_INPUT_MIDDLE);     //中
    MmMouseCheck(MOUSE_INPUT_RIGHT);      //右

    //ホイールの回転量を取得
    m_wheel_value = GetMouseWheelRotVol();

    return 0;
}	

/// <summary>
/// マウスコードに対応したボタンが押されているかチェック
/// </summary>
/// <param name="mouse">マウスクラス構造体</param>
/// <param name="mouse_input_">マウスコード</param>
VOID ClMouse::MmMouseCheck(int mouse_input_) {
    //押しているとき
    if ((m_input_value & mouse_input_) == mouse_input_){
        //押した瞬間のときクリック開始判定を行う
        if (m_button[mouse_input_] == UPPING_NUM) {
            //m_is_click_start[mouse_input_] = MmIsMousePointInPlayScreen(m_mouse, mouse_input_);
        }
        m_button[mouse_input_]++;  //加算
    }
    //押していないとき
    else if ((m_input_value & mouse_input_) != mouse_input_){
        if (m_button[mouse_input_] > UPPING_NUM) { //前までボタンが押されていた状態だったら
            m_button[mouse_input_] = UP_NUM;   //-1にする
           // m_is_click_start[mouse_input_] = FALSE; //画面上どの座標にいても離した瞬間、フラグを下す
        }
        else {  
            m_button[mouse_input_] = UPPING_NUM;   //0にする
        }
    }
}

//*------------------------------------------------*
//		当たり判定なしクリック判定
//*------------------------------------------------*

/// <summary>
/// ボタンの入力カウントを返す
/// </summary>
/// <param name="mouse_input_">マウスコード</param>
/// <returns>入力カウント</returns>
int ClMouse::GetButtonCnt(int mouse_input_) { return m_button[mouse_input_]; }

/// <summary>
/// ボタンが押されている状態か(押されている状態ならTRUE)
/// </summary>
/// <param name="mouse_input_">マウスコード</param>
/// <returns>押されているならTRUE</returns>
BOOL ClMouse::GetIsButton(int mouse_input_) {
    if (m_button[mouse_input_] > UPPING_NUM) { return TRUE; } //押されている
    else { return FALSE; }  //押されていない
}

/// <summary>
/// ボタンが押された瞬間か(一番最初の加算)
/// </summary>
/// <param name="mouse_input_">マウスコード</param>
/// <returns>押された瞬間ならTRUE</returns>
BOOL ClMouse::GetIsButtonDown(int mouse_input_) {
    if (m_button[mouse_input_] == DOWN_NUM) { return TRUE; } //押された
    else { return FALSE; }  //押されていない
}

/// <summary>
/// ボタンが離された瞬間か(離された瞬間ならTRUE)
/// </summary>
/// <param name="mouse_input_">マウスコード</param>
/// <returns>離された瞬間ならTRUE</returns>
BOOL ClMouse::GetIsButtonUp(int mouse_input_) {
    if (m_button[mouse_input_] == UP_NUM) { return TRUE; } //離された
    else { return FALSE; }  //それ以外
}

/// <summary>
/// ボタンを離している状態か(離されているならTRUE)
/// </summary>
/// <param name="mouse_input_">マウスコード</param>
/// <returns>離されているならTRUE</returns>
BOOL ClMouse::GetIsButtonAway(int mouse_input_) {
    if (m_button[mouse_input_] <= UPPING_NUM) { return TRUE; } //離している
    else { return FALSE; }  //離していない
}

//指定時間(秒)押されたか
BOOL ClMouse::GetIsButtonTimeInput(int mouse_input_, float time) {
    //離された瞬間は-1になっているのでエラーが起きないように0に修正
    int button = m_button[mouse_input_];
    if (button < UPPING_NUM) { button = UPPING_NUM; }

    //ボタンが離されているならフラグを下す
    if (button == UPPING_NUM) {
        if (m_is_time_input_button_after[mouse_input_][n_com::IF_CASE_TYPE::EQUAL] == TRUE) {
            m_is_time_input_button_after[mouse_input_][n_com::IF_CASE_TYPE::EQUAL] = FALSE;
        }
        return FALSE;
    }

    //押し続けている時間はミリ秒数×FPS値
    //例：1.5秒×60FPS = 90(keyTime)
    int updateTime
        = static_cast<int>(time * ClFps::GetIns()->GetFpsFloatValue());

    //指定時間押されたか
    if (m_is_time_input_button_after[mouse_input_][n_com::IF_CASE_TYPE::EQUAL] == FALSE
        && button == updateTime) {
        m_is_time_input_button_after[mouse_input_][n_com::IF_CASE_TYPE::EQUAL] = TRUE;
        return TRUE;
    }
    else { return FALSE; }
}

//指定時間(ミリ秒)(を超えた / 以上 / と同等 / 以下 / 未満)ボタンが押されたか(基本：を超えた)
BOOL ClMouse::GetIsButtonTimeInput(int mouse_input_, float time, n_com::IF_CASE_TYPE mouse_case_type) {
    //離された瞬間は-1になっているのでエラーが起きないように0に修正
    int button = m_button[mouse_input_];
    if (button < UPPING_NUM) { button = UPPING_NUM; }

    //ボタンが離されているならフラグを下す
    if (button == UPPING_NUM) {
        if (m_is_time_input_button_after[mouse_input_][n_com::IF_CASE_TYPE::EQUAL] == TRUE) {
            m_is_time_input_button_after[mouse_input_][n_com::IF_CASE_TYPE::EQUAL] = FALSE;
        }
        return FALSE;
    }

    //押し続けている時間はミリ秒数×FPS値
    //例：1.5秒×60FPS = 90(keyTime)
    int updateTime
        = static_cast<int>(time * ClFps::GetIns()->GetFpsFloatValue());

    //判定する演算子の種類で条件が合ってたらTRUEで返す
    switch (mouse_case_type)
    {
        //指定時間(秒)を超えた( > )時 
    case n_com::IF_CASE_TYPE::OVER:
        if (m_is_time_input_button_after[mouse_input_][mouse_case_type] == TRUE) { return TRUE; }
        if (button > updateTime) {
            m_is_time_input_button_after[mouse_input_][mouse_case_type] = TRUE;
            return TRUE;
        }
        break;

        //指定時間(秒)　以上　( >= )時 
    case n_com::IF_CASE_TYPE::ABOVE:
        if (m_is_time_input_button_after[mouse_input_][mouse_case_type] == TRUE) { return TRUE; }
        if (button >= updateTime) {
            m_is_time_input_button_after[mouse_input_][mouse_case_type] = TRUE;
            return TRUE;
        }
        break;

        //指定時間(秒)と同等　( == )時 
    case n_com::IF_CASE_TYPE::EQUAL:
        if (m_is_time_input_button_after[mouse_input_][mouse_case_type] == FALSE
            &&button == updateTime) {
            m_is_time_input_button_after[mouse_input_][mouse_case_type] = TRUE;
            return TRUE;
        }
        break;

        //指定時間(秒)　以下　( <= )時 
    case n_com::IF_CASE_TYPE::IN_UNDER:
        if (m_is_time_input_button_after[mouse_input_][mouse_case_type] == TRUE) { return TRUE; }
        if (button <= updateTime) { return TRUE; }
        else { m_is_time_input_button_after[mouse_input_][mouse_case_type] = TRUE; }
        break;

        //指定時間(秒)　未満　( > )時 
    case n_com::IF_CASE_TYPE::LESS_THAN:
        if (m_is_time_input_button_after[mouse_input_][mouse_case_type] == TRUE) { return TRUE; }
        if (button < updateTime) { return TRUE; }
        else { m_is_time_input_button_after[mouse_input_][mouse_case_type] = TRUE; }
        break;

        //何もしない
    default:
        break;
    }

    //判定外だったらFALSEを返す
    return FALSE;
}


//*------------------------------------------------*
//		デバック
//*------------------------------------------------*

//マウスの位置情報を描画する
VOID ClMouse::MousePosDraw() {
    //デバックのとき
    if (ClWin().GetIsDebug() == TRUE) {
        //マウスの座標を描画
        DrawFormatString(
            0, ClWin().GetWinHeight() - ClCom().GetPowerNumPlas(5),
            ClCom().GetFlipColor(), "MOUSE[X:%4d/Y:%4d]", m_point.x, m_point.y
        );
    }
    return;
}