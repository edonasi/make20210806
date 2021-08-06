#pragma once

#include IMG_HPP	//継承に使用
#include<vector>	//分割画像のハンドルに使用
#include CNT_HPP	//分割画像のカウンタに使用

namespace n_img_div {
	//分割画像管理クラス
	class ClImgDiv:public n_img::ClImg{
	public:
		ClImgDiv();
		~ClImgDiv();

		//		プロパティ
		VOID SetIsDraw(BOOL is_draw)override;	//描画するかしないか

		//		関数
		//n_cnt::CNT_AFTER_TYPE cnt_afterなし系列
		BOOL Load(
			string path, int div_x, int div_y, int div_max,
			string cpp_name, string ins_name);
		BOOL Load(
			string path, int abs_speed, 
			int div_x, int div_y, int div_max,
			string cpp_name, string ins_name);
		BOOL Load(
			string path, int abs_speed, BOOL is_draw,
			int div_x, int div_y, int div_max,
			string cpp_name, string ins_name);
		BOOL Load(
			string path, int div_x, int div_y, int div_max,
			string cpp_name, string ins_name, BOOL is_draw);

		//n_cnt::CNT_AFTER_TYPE cnt_afterあり系列
		BOOL Load(
			string path, int div_x, int div_y, int div_max,
			n_cnt::CNT_AFTER_TYPE cnt_after,
			string cpp_name, string ins_name);
		BOOL Load(
			string path, int abs_speed,
			int div_x, int div_y, int div_max,
			n_cnt::CNT_AFTER_TYPE cnt_after,
			string cpp_name, string ins_name);
		BOOL Load(
			string path, int abs_speed, BOOL is_draw,
			int div_x, int div_y, int div_max,
			n_cnt::CNT_AFTER_TYPE cnt_after,
			string cpp_name, string ins_name);
		BOOL Load(
			string path, int div_x, int div_y, int div_max,
			n_cnt::CNT_AFTER_TYPE cnt_after,
			string cpp_name, string ins_name, BOOL is_draw);

		//
		VOID Draw()override;		//画像の描画
		VOID Delete()override;		//画像のメモリ消去

	private:
		//		メンバ関数
		//画像の読み込み
		BOOL MmLoad(
			string path,
			int div_x, int div_y, int div_max,
			int cnt_size, float all_time, n_cnt::CNT_AFTER_TYPE cnt_after,
			string cpp_name, string ins_name);
		
		//		メンバ変数
		std::vector<int> m_div_handle;
		n_xy::ClXY m_div;
		int m_div_max;
		n_cnt::ClCntArySec m_cnt;

		//		virtual private移行(外部使用禁止用)
		BOOL Load(string path, string cpp_name, string ins_name)override;
		BOOL Load(string path, int abs_speed,
			string cpp_name, string ins_name)override;
		BOOL Load(string path, int abs_speed, BOOL is_draw,
			string cpp_name, string ins_name)override;
		BOOL Load(
			string path, string cpp_name, string ins_name, BOOL is_draw)override;
		BOOL MmLoad(string path, string cpp_name, string ins_name)override;

	};

	
}