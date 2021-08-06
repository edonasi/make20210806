//*--------------------------------------------------------------------------------*
//								���C������
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�Q�l�T�C�g
//*--------------------------------------------------------------------------------*
//�E�V�E�b����`�Q�[���v���O���~���O�̊�[�c�w���C�u����]
//https://dixq.net/g/
//�E�c�w���C�u�����֐����t�@�����X�y�[�W
//https://dxlib.xsrv.jp/dxfunc.html
//C++�ɂ�����I�u�W�F�N�g�̎�舵����[�V���O���g��]
//https://www.haljion.net/index.php/2019-11-13-03-27-18/119-2019-11-13-03-22-16/rx-62n/222-c*/

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		Singleton�t�@�C��
#include AUDIO_MULT_HPP
using namespace n_audio_mult;
#include KEYBOARD_HPP
using namespace n_keyboard;
#include MOUSE_HPP
using namespace n_mouse;
#include GAME_SCENE_HPP
using namespace n_game_scene;
#include GAME_FLAG_HPP
using namespace n_game_flag;

//*--------------------------------------------------------------------------------*
//								����
//*--------------------------------------------------------------------------------*

//�֐��v���g�^�C�v�錾
VOID WinMainInit();			/// WinMain�̏�����
BOOL IsGameWhile();			//�Q�[���p������
VOID GameWhileDebugDraw();	//�Q�[���̌p���f�o�b�N�`��
VOID WinMainEnd();			// WinMain�I�������A�V���O���g���C���X�^���X��j��

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	//WinMain�̏�����
	WinMainInit();

	//�Q�[���J�n�O�̏���
	ClGameScene::GetIns()->GameInit();

	//�J��Ԃ�����
	while (IsGameWhile() == TRUE) {
		ClGameScene::GetIns()->GameSceneSwitch();	//�Q�[���̏���
		GameWhileDebugDraw();						//�p���f�o�b�N�`��
	}

	//WinMain�I�������A�V���O���g���C���X�^���X��j��
	WinMainEnd();

	// �\�t�g�̏I��
	return 0;
}

/// <summary>
/// WinMain�̏�����
/// </summary>
VOID WinMainInit() {
	ClWin().BeforeInit();
	ClWin().Init();
	ClWin().AfterInit();
}

//�Q�[���̌p������
BOOL IsGameWhile() {
	if (ProcessMessage() != 0) { return FALSE; }
	if (ClGameFlag::GetIns()->GetIsPlay() == FALSE) {	//�Q�[�����s���邩
		return FALSE;
	}
	if (ScreenFlip() != 0) { return FALSE; }			//��ʔ��]
	if (ClearDrawScreen() != 0) { return FALSE; }		//��ʂ̏���
	if (ClKeyboard::GetIns()->GpUpdateKey() != 0) {		//�L�[�̍X�V
		return FALSE; 
	}
	if (ClMouse::GetIns()->MouseUpdate() != 0) {		//�}�E�X�̍X�V
		return FALSE; 
	}

	ClFps::GetIns()->FpsUpdate();	//fps�̍X�V
	
	return TRUE;
}

//�p���f�o�b�N�`��
VOID GameWhileDebugDraw() {
	ClFps::GetIns()->FpsDraw();			//fps�̕`��
	ClMouse::GetIns()->MousePosDraw();	//�}�E�X�̈ʒu����`��
}

/// <summary>
/// WinMain�I�������A�V���O���g���C���X�^���X��j��
/// </summary>
VOID WinMainEnd() {
	//ComSingleton�N���X��j��
	ClFps::GetIns()->Destroy();

	//AnySingleton�N���X��j��
	ClAudioMult::GetIns()->Destroy();
	ClKeyboard::GetIns()->Destroy();
	ClMouse::GetIns()->Destroy();
	ClGameFlag::GetIns()->Destroy();
	ClGameScene::GetIns()->Destroy();

	// �c�w���C�u�����g�p�̏I����������(return 0�Ń\�t�g���I������)
	DxLib_End();
}