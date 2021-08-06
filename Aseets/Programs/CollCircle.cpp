//*--------------------------------------------------------------------------------*
//								�ۓ����蔻��
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								�w�b�_�t�@�C���ǂݍ���
//*--------------------------------------------------------------------------------*
//		CommonUse�t�@�C��
#include "IncludeFile.hpp"
//		���g�̃t�@�C��
#include COLL_CIRCLE_HPP
using namespace n_coll_circle;
//		�W���t�@�C��
#include <math.h>
using namespace std;
//		�l�[��
using namespace n_xy;
using namespace n_rect;
using namespace n_circle;

//*--------------------------------------------------------------------------------*
//								�R���X�g���N�^
//*--------------------------------------------------------------------------------*

ClCollCircle::ClCollCircle() { m_coll = ClCircle(); }
ClCollCircle::~ClCollCircle() { return; }

//*--------------------------------------------------------------------------------*
//								�v���p�e�B
//*--------------------------------------------------------------------------------*

//�����蔻��͈͂��Q��
ClCircle ClCollCircle::GetColl() { return m_coll; }

//�����蔻��͈͂�ݒ�(is_coll=FALSE�ł��\)
VOID ClCollCircle::SetColl(int x, int y, int radius) { m_coll.SetCircle(x, y, radius); }

//*--------------------------------------------------------------------------------*
//								�֐�
//*--------------------------------------------------------------------------------*

//�����蔻����X�V
VOID ClCollCircle::Update(int x, int y) {
	if (m_is_coll == FALSE) { return; }		//�����蔻�肪�쓮���Ă��Ȃ�
	m_coll.SetPos(x, y);
}		

BOOL ClCollCircle::IsStay(ClXY point) {
	if (MmIsStay(m_coll, point) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClCollCircle::IsStay(ClRect rect) {
	if (MmIsStay(m_coll, rect) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClCollCircle::IsStay(ClCircle circle) {
	if (MmIsStay(m_coll, circle) == TRUE) { return TRUE; }
	return FALSE;
}


const float PI = 3.14159265358979323846f;

const int DEFULT_LINE_THICK = 1;	//�f�t�H���g�̐��̑���

VOID ClCollCircle::DrawDebug() {
	DrawDebug(ClCom().GetFlipColor(), DEFULT_LINE_THICK);
}
VOID ClCollCircle::DrawDebug(unsigned int color) {
	DrawDebug(color, DEFULT_LINE_THICK);
}

const int POS_FIX = 1;

VOID ClCollCircle::DrawDebug(unsigned int color, int thick) {
	//�����蔻�肪�쓮���ĂȂ��Ȃ珈�����I��
	if (ClWin().GetIsDebug() == FALSE) { return; }
	if (m_is_coll == FALSE) { return; }

	float deg45 = 45.0f * PI / 180.0f;
	float mult = static_cast<float>(sin(static_cast<double>(deg45)));
	int center_fix = m_coll.radius * mult + POS_FIX;

	DrawLine(
		m_coll.center.x - center_fix + POS_FIX,
		m_coll.center.y - center_fix + POS_FIX,
		m_coll.center.x + center_fix,
		m_coll.center.y + center_fix,
		color, thick);

	DrawLine(
		m_coll.center.x + center_fix,
		m_coll.center.y - center_fix,
		m_coll.center.x - center_fix + POS_FIX,
		m_coll.center.y + center_fix + POS_FIX,
		color, thick);

	for (int i = 0; i < thick; i++) {
		DrawCircle(
			m_coll.center.x, m_coll.center.y,
			m_coll.radius - i, color,
			FALSE, DEFULT_LINE_THICK);
		if (m_coll.radius < i) { return; }
	}
}