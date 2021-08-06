#pragma once

#include IMG_HPP	//継承に使用
#include<vector>	//分割画像のハンドルに使用
#include CNT_HPP	//分割画像のカウンタに使用

#include XY_HPP
#include RECT_HPP
#include CIRCLE_HPP
#include COLL_CIRCLE_HPP

namespace n_img_div {
	//分割画像管理クラス
	class ClImgDiv:public n_img::ClImg{
	public:
		ClImgDiv();
		~ClImgDiv();

		//		プロパティ
		virtual VOID SetIsDraw(BOOL is_draw)override;	//描画するかしないか

		//		関数
		//n_cnt::CNT_AFTER_TYPE cnt_afterなし系列
		virtual BOOL Load(
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
		virtual VOID Draw()override;		//画像の描画
		virtual VOID Delete()override;		//画像のメモリ消去

	protected:
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
	private:
		//		メンバ関数
		
		
		

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

	class ClImgDivColl:public ClImgDiv{
	public:
		//		コンストラクタ
		ClImgDivColl();
		~ClImgDivColl();

		//		プロパティ
		n_circle::ClCircle GetColl();
		int GetRadius();
		BOOL GetIsDraw();
		int GetAbsSpeed();
		n_xy::ClXY GetSize();
		VOID SetIsDraw()override;
		VOID SetIsDraw(BOOL is_set)override;
		VOID SetIsDraw(BOOL is_draw, BOOL is_coll);

		//		関数
		BOOL Load(string path, int div_x, int div_y, int div_max,
			string cpp_name, string ins_name)override;
		VOID Draw()override;
		VOID Draw(BOOL is_coll_draw);
		VOID CollDebugDraw();
		VOID Delete()override;
		VOID Move(int x_mult, int y_mult)override;
		VOID SetMove(int x, int y);
		//当たり判定
		BOOL IsStay(n_xy::ClXY point);
		BOOL IsStay(n_rect::ClRect rect);
		BOOL IsStay(n_circle::ClCircle circle);

	private:

		//		メンバ変数
		n_coll_circle::ClCollCircle m_coll;
	};

	
}