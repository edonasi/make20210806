#pragma once

#include IMG_HPP

namespace n_movie {
	class ClMovie:public n_img::ClImg{
	public:
		ClMovie();
		~ClMovie();

		//		�����o�֐�
		VOID Draw()override;	//�f����`��
		VOID WinDraw();			//��ʃT�C�Y�ɍ��킹�ĕ`��

	private:
		//�����o�֐�
		BOOL MmLoad(string path, string cpp_name, string ins_name)override;

		//		�����o�ϐ�
		int m_time;
	};

	
}