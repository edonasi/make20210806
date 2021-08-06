//*--------------------------------------------------------------------------------*
//								Audioの音量を管理
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include AUDIO_MULT_HPP
using namespace n_audio_mult;

//*--------------------------------------------------------------------------------*
//								シングルトン実装
//*--------------------------------------------------------------------------------*

ClAudioMult* ClAudioMult::m_ins = nullptr;		//シングルトンなインスタンス

//インスタンス取得
ClAudioMult* ClAudioMult::GetIns() {

	//初めて取得する時、そのオブジェクトを生成
	if (m_ins == nullptr)
	{
		//メモリの確保
		m_ins = new ClAudioMult();
	}

	return m_ins;
}

//コンストラクタ
ClAudioMult::ClAudioMult() { 

	m_is_audio_mute = FALSE;	//音楽が流れる状態
	//ボリューム初期値を設定
	m_bgm_volume = ClCom().GetUnCharHalf();
	m_se_system_volume = ClCom().GetUnCharHalf();
	m_se_play_volume = ClCom().GetUnCharHalf();
	m_fade = n_fade::ClFade();

	return;
}

/// <summary>
/// コピーコンストラクタ
/// </summary>
/// <param name="src">コピー元アドレス</param>
ClAudioMult::ClAudioMult(const ClAudioMult& src) {

	//アドレスをコピーしておく
	m_ins = src.m_ins;
}

/// <summary>
/// コピーコンストラクタ
/// </summary>
/// <param name="src">コピー元アドレス</param>
/// <returns>このインスタンスのアドレス</returns>
ClAudioMult& ClAudioMult::operator=(const ClAudioMult& src) {

	//アドレスをコピーしておく
	m_ins = src.m_ins;
	return *this;
}

//デストラクタ
ClAudioMult::~ClAudioMult() { return; }

//*------------------------------------------------*
//		インスタンスの破棄
//*------------------------------------------------*

//インスタンスの破棄
VOID ClAudioMult::Destroy() {

	delete m_ins;
	m_ins = nullptr;
}

//*--------------------------------------------------------------------------------*
//								プロパティ
//*--------------------------------------------------------------------------------*

//読み込んだ音楽の数
int ClAudioMult::GetVecSize() { return m_load_audio.size(); }

//*------------------------------------------------*
//		割合(0.0～1.0)
//*------------------------------------------------*

//bgm音量の割合(0.0～1.0)を返す
float ClAudioMult::GetBgmDecimalPar() { return MmGetAudioParcent(m_bgm_volume); }

//seのsystem音量の小数割合を返す
float ClAudioMult::GetSeSystemDecimalPar() { return MmGetAudioParcent(m_se_system_volume); }

//seのplay	音量の小数割合を返す
float ClAudioMult::GetSePlayDecimalPar() { return MmGetAudioParcent(m_se_play_volume); }

//*------------------------------------------------*
//		割合(0%～100%)
//*------------------------------------------------*

//bgm音量の割合(0%～100%)を返す
int ClAudioMult::GetBgmIntPar() { return static_cast<int>(MmGetAudioParcent(m_bgm_volume) * 100); }

//seのsystem音量の割合(0%～100%)を返す
int ClAudioMult::GetSeSystemIntPar() { return static_cast<int>(MmGetAudioParcent(m_se_system_volume) * 100); }

//seのplay	音量の割合(0%～100%)を返す
int ClAudioMult::GetSePlayIntPar() { return static_cast<int>(MmGetAudioParcent(m_se_play_volume) * 100); }

//*------------------------------------------------*
//		共通関数
//*------------------------------------------------*

/// <summary>
/// 音量の割合(0.0～1.0)を返す
/// </summary>
/// <param name="m_volume">音量の種類</param>
/// <returns>音量の割合(0.0～1.0)</returns>
float ClAudioMult::MmGetAudioParcent(int m_volume) {
	float bgm_float = static_cast<float>(m_volume);
	float max_float = static_cast<float>(ClCom().GetUnCharMax());
	return  bgm_float / max_float;
}

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

/// <summary>
/// ロードした音楽を記録
/// </summary>
/// <param name="audio">記憶するClAudioポインタ</param>
VOID ClAudioMult::VectorAudioEmplace(n_audio::ClAudio* audio) {
	m_load_audio.emplace_back(audio);
}

