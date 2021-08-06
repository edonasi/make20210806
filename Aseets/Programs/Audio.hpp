#pragma once

namespace n_audio{

	//		enum
	//音楽の種類
	enum SE_TYPE {
		BGM,		//bgm
		SYSTEM,		//クリック音などのシステム音
		PLAY,		//攻撃音などの音
	};

	//音楽の管理
	class ClAudio{
		//*----------------------------------------------------------------------------*
		//							publicここから
		//*----------------------------------------------------------------------------*

	public:
		//		コンストラクタ、デストラクタ、変数の初期化
		ClAudio();
		/*ClAudio(const ClAudio& src);
		ClAudio& operator=(const ClAudio& src);*/
		~ClAudio();

		//		プロパティ
		int GetAudioHandle();		//ハンドルを取得
		int GetProductVolume();		//音量(制作者調整用)を取得
		SE_TYPE GetSeType();		//音楽の種類を取得

		//		関数
		//Bgm読み込み
		BOOL BgmLoad(string path, string cpp_name, string ins_name);
		BOOL BgmLoad(string path, int volume, string cpp_name, string ins_name);
		
		//Se 読み込み
		BOOL SeLoad(
			string path,SE_TYPE se_type,
			string cpp_name, string ins_name);
		BOOL SeLoad(
			string path, int volume, SE_TYPE se_type,
			string cpp_name, string ins_name);

		VOID Sound();	//音楽を再生
		VOID Stop();	//音楽を停止
		VOID Delete(BOOL is_vector_erase);	//音楽のメモリ消去


		//*----------------------------------------------------------------------------*
		//							privateここから
		//*----------------------------------------------------------------------------*

	private:
		//		メンバ関数
		BOOL MmLoad(					//音楽読み込み共通関数
			string path, string cpp_name, string ins_name);		
		VOID MmLoadVolume(int volume);	//音量の読み込み

		//		メンバ変数
		int m_handle;			//ハンドル
		string m_path;			//パス
		int m_product_volume;	//音量(制作者調整用)
		int m_play_type;		//再生方式
		SE_TYPE m_se_type;	//音楽の種類
	};
}
