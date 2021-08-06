//*--------------------------------------------------------------------------------*
//								�摜�Ǘ��̊��N���X
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include IMG_HPP
using namespace n_img;
//		�l�[��
using namespace n_xy;

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^�A�f�X�g���N�^�A�ϐ��̏�����
//*--------------------------------------------------------------------------------*

ClImg::ClImg() {
	m_handle = ClCom().GetHandleError();
	m_pos = ClXY();			//�ʒu
	m_size = ClXY();			//�T�C�Y
	m_abs_speed = 0;		//�ړ��X�s�[�h
	m_over_speed = 0.0f;	//�ړ��X�s�[�h�̏����_�ȉ�
	m_is_draw = FALSE;		//�`�悷�邩
}
ClImg::~ClImg() { return; }

//*--------------------------------------------------------------------------------*
//									�v���p�e�B
//*--------------------------------------------------------------------------------*

ClXY ClImg::GetPos() { return m_pos; }

//�摜��\����Ԃɂ���
VOID ClImg::SetIsDraw() { m_is_draw = TRUE; }

/// <summary>
/// �摜��\��/��\����Ԃɂ���
/// </summary>
/// <param name="is_draw">TRUE�ŕ\�����</param>
VOID ClImg::SetIsDraw(BOOL is_draw) { m_is_draw = is_draw; }

/// <summary>
/// �ړ��X�s�[�h�̐�Βl����(-�̂Ƃ���+�ɕϊ����đ��)
/// </summary>
/// <param name="abs_speed">�ړ��X�s�[�h�̐�Βl</param>
VOID ClImg::SetAbsSpeed(int abs_speed) { m_abs_speed = std::abs(abs_speed); }

//*------------------------------------------------*
//		�摜�ǂݍ���
//*------------------------------------------------*

