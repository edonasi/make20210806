#pragma once

#include IMG_HPP	//�p���Ɏg�p
#include<vector>	//�����摜�̃n���h���Ɏg�p
#include CNT_HPP	//�����摜�̃J�E���^�Ɏg�p

#include XY_HPP
#include RECT_HPP
#include CIRCLE_HPP
#include COLL_CIRCLE_HPP

namespace n_img_div {
	//�����摜�Ǘ��N���X
	class ClImgDiv:public n_img::ClImg{
	public:
		ClImgDiv();
		~ClImgDiv();

		//		�v���p�e�B
		virtual VOID SetIsDraw(BOOL is_draw)override;	//�`�悷�邩���Ȃ���

		//		�֐�
		//n_cnt::CNT_AFTER_TYPE cnt_after�Ȃ��n��
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

		//n_cnt::CNT_AFTER_TYPE cnt_after����n��
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
		virtual VOID Draw()override;		//�摜�̕`��
		virtual VOID Delete()override;		//�摜�̃���������

	protected:
		//�摜�̓ǂݍ���
		BOOL MmLoad(
			string path,
			int div_x, int div_y, int div_max,
			int cnt_size, float all_time, n_cnt::CNT_AFTER_TYPE cnt_after,
			string cpp_name, string ins_name);

		//		�����o�ϐ�
		std::vector<int> m_div_handle;
		n_xy::ClXY m_div;
		int m_div_max;
		n_cnt::ClCntArySec m_cnt;
	private:
		//		�����o�֐�
		
		
		

		//		virtual private�ڍs(�O���g�p�֎~�p)
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
		//		�R���X�g���N�^
		ClImgDivColl();
		~ClImgDivColl();

		//		�v���p�e�B
		n_circle::ClCircle GetColl();
		int GetRadius();
		BOOL GetIsDraw();
		int GetAbsSpeed();
		n_xy::ClXY GetSize();
		VOID SetIsDraw()override;
		VOID SetIsDraw(BOOL is_set)override;
		VOID SetIsDraw(BOOL is_draw, BOOL is_coll);

		//		�֐�
		BOOL Load(string path, int div_x, int div_y, int div_max,
			string cpp_name, string ins_name)override;
		VOID Draw()override;
		VOID Draw(BOOL is_coll_draw);
		VOID CollDebugDraw();
		VOID Delete()override;
		VOID Move(int x_mult, int y_mult)override;
		VOID SetMove(int x, int y);
		//�����蔻��
		BOOL IsStay(n_xy::ClXY point);
		BOOL IsStay(n_rect::ClRect rect);
		BOOL IsStay(n_circle::ClCircle circle);

	private:

		//		�����o�ϐ�
		n_coll_circle::ClCollCircle m_coll;
	};

	
}