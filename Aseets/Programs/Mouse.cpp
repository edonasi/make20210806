//*--------------------------------------------------------------------------------*
//								�}�E�X�̓���
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include MOUSE_HPP
using namespace n_mouse;

//*--------------------------------------------------------------------------------*
//								�V���O���g������
//*--------------------------------------------------------------------------------*

//�{�^���������ꂽ�u�ԁA�{�^�����͏���-1��
const signed char UP_NUM = -1;
//�{�^����������Ă�����(�{�^���������ꂽ�u�Ԃ�����)�A�{�^�����͏���0��
const signed char UPPING_NUM = 0;
//�{�^���������ꂽ�u��
const signed char DOWN_NUM = 1;

/// <summary>
/// �R���X�g���N�^�A�L�[�̏�Ԃ�������
/// </summary>
ClMouse::ClMouse() { 
     //�}�E�X�ϐ��̏�����
    m_input_value = 0;
    m_wheel_value = 0;
    m_point = n_xy::ClXY();
    //�}�E�X�J�E���^�̏�����
    for (int i = 0; i < MOUSE_BUTTON_CODE; i++) { m_button[i] = UPPING_NUM; }

    //�w��b�������ꂽ�����t���O�̏�����
    for (int i = 0; i < MOUSE_BUTTON_CODE; i++) {
        for (int j = 0; j < BUTTON_TIME_INPUT_NUM; j++) {
            m_is_time_input_button_after[i][j] = FALSE;
        }
    }
    return; 
}

