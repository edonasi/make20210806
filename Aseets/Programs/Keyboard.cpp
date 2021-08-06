//*--------------------------------------------------------------------------------*
//								キーボードの入力
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include KEYBOARD_HPP
using namespace n_keyboard;

//*--------------------------------------------------------------------------------*
//								シングルトン実装
//*--------------------------------------------------------------------------------*

//シングルトンなKeyboardクラスのオブジェクト
ClKeyboard* ClKeyboard::m_ins = nullptr;

/// <summary>
/// コンストラクタ、キーの状態を初期化
/// </summary>
ClKeyboard::ClKeyboard() {
    //キーフレームを初期化
    for (int i = 0; i < DEFAULT_KEY_NUM; i++) {

        m_key_cnt[i] = 0;
    }

    //時間指定入力のフラグを初期化
    for (int i = 0; i < DEFAULT_KEY_NUM; i++) {
        for (int j = 0; j < KEY_TIME_INPUT_NUM; j++) {
            m_is_time_input_after[i][j] = FALSE;
        }
    }
}

/// <summary>
/// コピーコンストラクタ
/// </summary>
/// <param name="src">コピー元アドレス</param>
ClKeyboard::ClKeyboard(const ClKeyboard& src) {

    //アドレスをコピーしておく
    m_ins = src.m_ins;
}

/// <summary>
/// コピーコンストラクタ
/// </summary>
/// <param name="src">コピー元アドレス</param>
/// <returns>このインスタンスのアドレス</returns>
ClKeyboard& ClKeyboard::operator=(const ClKeyboard& src) {

    //アドレスをコピーしておく
    m_ins = src.m_ins;
    return *this;
}

/// <summary>
/// デストラクタ
/// </summary>
ClKeyboard::~ClKeyboard() {

    return;
}

/// <summary>
/// インスタンス取得(初めて参照するときはインスタンスを生成)
/// </summary>
/// <returns>シングルトンなインスタンス</returns>
ClKeyboard* ClKeyboard::GetIns() {

    //初めて取得する時Keyboardオブジェクトを生成
    if (m_ins == nullptr) {

        //メモリの確保
        m_ins = new ClKeyboard();
    }

    return m_ins;
}


//*--------------------------------------------------------------------------------*
//								関数ここから
//*--------------------------------------------------------------------------------*


/// <summary>
/// オブジェクトの破棄
/// </summary>
VOID ClKeyboard::Destroy() {

    //メモリの破棄
    delete m_ins;
    m_ins = nullptr;
}

//キーが離された瞬間、キー入力情報を-1に
const signed char KEY_UP_NUM = -1;
//キーが離されている状態(キーが離された瞬間を除く)、キー入力情報を0に
const signed char KEY_UPPING_NUM = 0;
//キーが押された瞬間
const signed char KEY_DOWN_NUM = 1;

/// <summary>
/// キーの入力状態を更新する関数
/// </summary>
/// <returns></returns>
int ClKeyboard::GpUpdateKey() {

    int i = 0;
    //現在のキー入力状態を格納する
    char tmpKey[DEFAULT_KEY_NUM];

    //すべてのキー入力状態を得る
    GetHitKeyStateAll(tmpKey);

    //元々のキー(256個)のキーの状態を得る
    for (i = 0; i < DEFAULT_KEY_NUM; i++) {

        //i版のキーコードに対応するキーが押されていたら
        if (tmpKey[i] != 0) {

            //加算
            m_key_cnt[i]++;
        }
        else {

            //前までキーが押されていた状態だったら
            if (m_key_cnt[i] > 0) {

                //-1にする(離した瞬間の状態 -1)
                m_key_cnt[i] = KEY_UP_NUM;
            }
            else {

                //0にする(押されていない状態 0)
                m_key_cnt[i] = KEY_UPPING_NUM;
            }

        }
    }

    return 0;
}

/// <summary>
/// キーの入力カウントを返す
/// </summary>
/// <param name="key_input_">キーコード</param>
/// <returns>キーコードの入力時間(m_cnt)</returns>
int ClKeyboard::GetKeyCnt(int key_input_) { return m_key_cnt[key_input_]; }

/// <summary>
/// キーが押されている状態か(0を超えている , 1以上)
/// </summary>
/// <param name="key_input_">キーコード</param>
/// <returns>押されている状態ならTRUE</returns>
BOOL ClKeyboard::GetIsKey(int key_input_) {
    //キーが押されている状態か(0を超えている , 1以上)
    if (m_key_cnt[key_input_] > KEY_UPPING_NUM) { return TRUE; }  //押されている状態
    else { return FALSE; }                    //押されていない状態
}

/// <summary>
/// キーが押された瞬間か(一番最初の加算)
/// </summary>
/// <param name="key_input_">キーコード</param>
/// <returns>押された瞬間ならTRUE</returns>
BOOL ClKeyboard::GetIsKeyDown(int key_input_) {
    //キーが押されている状態か(一番最初の加算)
    if (m_key_cnt[key_input_] == KEY_DOWN_NUM) { return TRUE; }  //押された瞬間
    else { return FALSE; }                      //押された瞬間ではない
}

/// <summary>
/// キーが離された瞬間か(-1)
/// </summary>
/// <param name="key_input_">キーコード</param>
/// <returns>離された瞬間ならTRUE</returns>
BOOL ClKeyboard::GetIsKeyUp(int key_input_) {
    //キーが離された瞬間か(-1)
    if (m_key_cnt[key_input_] == KEY_UP_NUM) { return TRUE; }  //離された瞬間
    else { return FALSE; }                      //離された間ではない
}

