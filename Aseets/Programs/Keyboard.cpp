//*--------------------------------------------------------------------------------*
//								�L�[�{�[�h�̓���
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include KEYBOARD_HPP
using namespace n_keyboard;

//*--------------------------------------------------------------------------------*
//								�V���O���g������
//*--------------------------------------------------------------------------------*

//�V���O���g����Keyboard�N���X�̃I�u�W�F�N�g
ClKeyboard* ClKeyboard::m_ins = nullptr;

/// <summary>
/// �R���X�g���N�^�A�L�[�̏�Ԃ�������
/// </summary>
ClKeyboard::ClKeyboard() {
    //�L�[�t���[����������
    for (int i = 0; i < DEFAULT_KEY_NUM; i++) {

        m_key_cnt[i] = 0;
    }

    //���Ԏw����͂̃t���O��������
    for (int i = 0; i < DEFAULT_KEY_NUM; i++) {
        for (int j = 0; j < KEY_TIME_INPUT_NUM; j++) {
            m_is_time_input_after[i][j] = FALSE;
        }
    }
}

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
ClKeyboard::ClKeyboard(const ClKeyboard& src) {

    //�A�h���X���R�s�[���Ă���
    m_ins = src.m_ins;
}

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
/// <returns>���̃C���X�^���X�̃A�h���X</returns>
ClKeyboard& ClKeyboard::operator=(const ClKeyboard& src) {

    //�A�h���X���R�s�[���Ă���
    m_ins = src.m_ins;
    return *this;
}

/// <summary>
/// �f�X�g���N�^
/// </summary>
ClKeyboard::~ClKeyboard() {

    return;
}

/// <summary>
/// �C���X�^���X�擾(���߂ĎQ�Ƃ���Ƃ��̓C���X�^���X�𐶐�)
/// </summary>
/// <returns>�V���O���g���ȃC���X�^���X</returns>
ClKeyboard* ClKeyboard::GetIns() {

    //���߂Ď擾���鎞Keyboard�I�u�W�F�N�g�𐶐�
    if (m_ins == nullptr) {

        //�������̊m��
        m_ins = new ClKeyboard();
    }

    return m_ins;
}


//*--------------------------------------------------------------------------------*
//								�֐���������
//*--------------------------------------------------------------------------------*


/// <summary>
/// �I�u�W�F�N�g�̔j��
/// </summary>
VOID ClKeyboard::Destroy() {

    //�������̔j��
    delete m_ins;
    m_ins = nullptr;
}

//�L�[�������ꂽ�u�ԁA�L�[���͏���-1��
const signed char KEY_UP_NUM = -1;
//�L�[��������Ă�����(�L�[�������ꂽ�u�Ԃ�����)�A�L�[���͏���0��
const signed char KEY_UPPING_NUM = 0;
//�L�[�������ꂽ�u��
const signed char KEY_DOWN_NUM = 1;

/// <summary>
/// �L�[�̓��͏�Ԃ��X�V����֐�
/// </summary>
/// <returns></returns>
int ClKeyboard::GpUpdateKey() {

    int i = 0;
    //���݂̃L�[���͏�Ԃ��i�[����
    char tmpKey[DEFAULT_KEY_NUM];

    //���ׂẴL�[���͏�Ԃ𓾂�
    GetHitKeyStateAll(tmpKey);

    //���X�̃L�[(256��)�̃L�[�̏�Ԃ𓾂�
    for (i = 0; i < DEFAULT_KEY_NUM; i++) {

        //i�ł̃L�[�R�[�h�ɑΉ�����L�[��������Ă�����
        if (tmpKey[i] != 0) {

            //���Z
            m_key_cnt[i]++;
        }
        else {

            //�O�܂ŃL�[��������Ă�����Ԃ�������
            if (m_key_cnt[i] > 0) {

                //-1�ɂ���(�������u�Ԃ̏�� -1)
                m_key_cnt[i] = KEY_UP_NUM;
            }
            else {

                //0�ɂ���(������Ă��Ȃ���� 0)
                m_key_cnt[i] = KEY_UPPING_NUM;
            }

        }
    }

    return 0;
}

