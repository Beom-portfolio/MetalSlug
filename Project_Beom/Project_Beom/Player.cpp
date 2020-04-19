#include "pch.h"
#include "Player.h"
#include "KeyManager.h"
#include "CameraManager.h"
#include "PlayerBottom.h"
#include "PlayerTop.h"
#include "Camel.h"


Player::Player()
	: GameObject()
{
}

Player::~Player()
{
}

bool Player::Initialize()
{
	m_Info = GAMEOBJINFO{ 400, 300, 400, 267 };
	m_CollideInfo = GAMEOBJINFO{ 0, 10, 65, 90 };

	m_Speed = 250.f;
	m_RenderType = RENDER_OBJ;

	m_Bottom = AbstractFactory<PlayerBottom>::CreateObj();
	m_Top = AbstractFactory<PlayerTop>::CreateObj();

	m_isNotDead = true;

	m_Direction = DIR_RIGHT;
	m_Bottom->SetDirection(m_Direction);
	m_Top->SetDirection(m_Direction);

	// ���� �غ�
	if (DIR_RIGHT == m_Direction)
		m_SpriteInfo.key = L"player_spawn_r";
	else
		m_SpriteInfo.key = L"player_spawn_l";
	m_SpriteInfo.SpriteIndex = 0.f;
	m_SpriteInfo.StateIndex = 0;
	m_SpriteInfo.MaxFrame = 7;
	m_SpriteInfo.Speed = 20.f;
	m_Info.Size_X = 400;
	m_Info.Size_Y = 1150;
	m_spawnCheck = true;
	m_renderCheck = false;
	return true;
}

int Player::Update(const float& TimeDelta)
{
	// ���� ���
	if (m_isDead)
	{
		m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
		if ((float)(m_SpriteInfo.MaxFrame - 1) <= m_SpriteInfo.SpriteIndex)
			m_SpriteInfo.Speed = 0;

		if (!m_fallCheck)
		{
			m_TimeStack += TimeDelta;
			if (m_TimeStack >= 1.5f)
			{
				(m_renderCheck) ? (m_renderCheck = false) : (m_renderCheck = true);
				if (m_TimeStack >= 3.5f)
				{
					m_isDead = false;
					
					// ���� �غ�
					if (DIR_RIGHT == m_Direction)
						m_SpriteInfo.key = L"player_spawn_r";
					else
						m_SpriteInfo.key = L"player_spawn_l";
					m_SpriteInfo.SpriteIndex = 0.f;
					m_SpriteInfo.StateIndex = 0;
					m_SpriteInfo.MaxFrame = 7;
					m_SpriteInfo.Speed = 20.f;
					m_Info.Size_X = 400;
					m_Info.Size_Y = 1150;
					m_spawnCheck = true;
				}
			}
		}
		else
		{
			if (DIR_RIGHT == m_Direction)
				m_Info.Pos_X -= 100 * TimeDelta;
			else
				m_Info.Pos_X += 100 * TimeDelta;
		}
	}

	// ���� ���
	if (!m_fallCheck && m_spawnCheck)
	{
		m_renderCheck = true;
		m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
		if ((float)(m_SpriteInfo.MaxFrame) <= m_SpriteInfo.SpriteIndex)
		{
			m_TimeStack = 0.f;
			m_spawnCheck = false;
		}
	}

	// �߷�
	{
		if (m_fallCheck)
		{
			m_GravityTime += TimeDelta;
			m_GravitySpeed += GRAVITY_ACC * 1.5f * m_GravityTime;
			m_Info.Pos_Y += m_GravitySpeed * TimeDelta;
		}
	}

	// update part
	// �� ��ü ������Ʈ
	if(!m_isDead && !m_spawnCheck)
	{ 	
		if (m_TimeStack <= 2.f)
		{
			(m_renderCheck) ? (m_renderCheck = false) : (m_renderCheck = true);
		}
		else
		{
			m_isCollideOn = true;
			m_renderCheck = true;
		}

		if (m_rideCheck)
		{
			// ��Ÿ�� ���󰣴�.
			POSITION slugPos = m_Slug->GetPosition();
			m_Info.Pos_X = slugPos.X - 15.f;
			m_Info.Pos_Y = slugPos.Y - 50.f;

			if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_LEFT) ||
				GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_RIGHT))
			{
				m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
				if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
					m_SpriteInfo.SpriteIndex = 0.f;
			}
			else
			{
				m_SpriteInfo.SpriteIndex = 0.f;
			}

			if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_DOWN))
			{
				if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, 'S'))
				{
					SetFall(true);
					m_GravitySpeed = -300.f;
					m_rideCheck = false;
					((Camel*)m_Slug)->SetRideCheck(false);
					m_Slug = nullptr;
					m_Bottom->Update(TimeDelta);
					m_Top->Update(TimeDelta);
				}
			}
			m_Bottom->SetPosition(m_Info.Pos_X, m_Info.Pos_Y);
			m_Top->SetPosition(m_Info.Pos_X, m_Info.Pos_Y);
		}
		else
		{
			UpdateInput(TimeDelta);

			m_Bottom->SetDirection(m_Direction);
			m_Top->SetDirection(m_Direction);
			m_Bottom->SetFall(m_fallCheck);
			m_Top->SetFall(m_fallCheck);
			m_Bottom->Update(TimeDelta);
			m_Top->Update(TimeDelta);
			m_Bottom->SetPosition(m_Info.Pos_X, m_Info.Pos_Y);
			m_Top->SetPosition(m_Info.Pos_X, m_Info.Pos_Y);
		}
	}

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Player::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	if (m_rideCheck || m_isDead || m_spawnCheck)
	{
		HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();
		TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
			hMemDC,
			(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
			m_SpriteInfo.StateIndex * m_Info.Size_Y,
			m_Info.Size_X, m_Info.Size_Y, RGB(86, 177, 222));
	}

	if (!m_rideCheck && !m_isDead && !m_spawnCheck)
	{
		m_Bottom->Render(hdc);
		m_Top->Render(hdc);
	}
}