/// <summary>
/// キーを離している状態か(0以下)
/// </summary>
/// <param name="key_input_">キーコード</param>
/// <returns>離されているならTRUE</returns>
BOOL ClKeyboard::GetIsKeyAway(int key_input_) {
    //キーを離している状態か(0以下)
    if (m_key_cnt[key_input_] <= KEY_UPPING_NUM) { return TRUE; }   //離している状態
    else { return FALSE; }                      //離されていない状態
}

/// <summary>
/// 指定時間押されたか
/// </summary>
/// <param name="key_input_">キーコード</param>
/// <param name="time">指定時間(秒)</param>
/// <returns>指定時間押された瞬間TRUE</returns>
BOOL ClKeyboard::GetIsKeyTimeInput(int key_input_, float time) {
    //離された瞬間は-1になっているのでエラーが起きないように0に修正
    int key = m_key_cnt[key_input_];
    if (key < KEY_UPPING_NUM) { key = KEY_UPPING_NUM; }

    //キーが離されているならフラグをおろす
    if (key == KEY_UPPING_NUM) {
        //判定後フラグを戻す
        if (m_is_time_input_after[key_input_][n_com::IF_CASE_TYPE::EQUAL] == TRUE) {
            m_is_time_input_after[key_input_][n_com::IF_CASE_TYPE::EQUAL] = FALSE;
        }
        return FALSE;
    }

    //押し続けている時間はミリ秒数×FPS値
    //例：1.5秒×60FPS = 90(keyTime)
    int updateTime
        = static_cast<int>(time * ClFps::GetIns()->GetFpsFloatValue());

    //指定時間押されたか
    //押された
    if (m_is_time_input_after[key_input_][n_com::IF_CASE_TYPE::EQUAL] == FALSE 
        &&key == updateTime) {
        m_is_time_input_after[key_input_][n_com::IF_CASE_TYPE::EQUAL] = TRUE;
        return  TRUE; 
    }    
    else { return FALSE; }                      //押されていない
}

/// <summary>
/// 指定時間(秒)(を超えた / 以上 / と同等 / 以下 / 未満キーが押されたか(基本：を超えた)
/// </summary>
/// <param name="key_input_">キーコード</param>
/// <param name="milliTime">判定する時間(秒)</param>
/// <param name="key_keep_type">判定する演算子の種類 : 判定する時間(を超えた / 以上 / と同等 / 以下 / 未満)</param>
/// <returns></returns>
BOOL ClKeyboard::GetIsKeyTimeInput(int key_input_, float time, n_com::IF_CASE_TYPE key_case_type) {
   
    //離された瞬間は-1になっているのでエラーが起きないように0に修正
    int key = m_key_cnt[key_input_];
    if (key < KEY_UPPING_NUM) { key = KEY_UPPING_NUM; }

    //キーを離しているならFALSEを返す
    if (key == KEY_UPPING_NUM) { 
        //判定後フラグを戻す
        if (m_is_time_input_after[key_input_][key_case_type] == TRUE) {
            m_is_time_input_after[key_input_][key_case_type] = FALSE;
        }
        return FALSE;
    }

    //押し続けている時間はミリ秒数×FPS値
    //例：1.5秒×60FPS = 90(keyTime)
    int updateTime
        = static_cast<int>(time * ClFps::GetIns()->GetFpsFloatValue());

    //判定する演算子の種類で条件が合ってたらTRUEで返す
    switch (key_case_type) {

        //指定時間(秒)を超えた( > )時 
    case n_com::IF_CASE_TYPE::OVER:
        if (m_is_time_input_after[key_input_][key_case_type] == TRUE) { return TRUE; }
        if ( key > updateTime) {
            m_is_time_input_after[key_input_][key_case_type] = TRUE;
            return TRUE;
        }
        break;

        //指定時間(秒)　以上　( >= )時 
    case n_com::IF_CASE_TYPE::ABOVE:
        if (m_is_time_input_after[key_input_][key_case_type] == TRUE) { return TRUE; }
        if (key >= updateTime) { 
            m_is_time_input_after[key_input_][key_case_type] = TRUE;
            return TRUE; 
        }
        break;

        //指定時間(秒)と同等　( == )時 
    case n_com::IF_CASE_TYPE::EQUAL:
        if (m_is_time_input_after[key_input_][key_case_type] == FALSE
            && key == updateTime) {
            m_is_time_input_after[key_input_][key_case_type] = TRUE;
            return TRUE;
        }
        break;

        //指定時間(秒)　以下　( <= )時 
    case n_com::IF_CASE_TYPE::IN_UNDER:
        if (m_is_time_input_after[key_input_][key_case_type] == TRUE) { return FALSE; }
        if (key <= updateTime) { return TRUE; }
        else { m_is_time_input_after[key_input_][key_case_type] = TRUE; }
        break;

        //指定時間(秒)　未満　( > )時 
    case n_com::IF_CASE_TYPE::LESS_THAN:
        if (m_is_time_input_after[key_input_][key_case_type] == TRUE) { return FALSE; }
        if (key < updateTime) { return TRUE; }
        else { m_is_time_input_after[key_input_][key_case_type] = TRUE; }
        break;

        //違う値を間違って入れてしまったときは何もしない
    default:
        break;
    }

    //判定外だったらFALSEを返す
    return FALSE;
}