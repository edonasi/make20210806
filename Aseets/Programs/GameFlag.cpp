//*--------------------------------------------------------------------------------*
//							�Q�[�����s�̃t���O���Ǘ�����
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include GAME_FLAG_HPP
using namespace n_game_flag;

//*--------------------------------------------------------------------------------*
//								�V���O���g������
//*--------------------------------------------------------------------------------*

//�V���O���g����GameStateManager�N���X�̃I�u�W�F�N�g
ClGameFlag* ClGameFlag::m_ins = nullptr;

/// <summary>
/// �R���X�g���N�^�A������
/// </summary>
ClGameFlag::ClGameFlag() { m_is_play = TRUE; }

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
ClGameFlag::ClGameFlag(const ClGameFlag& src){
	//�A�h���X���R�s�[���Ă���
	m_ins = src.m_ins;
}

/// <summary>
/// �R�s�[�R���X�g���N�^
/// </summary>
/// <param name="src">�R�s�[���A�h���X</param>
/// <returns>���̃C���X�^���X�̃A�h���X</returns>
ClGameFlag& ClGameFlag::operator=(const ClGameFlag& src){
	//�A�h���X���R�s�[���Ă���
	m_ins = src.m_ins;
	return *this;
}


/// <summary>
/// �f�X�g���N�^
/// </summary>
ClGameFlag::~ClGameFlag() { return; }

/// <summary>
/// �C���X�^���X�擾(���߂ĎQ�Ƃ���Ƃ��̓C���X�^���X�𐶐�)
/// </summary>
/// <returns><�V���O���g���ȃC���X�^���X/returns>
ClGameFlag* ClGameFlag::GetIns(){
	//���߂Ď擾���鎞�A���̃I�u�W�F�N�g�𐶐��𐶐�
	if (m_ins == nullptr)
	{
		//�������̊m��
		m_ins = new ClGameFlag();
	}

	return m_ins;
}

/// <summary>
/// �I�u�W�F�N�g�̔j��
/// </summary>
VOID ClGameFlag::Destroy(){
	//�������̔j��
	delete m_ins;
	m_ins = nullptr;
}

//�Q�[�����s�̃t���O�����낷
VOID ClGameFlag::SetEndPlay() { m_is_play = FALSE; }

//�Q�[�����s���Ă���̂��Q�Ƃ���
BOOL ClGameFlag::GetIsPlay() { return m_is_play; }