void Player::Release()
{
	SAFE_RELEASE(m_Bottom);
	SAFE_RELEASE(m_Top);
}

void Player::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget)
{
	if ((dir & DIR_BOTTOM))
	{
		if (m_GravitySpeed < 0)
			return;

		SetFall(false);

		// ���� �ø�
		int x = (int)m_Info.Pos_X;
		int y = (int)m_CollideRect.bottom - (int)GETMGR(CameraManager)->GetPos().Y;

		const PIXELCOLLIDERINFO* pixelCollide = PixelTarget->GetPixelCollider();
		if (nullptr == pixelCollide)
			return;

		int count = 0;
		for (int i = 1; i < 1000; ++i)
		{
			int addr = (int)(y - i) * pixelCollide->Width + (int)x;
			if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
			if (!(pixelCollide->vecPixel[addr].r == pixelCollide->CollPixel.r &&
				 pixelCollide->vecPixel[addr].g == pixelCollide->CollPixel.g &&
				 pixelCollide->vecPixel[addr].b == pixelCollide->CollPixel.b))
			{
				break;
			}
			++count;
		}
		m_Info.Pos_Y -= count;		
	}
	else
	{
		if (m_fallCheck || m_GravitySpeed < 0)
			return;

		// �Ʒ��� ����
		int x = (int)m_Info.Pos_X;
		int y = (int)m_CollideRect.bottom - (int)GETMGR(CameraManager)->GetPos().Y;

		const PIXELCOLLIDERINFO* pixelCollide = PixelTarget->GetPixelCollider();
		if (nullptr == pixelCollide)
			return;

		int count = 0;
		for (int i = 0; i < 1000; ++i)
		{
			int addr = (int)(y + i) * pixelCollide->Width + (int)x;
			if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
			if (pixelCollide->vecPixel[addr].r == pixelCollide->CollPixel.r &&
				pixelCollide->vecPixel[addr].g == pixelCollide->CollPixel.g &&
				pixelCollide->vecPixel[addr].b == pixelCollide->CollPixel.b)
			{
				break;
			}
			++count;
		}
		m_Info.Pos_Y += count;
	}
}

