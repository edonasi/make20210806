#pragma once

//		�C���N���[�h�t�@�C��
//XY�g�p
#include XY_HPP

namespace n_circle {
	//��
	class ClCircle{
	public:
		//		�R���X�g���N�^
		ClCircle();
		~ClCircle();

		//		�v���p�e�B
		VOID SetPos(int x,int y);
		VOID SetRadius(int radius_in);
		VOID SetCircle(int x,int y,int radius_in);

		//		�ϐ�
		n_xy::ClXY center;
		int radius;
	};
}