/// <summary>
/// �L�[�̓��̓J�E���g��Ԃ�
/// </summary>
/// <param name="key_input_">�L�[�R�[�h</param>
/// <returns>�L�[�R�[�h�̓��͎���(m_cnt)</returns>
int ClKeyboard::GetKeyCnt(int key_input_) { return m_key_cnt[key_input_]; }

/// <summary>
/// �L�[��������Ă����Ԃ�(0�𒴂��Ă��� , 1�ȏ�)
/// </summary>
/// <param name="key_input_">�L�[�R�[�h</param>
/// <returns>������Ă����ԂȂ�TRUE</returns>
BOOL ClKeyboard::GetIsKey(int key_input_) {
    //�L�[��������Ă����Ԃ�(0�𒴂��Ă��� , 1�ȏ�)
    if (m_key_cnt[key_input_] > KEY_UPPING_NUM) { return TRUE; }  //������Ă�����
    else { return FALSE; }                    //������Ă��Ȃ����
}

/// <summary>
/// �L�[�������ꂽ�u�Ԃ�(��ԍŏ��̉��Z)
/// </summary>
/// <param name="key_input_">�L�[�R�[�h</param>
/// <returns>�����ꂽ�u�ԂȂ�TRUE</returns>
BOOL ClKeyboard::GetIsKeyDown(int key_input_) {
    //�L�[��������Ă����Ԃ�(��ԍŏ��̉��Z)
    if (m_key_cnt[key_input_] == KEY_DOWN_NUM) { return TRUE; }  //�����ꂽ�u��
    else { return FALSE; }                      //�����ꂽ�u�Ԃł͂Ȃ�
}

/// <summary>
/// �L�[�������ꂽ�u�Ԃ�(-1)
/// </summary>
/// <param name="key_input_">�L�[�R�[�h</param>
/// <returns>�����ꂽ�u�ԂȂ�TRUE</returns>
BOOL ClKeyboard::GetIsKeyUp(int key_input_) {
    //�L�[�������ꂽ�u�Ԃ�(-1)
    if (m_key_cnt[key_input_] == KEY_UP_NUM) { return TRUE; }  //�����ꂽ�u��
    else { return FALSE; }                      //�����ꂽ�Ԃł͂Ȃ�
}

/// <summary>
/// �L�[�𗣂��Ă����Ԃ�(0�ȉ�)
/// </summary>
/// <param name="key_input_">�L�[�R�[�h</param>
/// <returns>������Ă���Ȃ�TRUE</returns>
BOOL ClKeyboard::GetIsKeyAway(int key_input_) {
    //�L�[�𗣂��Ă����Ԃ�(0�ȉ�)
    if (m_key_cnt[key_input_] <= KEY_UPPING_NUM) { return TRUE; }   //�����Ă�����
    else { return FALSE; }                      //������Ă��Ȃ����
}

/// <summary>
/// �w�莞�ԉ����ꂽ��
/// </summary>
/// <param name="key_input_">�L�[�R�[�h</param>
/// <param name="time">�w�莞��(�b)</param>
/// <returns>�w�莞�ԉ����ꂽ�u��TRUE</returns>
BOOL ClKeyboard::GetIsKeyTimeInput(int key_input_, float time) {
    //�����ꂽ�u�Ԃ�-1�ɂȂ��Ă���̂ŃG���[���N���Ȃ��悤��0�ɏC��
    int key = m_key_cnt[key_input_];
    if (key < KEY_UPPING_NUM) { key = KEY_UPPING_NUM; }

    //�L�[��������Ă���Ȃ�t���O�����낷
    if (key == KEY_UPPING_NUM) {
        //�����t���O��߂�
        if (m_is_time_input_after[key_input_][n_com::IF_CASE_TYPE::EQUAL] == TRUE) {
            m_is_time_input_after[key_input_][n_com::IF_CASE_TYPE::EQUAL] = FALSE;
        }
        return FALSE;
    }

    //���������Ă��鎞�Ԃ̓~���b���~FPS�l
    //��F1.5�b�~60FPS = 90(keyTime)
    int updateTime
        = static_cast<int>(time * ClFps::GetIns()->GetFpsFloatValue());

    //�w�莞�ԉ����ꂽ��
    //�����ꂽ
    if (m_is_time_input_after[key_input_][n_com::IF_CASE_TYPE::EQUAL] == FALSE 
        &&key == updateTime) {
        m_is_time_input_after[key_input_][n_com::IF_CASE_TYPE::EQUAL] = TRUE;
        return  TRUE; 
    }    
    else { return FALSE; }                      //������Ă��Ȃ�
}

