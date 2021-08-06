#pragma once

namespace n_xy {
	//enum
	//����							
	enum PIVOT {
		TOP_LEFT,		//����@
		TOP_CENTER,		//�@��
		TOP_RIGHT,		//�E��
		CENTER_LEFT,	//��
		CENTER_CENTER,	//�^��
		CENTER_RIGHT,	//�E
		BUTTOM_LEFT,	//����
		BUTTOM_CENTER,	//�@��
		BUTTOM_RIGHT	//�E��
	};

	enum ONE_PIVOT {
		MIN,	//�E/��
		HALF,	//�^��
		MAX		//��/��
	};

	//XY�N���X�\����
	class ClXY{
	public:
		//�R���X�g���N�^
		ClXY();
		ClXY(int x_in,int y_in);
		~ClXY();

		//		�v���p�e�B
		VOID SetX(int x_in);			//x��ݒ�
		VOID SetY(int y_in);			//y��ݒ�
		VOID SetXY(int x_in,int y_in);	//xy��ݒ�

		//		�֐�
		ClXY GetPivot();			//����[���擾
		ClXY GetPivot(PIVOT pivot);	//�w�肵�������̍��W���擾
		//�Б���pivot�擾
		int GetPivotX(ONE_PIVOT pivot_x);
		int GetPivotY(ONE_PIVOT pivot_y);
		
		//		�ϐ�
		int x;
		int y;
	};
}