//*--------------------------------------------------------------------------------*
//								当たり判定のある画像
//*--------------------------------------------------------------------------------*

//*--------------------------------------------------------------------------------*
//								ヘッダファイル読み込み
//*--------------------------------------------------------------------------------*
//		CommonUseファイル
#include "IncludeFile.hpp"
//		自身のファイル
#include IMG_COLL_HPP
using namespace n_img_coll;
//		ネーム
using namespace n_rect;
using namespace n_coll_rect;
using namespace n_circle;
using namespace n_coll_circle;

//*--------------------------------------------------------------------------------*
//								コンストラクタ
//*--------------------------------------------------------------------------------*

ClImgColl::ClImgColl() { m_coll_rect = ClCollRect(); }
ClImgColl::~ClImgColl() { return; }

//*--------------------------------------------------------------------------------*
//								プロパティ
//*--------------------------------------------------------------------------------*

ClRect ClImgColl::GetCollRect() {
	return m_coll_rect.GetColl();
}

n_xy::ClXY ClImgColl::GetSize() {
	return m_size;
}

VOID ClImgColl::SetIsDraw() {
	m_is_draw = TRUE;
	m_coll_rect.SetIsColl(TRUE);
}

VOID ClImgColl::SetIsDraw(BOOL is_set) {
	m_is_draw = is_set;
	m_coll_rect.SetIsColl(is_set);
}

VOID ClImgColl::SetIsDraw(BOOL is_draw, BOOL is_coll) {
	m_is_draw = is_draw;
	m_coll_rect.SetIsColl(is_coll);
}

//*--------------------------------------------------------------------------------*
//								関数
//*--------------------------------------------------------------------------------*

BOOL ClImgColl::Load(string path, string cpp_name, string ins_name) {
	//FALSEなら読み込み失敗
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	m_coll_rect.SetColl(m_pos.x, m_pos.y, m_size.x, m_size.y);

	return TRUE;	//読み込み成功
}

VOID ClImgColl::Draw() {
	if (m_is_draw == TRUE) { DrawGraph(m_pos.x, m_pos.y, m_handle, TRUE); }
	m_coll_rect.DrawDebug();
}

VOID ClImgColl::Draw(BOOL is_coll_draw) {
	if (m_is_draw == TRUE) { DrawGraph(m_pos.x, m_pos.y, m_handle, TRUE); }
	
	if (is_coll_draw == TRUE) { m_coll_rect.DrawDebug(); }
	
}

VOID ClImgColl::CollDebugDraw() { m_coll_rect.DrawDebug(); }

VOID ClImgColl::Delete() {
	DeleteGraph(m_handle);
	m_is_draw = FALSE;
	m_coll_rect.SetIsColl(FALSE);
}

VOID ClImgColl::Move(int x_mult, int y_mult) {
	m_pos.x += ClFps::GetIns()->GetFpsIntFix(x_mult * m_abs_speed, &m_over_speed);
	m_pos.y += ClFps::GetIns()->GetFpsIntFix(y_mult * m_abs_speed, &m_over_speed);
	m_coll_rect.Update(m_pos.x, m_pos.y);
}

VOID ClImgColl::SetMove(int x, int y) {
	m_pos.x = x;
	m_pos.y = y;
	m_coll_rect.Update(m_pos.x, m_pos.y);
}

