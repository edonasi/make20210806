//*--------------------------------------------------------------------------------*
//								丸当たり判定
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include COLL_CIRCLE_HPP
using namespace n_coll_circle;
//		標準ファイル
#include <math.h>
using namespace std;
//		ネーム
using namespace n_xy;
using namespace n_rect;
using namespace n_circle;

//*--------------------------------------------------------------------------------*
//								コンストラクタ
//*--------------------------------------------------------------------------------*

ClCollCircle::ClCollCircle() { m_coll = ClCircle(); }
ClCollCircle::~ClCollCircle() { return; }

//*--------------------------------------------------------------------------------*
//								プロパティ
//*--------------------------------------------------------------------------------*

//当たり判定範囲を参照
ClCircle ClCollCircle::GetColl() { return m_coll; }

//当たり判定範囲を設定(is_coll=FALSEでも可能)
VOID ClCollCircle::SetColl(int x, int y, int radius) { m_coll.SetCircle(x, y, radius); }

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

//当たり判定を更新
VOID ClCollCircle::Update(int x, int y) {
	if (m_is_coll == FALSE) { return; }		//当たり判定が作動していない
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

const int DEFULT_LINE_THICK = 1;	//デフォルトの線の太さ

VOID ClCollCircle::DrawDebug() {
	DrawDebug(ClCom().GetFlipColor(), DEFULT_LINE_THICK);
}
VOID ClCollCircle::DrawDebug(unsigned int color) {
	DrawDebug(color, DEFULT_LINE_THICK);
}

const int POS_FIX = 1;

VOID ClCollCircle::DrawDebug(unsigned int color, int thick) {
	//当たり判定が作動してないなら処理を終了
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