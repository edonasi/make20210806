#pragma once
#include AUDIO_HPP	//���ʒ����ȂǂɎg�p
#include FADE_HPP	//�t�F�[�h�A�E�g�C�������Ɏg�p
#include<vector>	//���[�h�������y���L�^����p�Ɏg�p

namespace n_audio_mult {

	//Audio�̉��ʂ��Ǘ�
	class ClAudioMult {

		//*----------------------------------------------------------------------------*
		//							public��������
		//*----------------------------------------------------------------------------*

	public:

		//		�V���O���g������
		static ClAudioMult* GetIns();		//�C���X�^���X�擾
		VOID Destroy();			//�C���X�^���X�̔j��

		//		�v���p�e�B
		int GetVecSize();					//�ǂݍ���ł��鐔
		//����(0.0�`1.0)
		float GetBgmDecimalPar();			//bgm���ʂ̊���(0.0�`1.0)��Ԃ�
		float GetSeSystemDecimalPar();		//se��system�̉��ʂ̊�����Ԃ�
		float GetSePlayDecimalPar();		//se��play	�̉��ʂ̊�����Ԃ�
		//����(0%�`100%)
		int GetBgmIntPar();					//bgm���ʂ̊���(0%�`100%)��Ԃ�
		int GetSeSystemIntPar();			//se��system���ʂ̊���(0%�`100%)��Ԃ�
		int GetSePlayIntPar();				//se��play	���ʂ̊���(0%�`100%)��Ԃ�

		//		�֐�
		VOID VectorAudioEmplace(n_audio::ClAudio* audio);	//���[�h�������y���L��
		VOID VectorAudioFindErase(n_audio::ClAudio* audio);	//�L���������y�̒�����w�肵�����y��T���ď���
		VOID VectorAudioAllErase();		//�L���������y��S�폜
		VOID VecSizeDraw();
		//		���ʕύX
		//64�i�K�F�}�E�X�n���A�A�ˌn��
		VOID BgmVolumeChange64Step(BOOL is_up);			//BGM
		VOID SeSystemVolumeChange64Step(BOOL is_up);	//�V�X�e����
		VOID SePlayVolumeChange64Step(BOOL is_up);		//�U�����n
		//16�i�K�F�L�[�{�[�h�n��
		VOID BgmVolumeChange16Step(BOOL is_up);			//BGM
		VOID SeSystemVolumeChange16Step(BOOL is_up);	//�V�X�e����
		VOID SePlayVolumeChange16Step(BOOL is_up);		//�U�����n
		//���y�S�̂��~���[�g
		VOID VecMute();
		//�t�F�[�h�A�E�g�C��
		VOID SetFadeUpStart(float all_time);
		VOID SetFadeDownStart(float all_time);
		VOID SetFadeDownUpStart(float all_time);
		VOID FadeProc();

		//*----------------------------------------------------------------------------*
		//							private��������
		//*----------------------------------------------------------------------------*

	private:
		//		�V���O���g������
		static ClAudioMult* m_ins;		//�V���O���g���ȃC���X�^���X
		ClAudioMult();						//�R���X�g���N�^
		ClAudioMult(const ClAudioMult& src);		//�R�s�[�R���X�g���N�^
		ClAudioMult& operator=(const ClAudioMult& src);
		virtual ~ClAudioMult();				//�f�X�g���N�^

		//		�����o�֐�
		//���ʂ̊���(0.0�`1.0)��Ԃ�
		float MmGetAudioParcent(int m_volume);	
		//���̌㉹�ʂ̕ύX���s����
		BOOL MmIsVolumeChange(int POWER_NUM_, BOOL is_up, int* m_change_volume);
		//���ʂ̕ύX
		VOID MmVolumeChange(n_audio::SE_TYPE se_type, float decimal_par);
		//SeType�ɂ���ĉ��ʂ̊�����Ԃ�(0.0f�`1.0f)
		float MmGetDecimalPar(n_audio::SE_TYPE se_type);

		//		�����o�ϐ�
		std::vector<n_audio::ClAudio*> m_load_audio;
		BOOL m_is_audio_mute;		//�~���[�g��
		int m_bgm_volume;			//bgm�̃{�����[��
		int m_se_system_volume;		//se��system�̃{�����[��
		int m_se_play_volume;		//se��play  �̃{�����[��
		n_fade::ClFade m_fade;		//�t�F�[�h�A�E�g�C������Ƃ��Ɏg�p
	};
}