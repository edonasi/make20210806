//*--------------------------------------------------------------------------------*
//								�����摜�Ǘ��N���X
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*

//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include IMG_DIV_HPP
using namespace n_img_div;
//		�l�[��
using namespace n_xy;
using namespace n_rect;
using namespace n_circle;
using namespace n_coll_circle;

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^
//*--------------------------------------------------------------------------------*

ClImgDiv::ClImgDiv(){
	m_div = n_xy::ClXY();
	m_div_max = 0;
	m_cnt = n_cnt::ClCntArySec();
}
ClImgDiv::~ClImgDiv() { return; }

//*--------------------------------------------------------------------------------*
//								�v���p�e�B
//*--------------------------------------------------------------------------------*

/// <summary>
/// �摜��\��/��\����Ԃɂ���
/// </summary>
/// <param name="is_draw">TRUE�ŕ\�����</param>
VOID ClImgDiv::SetIsDraw(BOOL is_draw) {
	m_is_draw = is_draw;

	//�J�E���^��0�ɖ߂�
	if (is_draw == FALSE) { m_cnt.SetCnt(); }
}

//*--------------------------------------------------------------------------------*
//								�֐�
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		�摜�ǂݍ���
//*------------------------------------------------*

const float DEFALT_ALL_DRAW_TIME = 1.0f;	//�����摜�̍ő�l�z��܂ŉ��Z���鎞��

//*------------------------------------------------*
//		n_cnt::CNT_AFTER_TYPE cnt_after�Ȃ��n��
//*------------------------------------------------*

