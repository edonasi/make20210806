#pragma once

#include RECT_HPP
#include IMG_HPP
#include COLL_RECT_HPP

#include CIRCLE_HPP
#include COLL_CIRCLE_HPP

namespace n_img_coll {

	class ClImgColl :public n_img::ClImg{
	public:
		//		�R���X�g���N�^
		ClImgColl();
		~ClImgColl();

		//		�v���p�e�B
		n_rect::ClRect GetCollRect();
		n_xy::ClXY GetSize();
		VOID SetIsDraw()override;
		VOID SetIsDraw(BOOL is_set)override;
		VOID SetIsDraw(BOOL is_draw, BOOL is_coll);

		//		�֐�
		BOOL Load(string path, string cpp_name, string ins_name)override;
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
		n_coll_rect::ClCollRect m_coll_rect;
	};



	class ClImgCollCircle :public n_img::ClImg{
	public:
		//		�R���X�g���N�^
		ClImgCollCircle();
		~ClImgCollCircle();

		//		�v���p�e�B
		n_circle::ClCircle GetCollCircle();
		BOOL GetIsDraw();
		int GetRadius();
		VOID SetIsDraw()override;
		VOID SetIsDraw(BOOL is_set)override;
		VOID SetIsDraw(BOOL is_draw, BOOL is_coll);

		//		�֐�
		BOOL Load(string path, string cpp_name, string ins_name)override;
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
		n_coll_circle::ClCollCircle m_coll_circle;
	};

	
}