//�V���O���g����Keyboard�N���X�̃I�u�W�F�N�g
ClMouse* ClMouse::m_ins = nullptr;

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
ClMouse::ClMouse(const ClMouse& src) {

    //�A�h���X���R�s�[���Ă���
    m_ins = src.m_ins;
}

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
/// <returns>���̃C���X�^���X�̃A�h���X</returns>
ClMouse& ClMouse::operator=(const ClMouse& src) {

    //�A�h���X���R�s�[���Ă���
    m_ins = src.m_ins;
    return *this;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ClMouse::~ClMouse() { return; }

/// <summary>
/// �C���X�^���X�擾(���߂ĎQ�Ƃ���Ƃ��̓C���X�^���X�𐶐�)
/// </summary>
/// <returns>�V���O���g���ȃC���X�^���X</returns>
ClMouse* ClMouse::GetIns() {

    //���߂Ď擾���鎞Keyboard�I�u�W�F�N�g�𐶐�
    if (m_ins == nullptr) {

        //�������̊m��
        m_ins = new ClMouse();
    }

    return m_ins;
}

//*--------------------------------------------------------------------------------*
//								�֐���������
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		�I�u�W�F�N�g�̔j��
//*------------------------------------------------*

/// <summary>
/// �I�u�W�F�N�g�̔j��
/// </summary>
VOID ClMouse::Destroy() {

    //�������̔j��
    delete m_ins;
    m_ins = nullptr;
}

//*------------------------------------------------*
//		�}�E�X�̍X�V
//*------------------------------------------------*

n_xy::ClXY ClMouse::GetPos() { return m_point; }

//�}�E�X�̍��W�����͈�
const RECT LIMIT_SCREEN = { 0,0,ClWin().GetWinWidth() ,ClWin().GetWinHeight() };
const BOOL IS_MOUSE_POS_LIMIT = TRUE;   //�}�E�X�̍��W����ʓ��ɐ������邩

//�}�E�X�̍X�V
int ClMouse::MouseUpdate() {
    //�}�E�X�̍��W���擾
    GetMousePoint(&m_point.x, &m_point.y);  
    
    //�v���C��ʏ�̃}�E�X�̍��W����ʓ��ɐ�������
    if (IS_MOUSE_POS_LIMIT == TRUE) {
        if (m_point.x < LIMIT_SCREEN.left) { m_point.x = LIMIT_SCREEN.left; }
        if (m_point.x > LIMIT_SCREEN.right) { m_point.x = LIMIT_SCREEN.right; }
        if (m_point.y < LIMIT_SCREEN.top) { m_point.y = LIMIT_SCREEN.top; }
        if (m_point.y > LIMIT_SCREEN.bottom) { m_point.y = LIMIT_SCREEN.bottom; }
    }

    //�}�E�X�̉����Ă���{�^�����擾
    m_input_value = GetMouseInput();

    //�}�E�X�R�[�h�ɑΉ������{�^����������Ă��邩�`�F�b�N
    MmMouseCheck(MOUSE_INPUT_LEFT);       //��
    MmMouseCheck(MOUSE_INPUT_MIDDLE);     //��
    MmMouseCheck(MOUSE_INPUT_RIGHT);      //�E

    //�z�C�[���̉�]�ʂ��擾
    m_wheel_value = GetMouseWheelRotVol();

    return 0;
}	

/// <summary>
/// �}�E�X�R�[�h�ɑΉ������{�^����������Ă��邩�`�F�b�N
/// </summary>
/// <param name="mouse">�}�E�X�N���X�\����</param>
/// <param name="mouse_input_">�}�E�X�R�[�h</param>
VOID ClMouse::MmMouseCheck(int mouse_input_) {
    //�����Ă���Ƃ�
    if ((m_input_value & mouse_input_) == mouse_input_){
        //�������u�Ԃ̂Ƃ��N���b�N�J�n������s��
        if (m_button[mouse_input_] == UPPING_NUM) {
            //m_is_click_start[mouse_input_] = MmIsMousePointInPlayScreen(m_mouse, mouse_input_);
        }
        m_button[mouse_input_]++;  //���Z
    }
    //�����Ă��Ȃ��Ƃ�
    else if ((m_input_value & mouse_input_) != mouse_input_){
        if (m_button[mouse_input_] > UPPING_NUM) { //�O�܂Ń{�^����������Ă�����Ԃ�������
            m_button[mouse_input_] = UP_NUM;   //-1�ɂ���
           // m_is_click_start[mouse_input_] = FALSE; //��ʏ�ǂ̍��W�ɂ��Ă��������u�ԁA�t���O������
        }
        else {  
            m_button[mouse_input_] = UPPING_NUM;   //0�ɂ���
        }
    }
}

//*------------------------------------------------*
//		�����蔻��Ȃ��N���b�N����
//*------------------------------------------------*

/// <summary>
/// �{�^���̓��̓J�E���g��Ԃ�
/// </summary>
/// <param name="mouse_input_">�}�E�X�R�[�h</param>
/// <returns>���̓J�E���g</returns>
int ClMouse::GetButtonCnt(int mouse_input_) { return m_button[mouse_input_]; }

/// <summary>
/// �{�^����������Ă����Ԃ�(������Ă����ԂȂ�TRUE)
/// </summary>
/// <param name="mouse_input_">�}�E�X�R�[�h</param>
/// <returns>������Ă���Ȃ�TRUE</returns>
BOOL ClMouse::GetIsButton(int mouse_input_) {
    if (m_button[mouse_input_] > UPPING_NUM) { return TRUE; } //������Ă���
    else { return FALSE; }  //������Ă��Ȃ�
}

/// <summary>
/// �{�^���������ꂽ�u�Ԃ�(��ԍŏ��̉��Z)
/// </summary>
/// <param name="mouse_input_">�}�E�X�R�[�h</param>
/// <returns>�����ꂽ�u�ԂȂ�TRUE</returns>
BOOL ClMouse::GetIsButtonDown(int mouse_input_) {
    if (m_button[mouse_input_] == DOWN_NUM) { return TRUE; } //�����ꂽ
    else { return FALSE; }  //������Ă��Ȃ�
}

/// <summary>
/// �{�^���������ꂽ�u�Ԃ�(�����ꂽ�u�ԂȂ�TRUE)
/// </summary>
/// <param name="mouse_input_">�}�E�X�R�[�h</param>
/// <returns>�����ꂽ�u�ԂȂ�TRUE</returns>
BOOL ClMouse::GetIsButtonUp(int mouse_input_) {
    if (m_button[mouse_input_] == UP_NUM) { return TRUE; } //�����ꂽ
    else { return FALSE; }  //����ȊO
}

/// <summary>
/// �{�^���𗣂��Ă����Ԃ�(������Ă���Ȃ�TRUE)
/// </summary>
/// <param name="mouse_input_">�}�E�X�R�[�h</param>
/// <returns>������Ă���Ȃ�TRUE</returns>
BOOL ClMouse::GetIsButtonAway(int mouse_input_) {
    if (m_button[mouse_input_] <= UPPING_NUM) { return TRUE; } //�����Ă���
    else { return FALSE; }  //�����Ă��Ȃ�
}

//�w�莞��(�b)�����ꂽ��
BOOL ClMouse::GetIsButtonTimeInput(int mouse_input_, float time) {
    //�����ꂽ�u�Ԃ�-1�ɂȂ��Ă���̂ŃG���[���N���Ȃ��悤��0�ɏC��
    int button = m_button[mouse_input_];
    if (button < UPPING_NUM) { button = UPPING_NUM; }

    //�{�^����������Ă���Ȃ�t���O������
    if (button == UPPING_NUM) {
        if (m_is_time_input_button_after[mouse_input_][n_com::IF_CASE_TYPE::EQUAL] == TRUE) {
            m_is_time_input_button_after[mouse_input_][n_com::IF_CASE_TYPE::EQUAL] = FALSE;
        }
        return FALSE;
    }

    //���������Ă��鎞�Ԃ̓~���b���~FPS�l
    //��F1.5�b�~60FPS = 90(keyTime)
    int updateTime
        = static_cast<int>(time * ClFps::GetIns()->GetFpsFloatValue());

    //�w�莞�ԉ����ꂽ��
    if (m_is_time_input_button_after[mouse_input_][n_com::IF_CASE_TYPE::EQUAL] == FALSE
        && button == updateTime) {
        m_is_time_input_button_after[mouse_input_][n_com::IF_CASE_TYPE::EQUAL] = TRUE;
        return TRUE;
    }
    else { return FALSE; }
}

//�w�莞��(�~���b)(�𒴂��� / �ȏ� / �Ɠ��� / �ȉ� / ����)�{�^���������ꂽ��(��{�F�𒴂���)
BOOL ClMouse::GetIsButtonTimeInput(int mouse_input_, float time, n_com::IF_CASE_TYPE mouse_case_type) {
    //�����ꂽ�u�Ԃ�-1�ɂȂ��Ă���̂ŃG���[���N���Ȃ��悤��0�ɏC��
    int button = m_button[mouse_input_];
    if (button < UPPING_NUM) { button = UPPING_NUM; }

    //�{�^����������Ă���Ȃ�t���O������
    if (button == UPPING_NUM) {
        if (m_is_time_input_button_after[mouse_input_][n_com::IF_CASE_TYPE::EQUAL] == TRUE) {
            m_is_time_input_button_after[mouse_input_][n_com::IF_CASE_TYPE::EQUAL] = FALSE;
        }
        return FALSE;
    }

    //���������Ă��鎞�Ԃ̓~���b���~FPS�l
    //��F1.5�b�~60FPS = 90(keyTime)
    int updateTime
        = static_cast<int>(time * ClFps::GetIns()->GetFpsFloatValue());

    //���肷�鉉�Z�q�̎�ނŏ����������Ă���TRUE�ŕԂ�
    switch (mouse_case_type)
    {
        //�w�莞��(�b)�𒴂���( > )�� 
    case n_com::IF_CASE_TYPE::OVER:
        if (m_is_time_input_button_after[mouse_input_][mouse_case_type] == TRUE) { return TRUE; }
        if (button > updateTime) {
            m_is_time_input_button_after[mouse_input_][mouse_case_type] = TRUE;
            return TRUE;
        }
        break;

        //�w�莞��(�b)�@�ȏ�@( >= )�� 
    case n_com::IF_CASE_TYPE::ABOVE:
        if (m_is_time_input_button_after[mouse_input_][mouse_case_type] == TRUE) { return TRUE; }
        if (button >= updateTime) {
            m_is_time_input_button_after[mouse_input_][mouse_case_type] = TRUE;
            return TRUE;
        }
        break;

        //�w�莞��(�b)�Ɠ����@( == )�� 
    case n_com::IF_CASE_TYPE::EQUAL:
        if (m_is_time_input_button_after[mouse_input_][mouse_case_type] == FALSE
            &&button == updateTime) {
            m_is_time_input_button_after[mouse_input_][mouse_case_type] = TRUE;
            return TRUE;
        }
        break;

        //�w�莞��(�b)�@�ȉ��@( <= )�� 
    case n_com::IF_CASE_TYPE::IN_UNDER:
        if (m_is_time_input_button_after[mouse_input_][mouse_case_type] == TRUE) { return TRUE; }
        if (button <= updateTime) { return TRUE; }
        else { m_is_time_input_button_after[mouse_input_][mouse_case_type] = TRUE; }
        break;

        //�w�莞��(�b)�@�����@( > )�� 
    case n_com::IF_CASE_TYPE::LESS_THAN:
        if (m_is_time_input_button_after[mouse_input_][mouse_case_type] == TRUE) { return TRUE; }
        if (button < updateTime) { return TRUE; }
        else { m_is_time_input_button_after[mouse_input_][mouse_case_type] = TRUE; }
        break;

        //�������Ȃ�
    default:
        break;
    }

    //����O��������FALSE��Ԃ�
    return FALSE;
}


//*------------------------------------------------*
//		�f�o�b�N
//*------------------------------------------------*

//�}�E�X�̈ʒu����`�悷��
VOID ClMouse::MousePosDraw() {
    //�f�o�b�N�̂Ƃ�
    if (ClWin().GetIsDebug() == TRUE) {
        //�}�E�X�̍��W��`��
        DrawFormatString(
            0, ClWin().GetWinHeight() - ClCom().GetPowerNumPlas(5),
            ClCom().GetFlipColor(), "MOUSE[X:%4d/Y:%4d]", m_point.x, m_point.y
        );
    }
    return;
}