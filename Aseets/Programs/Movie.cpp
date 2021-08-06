//*--------------------------------------------------------------------------------*
//								�f���Ǘ��N���X
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*

//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include MOVIE_HPP
using namespace n_movie;

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^
//*--------------------------------------------------------------------------------*

const int START_TIME = 0;	//�Đ��n�_�̍ŏ��̒n�_

ClMovie::ClMovie(){
	m_time = START_TIME;
}
ClMovie::~ClMovie() { return; }

//*--------------------------------------------------------------------------------*
//								�֐�
//*--------------------------------------------------------------------------------*

const int MOVIE_STATE_STOP = 0;	//�f�����Đ����̂Ƃ�

//�f����`��
VOID ClMovie::Draw() {
	//�`��t���O�������Ă��Ȃ��Ȃ�`�悵�Ȃ�
	if (m_is_draw == FALSE) { return; }

	//�Đ�����Ă��Ȃ��Ȃ�J�n���Ԃ�0�ɂ���
	if (GetMovieStateToGraph(m_handle) == MOVIE_STATE_STOP) {
		//�Đ��n�_���ŏ��ɖ߂�
		SeekMovieToGraph(m_handle, START_TIME);
		PlayMovieToGraph(m_handle);
	}

	//�����`��
	DrawGraph(m_pos.x, m_pos.y, m_handle, TRUE);
}	

//��ʃT�C�Y�ɍ��킹�ĕ`��
VOID ClMovie::WinDraw() {
	//�`��t���O�������Ă��Ȃ��Ȃ�`�悵�Ȃ�
	if (m_is_draw == FALSE) { return; }

	//�Đ�����Ă��Ȃ��Ȃ�J�n���Ԃ�0�ɂ���
	if (GetMovieStateToGraph(m_handle) == MOVIE_STATE_STOP) {
		//�Đ��n�_���ŏ��ɖ߂�
		SeekMovieToGraph(m_handle, START_TIME);
		PlayMovieToGraph(m_handle);
	}

	//�����`��
	DrawExtendGraph(
		ClWin().GetWinPivot().x, ClWin().GetWinPivot().y,
		ClWin().GetWinWidth(), ClWin().GetWinHeight(),
		m_handle, TRUE);
}

/// <summary>
/// �摜�ǂݍ��݋��ʊ֐�
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="cpp_name">cpp��_����</param>
/// <param name="ins_name">�C���X�^���X��_����</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClMovie::MmLoad(string path, string cpp_name, string ins_name) {
	//�摜�̓ǂݍ���
	string all_path = ClCom().GetMoviesPath() + path;
	m_handle = LoadGraph(all_path.c_str());
	m_path = all_path;						//�p�X���R�s�[

	//�ǂݍ��ݎ��s
	if (m_handle == ClCom().GetHandleError()) {
		//�G���[���b�Z�[�W
		string error_meg
			= cpp_name + ".cpp : " + ins_name + " : " + "�f���ǂݍ��݃G���[";

		MessageBox(
			GetMainWindowHandle(), all_path.c_str(),
			error_meg.c_str(), MB_OK
		);
		return FALSE;
	}

	//�摜�̕��ƍ������擾
	GetGraphSize(m_handle, &m_size.x, &m_size.y);

	return TRUE;	//�ǂݍ��ݐ���
}