/// <summary>
/// �摜�ǂݍ���
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImg::Load(string path, string cpp_name, string ins_name) {
	//FALSE�Ȃ�ǂݍ��ݎ��s
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// �ړ��X�s�[�h���w�肵�ĉ摜�ǂݍ���
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="abs_speed">�ړ��X�s�[�h</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImg::Load(string path, int abs_speed, string cpp_name, string ins_name) {
	//FALSE�Ȃ�ǂݍ��ݎ��s
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	SetAbsSpeed(abs_speed);	//�ړ����x����

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// �ړ��X�s�[�h�ƕ\����\�����w�肵�ĉ摜�ǂݍ���
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="abs_speed">�ړ��X�s�[�h</param>
/// <param name="is_draw">�\����\��</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImg::Load(string path, int abs_speed, BOOL is_draw, string cpp_name, string ins_name) {
	//FALSE�Ȃ�ǂݍ��ݎ��s
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	SetAbsSpeed(abs_speed);		//�ړ����x����
	SetIsDraw(is_draw);			//�\����\������

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// �ړ��X�s�[�h�ƕ\����\�����w�肵�ĉ摜�ǂݍ���
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="cpp_name">�ǂݍ��ޏꏊ��cpp��(�x�^�ł�)</param>
/// <param name="ins_name">�ǂݍ��ރC���X�^���X��(�x�^�ł�)</param>
/// <param name="is_draw">�\����\��</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImg::Load(string path, string cpp_name, string ins_name, BOOL is_draw) {
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	SetIsDraw(is_draw);			//�\����\������

	return TRUE;	//�ǂݍ��ݐ���
}

/// <summary>
/// �摜�ǂݍ��݋��ʊ֐�
/// </summary>
/// <param name="path">�ǂݍ��ݏꏊ</param>
/// <param name="cpp_name">cpp��_����</param>
/// <param name="ins_name">�C���X�^���X��_����</param>
/// <returns>TRUE�œǂݍ��ݐ���</returns>
BOOL ClImg::MmLoad(string path, string cpp_name, string ins_name) {
	//�摜�̓ǂݍ���
	string all_path = ClCom().GetImagesPath() + path;
	m_handle = LoadGraph(all_path.c_str());
	m_path = all_path;						//�p�X���R�s�[

	//�ǂݍ��ݎ��s
	if (m_handle == ClCom().GetHandleError()) {
		//�G���[���b�Z�[�W
		string error_meg
			= cpp_name + ".cpp : " + ins_name + " : " + "�摜�ǂݍ��݃G���[";

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

//*------------------------------------------------*
//		
//*------------------------------------------------*

//�摜��`��(��is_draw��TRUE�̂Ƃ��̂�)
VOID ClImg::Draw() { if (m_is_draw == TRUE) { DrawGraph(m_pos.x, m_pos.y, m_handle, TRUE); } }

//�摜���������������
VOID ClImg::Delete() { 
	DeleteGraph(m_handle); 
	m_is_draw = FALSE;
}

//*------------------------------------------------*
//		�ړ�
//*------------------------------------------------*

/// <summary>
/// �����ړ�
/// </summary>
/// <param name="move_type">�ǂ̕����ɒ����ړ����邩</param>
VOID ClImg::Move(MOVE_LINE_TYPE move_type) {
	//X�ړ��̌v�Z
	switch (move_type) {
		//STOP�̂Ƃ��͏������I��
	case n_img::STOP:return; break;

	case n_img::UP_LEFT:
	case n_img::LEFT:
	case n_img::DOWN_LEFT:
		m_pos.x += -ClFps::GetIns()->GetFpsIntFix(m_abs_speed, &m_over_speed);
		break;

	case n_img::UP_RIGHT:
	case n_img::RIGHT:
	case n_img::DOWN_RIGHT:
		m_pos.x += ClFps::GetIns()->GetFpsIntFix(m_abs_speed, &m_over_speed);
		break;

	default:break;
	}

	//Y�ړ��̌v�Z
	switch (move_type){
	case n_img::UP_LEFT:
	case n_img::UP:
	case n_img::UP_RIGHT:
		m_pos.y += -ClFps::GetIns()->GetFpsIntFix(m_abs_speed, &m_over_speed);
		break;

	case n_img::DOWN_LEFT:
	case n_img::DOWN:
	case n_img::DOWN_RIGHT:
		m_pos.y += ClFps::GetIns()->GetFpsIntFix(m_abs_speed, &m_over_speed);
		break;

	default:break;
	}
}

/// <summary>
/// delta�������Ĉړ�
/// </summary>
/// <param name="x_mult">+ �ŉE�����A- �ō������Ɉړ�</param>
/// <param name="y_mult">+ �ŉ������A- �ŏ�����Ɉړ�</param>
VOID ClImg::Move(int x_mult, int y_mult) {
	m_pos.x += ClFps::GetIns()->GetFpsIntFix(x_mult * m_abs_speed, &m_over_speed);
	m_pos.y += ClFps::GetIns()->GetFpsIntFix(y_mult * m_abs_speed, &m_over_speed);
}

/// <summary>
/// delta�������Ĉړ����邩�|���Ȃ��ňړ����邩
/// </summary>
/// <param name="x_mult">+ �ŉE�����A- �ō������Ɉړ�</param>
/// <param name="y_mult">+ �ŉ������A- �ŏ�����Ɉړ�</param>
/// <param name="move_mult">�W���̎��</param>
VOID ClImg::Move(int x_mult, int y_mult, n_img::MOVE_MULT move_mult) {
	switch (move_mult)
	{
	case n_img::ABS_SPEED:
		m_pos.x += x_mult * m_abs_speed, & m_over_speed;
		m_pos.y += y_mult * m_abs_speed, & m_over_speed;
		break;
	case n_img::DELTA:
		m_pos.x += ClFps::GetIns()->GetFpsIntFix(x_mult * m_abs_speed, &m_over_speed);
		m_pos.y += ClFps::GetIns()->GetFpsIntFix(y_mult * m_abs_speed, &m_over_speed);
		break;
	default:
		break;
	}
}

//*------------------------------------------------*
//		��ʑ��Έʒu�ɉ摜�̈ʒu��ݒ�
//*------------------------------------------------*

//��ʍ���[�ɉ摜�̈ʒu��ݒ�
VOID ClImg::SetPos() {
	m_pos.x = ClWin().GetWinPivot().x;
	m_pos.y = ClWin().GetWinPivot().y;
}

/// <summary>
/// ��ʍ���[����margin�����������ʒu�ɐݒ�
/// </summary>
/// <param name="margin_x">����x�ʒu</param>
/// <param name="margin_y">����y�ʒu</param>
VOID ClImg::SetPos(int margin_x, int margin_y) {
	m_pos.x = ClWin().GetWinPivot().x + margin_x;
	m_pos.y = ClWin().GetWinPivot().y + margin_y;
}

/// <summary>
/// ��ʏ�̐�������_�ɂ��đ��Έʒu�ɐݒ肷��
/// </summary>
/// <param name="win_pivot">XY�̐���</param>
/// <param name="img_pivot">XY�̐���</param>
VOID ClImg::SetPos(PIVOT win_pivot, PIVOT img_pivot) {
	m_pos.x = ClWin().GetWinPivot(win_pivot).x - m_size.GetPivot(img_pivot).x;
	m_pos.y = ClWin().GetWinPivot(win_pivot).y - m_size.GetPivot(img_pivot).y;
}

/// <summary>
/// ���pivot����_�ɉ摜pivot�ɑΉ������ʒu����margin�������ʒu�ɂ���
/// </summary>
/// <param name="win_pivot">��ʂ�pivot</param>
/// <param name="img_pivot">���̉摜��pivot</param>
/// <param name="margin_x">+ �ŉE�����A- �ō������ɗ���</param>
/// <param name="margin_y">+ �ŉ������A- �ŏ�����ɗ���</param>
VOID ClImg::SetPos(
	PIVOT win_pivot, PIVOT img_pivot,
	int margin_x, int margin_y) {
	m_pos.x = ClWin().GetWinPivot(win_pivot).x - m_size.GetPivot(img_pivot).x + margin_x;
	m_pos.y = ClWin().GetWinPivot(win_pivot).y - m_size.GetPivot(img_pivot).y + margin_y;
}

//*------------------------------------------------*
//		��_�摜�̑��Έʒu�ɉ摜�̈ʒu��ݒ�
//*------------------------------------------------*

/// <summary>
/// ��_�摜�̍���[�̈ʒu�ɂ��̃C���X�^���X�̉摜�̈ʒu��ݒ�
/// </summary>
/// <param name="base_img">��_�摜</param>
VOID ClImg::SetPos(ClImg base_img) {
	m_pos.x = base_img.m_pos.x;
	m_pos.y = base_img.m_pos.y;
}

/// <summary>
/// ��_�摜�̍���[�̈ʒu����margin�����������ʒu�ɂ��̃C���X�^���X�̉摜�̈ʒu��ݒ�
/// </summary>
/// <param name="base_img">��_�摜</param>
/// <param name="margin_x">��_�摜����[���痣��X�ʒu</param>
/// <param name="margin_y">��_�摜����[���痣��Y�ʒu</param>
VOID ClImg::SetPos(ClImg base_img, int margin_x, int margin_y) {
	m_pos.x = base_img.m_pos.x + margin_x;
	m_pos.y = base_img.m_pos.y + margin_y;
}

/// <summary>
/// ��_�摜��pivot�ʒu�ɂ��̃C���X�^���X��pivot�ʒu��ݒ�
/// </summary>
/// <param name="base_img">��_�摜</param>
/// <param name="base_pivot">��_�摜�̐���</param>
/// <param name="this_pivot">���̃C���X�^���X�摜�̐���</param>
VOID ClImg::SetPos(ClImg base_img,
	PIVOT base_pivot, PIVOT this_pivot) {
	m_pos.x = base_img.m_pos.x + base_img.m_size.GetPivot(base_pivot).x - m_size.GetPivot(this_pivot).x;
	m_pos.y = base_img.m_pos.y + base_img.m_size.GetPivot(base_pivot).y - m_size.GetPivot(this_pivot).y;
}

/// <summary>
/// ��_�摜��pivot�ʒu�ɂ��̃C���X�^���X��pivot+margin�ʒu��ݒ�
/// </summary>
/// <param name="base_img">��_�摜</param>
/// <param name="base_pivot">��_�摜�̐���</param>
/// <param name="this_pivot">���̃C���X�^���X�摜�̐���</param>
/// <param name="margin_x">��_�摜����[���痣��X�ʒu</param>
/// <param name="margin_y">��_�摜����[���痣��Y�ʒu</param>
VOID ClImg::SetPos(ClImg base_img,
	PIVOT base_pivot, PIVOT this_pivot,
	int margin_x, int margin_y) {
	m_pos.x = base_img.m_pos.x + base_img.m_size.GetPivot(base_pivot).x - m_size.GetPivot(this_pivot).x + margin_x;
	m_pos.y = base_img.m_pos.y + base_img.m_size.GetPivot(base_pivot).y - m_size.GetPivot(this_pivot).y + margin_y;
}
