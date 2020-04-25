#include "pch.h"
#include "SoldierBomb.h"
#include "MediumExplosion.h"

SoldierBomb::SoldierBomb()
{
}

SoldierBomb::~SoldierBomb()
{
}

void SoldierBomb::SetBombRoot(POSITION dst, POSITION src)
{
	// 폭탄의 루트를 미리 예측한다
	// 속력을 미리 구한다. x, y축
	// https://robatokim.tistory.com/entry/%EA%B2%8C%EC%9E%84%EC%88%98%ED%95%99-%EC%97%AD%ED%83%84%EB%8F%84%EA%B3%84%EC%82%B0%EC%9D%84-%EC%9D%B4%EC%9A%A9%ED%95%9C-%EB%91%90%EC%A0%90-%EC%82%AC%EC%9D%98-%ED%8F%AC%EB%AC%BC%EC%84%A0-%EA%B5%AC%ED%95%98%EA%B8%B0
	
	m_originPos = src;

	float distHeight = abs(dst.Y - src.Y);
	float maxHeight = 220;
	m_Gravity = 2 * maxHeight / (0.7f * 0.7f);
	m_velocityY = sqrtf(2 * m_Gravity * maxHeight);

	float b = -2 * m_velocityY;
	float c = 2 * distHeight;

	float dat = (-b + sqrtf(b * b - 4 * m_Gravity * c)) / (2 * m_Gravity);
	m_velocityX = -(src.X - dst.X) / dat;
}

bool SoldierBomb::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 150, 150 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 30, 30 };
	m_ObjType = OBJ_MONSTER_BULLET;
	m_RenderType = RENDER_OBJ;
	m_SpriteInfo.key = L"soldier_bomb_bullet";
	m_SpriteInfo.MaxFrame = 16;
	m_SpriteInfo.SpriteIndex = 0.f;
	m_SpriteInfo.Speed = 25.f;

	m_Speed = 330.f;

	return true;
}

int SoldierBomb::Update(const float& TimeDelta)
{
	// 포물선 예측 운동
	m_Info.Pos_X = m_originPos.X + m_velocityX * m_TimeStack;
	m_Info.Pos_Y = m_originPos.Y - (m_velocityY * m_TimeStack - 0.5f * m_Gravity * m_TimeStack * m_TimeStack);

	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;

	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_SpriteInfo.SpriteIndex = 0.f;

	if (m_cullingCheck)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void SoldierBomb::Render(HDC hdc)
{
	HDC hMemDC;
	hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC, (int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(255, 0, 255));
}

void SoldierBomb::Release()
{
}

void SoldierBomb::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
{
	if (PIXEL24{ 0, 0, 248 } == collPixelColor && 0 != dir)
	{
		GameObject* effect = AbstractFactory<MediumExplosion>::CreateObj();
		effect->SetPosition(m_Info.Pos_X, m_Info.Pos_Y);
		GETMGR(ObjectManager)->AddObject(effect, OBJ_PLAYER_BULLET);
		m_isDead = true;
	}
}

void SoldierBomb::CollisionActivate(GameObject* collideTarget)
{
	GameObject* effect = AbstractFactory<MediumExplosion>::CreateObj();
	effect->SetPosition(m_Info.Pos_X, m_Info.Pos_Y);
	GETMGR(ObjectManager)->AddObject(effect, OBJ_PLAYER_BULLET);
	m_isDead = true;
}