BOOL ClImgColl::IsStay(n_xy::ClXY point) {
	if (m_coll_rect.IsStay(point) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClImgColl::IsStay(n_rect::ClRect rect) {
	if (m_coll_rect.IsStay(rect) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClImgColl::IsStay(n_circle::ClCircle circle) {
	if (m_coll_rect.IsStay(circle) == TRUE) { return TRUE; }
	return FALSE;
}


//*--------------------------------------------------------------------------------*
//								円
//*--------------------------------------------------------------------------------*

//*------------------------------------------------*
//		コンストラクタ
//*------------------------------------------------*

ClImgCollCircle::ClImgCollCircle() { m_coll_circle = ClCollCircle(); }
ClImgCollCircle::~ClImgCollCircle() { return; }

//*------------------------------------------------*
//		プロパティ
//*------------------------------------------------*

ClCircle ClImgCollCircle::GetCollCircle() {
	return m_coll_circle.GetColl();
}

BOOL ClImgCollCircle::GetIsDraw() { return m_is_draw; }

int ClImgCollCircle::GetRadius() { return m_coll_circle.GetRadius(); }

int ClImgCollCircle::GetHandle() { return m_handle; }

VOID ClImgCollCircle::SetHandle(int handle) { m_handle = handle; }

VOID ClImgCollCircle::SetIsDraw() {
	m_is_draw = TRUE;
	m_coll_circle.SetIsColl(TRUE);
}

VOID ClImgCollCircle::SetIsDraw(BOOL is_set) {
	m_is_draw = is_set;
	m_coll_circle.SetIsColl(is_set);
}

VOID ClImgCollCircle::SetIsDraw(BOOL is_draw, BOOL is_coll) {
	m_is_draw = is_draw;
	m_coll_circle.SetIsColl(is_coll);
}

//*------------------------------------------------*
//		関数
//*------------------------------------------------*

BOOL ClImgCollCircle::Load(string path, string cpp_name, string ins_name) {
	//FALSEなら読み込み失敗
	if (MmLoad(path, cpp_name, ins_name) == FALSE) { return FALSE; }

	int radius = m_size.x < m_size.y ? m_size.x / 2 : m_size.y / 2;
	m_coll_circle.SetColl(m_pos.x + radius, m_pos.y + radius, radius);

	return TRUE;	//読み込み成功
}

VOID ClImgCollCircle::Draw() {
	if (m_is_draw == TRUE) { DrawGraph(m_pos.x, m_pos.y, m_handle, TRUE); }
	m_coll_circle.DrawDebug();
}

VOID ClImgCollCircle::Draw(BOOL is_coll_draw) {
	if (m_is_draw == TRUE) { DrawGraph(m_pos.x, m_pos.y, m_handle, TRUE); }

	if (is_coll_draw == TRUE) { m_coll_circle.DrawDebug(); }

}

VOID ClImgCollCircle::CollDebugDraw() { m_coll_circle.DrawDebug(); }

VOID ClImgCollCircle::Delete() {
	DeleteGraph(m_handle);
	m_is_draw = FALSE;
	m_coll_circle.SetIsColl(FALSE);
}

VOID ClImgCollCircle::SetMove(int x, int y) {
	m_pos.x = x; //ClFps::GetIns()->GetFpsIntFix(x * m_abs_speed, &m_over_speed);
	m_pos.y = y;// ClFps::GetIns()->GetFpsIntFix(y * m_abs_speed, &m_over_speed);
	m_coll_circle.Update(
		m_pos.x + m_coll_circle.GetColl().radius,
		m_pos.y + m_coll_circle.GetColl().radius);
}

VOID ClImgCollCircle::Move(int x_mult, int y_mult) {
	m_pos.x += ClFps::GetIns()->GetFpsIntFix(x_mult * m_abs_speed, &m_over_speed);
	m_pos.y += ClFps::GetIns()->GetFpsIntFix(y_mult * m_abs_speed, &m_over_speed);
	m_coll_circle.Update(
		m_pos.x + m_coll_circle.GetColl().radius,
		m_pos.y + m_coll_circle.GetColl().radius);
}

BOOL ClImgCollCircle::IsStay(n_xy::ClXY point) {
	if (m_coll_circle.IsStay(point) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClImgCollCircle::IsStay(n_rect::ClRect circle) {
	if (m_coll_circle.IsStay(circle) == TRUE) { return TRUE; }
	return FALSE;
}

BOOL ClImgCollCircle::IsStay(n_circle::ClCircle circle, BOOL is_circle_coll) {
	if (is_circle_coll==TRUE&&m_coll_circle.IsStay(circle) == TRUE) { return TRUE; }
	return FALSE;
}
