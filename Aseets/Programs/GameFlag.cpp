//*--------------------------------------------------------------------------------*
//							ゲーム続行のフラグを管理する
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include GAME_FLAG_HPP
using namespace n_game_flag;

//*--------------------------------------------------------------------------------*
//								シングルトン実装
//*--------------------------------------------------------------------------------*

//シングルトンなGameStateManagerクラスのオブジェクト
ClGameFlag* ClGameFlag::m_ins = nullptr;

/// <summary>
/// コンストラクタ、初期化
/// </summary>
ClGameFlag::ClGameFlag() { m_is_play = TRUE; }

/// <summary>
/// コピーコンストラクタ
/// </summary>
/// <param name="src">コピー元アドレス</param>
ClGameFlag::ClGameFlag(const ClGameFlag& src){
	//アドレスをコピーしておく
	m_ins = src.m_ins;
}

/// <summary>
/// コピーコンストラクタ
/// </summary>
/// <param name="src">コピー元アドレス</param>
/// <returns>このインスタンスのアドレス</returns>
ClGameFlag& ClGameFlag::operator=(const ClGameFlag& src){
	//アドレスをコピーしておく
	m_ins = src.m_ins;
	return *this;
}


/// <summary>
/// デストラクタ
/// </summary>
ClGameFlag::~ClGameFlag() { return; }

/// <summary>
/// インスタンス取得(初めて参照するときはインスタンスを生成)
/// </summary>
/// <returns><シングルトンなインスタンス/returns>
ClGameFlag* ClGameFlag::GetIns(){
	//初めて取得する時、そのオブジェクトを生成を生成
	if (m_ins == nullptr)
	{
		//メモリの確保
		m_ins = new ClGameFlag();
	}

	return m_ins;
}

/// <summary>
/// オブジェクトの破棄
/// </summary>
VOID ClGameFlag::Destroy(){
	//メモリの破棄
	delete m_ins;
	m_ins = nullptr;
}

//ゲーム続行のフラグをおろす
VOID ClGameFlag::SetEndPlay() { m_is_play = FALSE; }

//ゲームを行っているのか参照する
BOOL ClGameFlag::GetIsPlay() { return m_is_play; }