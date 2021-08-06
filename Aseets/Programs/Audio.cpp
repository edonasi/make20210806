//*--------------------------------------------------------------------------------*
//								音楽の管理
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include AUDIO_HPP
using namespace n_audio;
//		Singletonファイル
#include AUDIO_MULT_HPP
using namespace n_audio_mult;


//実装してないことメモ
//・Seの再生で音が重なって再生かつ再生時間インターバルを秒数毎指定

//*--------------------------------------------------------------------------------*
//								コンストラクタ、デストラクタ、変数の初期化
//*--------------------------------------------------------------------------------*

ClAudio::ClAudio() {
	//変数の初期化
	m_handle = ClCom().GetHandleError();
	m_product_volume = ClCom().GetUnCharHalf();
	m_play_type = -1;
	m_se_type = SE_TYPE::BGM;
}

//コピーコンストラクタ
ClAudio::ClAudio(const ClAudio &src) { 
	m_handle = src.m_handle;
	m_path = src.m_path;
	m_product_volume = src.m_product_volume;
	m_play_type = src.m_play_type;
	m_se_type = src.m_se_type;
	return; 
}
ClAudio &ClAudio::operator=(const ClAudio &src) { 
	if (this != &src) { ClAudio::operator=(src); }
	return (*this);
}
ClAudio::~ClAudio() { return; }

//*--------------------------------------------------------------------------------*
//								プロパティ
//*--------------------------------------------------------------------------------*

//ハンドルを取得
int ClAudio::GetAudioHandle() { return m_handle; }
//音量(制作者調整用)を取得
int ClAudio::GetProductVolume() { return m_product_volume; }
//音楽の種類を取得
SE_TYPE ClAudio::GetSeType() { return m_se_type; }

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

/// <summary>
/// Bgmの読み込み(読み込み方法はSeと同じ)(※if(BgmLoad==FALSE){return FALSE;}で使用)
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns>読み込めたらTRUE</returns>
BOOL ClAudio::BgmLoad(string path, string cpp_name, string ins_name) {
	//音楽読み込み
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	//必要な変数を代入
	m_play_type = DX_PLAYTYPE_LOOP;			//再生方式
	m_se_type = SE_TYPE::BGM;	//音楽の種類
	MmLoadVolume(m_product_volume);			//音量の読み込み

	return TRUE;	//読み込み成功
}

/// <summary>
/// 音量を変えてBgmの読み込み(読み込み方法はSeと同じ)(※if(BgmLoad==FALSE){return FALSE;}で使用)
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="volume">音量(0~255)</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns>読み込めたらTRUE</returns>
BOOL ClAudio::BgmLoad(string path, int volume, string cpp_name, string ins_name) {
	//音楽読み込み
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	//必要な変数を代入
	m_play_type = DX_PLAYTYPE_LOOP;			//再生方式
	m_se_type = SE_TYPE::BGM;	//音楽の種類
	m_product_volume = volume;				//音量の変更
	MmLoadVolume(m_product_volume);			//音量の読み込み

	return TRUE;	//読み込み成功
}

/// <summary>
/// Seの読み込み(読み込み方法はBgmと同じ)(※if(SeLoad==FALSE){return FALSE;}で使用)
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="se_type">Seの種類</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns></returns>
BOOL ClAudio::SeLoad(
	string path, SE_TYPE se_type,
	string cpp_name, string ins_name) {
	//音楽読み込み
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	//必要な変数を代入
	m_play_type = DX_PLAYTYPE_BACK;		//再生方式
	m_se_type = se_type;				//音楽の種類
	MmLoadVolume(m_product_volume);		//音量の読み込み

	return TRUE;	//読み込み成功
}

/// <summary>
/// 音楽読み込み(※if(SeLoad==FALSE){return FALSE;}で使用)
/// </summary>
/// <param name="path">読み込み場所</param>
/// <param name="volume">音量(0~255)</param>
/// <param name="se_type">音楽の種類(※BGMならBGM)</param>
/// <param name="cpp_name">読み込む場所のcpp名(ベタ打ち)</param>
/// <param name="ins_name">読み込むインスタンス名(ベタ打ち)</param>
/// <returns>読み込めたらTRUE</returns>
BOOL ClAudio::SeLoad(
	string path, int volume, SE_TYPE se_type,
	string cpp_name,string ins_name) {
	//音楽読み込み
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	//必要な変数を代入
	m_play_type = DX_PLAYTYPE_BACK;	//再生方式
	m_se_type = se_type;			//音楽の種類
	m_product_volume = volume;		//音量の変更
	MmLoadVolume(volume);			//音量の読み込み
	
	return TRUE;	//読み込み成功
}

/// <summary>
/// 音楽読み込み共通関数
/// </summary>
/// <param name="path">読み込み場所_引数</param>
/// <param name="cpp_name">cpp名_引数</param>
/// <param name="ins_name">インスタンス名_引数</param>
/// <returns>読み込めたらTRUE</returns>
BOOL ClAudio::MmLoad(string path, string cpp_name, string ins_name) {
	//音楽読み込み
	string all_path = ClCom().GetAudiosPath() + path;
	m_handle = LoadSoundMem(all_path.c_str());	//音楽の読み込み
	m_path = all_path;							//パスをコピー

	//読み込み失敗
	if (m_handle == ClCom().GetHandleError()) {
		//エラーメッセージ
		string error_meg
			= cpp_name + ".cpp : " + ins_name + " : " + "音楽読み込みエラー";

		MessageBox(
			GetMainWindowHandle(), all_path.c_str(),
			error_meg.c_str(), MB_OK
		);
		return FALSE;
	}

	//現在使用している音楽を登録
	ClAudioMult::GetIns()->VectorAudioEmplace(this);

	return TRUE;
}

/// <summary>
/// 音量の読み込み(※m_se_typeの代入必須)
/// </summary>
/// <param name="volume">Load関数の引数volume</param>
VOID ClAudio::MmLoadVolume(int volume) {
	if (volume > ClCom().GetUnCharMax()) { volume = ClCom().GetUnCharMax(); }
	if (volume < ClCom().GetUnCharMin()) { volume = ClCom().GetUnCharMin(); }
	m_product_volume = volume;

	//音量を調整
	switch (m_se_type)
	{
	case n_audio::BGM:
		ChangeVolumeSoundMem(
			static_cast<int>(m_product_volume * ClAudioMult::GetIns()->GetBgmDecimalPar())
			, m_handle);
		break;
	case n_audio::SYSTEM:
		ChangeVolumeSoundMem(
			static_cast<int>(m_product_volume * ClAudioMult::GetIns()->GetSeSystemDecimalPar())
			, m_handle);
		break;
	case n_audio::PLAY:
		ChangeVolumeSoundMem(
			static_cast<int>(m_product_volume * ClAudioMult::GetIns()->GetSePlayDecimalPar())
			, m_handle);
		break;
	default:
		break;
	}
}

VOID ClAudio::Sound() {
	//再生されていないなら再生
	if (CheckSoundMem(m_handle) == FALSE) {
		PlaySoundMem(m_handle, m_play_type);
	}
}

/// <summary>
/// 音楽のメモリ消去
/// </summary>
/// <param name="is_vector_erase">TRUEならロード記録も消去</param>
VOID ClAudio::Delete(BOOL is_vector_erase) {
	//ハンドル消去
	DeleteSoundMem(m_handle); 
	//ロード記録を消去
	if (is_vector_erase == TRUE) { ClAudioMult::GetIns()->VectorAudioFindErase(this); }
}