/// <summary>
/// 記憶した音楽の中から1つの指定した音楽を探して消去
/// </summary>
/// <param name="audio">ロード記録を消す音楽</param>
VOID ClAudioMult::VectorAudioFindErase(n_audio::ClAudio* audio) {
	auto itr = m_load_audio.begin();
	while (itr != m_load_audio.end()) {
		//指定した音楽を捜査してvectorから消去
		if (((*itr) == audio)) {
			itr = m_load_audio.erase(itr);
			return;
		}
		else { itr++; }
	}
}	

//記憶した音楽を全削除(https://blog.dalt.me/666)
VOID ClAudioMult::VectorAudioAllErase() {
	auto itr = m_load_audio.begin();
	while (itr != m_load_audio.end()) { itr = m_load_audio.erase(itr); }
}

//
VOID ClAudioMult::VecSizeDraw() {
	DrawFormatString(0, 0, ClCom().GetFlipColor(), "%d", m_load_audio.size());
}

//*------------------------------------------------*
//		64段階：マウス系統、連射系統
//*------------------------------------------------*

const int POWER_NUM_04_INDEX = 2;	//64段階：マウス系統

/// <summary>
/// BGMの音量を変更(64段階)
/// </summary>
/// <param name="plas_volume">音量変更量(TRUEで大きく、FALSEで小さく)</param>
VOID ClAudioMult::BgmVolumeChange64Step(BOOL is_up) {
	//ミュート状態のときは音量を変更しない(0のまま)
	if (MmIsVolumeChange(POWER_NUM_04_INDEX, is_up, &m_bgm_volume) == FALSE) { return; }

	//音量の変更
	MmVolumeChange(n_audio::SE_TYPE::BGM, GetBgmDecimalPar());
}

/// <summary>
/// SeのSystem音量を変更(64段階)
/// </summary>
/// <param name="is_up">音量変更量(TRUEで大きく、FALSEで小さく)</param>
VOID ClAudioMult::SeSystemVolumeChange64Step(BOOL is_up) {
	//ミュート状態のときは音量を変更しない(0のまま)
	if (MmIsVolumeChange(POWER_NUM_04_INDEX, is_up, &m_se_system_volume) == FALSE) { return; }

	//音量の変更
	MmVolumeChange(n_audio::SE_TYPE::SYSTEM, GetSeSystemDecimalPar());
}	

/// <summary>
/// SeのPlay音量を変更(64段階)
/// </summary>
/// <param name="is_up">音量変更量(TRUEで大きく、FALSEで小さく)</param>
VOID ClAudioMult::SePlayVolumeChange64Step(BOOL is_up) {
	//ミュート状態のときは音量を変更しない(0のまま)
	if (MmIsVolumeChange(POWER_NUM_04_INDEX, is_up, &m_se_play_volume) == FALSE) { return; }

	//音量の変更
	MmVolumeChange(n_audio::SE_TYPE::PLAY, GetSePlayDecimalPar());
}

//*------------------------------------------------*
//		16段階：キーボード系統
//*------------------------------------------------*

const int POWER_NUM_16_INDEX = 4;	//16段階：キーボード系統

/// <summary>
/// BGMの音量を変更(16段階)
/// </summary>
/// <param name="is_up">音量変更量(TRUEで大きく、FALSEで小さく)</param>
VOID ClAudioMult::BgmVolumeChange16Step(BOOL is_up) {
	//ミュート状態のときは音量を変更しない(0のまま)
	if (MmIsVolumeChange(POWER_NUM_16_INDEX, is_up, &m_bgm_volume) == FALSE) { return; }

	//音量の変更
	MmVolumeChange(n_audio::SE_TYPE::BGM, GetBgmDecimalPar());
}

/// <summary>
/// SeのSystem音量を変更(16段階)
/// </summary>
/// <param name="is_up">音量変更量(TRUEで大きく、FALSEで小さく)</param>
VOID ClAudioMult::SeSystemVolumeChange16Step(BOOL is_up) {
	//ミュート状態のときは音量を変更しない(0のまま)
	if (MmIsVolumeChange(POWER_NUM_16_INDEX, is_up, &m_se_system_volume) == FALSE) { return; }

	//音量の変更
	MmVolumeChange(n_audio::SE_TYPE::SYSTEM, GetSeSystemDecimalPar());
}	

