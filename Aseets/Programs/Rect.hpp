#pragma once

//PIVOT���Ɏg�p
#include XY_HPP

namespace n_rect {
	//��`
	class ClRect{
	public:
		//�R���X�g���N�^
		ClRect();
		~ClRect();

		//�v���p�e�B
		n_xy::ClXY GetPivot(n_xy::PIVOT pivot);
		VOID SetRect(int left_in, int top_in, int right_in, int bottom_in);

		//		�ϐ�
		int left;
		int top;
		int right;
		int bottom;
	};
}