/// <summary>
/// �摜�ǂݍ���(1�b���[�v�A�����摜�S�\��)
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="div_x">�������鐔(��)</param>
/// <param name="div_y">�������鐔(�c)</param>
/// <param name="div_max">��������</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImgDiv::Load(string path, int div_x, int div_y, int div_max,
	string cpp_name, string ins_name) {
	//FALSE�Ȃ�ǂݍ��ݎ��s
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, n_cnt::CNT_AFTER_TYPE::LOOP,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// �摜�ǂݍ���(1�b���[�v�A�����摜�S�\��)
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="abs_speed">�ړ��X�s�[�h��Βl</param>
/// <param name="div_x">�������鐔(��)</param>
/// <param name="div_y">�������鐔(�c)</param>
/// <param name="div_max">��������</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImgDiv::Load(string path, int abs_speed,
	int div_x, int div_y, int div_max,
	string cpp_name, string ins_name) {
	//FALSE�Ȃ�ǂݍ��ݎ��s
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, n_cnt::CNT_AFTER_TYPE::LOOP,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	SetAbsSpeed(abs_speed);		//���x�̐ݒ�

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// �摜�ǂݍ���(1�b���[�v�A�����摜�S�\��)
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="abs_speed">�ړ��X�s�[�h��Βl</param>
/// <param name="is_draw">�`�悷�邩</param>
/// <param name="div_x">�������鐔(��)</param>
/// <param name="div_y">�������鐔(�c)</param>
/// <param name="div_max">��������</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImgDiv::Load(string path, int abs_speed, BOOL is_draw,
	int div_x, int div_y, int div_max,
	string cpp_name, string ins_name) {
	//FALSE�Ȃ�ǂݍ��ݎ��s
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, n_cnt::CNT_AFTER_TYPE::LOOP,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	SetAbsSpeed(abs_speed);		//���x�̐ݒ�
	n_img_div::ClImgDiv::SetIsDraw(is_draw);	//�`�悷�邩��ݒ�

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// �摜�ǂݍ���(1�b���[�v�A�����摜�S�\��)
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="div_x">�������鐔(��)</param>
/// <param name="div_y">�������鐔(�c)</param>
/// <param name="div_max">��������</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <param name="is_draw">�`�悷�邩</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImgDiv::Load(string path, int div_x, int div_y, int div_max,
	string cpp_name, string ins_name, BOOL is_draw) {
	//FALSE�Ȃ�ǂݍ��ݎ��s
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, n_cnt::CNT_AFTER_TYPE::LOOP,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	n_img_div::ClImgDiv::SetIsDraw(is_draw);	//�`�悷�邩��ݒ�

	return TRUE;	//�ǂݍ��ݐ���
}

//*------------------------------------------------*
//		n_cnt::CNT_AFTER_TYPE cnt_after����n��
//*------------------------------------------------*

/// <summary>
/// �摜�ǂݍ���(1�b�w��J�E���g���@�A�����摜�S�\��)
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="div_x">�������鐔(��)</param>
/// <param name="div_y">�������鐔(�c)</param>
/// <param name="div_max">��������</param>
/// <param name="cnt_after">�J�E���g�̕��@</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImgDiv::Load(string path, int div_x, int div_y, int div_max,
	n_cnt::CNT_AFTER_TYPE cnt_after,
	string cpp_name, string ins_name) {
	//FALSE�Ȃ�ǂݍ��ݎ��s
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, cnt_after,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// �摜�ǂݍ���(1�b�w��J�E���g���@�A�����摜�S�\��)
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="abs_speed">�ړ��X�s�[�h��Βl</param>
/// <param name="div_x">�������鐔(��)</param>
/// <param name="div_y">�������鐔(�c)</param>
/// <param name="div_max">��������</param>
/// <param name="cnt_after">�J�E���g�̕��@</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImgDiv::Load(string path, int abs_speed,
	int div_x, int div_y, int div_max,
	n_cnt::CNT_AFTER_TYPE cnt_after,
	string cpp_name, string ins_name) {
	//FALSE�Ȃ�ǂݍ��ݎ��s
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, cnt_after,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	SetAbsSpeed(abs_speed);		//���x�̐ݒ�

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// �摜�ǂݍ���(1�b�w��J�E���g���@�A�����摜�S�\��)
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="abs_speed">�ړ��X�s�[�h��Βl</param>
/// <param name="is_draw">�`�悷�邩</param>
/// <param name="div_x">�������鐔(��)</param>
/// <param name="div_y">�������鐔(�c)</param>
/// <param name="div_max">��������</param>
/// <param name="cnt_after">�J�E���g�̕��@</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImgDiv::Load(string path, int abs_speed, BOOL is_draw,
	int div_x, int div_y, int div_max,
	n_cnt::CNT_AFTER_TYPE cnt_after,
	string cpp_name, string ins_name) {
	//FALSE�Ȃ�ǂݍ��ݎ��s
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, cnt_after,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	SetAbsSpeed(abs_speed);		//���x�̐ݒ�
	n_img_div::ClImgDiv::SetIsDraw(is_draw);	//�`�悷�邩��ݒ�

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// �摜�ǂݍ���(1�b�w��J�E���g���@�A�����摜�S�\��)
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="div_x">�������鐔(��)</param>
/// <param name="div_y">�������鐔(�c)</param>
/// <param name="div_max">��������</param>
/// <param name="cnt_after">�J�E���g�̕��@</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <param name="is_draw">�`�悷�邩</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImgDiv::Load(string path, int div_x, int div_y, int div_max,
	n_cnt::CNT_AFTER_TYPE cnt_after,
	string cpp_name, string ins_name, BOOL is_draw) {
	//FALSE�Ȃ�ǂݍ��ݎ��s
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, cnt_after,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	n_img_div::ClImgDiv::SetIsDraw(is_draw);	//�`�悷�邩��ݒ�

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// �摜�ǂݍ��݋��ʊ֐�
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="div_x">�������鐔(��)</param>
/// <param name="div_y">�������鐔(�c)</param>
/// <param name="div_max">��������</param>
/// <param name="cnt_size">�J�E���g�̍ő�l</param>
/// <param name="all_time">cnt_size���`�悷��̂ɂ����鎞��(�b)</param>
/// <param name="cnt_after">�J�E���g�̕��@</param>
/// <param name="cpp_name">cpp��_����</param>
/// <param name="ins_name">�C���X�^���X��_����</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImgDiv::MmLoad(string path, int div_x, int div_y, int div_max,
	int cnt_size, float all_time, n_cnt::CNT_AFTER_TYPE cnt_after,
	string cpp_name, string ins_name) {
	//�p�X
	string all_path = ClCom().GetImagesPath() + path;
	m_path = all_path;						//�p�X���R�s�[

	//*------------------------------------------------*

	//�P��摜�Ƃ��Ď擾
	int img_handle = ClCom().GetHandleError();
	img_handle = LoadGraph(all_path.c_str());

	//�P��摜�̓ǂݍ��݃G���[����
	if (img_handle == ClCom().GetHandleError()) {
		//�G���[���b�Z�[�W
		string error_meg
			= cpp_name + ".cpp : " + ins_name + " : " + "����- �� -�摜�ǂݍ��݃G���[";

		MessageBox(
			GetMainWindowHandle(), all_path.c_str(),
			error_meg.c_str(), MB_OK
		);
		return FALSE;	//�ǂݍ��ݎ��s
	}

	//�P��摜�Ƃ��ăT�C�Y���擾
	n_xy::ClXY img_size = n_xy::ClXY();
	GetGraphSize(img_handle, &img_size.x, &img_size.y);

	//*------------------------------------------------*

	//vector�̗v�f���m��
	m_div_handle.resize(div_max);

	//�G���[����p�n���h��
	int load_div_handle = ClCom().GetHandleError();

	//�����摜�̓ǂݍ���
	load_div_handle = LoadDivGraph(
		all_path.c_str(), div_max, div_x, div_y,
		img_size.x / div_x, img_size.y / div_y, &m_div_handle[0]);

	//�����摜�̓ǂݍ��݃G���[����
	if (load_div_handle == ClCom().GetHandleError()) {
		//�G���[���b�Z�[�W
		string error_meg
			= cpp_name + ".cpp : " + ins_name + " : " + "�����摜�ǂݍ��݃G���[";

		MessageBox(
			GetMainWindowHandle(), all_path.c_str(),
			error_meg.c_str(), MB_OK
		);
		return FALSE;	//�ǂݍ��ݎ��s
	}

	//�����摜�̕������ƃT�C�Y���擾
	m_div.x = div_x;
	m_div.y = div_y;
	m_div_max = div_max;
	m_size.x = img_size.x / div_x;
	m_size.y = img_size.y / div_y;

	//�J�E���g�̐ݒ�
	m_cnt.SetCnt(cnt_size, all_time, cnt_after);

	//�P��摜�n���h���̖����͂Ȃ��Ȃ�̂ŏ���
	DeleteGraph(img_handle);

	return TRUE;	//�ǂݍ��ݐ���
}

//*------------------------------------------------*

const int HANDLE_VEC_EMPTY = 0;	//�n���h���̃x�N�^�[����̂Ƃ�

//�摜�̕`��
VOID ClImgDiv::Draw() {
	if (m_is_draw == FALSE) { return; }
	m_cnt.Proc();
	if (m_div_handle.size() == HANDLE_VEC_EMPTY) { return; }
	DrawGraph(m_pos.x, m_pos.y, m_div_handle[m_cnt.GetIndex()], TRUE);
}	

//�摜�̃���������
VOID ClImgDiv::Delete() {
	for (unsigned int i = 0; i < m_div_handle.size(); i++) {
		DeleteGraph(m_div_handle[i]);
	}
	m_is_draw = FALSE;
}

//*--------------------------------------------------------------------------------*
//								virtual private�ڍs
//*--------------------------------------------------------------------------------*

BOOL ClImgDiv::Load(string path, string cpp_name, string ins_name) {
	ClCom().VirtualError();
	return FALSE;
}

BOOL ClImgDiv::Load(string path, int abs_speed,
	string cpp_name, string ins_name) {
	ClCom().VirtualError();
	return FALSE;
}

BOOL ClImgDiv::Load(string path, int abs_speed, BOOL is_draw,
	string cpp_name, string ins_name) {
	ClCom().VirtualError();
	return FALSE;
}

BOOL ClImgDiv::Load(string path, string cpp_name, string ins_name, BOOL is_draw) {
	ClCom().VirtualError();
	return FALSE;
}

BOOL ClImgDiv::MmLoad(string path, string cpp_name, string ins_name) {
	ClCom().VirtualError();
	return FALSE;
}

//*--------------------------------------------------------------------------------*
//								�����摜�����蔻��ۊǗ��N���X
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		�R���X�g���N�^
//*------------------------------------------------*

ClImgDivColl::ClImgDivColl() { m_coll = ClCollCircle(); }

ClImgDivColl::~ClImgDivColl() { return; }

//*------------------------------------------------*
//		�v���p�e�B
//*------------------------------------------------*

ClCircle ClImgDivColl::GetColl() { return m_coll.GetColl(); }

int ClImgDivColl::GetRadius() { return m_coll.GetRadius(); }

BOOL ClImgDivColl::GetIsDraw() { return m_is_draw; }

BOOL ClImgDivColl::GetIsColl() { return m_coll.GetIsColl(); }

int ClImgDivColl::GetAbsSpeed() { return m_abs_speed; }

ClXY ClImgDivColl::GetSize() { return m_size; }

VOID ClImgDivColl::SetIsDraw() {
	m_is_draw = TRUE;
	m_coll.SetIsColl(TRUE);
}

VOID ClImgDivColl::SetIsDraw(BOOL is_set) {
	m_is_draw = is_set;
	m_coll.SetIsColl(is_set);
}

VOID ClImgDivColl::SetIsDraw(BOOL is_draw, BOOL is_coll) {
	m_is_draw = is_draw;
	m_coll.SetIsColl(is_coll);
}

//*------------------------------------------------*
//		�֐�
//*------------------------------------------------*

//		�֐�
BOOL ClImgDivColl::Load(string path, int div_x, int div_y, int div_max,
	string cpp_name, string ins_name) {
	//FALSE�Ȃ�ǂݍ��ݎ��s
	if (MmLoad(
		path, div_x, div_y, div_max,
		div_max, DEFALT_ALL_DRAW_TIME, n_cnt::CNT_AFTER_TYPE::LOOP,
		cpp_name, ins_name) == FALSE
		) {
		return FALSE;
	}

	int radius = m_size.x < m_size.y ? m_size.x / 2 : m_size.y / 2;
	m_coll.SetColl(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2, radius);

	return TRUE;	//�ǂݍ��ݐ���
}

VOID ClImgDivColl::Draw() {
	if (m_is_draw == FALSE) { return; }
	m_cnt.Proc();
	if (m_div_handle.size() == HANDLE_VEC_EMPTY) { return; }
	DrawGraph(m_pos.x, m_pos.y, m_div_handle[m_cnt.GetIndex()], TRUE);

	m_coll.DrawDebug();
}

VOID ClImgDivColl::Draw(BOOL is_coll_draw) {
	if (m_is_draw == FALSE) { return; }
	m_cnt.Proc();
	if (m_div_handle.size() == HANDLE_VEC_EMPTY) { return; }
	DrawGraph(m_pos.x, m_pos.y, m_div_handle[m_cnt.GetIndex()], TRUE);

	if (is_coll_draw == TRUE) { m_coll.DrawDebug(); }
}

VOID ClImgDivColl::CollDebugDraw() {
	m_coll.DrawDebug();
}

VOID ClImgDivColl::Delete() {
	for (unsigned int i = 0; i < m_div_handle.size(); i++) {
		DeleteGraph(m_div_handle[i]);
	}
	m_is_draw = FALSE;
	m_coll.SetIsColl(FALSE);
}

VOID ClImgDivColl::Move(int x_mult, int y_mult) {
	m_pos.x += ClFps::GetIns()->GetFpsIntFix(x_mult * m_abs_speed, &m_over_speed);
	m_pos.y += ClFps::GetIns()->GetFpsIntFix(y_mult * m_abs_speed, &m_over_speed);
	m_coll.Update(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2);
}


VOID ClImgDivColl::SetMove(int x, int y) {
	m_pos.x = x;
	m_pos.y = y;
	m_coll.Update(m_pos.x + m_size.x / 2, m_pos.y + m_size.y / 2);
}

//�����蔻��
BOOL ClImgDivColl::IsStay(n_xy::ClXY point) {
	if (m_coll.IsStay(point) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClImgDivColl::IsStay(n_rect::ClRect rect) {
	if (m_coll.IsStay(rect) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClImgDivColl::IsStay(n_circle::ClCircle circle) {
	if (m_coll.IsStay(circle) == TRUE) { return TRUE; }
	return FALSE;
}