/// <summary>
/// �w�莞��(�b)(�𒴂��� / �ȏ� / �Ɠ��� / �ȉ� / �����L�[�������ꂽ��(��{�F�𒴂���)
/// </summary>
/// <param name="key_input_">�L�[�R�[�h</param>
/// <param name="milliTime">���肷�鎞��(�b)</param>
/// <param name="key_keep_type">���肷�鉉�Z�q�̎�� : ���肷�鎞��(�𒴂��� / �ȏ� / �Ɠ��� / �ȉ� / ����)</param>
/// <returns></returns>
BOOL ClKeyboard::GetIsKeyTimeInput(int key_input_, float time, n_com::IF_CASE_TYPE key_case_type) {
   
    //�����ꂽ�u�Ԃ�-1�ɂȂ��Ă���̂ŃG���[���N���Ȃ��悤��0�ɏC��
    int key = m_key_cnt[key_input_];
    if (key < KEY_UPPING_NUM) { key = KEY_UPPING_NUM; }

    //�L�[�𗣂��Ă���Ȃ�FALSE��Ԃ�
    if (key == KEY_UPPING_NUM) { 
        //�����t���O��߂�
        if (m_is_time_input_after[key_input_][key_case_type] == TRUE) {
            m_is_time_input_after[key_input_][key_case_type] = FALSE;
        }
        return FALSE;
    }

    //���������Ă��鎞�Ԃ̓~���b���~FPS�l
    //��F1.5�b�~60FPS = 90(keyTime)
    int updateTime
        = static_cast<int>(time * ClFps::GetIns()->GetFpsFloatValue());

    //���肷�鉉�Z�q�̎�ނŏ����������Ă���TRUE�ŕԂ�
    switch (key_case_type) {

        //�w�莞��(�b)�𒴂���( > )�� 
    case n_com::IF_CASE_TYPE::OVER:
        if (m_is_time_input_after[key_input_][key_case_type] == TRUE) { return TRUE; }
        if ( key > updateTime) {
            m_is_time_input_after[key_input_][key_case_type] = TRUE;
            return TRUE;
        }
        break;

        //�w�莞��(�b)�@�ȏ�@( >= )�� 
    case n_com::IF_CASE_TYPE::ABOVE:
        if (m_is_time_input_after[key_input_][key_case_type] == TRUE) { return TRUE; }
        if (key >= updateTime) { 
            m_is_time_input_after[key_input_][key_case_type] = TRUE;
            return TRUE; 
        }
        break;

        //�w�莞��(�b)�Ɠ����@( == )�� 
    case n_com::IF_CASE_TYPE::EQUAL:
        if (m_is_time_input_after[key_input_][key_case_type] == FALSE
            && key == updateTime) {
            m_is_time_input_after[key_input_][key_case_type] = TRUE;
            return TRUE;
        }
        break;

        //�w�莞��(�b)�@�ȉ��@( <= )�� 
    case n_com::IF_CASE_TYPE::IN_UNDER:
        if (m_is_time_input_after[key_input_][key_case_type] == TRUE) { return FALSE; }
        if (key <= updateTime) { return TRUE; }
        else { m_is_time_input_after[key_input_][key_case_type] = TRUE; }
        break;

        //�w�莞��(�b)�@�����@( > )�� 
    case n_com::IF_CASE_TYPE::LESS_THAN:
        if (m_is_time_input_after[key_input_][key_case_type] == TRUE) { return FALSE; }
        if (key < updateTime) { return TRUE; }
        else { m_is_time_input_after[key_input_][key_case_type] = TRUE; }
        break;

        //�Ⴄ�l���Ԉ���ē���Ă��܂����Ƃ��͉������Ȃ�
    default:
        break;
    }

    //����O��������FALSE��Ԃ�
    return FALSE;
}