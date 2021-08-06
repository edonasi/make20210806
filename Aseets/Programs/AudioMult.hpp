#pragma once
#include AUDIO_HPP	//音量調整などに使用
#include FADE_HPP	//フェードアウトイン処理に使用
#include<vector>	//ロードした音楽を記録する用に使用

namespace n_audio_mult {

	//Audioの音量を管理
	class ClAudioMult {

		//*----------------------------------------------------------------------------*
		//							publicここから
		//*----------------------------------------------------------------------------*

	public:

		//		シングルトン実装
		static ClAudioMult* GetIns();		//インスタンス取得
		VOID Destroy();			//インスタンスの破棄

		//		プロパティ
		int GetVecSize();					//読み込んでいる数
		//割合(0.0～1.0)
		float GetBgmDecimalPar();			//bgm音量の割合(0.0～1.0)を返す
		float GetSeSystemDecimalPar();		//seのsystemの音量の割合を返す
		float GetSePlayDecimalPar();		//seのplay	の音量の割合を返す
		//割合(0%～100%)
		int GetBgmIntPar();					//bgm音量の割合(0%～100%)を返す
		int GetSeSystemIntPar();			//seのsystem音量の割合(0%～100%)を返す
		int GetSePlayIntPar();				//seのplay	音量の割合(0%～100%)を返す

		//		関数
		VOID VectorAudioEmplace(n_audio::ClAudio* audio);	//ロードした音楽を記憶
		VOID VectorAudioFindErase(n_audio::ClAudio* audio);	//記憶した音楽の中から指定した音楽を探して消去
		VOID VectorAudioAllErase();		//記憶した音楽を全削除
		VOID VecSizeDraw();
		//		音量変更
		//64段階：マウス系統、連射系統
		VOID BgmVolumeChange64Step(BOOL is_up);			//BGM
		VOID SeSystemVolumeChange64Step(BOOL is_up);	//システム音
		VOID SePlayVolumeChange64Step(BOOL is_up);		//攻撃音系
		//16段階：キーボード系統
		VOID BgmVolumeChange16Step(BOOL is_up);			//BGM
		VOID SeSystemVolumeChange16Step(BOOL is_up);	//システム音
		VOID SePlayVolumeChange16Step(BOOL is_up);		//攻撃音系
		//音楽全体をミュート
		VOID VecMute();
		//フェードアウトイン
		VOID SetFadeUpStart(float all_time);
		VOID SetFadeDownStart(float all_time);
		VOID SetFadeDownUpStart(float all_time);
		VOID FadeProc();

		//*----------------------------------------------------------------------------*
		//							privateここから
		//*----------------------------------------------------------------------------*

	private:
		//		シングルトン実装
		static ClAudioMult* m_ins;		//シングルトンなインスタンス
		ClAudioMult();						//コンストラクタ
		ClAudioMult(const ClAudioMult& src);		//コピーコンストラクタ
		ClAudioMult& operator=(const ClAudioMult& src);
		virtual ~ClAudioMult();				//デストラクタ

		//		メンバ関数
		//音量の割合(0.0～1.0)を返す
		float MmGetAudioParcent(int m_volume);	
		//この後音量の変更を行うか
		BOOL MmIsVolumeChange(int POWER_NUM_, BOOL is_up, int* m_change_volume);
		//音量の変更
		VOID MmVolumeChange(n_audio::SE_TYPE se_type, float decimal_par);
		//SeTypeによって音量の割合を返す(0.0f～1.0f)
		float MmGetDecimalPar(n_audio::SE_TYPE se_type);

		//		メンバ変数
		std::vector<n_audio::ClAudio*> m_load_audio;
		BOOL m_is_audio_mute;		//ミュートか
		int m_bgm_volume;			//bgmのボリューム
		int m_se_system_volume;		//seのsystemのボリューム
		int m_se_play_volume;		//seのplay  のボリューム
		n_fade::ClFade m_fade;		//フェードアウトインするときに使用
	};
}