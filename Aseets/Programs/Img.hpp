#pragma once
//�C���N���[�h�t�@�C��
#include XY_HPP	//XY��PIVOT�Ȃ�

namespace n_img {
	//		enum
	//�ړ�����
	enum MOVE_LINE_TYPE {
		UP_LEFT,	//����@
		UP,			//�@��
		UP_RIGHT,	//�E��
		LEFT,		//��
		STOP,		//��~
		RIGHT,		//�E
		DOWN_LEFT,	//����
		DOWN,		//�@��
		DOWN_RIGHT	//�E��
	};

	//�ړ����鎞�A�ړ������W���ȊO�łǂ̕ϐ����W���ɂ��邩					
	enum MOVE_MULT {
		ABS_SPEED,	//m_abs_speed�̕ϐ����W���Ƃ��Ĉړ�(delta�͊֌W�Ȃ�)
		DELTA		//m_abs_speed�̕ϐ����W���Ƃ���delta�������Ĉړ�
	};

	//�摜�Ǘ��̊��N���X
	class ClImg{
		//*----------------------------------------------------------------------------*
		//							public��������
		//*----------------------------------------------------------------------------*

	public:
		//		�R���X�g���N�^�A�f�X�g���N�^�A�ϐ��̏�����
		ClImg();
		~ClImg();

		//		�v���p�e�B
		n_xy::ClXY GetPos();
		virtual VOID SetIsDraw();					//�`���Ԃ�ON�ɂ���
		virtual VOID SetIsDraw(BOOL is_draw);		//�`�悷�邩���Ȃ���
		VOID SetAbsSpeed(int abs_speed);			//���̒l�̃X�s�[�h��ݒ�

		//		�֐�
		//�摜�ǂݍ���
		virtual BOOL Load(string path, string cpp_name, string ins_name);
		virtual BOOL Load(string path, int abs_speed,
			string cpp_name, string ins_name);
		virtual BOOL Load(string path, int abs_speed, BOOL is_draw,
			string cpp_name, string ins_name);
		virtual BOOL Load(
			string path, string cpp_name, string ins_name, BOOL is_draw);

		//
		virtual VOID Draw();		//���ߕ`��
		virtual VOID Delete();		//�摜����������

		//		�ړ�
		virtual VOID Move(int x_mult, int y_mult);		//�摜�̈ړ�
		VOID Move(
			int x_mult, int y_mult, MOVE_MULT move_mult);
		VOID Move(MOVE_LINE_TYPE move_type);//���������Ɉړ�	

		//		��ʑ��Έʒu�ɉ摜�̈ʒu��ݒ�
		//(���)����[�F����[
		VOID SetPos();
		//(���)����[�F����[ + margin
		VOID SetPos(int margin_x, int margin_y);
		//(���)Pivot�FPivot
		VOID SetPos(n_xy::PIVOT win_pivot, n_xy::PIVOT img_pivot);
		//(���)Pivot�FPivot + margin
		VOID SetPos(n_xy::PIVOT win_pivot, n_xy::PIVOT img_pivot,
			int margin_x, int margin_y
		);

		//		�w��摜�̑��Έʒu�ɉ摜�̈ʒu��ݒ�
		//(��_�摜)����[�F����[
		VOID SetPos(ClImg base_img);
		//(��_�摜)����[�F����[ + margin
		VOID SetPos(ClImg base_img, int margin_x, int margin_y);
		//(��_�摜)Pivot�FPivot
		VOID SetPos(ClImg base_img,
			n_xy::PIVOT base_pivot, n_xy::PIVOT this_pivot);
		//(��_�摜)Pivot�FPivot + margin
		VOID SetPos(ClImg base_img,
			n_xy::PIVOT base_pivot, n_xy::PIVOT this_pivot,
			int margin_x, int margin_y);

		//*----------------------------------------------------------------------------*
		//							protected��������
		//*----------------------------------------------------------------------------*

	protected:
		//		�v���e�N�g�֐�
		//���ʉ摜�̓ǂݍ���
		virtual BOOL MmLoad(string path, string cpp_name, string ins_name);

		//		�v���e�N�g�ϐ�
		int m_handle;			//�摜�n���h��
		string m_path;			//�p�X
		n_xy::ClXY m_pos;			//�ʒu
		n_xy::ClXY m_size;		//�T�C�Y
		int m_abs_speed;		//�ړ��X�s�[�h
		float m_over_speed;		//�ړ��X�s�[�h�̏����_�ȉ�
		BOOL m_is_draw;			//�`�悷�邩
	};



	//class IMG_COLL:public ClImg{
	//public:
	//	IMG_COLL();
	//	~IMG_COLL();

	//	//		�֐�
	//	BOOL Load(string path, string cpp_name, string ins_name)override;
	//	BOOL Load(string path, int abs_speed,
	//		string cpp_name, string ins_name)override;
	//	BOOL Load(string path, int abs_speed, BOOL is_draw,
	//		string cpp_name, string ins_name)override;
	//	BOOL Load(
	//		string path, string cpp_name, string ins_name, BOOL is_draw)override;
	//	VOID Draw()override;

	//	//		�ړ�
	//	VOID Move(int x_mult, int y_mult)override;		//�摜�̈ړ�
	//	VOID Move(
	//		int x_mult, int y_mult, MOVE_MULT move_mult)override;
	//	VOID Move(MOVE_LINE_TYPE move_type)override;//���������Ɉړ�	

	//	//		��ʑ��Έʒu�ɉ摜�̈ʒu��ݒ�
	//	//(���)����[�F����[
	//	VOID SetPos()override;
	//	//(���)����[�F����[ + margin
	//	VOID SetPos(int margin_x, int margin_y)override;
	//	//(���)Pivot�FPivot
	//	VOID SetPos(n_xy::ClXY::PIVOT win_pivot, n_xy::ClXY::PIVOT img_pivot)override;
	//	//(���)Pivot�FPivot + margin
	//	VOID SetPos(n_xy::ClXY::PIVOT win_pivot, n_xy::ClXY::PIVOT img_pivot,
	//		int margin_x, int margin_y
	//	)override;

	//	//		�w��摜�̑��Έʒu�ɉ摜�̈ʒu��ݒ�
	//	//(��_�摜)����[�F����[
	//	VOID SetPos(ClImg base_img)override;
	//	//(��_�摜)����[�F����[ + margin
	//	VOID SetPos(ClImg base_img, int margin_x, int margin_y)override;
	//	//(��_�摜)Pivot�FPivot
	//	VOID SetPos(ClImg base_img,
	//		n_xy::ClXY::PIVOT base_pivot, n_xy::ClXY::PIVOT this_pivot)override;
	//	//(��_�摜)Pivot�FPivot + margin
	//	VOID SetPos(ClImg base_img,
	//		n_xy::ClXY::PIVOT base_pivot, n_xy::ClXY::PIVOT this_pivot,
	//		int margin_x, int margin_y)override;

	//	//�����蔻��
	//	BOOL IsStay(IMG_COLL coll_a, IMG_COLL coll_b);

	//private:
	//	//		�����o�֐�
	//	BOOL MmCollUpdate(RECT coll);

	//	//		�����o�ϐ�
	//	RECT m_coll;

	//	//		virtual private�ڍs(�O���g�p�֎~�p)
	//};

	//IMG_COLL::IMG_COLL()
	//{
	//}

	//IMG_COLL::~IMG_COLL()
	//{
	//}
}
