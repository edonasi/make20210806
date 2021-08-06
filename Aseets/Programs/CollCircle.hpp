#pragma once

#include COLL_HPP

#include XY_HPP
//�����蔻��͈͂Ɏg�p
#include RECT_HPP
#include CIRCLE_HPP

namespace n_coll_circle {
	class ClCollCircle:public n_coll::ClColl{
	public:
		ClCollCircle();
		~ClCollCircle();

		//		�v���p�e�B
		int GetRadius();
		n_circle::ClCircle GetColl();		//�����蔻��͈͂��Q��
		VOID SetColl(int x, int y, int radius);//�����蔻��͈͂�ݒ�(is_coll=FALSE�ł��\)

		//		�֐�
		VOID Update(int x, int y);		//�����蔻����X�V
		//�~�Ɠ_
		BOOL IsStay(n_xy::ClXY point);
		//BOOL IsStay(n_coll_point::ClCollPoint point, n_com::IF_CASE_WHICH if_case);
		//�~�Ƌ�`
		BOOL IsStay(n_rect::ClRect rect);		//�����蔻�肪���̒��ɓ�������
		//BOOL IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case);		//�����蔻�肪���̒��ɓ�������
		//�~�Ɖ~
		BOOL IsStay(n_circle::ClCircle circle);
		//�f�o�b�N�`��
		VOID DrawDebug();
		VOID DrawDebug(unsigned int color);
		VOID DrawDebug(unsigned int color, int thick);

	private:
		//		�����o�ϐ�
		n_circle::ClCircle m_coll;
	};

	
}