/// <summary>
/// SeのPlay音量を変更(16段階)
/// </summary>
/// <param name="is_up">音量変更量(TRUEで大きく、FALSEで小さく)</param>
VOID ClAudioMult::SePlayVolumeChange16Step(BOOL is_up) {
	//ミュート状態のときは音量を変更しない(0のまま)
	if (MmIsVolumeChange(POWER_NUM_16_INDEX, is_up, &m_se_play_volume) == FALSE) { return; }

	//音量の変更
	MmVolumeChange(n_audio::SE_TYPE::PLAY, GetSePlayDecimalPar());
}

//*------------------------------------------------*
//		共通関数
//*------------------------------------------------*

const int ZERO = 0;		//0より小さいやつで使用
const int EVEN_FIX = 1;	//音量が255(奇数の最大値)のとき偶数に整える

/// <summary>
/// この後音量の変更を行うか
/// </summary>
/// <param name="POWER_NUM_">変更する量のindex</param>
/// <param name="is_up">上げるか下げるかの引数</param>
/// <param name="m_change_volume">どの音量を変更するか</param>
/// <returns>この後音量の変更を行うならTRUE</returns>
BOOL ClAudioMult::MmIsVolumeChange(int POWER_NUM_, BOOL is_up, int* m_change_volume) {
	//変更する音量の量を計算
	int volume = ClCom().GetPowerNumPlas(POWER_NUM_);
	int plas_volume = (is_up == TRUE) ? volume : -volume;

	//音量の変更
	if (*m_change_volume == ClCom().GetUnCharMax() && plas_volume < ZERO) {
		//音量最大値の時で音量を下げる場合のときは下げた結果が偶数になるように調整
		*m_change_volume += plas_volume + EVEN_FIX;
	}
	else {
		*m_change_volume += plas_volume;
		//0未満、255より上にならないように調整
		if (*m_change_volume > ClCom().GetUnCharMax()) { *m_change_volume = ClCom().GetUnCharMax(); }
		if (*m_change_volume < ClCom().GetUnCharMin()) { *m_change_volume = ClCom().GetUnCharMin(); }
	}

	//ミュート状態のときは音量を変更しない(0のまま)
	if (m_is_audio_mute == TRUE) { return FALSE; }

	//音量の変更を行う
	return TRUE;
}

/// <summary>
/// 音量の変更
/// </summary>
/// <param name="se_type">音量の種類</param>
/// <param name="decimal_par">se_typeによっての係数</param>
VOID ClAudioMult::MmVolumeChange(n_audio::SE_TYPE se_type, float decimal_par) {
	//se_typeの読み込んだ音量を捜査
	for (unsigned int i = 0; i < m_load_audio.size(); i++) {
		if (m_load_audio[i]->GetSeType() == se_type) {
			//音量を変更
			ChangeVolumeSoundMem(
				static_cast<int>(m_load_audio[i]->GetProductVolume() * decimal_par)
				, m_load_audio[i]->GetAudioHandle());
		}
	}
}

//*------------------------------------------------*
//		音楽全体をミュート
//*------------------------------------------------*

/// <summary>
/// 音楽全体をミュートにする
/// </summary>
VOID ClAudioMult::VecMute() {
	//ミュート状態のときはミュート解除
	if (m_is_audio_mute == TRUE) {
		for (unsigned int i = 0; i < m_load_audio.size(); i++) {
			//音楽の種類によって音量の割合を計算
			float decimal_par = MmGetDecimalPar(m_load_audio[i]->GetSeType());

			//音量の変更
			ChangeVolumeSoundMem(
				static_cast<int>(m_load_audio[i]->GetProductVolume() * decimal_par)
				, m_load_audio[i]->GetAudioHandle());
		}
		//ミュート状態ではないフラグ
		m_is_audio_mute = FALSE;

	}	//ミュート状態ではないときは音量をゼロに
	else {
		for (unsigned int i = 0; i < m_load_audio.size(); i++) {
			ChangeVolumeSoundMem(0/*無音状態*/, m_load_audio[i]->GetAudioHandle());
		}
		//ミュート状態フラグ
		m_is_audio_mute = TRUE;
	}
}

