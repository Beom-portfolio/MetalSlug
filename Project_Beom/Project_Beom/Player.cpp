#include "pch.h"
#include "Player.h"
#include "KeyManager.h"
#include "CameraManager.h"
#include "PlayerBottom.h"
#include "PlayerTop.h"
#include "Camel.h"
#include "Bomb.h"
#include "Number.h"


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
	m_Bottom->SetParentObj(this);
	m_Top->SetParentObj(this);

	// 스폰 준비
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

	m_TimeUI = GETMGR(ObjectManager)->GetObjFromTag(L"TimeUI", OBJ_UI);
	m_Infinite = GETMGR(ObjectManager)->GetObjFromTag(L"BulletInfinite", OBJ_UI);
	m_BulletUI = GETMGR(ObjectManager)->GetObjFromTag(L"BulletUI", OBJ_UI);
	m_BombUI = GETMGR(ObjectManager)->GetObjFromTag(L"BombUI", OBJ_UI);
	return true;
}

int Player::Update(const float& TimeDelta)
{
	// ui update
	{
		m_DecreaseStack += TimeDelta;
		if (5.f <= m_DecreaseStack)
		{
			if (m_timeCount > 0)
				--m_timeCount;
			m_DecreaseStack = 0.f;
		}

		if (!m_isDead && 0 == m_timeCount)
		{
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
			if (m_rideCheck)
			{
				m_rideCheck = false;
				((Camel*)m_Slug)->SetRideCheck(false);
				m_Slug = nullptr;
				m_Bottom->Update(0.f);
				m_Top->Update(0.f);
			}
		}

		((Number*)m_TimeUI)->SetNumber(m_timeCount);

		if (m_bulletCount <= 0)
		{
			m_bulletCount = 0;
			((PlayerTop*)m_Top)->SetPlayerWeapon(PLAYER_PISTOL);
			((PlayerBottom*)m_Bottom)->SetPlayerWeapon(PLAYER_PISTOL);
			m_BulletUI->SetRenderCheck(false);
			m_Infinite->SetRenderCheck(true);
		}
		else
		{
			((PlayerTop*)m_Top)->SetPlayerWeapon(PLAYER_HEAVY);
			((PlayerBottom*)m_Bottom)->SetPlayerWeapon(PLAYER_HEAVY);
			m_BulletUI->SetRenderCheck(true);
			m_Infinite->SetRenderCheck(false);
		}

		((Number*)m_BulletUI)->SetNumber(m_bulletCount);
		((Number*)m_BombUI)->SetNumber(m_bombCount);
	}

	// 죽음 모션
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
					
					// 스폰 준비
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

	// 스폰 모션
	if (!m_fallCheck && m_spawnCheck)
	{
		m_renderCheck = true;
		m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
		if ((float)(m_SpriteInfo.MaxFrame) <= m_SpriteInfo.SpriteIndex)
		{
			m_timeCount = 59;
			m_bulletCount = 0;
			m_bombCount = 10;
			m_TimeStack = 0.f;
			m_spawnCheck = false;
		}
	}

	// 중력
	{
		if (m_fallCheck)
		{
			m_GravityTime += TimeDelta;
			m_GravitySpeed += GRAVITY_ACC * 1.5f * m_GravityTime;
			m_Info.Pos_Y += m_GravitySpeed * TimeDelta;
		}
	}

	// update part
	// 상 하체 업데이트
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
			// 낙타를 따라간다.
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
					m_TimeStack = 0.f;
				}
			}

			if (GETMGR(KeyManager)->GetKeyState(STATE_DOWN, 'D'))
			{
				if (0 < m_bombCount)
				{
					--m_bombCount;
					POSITION aPos = AnglePos(m_OriginCollidePos.X, m_OriginCollidePos.Y, 65.f, 60);

					GameObject* bullet = AbstractFactory<Bomb>::CreateObj();
					bullet->SetDirection(DIR_RIGHT);
					bullet->SetPosition(aPos.X, aPos.Y);
					bullet->SetGravitySpeed(-300);
					GETMGR(ObjectManager)->AddObject(bullet, OBJ_PLAYER_BULLET);
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

void Player::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
{
	if (PIXEL24{ 0, 0, 248 } == collPixelColor || PIXEL24{ 248, 0, 248 } == collPixelColor)
	{
		if ((dir & DIR_BOTTOM))
		{
			if (m_GravitySpeed < 0)
				return;

			SetFall(false);

			// 위로 올림
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
				if (!(pixelCollide->vecPixel[addr].r == collPixelColor.r &&
					pixelCollide->vecPixel[addr].g == collPixelColor.g &&
					pixelCollide->vecPixel[addr].b == collPixelColor.b))
				{
					break;
				}
				++count;
			}
			m_Info.Pos_Y -= count;
		}
		else
		{
			if (m_fallCheck || m_GravitySpeed < 0 || m_rideCheck)
				return;
			
			int x = (int)m_Info.Pos_X;
			int y = (int)m_CollideRect.bottom - (int)GETMGR(CameraManager)->GetPos().Y;

			const PIXELCOLLIDERINFO* pixelCollide = PixelTarget->GetPixelCollider();
			if (nullptr == pixelCollide)
				return;

			// 빨간 충돌 픽셀이 아니면 내리는 작업을 하지 않는다.
			for (int i = 0; i < 10; ++i)
			{
				int addr = (int)(y + i) * pixelCollide->Width + (int)x;
				if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
				if (pixelCollide->vecPixel[addr].r == 248 &&
					pixelCollide->vecPixel[addr].g == 0 &&
					pixelCollide->vecPixel[addr].b == 248)
				{
					return;
				}
			}

			// 빨간 충돌 픽셀이 안보이면 중력 적용
			bool isRed = false;
			for (int i = 0; i < 10; ++i)
			{
				int addr = (int)(y + i) * pixelCollide->Width + (int)x;
				if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
				if (pixelCollide->vecPixel[addr].r == 248 &&
					pixelCollide->vecPixel[addr].g == 0 &&
					pixelCollide->vecPixel[addr].b == 0)
				{
					isRed = true;
				}
			}

			if (!isRed)
			{
				SetFall(true);
				return;
			}

			// 빨간 충돌 픽셀이면 아래로 내림
			int count = 0;
			for (int i = 0; i < 1000; ++i)
			{
				int addr = (int)(y + i) * pixelCollide->Width + (int)x;
				if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
				if (pixelCollide->vecPixel[addr].r == 248 &&
					pixelCollide->vecPixel[addr].g == 0 &&
					pixelCollide->vecPixel[addr].b == 0)
				{
					break;
				}
				++count;
			}
			m_Info.Pos_Y += count;
		}
	}
}

void Player::CollisionActivate(GameObject* collideTarget)
{
	switch (collideTarget->GetObjectType())
	{
	case OBJ_SLUG:
		if (m_rideCheck || 1.f > m_TimeStack) break;
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
		if (!collideTarget->GetCollideCheck())
		{
			m_Top->SetCollideCheck(true);
			m_Bottom->SetCollideCheck(true);
		}
		break;
	case OBJ_MONSTER_BULLET:
		if (m_TimeStack <= 2.5f) break;
		//dead
		GETMGR(SoundManager)->PlaySound(L"Die.mp3", CH_PLAYER);
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
		if (m_rideCheck)
		{
			m_rideCheck = false;
			((Camel*)m_Slug)->SetRideCheck(false);
			m_Slug = nullptr;
			m_Bottom->Update(0.f);
			m_Top->Update(0.f);
		}
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
		m_bulletCount += 100;
		m_bombCount += 10;
	}

	return 0;
}
