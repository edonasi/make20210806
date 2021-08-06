#pragma once

//		�C���N���[�h�t�@�C��
#include XY_HPP
#include RECT_HPP
#include CIRCLE_HPP

namespace n_coll {
	//Coll�̋��ʍ���
	class ClColl{
	public:
		//		�R���X�g���N�^
		ClColl();
		~ClColl();

		//		�v���p�e�B
		BOOL GetIsColl();				//�����蔻�肪�쓮���Ă��邩���Q��
		VOID SetIsColl(BOOL is_coll);	//�����蔻����쓮�����邩

	protected:
		

		//		�֐�
		BOOL MmIsStay(n_xy::ClXY m_point, n_xy::ClXY point);
		BOOL MmIsStay(n_xy::ClXY m_point, n_rect::ClRect rect);
		BOOL MmIsStay(n_xy::ClXY m_point, n_circle::ClCircle circle);
		BOOL MmIsStay(n_rect::ClRect m_rect, n_rect::ClRect rect);
		BOOL MmIsStay(n_rect::ClRect m_rect, n_xy::ClXY point);
		BOOL MmIsStay(n_rect::ClRect m_rect, n_circle::ClCircle circle);
		BOOL MmIsStay(n_circle::ClCircle m_circle, n_circle::ClCircle circle);
		BOOL MmIsStay(n_circle::ClCircle m_circle, n_xy::ClXY point);
		BOOL MmIsStay(n_circle::ClCircle m_circle, n_rect::ClRect rect);
		

		//		�v���e�N�g�ϐ�
		BOOL m_is_coll;		//�����蔻��𓮍삳���邩

	private:
		//		�����o�֐�
		BOOL MmIsCollEqualOut(n_xy::ClXY m_point, n_rect::ClRect rect);
		BOOL MmIsCollEqualIn(n_xy::ClXY m_point, n_rect::ClRect rect);

		BOOL MmIsCollEqualIn(n_xy::ClXY m_point, n_circle::ClCircle circle);
		BOOL MmIsCollEqualOut(n_rect::ClRect m_rect, n_rect::ClRect rect);
		BOOL MmIsCollEqualIn(n_rect::ClRect m_rect, n_rect::ClRect rect);
		BOOL MmIsCollEqualOut(n_rect::ClRect m_rect, n_xy::ClXY point);
		BOOL MmIsCollEqualIn(n_rect::ClRect m_rect, n_xy::ClXY point);

		BOOL MmIsCollEqualIn(n_rect::ClRect m_rect, n_circle::ClCircle circle);

		BOOL MmIsCollEqualIn(n_circle::ClCircle m_circle, n_circle::ClCircle circle);

		BOOL MmIsCollEqualIn(n_circle::ClCircle m_circle, n_xy::ClXY point);

		BOOL MmIsCollEqualIn(n_circle::ClCircle m_circle, n_rect::ClRect rect);
	};
}

//
////		�C���N���[�h�t�@�C��
//
////Circle���g�p
//#include CIRCLE_HPP
////Rect���g�p
//#include RECT_HPP
////XY�g�p
//#include XY_HPP
//
//namespace n_coll {
//	//�_�����蔻��
//	class ClCollPoint{
//	public:
//		//		�R���X�g���N�^
//		ClCollPoint();
//		~ClCollPoint();
//
//		//		�v���p�e�B
//		n_xy::ClXY GetColl();			//�����蔻��ʒu���Q��
//		BOOL GetIsColl();				//�����蔻�肪�쓮���Ă��邩���Q��
//		VOID SetColl(int x, int y);		//�����蔻��ʒu��ݒ�(is_coll=FALSE�ł��\)
//		VOID SetIsColl(BOOL is_coll);	//�����蔻����쓮�����邩
//		
//		//		�֐�
//		//�����蔻����X�V
//		VOID Update(int x, int y);
//		//�_�Ɠ_
//		BOOL IsStay(ClCollPoint point);
//		//�_�Ƌ�`
//		BOOL IsStay(ClCollRect rect);		
//		BOOL IsStay(ClCollRect rect, n_com::IF_CASE_WHICH if_case);
//		//�f�o�b�N�`��
//		VOID DrawDebug();
//		VOID DrawDebug(unsigned int color);
//		VOID DrawDebug(unsigned int color, int thick);
//
//	private:
//		//		�����o�֐�
//		//		�����o�֐�
//		BOOL MmIsCollRectEqualOut(ClCollRect rect);
//		BOOL MmIsCollRectEqualIn(ClCollRect rect);
//
//		//		�����o�ϐ�
//		n_xy::ClXY m_coll;		//�����蔻��͈�
//		BOOL m_is_coll;			//�����蔻��𓮍삳���邩
//	};
//
//	//��`�����蔻��
//	class ClCollRect{
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
//		BOOL IsStay(ClCollPoint point);
//		BOOL IsStay(ClCollPoint point, n_com::IF_CASE_WHICH if_case);
//		//��`�Ƌ�`
//		BOOL IsStay(ClCollRect rect);		//�����蔻�肪���̒��ɓ�������
//		BOOL IsStay(ClCollRect rect,n_com::IF_CASE_WHICH if_case);		//�����蔻�肪���̒��ɓ�������
//		//�f�o�b�N�`��
//		VOID DrawDebug();
//		VOID DrawDebug(unsigned int color);
//		VOID DrawDebug(unsigned int color, int thick);
//		
//
//	private:
//		//		�����o�֐�
//		BOOL MmIsCollRectEqualOut(ClCollRect rect);
//		BOOL MmIsCollRectEqualIn(ClCollRect rect);
//
//		//		�����o�ϐ�
//		n_rect::ClRect m_coll;	//�����蔻��͈�
//		BOOL m_is_coll;			//�����蔻��𓮍삳���邩
//	};
//
//	
//
//	//class ClCollCircle{
//	//public:
//	//	ClCollCircle();
//	//	~ClCollCircle();
//
//	//	//		�v���p�e�B
//	//	n_circle::ClCircle GetColl();
//
//	//private:
//	//	n_circle::ClCircle m_coll;
//	//};
//
//	
//}