/// <summary>
/// SeTypeによって音量の割合を返す(0.0f～1.0f)
/// </summary>
/// <param name="se_type">音楽の種類</param>
/// <returns>SeTypeによって音量の割合(0.0f～1.0f)</returns>
float ClAudioMult::MmGetDecimalPar(n_audio::SE_TYPE se_type) {
	switch (se_type){
		//BGM
	case n_audio::SE_TYPE::BGM:
		return GetBgmDecimalPar();
		break;

		//システム音
	case n_audio::SE_TYPE::SYSTEM:
		return GetSeSystemDecimalPar();
		break;

		//プレイ音楽
	case n_audio::SE_TYPE::PLAY:
		return GetSePlayDecimalPar();
		break;

	default:break;
	}
	return 0.0f;	//音量が急にでかくならないように
}

//*------------------------------------------------*
//		音量フェード
//*------------------------------------------------*

/// <summary>
/// 音量フェードアップ開始処理(音楽のメモリを消したり、音楽の再生を切ったりする処理は別途)
/// </summary>
/// <param name="all_time">フェードにかかる時間</param>
VOID ClAudioMult::SetFadeUpStart(float all_time) {
	//ミュートのときは行わない(※実際には必要ない音楽を消去)
	if (m_is_audio_mute == TRUE) { return; }

	//開始処理
	m_fade.FadeUpStart(all_time);
}

/// <summary>
/// 音量フェードダウン開始処理(音楽のメモリを消したり、音楽の再生を切ったりする処理は別途)
/// </summary>
/// <param name="all_time">フェードにかかる時間</param>
VOID ClAudioMult::SetFadeDownStart(float all_time) {
	//ミュートのときは行わない(※実際には必要ない音楽を消去)
	if (m_is_audio_mute == TRUE) { return; }

	//開始処理
	m_fade.FadeDownStart(all_time);
}

/// <summary>
/// 音量フェードダウンアップ開始処理(音楽のメモリを消したり、音楽の再生を切ったりする処理は別途)
/// </summary>
/// <param name="all_time">フェードにかかる時間</param>
VOID ClAudioMult::SetFadeDownUpStart(float all_time) {
	//ミュートのときは行わない(※実際には必要ない音楽を消去)
	if (m_is_audio_mute == TRUE) { return; }

	//開始処理
	m_fade.FadeDownUpStart(all_time);
}

//フェードが終了したときに音切れが起きないようにする
const float FADE_MIN_MULT = 0.0f;	
const float FADE_MAX_MULT = 1.0f;	

//音量フェード処理(音楽のメモリを消したり、音楽の再生を切ったりする処理は別途)
VOID ClAudioMult::FadeProc() {
	//ミュートのときは行わない(※実際には必要ない音楽を消去)
	if (m_is_audio_mute == TRUE) { return; }
	//フェードを行っていないなら処理を行わない
	if (m_fade.GetIsFadeNone() == TRUE) { return; }

	//フェードカウンタ処理
	m_fade.FadeProc();

	//音量をフェード
	for (unsigned int i = 0; i < m_load_audio.size(); i++) {
		//音楽の種類によって音量の割合を計算
		float decimal_par = MmGetDecimalPar(m_load_audio[i]->GetSeType());

		//音量を変更
		if (m_fade.GetIsFadeStop() == FALSE) {
			ChangeVolumeSoundMem(
				static_cast<int>(m_load_audio[i]->GetProductVolume() * decimal_par * m_fade.GetFadeDecimalPar()),
				m_load_audio[i]->GetAudioHandle());
		}
		else {	
			//終了時音量調整
			switch (m_fade.GetFadeType()){
				//音量割合を1.0fに
			case n_fade::FADE_TYPE::FADE_DOWN_UP_TYPE:
			case n_fade::FADE_TYPE::FADE_UP_TYPE:
				ChangeVolumeSoundMem(
					static_cast<int>(m_load_audio[i]->GetProductVolume() * decimal_par * FADE_MAX_MULT),
					m_load_audio[i]->GetAudioHandle());
				break;

				//音量割合を0.0fに
			case n_fade::FADE_TYPE::FADE_UP_DOWN_TYPE:
			case n_fade::FADE_TYPE::FADE_DOWN_TYPE:
				ChangeVolumeSoundMem(
					static_cast<int>(m_load_audio[i]->GetProductVolume() * decimal_par * FADE_MIN_MULT),
					m_load_audio[i]->GetAudioHandle());
				break;
			default:break;
			}
			
		}
	}
}