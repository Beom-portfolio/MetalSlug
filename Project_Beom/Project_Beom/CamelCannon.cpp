#include "pch.h"
#include "CamelCannon.h"
#include "CamelCannonBullet.h"

CamelCannon::CamelCannon()
{
}

CamelCannon::~CamelCannon()
{
}

bool CamelCannon::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 300, 300 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 10, 10 };

	m_SpriteInfo.key = L"camel_cannon";
	m_SpriteInfo.SpriteIndex = 0.f;
	m_SpriteInfo.StateIndex = 0;
	m_SpriteInfo.MaxFrame = 32;
	m_SpriteInfo.Speed = 20.f;

	m_Angle = 0.f;
	m_Speed = 200.f;
	return true;
}

int CamelCannon::Update(const float& TimeDelta)
{
	float tAngle = m_Angle;
	int count = 0;
	while (0 <= tAngle)
	{
		tAngle -= 11.25f;
		++count;
	}

	if (0 > tAngle)
		--count;

	m_SpriteInfo.StateIndex = (int)m_spriteIndexY;

	POSITION pos = AnglePos(0.f, 0.f, 11.25f * count, 30);
	m_CollideInfo.Pos_X = pos.X;
	m_CollideInfo.Pos_Y = pos.Y;

	m_SpriteInfo.SpriteIndex = (float)count;

	GameObject::Update(TimeDelta);

	return 0;
}

void CamelCannon::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();
	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(255, 255, 255));
}

void CamelCannon::Release()
{
}

int CamelCannon::UpdateInput(const float& TimeDelta)
{
	// 제대로 하려면 문제가 많아짐...
	{
		if (m_Angle >= 90.f && m_Angle < 270.f)
			m_leftCheck = true;
		else if (m_Angle <= 90.f || m_Angle >= 270.f)
			m_leftCheck = false;

		if (m_Angle >= 0.f && m_Angle < 180.f)
			m_upCheck = true;
		else if (m_Angle <= 360.f && m_Angle >= 180.f)
			m_upCheck = false;


		if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_LEFT))
		{
			if (m_upCheck)
			{
				m_Angle += m_Speed * TimeDelta;
				if (m_Angle > 180.f)
					m_Angle = 180.f;
			}
			else
			{
				m_Angle -= m_Speed * TimeDelta;
				if (m_Angle < 180.f)
					m_Angle = 180.f;
			}
		}

		if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_RIGHT))
		{
			if (m_upCheck)
			{
				m_Angle -= m_Speed * TimeDelta;
				if (m_Angle < 0.f)
					m_Angle = 0.f;
			}
			else
			{
				m_Angle += m_Speed * TimeDelta;
				if (m_Angle > 360.f)
					m_Angle = 360.f;
			}
		}

		if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_UP))
		{
			if (m_leftCheck)
			{
				m_Angle -= m_Speed * TimeDelta;
				if (m_Angle < 90.f)
					m_Angle = 90.f;
			}
			else
			{
				m_Angle += m_Speed * TimeDelta;
				if (m_Angle < 270.f && m_Angle > 90.f)
					m_Angle = 90.f;
			}
		}

		if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_DOWN))
		{
			if (m_leftCheck)
			{
				m_Angle += m_Speed * TimeDelta;
				if (m_Angle > 270.f)
					m_Angle = 270.f;
			}
			else
			{
				m_Angle -= m_Speed * TimeDelta;
				if (m_Angle > 90.f && m_Angle < 270.f)
					m_Angle = 270.f;
			}
		}

		if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, 'A'))
		{
			if (m_TimeStack > 0.045f)
			{
				GameObject* bullet = AbstractFactory<CamelCannonBullet>::CreateObj();
				bullet->SetPosition(m_OriginCollidePos.X, m_OriginCollidePos.Y);
				bullet->SetAngle(((int)m_Angle / 10) * 10.f);
				GETMGR(ObjectManager)->AddObject(bullet, OBJ_PLAYER_BULLET);
				m_TimeStack = 0.f;
			}

			m_spriteIndexY += 40.f * TimeDelta;

			if (5.f <= m_spriteIndexY)
				m_spriteIndexY = 1.f;
		}
		else
		{
			m_spriteIndexY = 0.f;
		}
	}

	if (m_Angle < 0.f)
		m_Angle += 360.f;

	if (m_Angle >= 360.f)
		m_Angle = 0.f;

	return 0;
}
