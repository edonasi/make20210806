#pragma once

#include IMG_HPP

namespace n_movie {
	class ClMovie:public n_img::ClImg{
	public:
		ClMovie();
		~ClMovie();

		//		メンバ関数
		VOID Draw()override;	//映像を描画
		VOID WinDraw();			//画面サイズに合わせて描画

	private:
		//メンバ関数
		BOOL MmLoad(string path, string cpp_name, string ins_name)override;

		//		メンバ変数
		int m_time;
	};

	
}