void Player::CollisionActivate(GameObject* collideTarget)
{
	switch (collideTarget->GetObjectType())
	{
	case OBJ_SLUG:
		if (m_rideCheck) break;
		if (m_fallCheck && 0 < m_GravitySpeed)
		{
			SetFall(false);
			m_Slug = collideTarget;
			((Camel*)m_Slug)->SetRideCheck(true);
			m_rideCheck = true;

			m_SpriteInfo.key = L"player_ride";
			m_SpriteInfo.SpriteIndex = 0.f;
			m_SpriteInfo.StateIndex = 0;
			m_SpriteInfo.MaxFrame = 12;
			m_SpriteInfo.Speed = 25.f;
			m_Info.Size_X = 400; m_Info.Size_Y = 267;
		}
		break;
	case OBJ_MONSTER:
		m_Top->SetCollideCheck(true);
		m_Bottom->SetCollideCheck(true);
		break;
	case OBJ_MONSTER_BULLET:
		if (m_TimeStack <= 2.5f) break;
		//dead
		m_Info.Size_X = 400;
		m_Info.Size_Y = 267;
		if (DIR_RIGHT == m_Direction)
		{
			m_SpriteInfo.key = L"player_dead_r";
			SetFall(true);
			m_GravitySpeed = -170;
		}
		else
		{
			m_SpriteInfo.key = L"player_dead_l";
			SetFall(true);
			m_GravitySpeed = -170;
		}
		m_SpriteInfo.SpriteIndex = 0.f;
		m_SpriteInfo.StateIndex = 0;
		m_SpriteInfo.MaxFrame = 10;
		m_SpriteInfo.Speed = 10.f;
		m_TimeStack = 0.f;
		m_isDead = true;
		m_isCollideOn = false;
		m_rideCheck = false;
		break;
	}
}

void Player::CollisionDeactivate(GameObject* collideTarget)
{
	if (OBJ_MONSTER == collideTarget->GetObjectType())
	{
		m_Top->SetCollideCheck(false);
		m_Bottom->SetCollideCheck(false);
	}
}

int Player::UpdateInput(const float& TimeDelta)
{
	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_DOWN))
		m_CollideInfo = GAMEOBJINFO{ 0, 20, 55, 55 };
	else
		m_CollideInfo = GAMEOBJINFO{ 0, 10, 55, 90 };

	if (-1 == (int)m_Bottom->GetSpeed())
		m_Speed = 100.f;
	else if (0 == (int)m_Bottom->GetSpeed())
		m_Speed = 0.f;
	else
		m_Speed = 250.f;

	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_LEFT))
	{
		m_Info.Pos_X -= m_Speed * TimeDelta;

		if (!m_fallCheck)
			m_Direction = DIR_LEFT;
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_PUSH, VK_RIGHT))
	{
		m_Info.Pos_X += m_Speed * TimeDelta;

		if (!m_fallCheck)
			m_Direction = DIR_RIGHT;
	}


	if (!m_fallCheck && GETMGR(KeyManager)->GetKeyState(STATE_DOWN, 'S'))
	{
		SetFall(true);
		m_GravitySpeed = -300.f;
	}

	if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, VK_F2))
	{
		PLAYERWEAPON w = ((PlayerTop*)m_Top)->GetPlayerWeapon();
		(PLAYER_PISTOL == w) ? w = PLAYER_HEAVY : w = PLAYER_PISTOL;
		((PlayerTop*)m_Top)->SetPlayerWeapon(w);
		((PlayerBottom*)m_Bottom)->SetPlayerWeapon(w);
	}

	return 0;
}
