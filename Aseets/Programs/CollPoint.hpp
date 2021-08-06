#pragma once

#include COLL_HPP
//XY�g�p
#include XY_HPP
//
#include RECT_HPP
#include CIRCLE_HPP


namespace n_coll_point {
	class ClCollPoint:public n_coll::ClColl{
	public:
		ClCollPoint();
		~ClCollPoint();

		//		�v���p�e�B
		n_xy::ClXY GetColl();			//�����蔻��ʒu���Q��
		VOID SetColl(int x, int y);		//�����蔻��ʒu��ݒ�(is_coll=FALSE�ł��\)

		//		�֐�
		//�����蔻����X�V
		VOID Update(int x, int y);
		//�_�Ɠ_
		BOOL IsStay(n_xy::ClXY point);
		//�_�Ƌ�`
		BOOL IsStay(n_rect::ClRect rect);
		//�_�Ɖ~
		BOOL IsStay(n_circle::ClCircle circle);
		//BOOL IsStay(n_rect::ClRect rect, n_com::IF_CASE_WHICH if_case);
		//�f�o�b�N�`��
		VOID DrawDebug();
		VOID DrawDebug(unsigned int color);
		VOID DrawDebug(unsigned int color, int thick);

	private:
		//		�����o�ϐ�
		n_xy::ClXY m_coll;		//�����蔻��͈�
	};
}

//namespace n_coll_point {
//	//�_�����蔻��
//	class ClCollPoint {
//	public:
//		//		�R���X�g���N�^
//		ClCollPoint();
//		~ClCollPoint();
//
//		//		�v���p�e�B
//		n_xy::ClXY aGetColl();			//�����蔻��ʒu���Q��
//		BOOL aGetIsColl();				//�����蔻�肪�쓮���Ă��邩���Q��
//		VOID aSetColl(int x, int y);		//�����蔻��ʒu��ݒ�(is_coll=FALSE�ł��\)
//		VOID aSetIsColl(BOOL is_coll);	//�����蔻����쓮�����邩
//
//		//		�֐�
//		//�����蔻����X�V
//		VOID aUpdate(int x, int y);
//		//�_�Ɠ_
//		BOOL aIsStay(ClCollPoint point);
//		//�_�Ƌ�`
//		//BOOL aIsStay(n_coll_rect::ClCollRect rect);
//		//BOOL aIsStay(n_coll_rect::ClCollRect rect, n_com::IF_CASE_WHICH if_case);
//		//�f�o�b�N�`��
//		VOID aDrawDebug();
//		VOID aDrawDebug(unsigned int color);
//		VOID aDrawDebug(unsigned int color, int thick);
//
//	private:
//		//		�����o�֐�
//		//BOOL aMmIsCollRectEqualOut(n_coll_rect::ClCollRect rect);
//		//BOOL aMmIsCollRectEqualIn(n_coll_rect::ClCollRect rect);
//
//		//		�����o�ϐ�
//		n_xy::ClXY am_coll;		//�����蔻��͈�
//		BOOL am_is_coll;			//�����蔻��𓮍삳���邩
//	};
//}