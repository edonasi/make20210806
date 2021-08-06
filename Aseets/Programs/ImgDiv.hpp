#pragma once

#include IMG_HPP	//�p���Ɏg�p
#include<vector>	//�����摜�̃n���h���Ɏg�p
#include CNT_HPP	//�����摜�̃J�E���^�Ɏg�p

namespace n_img_div {
	//�����摜�Ǘ��N���X
	class ClImgDiv:public n_img::ClImg{
	public:
		ClImgDiv();
		~ClImgDiv();

		//		�v���p�e�B
		VOID SetIsDraw(BOOL is_draw)override;	//�`�悷�邩���Ȃ���

		//		�֐�
		//n_cnt::CNT_AFTER_TYPE cnt_after�Ȃ��n��
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
		VOID Draw()override;		//�摜�̕`��
		VOID Delete()override;		//�摜�̃���������

	private:
		//		�����o�֐�
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

	
}