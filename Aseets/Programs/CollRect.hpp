#pragma once

#include COLL_HPP

#include XY_HPP
//�����蔻��͈͂Ɏg�p
#include RECT_HPP
#include CIRCLE_HPP

namespace n_coll_rect {
	class ClCollRect:public n_coll::ClColl
	{
	public:
		//		�R���X�g���N�^
		ClCollRect();
		~ClCollRect();

		//		�v���p�e�B
		n_rect::ClRect GetColl();		//�����蔻��͈͂��Q��
		VOID SetColl(					//�����蔻��͈͂�ݒ�(is_coll=FALSE�ł��\)
			int pos_x, int pos_y, int size_x, int size_y);

		//		�֐�
		VOID Update(int x, int y);		//�����蔻����X�V
		//��`�Ɠ_
		BOOL IsStay(n_xy::ClXY point);
		//BOOL IsStay(n_coll_point::ClCollPoint point, n_com::IF_CASE_WHICH if_case);
		//��`�Ƌ�`
		BOOL IsStay(n_rect::ClRect rect);		//�����蔻�肪���̒��ɓ�������
		//��`�Ɖ~
		BOOL IsStay(n_circle::ClCircle circle);		//�����蔻�肪���̒��ɓ�������
		//BOOL IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case);		//�����蔻�肪���̒��ɓ�������
		//�f�o�b�N�`��
		VOID DrawDebug();
		VOID DrawDebug(unsigned int color);
		VOID DrawDebug(unsigned int color, int thick);

	private:
		//		�����o�ϐ�
		n_rect::ClRect m_coll;	//�����蔻��͈�
		n_xy::ClXY m_size;
	};
}

//namespace n_coll_rect {
//	//��`�����蔻��
//	class ClCollRect {
//	public:
//		//		�R���X�g���N�^
//		ClCollRect();
//		~ClCollRect();
//
//		//		�v���p�e�B
//		n_rect::ClRect GetColl();		//�����蔻��͈͂��Q��
//		BOOL GetIsColl();				//�����蔻�肪�쓮���Ă��邩���Q��
//		VOID SetColl(					//�����蔻��͈͂�ݒ�(is_coll=FALSE�ł��\)
//			int left, int top, int right, int bottom);
//		VOID SetIsColl(BOOL is_coll);	//�����蔻����쓮�����邩
//
//		//		�֐�
//		VOID Update(int left, int top, int right, int bottom);		//�����蔻����X�V
//		//��`�Ɠ_
//		//BOOL IsStay(n_coll_point::ClCollPoint point);
//		//BOOL IsStay(n_coll_point::ClCollPoint point, n_com::IF_CASE_WHICH if_case);
//		//��`�Ƌ�`
//		BOOL IsStay(ClCollRect rect);		//�����蔻�肪���̒��ɓ�������
//		BOOL IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case);		//�����蔻�肪���̒��ɓ�������
//		//�f�o�b�N�`��
//		VOID DrawDebug();
//		VOID DrawDebug(unsigned int color);
//		VOID DrawDebug(unsigned int color, int thick);
//
//
//	private:
//		//		�����o�֐�
//		//BOOL MmIsCollPointEqualOut(n_coll_point::ClCollPoint point);
//		//BOOL MmIsCollPointEqualIn(n_coll_point::ClCollPoint point);
//		BOOL MmIsCollRectEqualOut(ClCollRect rect);
//		BOOL MmIsCollRectEqualIn(ClCollRect rect);
//
//		//		�����o�ϐ�
//		n_rect::ClRect m_coll;	//�����蔻��͈�
//		BOOL m_is_coll;			//�����蔻��𓮍삳���邩
//	};
//
//}