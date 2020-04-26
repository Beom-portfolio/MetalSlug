#include "pch.h"
#include "Bomb.h"
#include "GranadeExplosion.h"

Bomb::Bomb()
{
}

Bomb::~Bomb()
{
}

bool Bomb::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 40, 40 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 30, 30 };
	m_ObjType = OBJ_PLAYER_BULLET;
	m_RenderType = RENDER_OBJ;
	m_SpriteInfo.key = L"bomb_bullet";
	m_SpriteInfo.MaxFrame = 32;
	m_SpriteInfo.SpriteIndex = 0.f;
	m_SpriteInfo.Speed = 50.f;

	m_Speed = 330.f;
	m_Damage = 5;
	return true;
}

int Bomb::Update(const float& TimeDelta)
{
	if (DIR_RIGHT == m_Direction)
		m_Info.Pos_X += m_Speed * TimeDelta;
	if (DIR_LEFT == m_Direction)
		m_Info.Pos_X -= m_Speed * TimeDelta;

	{
		if (m_fallCheck)
		{
			m_GravityTime += TimeDelta;
			m_GravitySpeed += (GRAVITY_ACC * m_AdditionalGravity) * m_GravityTime;
			m_Info.Pos_Y += m_GravitySpeed * TimeDelta;
		}
	}

	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;

	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_SpriteInfo.SpriteIndex = 0.f;

	if (m_cullingCheck)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Bomb::Render(HDC hdc)
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

void Bomb::Release()
{
}

void Bomb::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
{
	if (0 == dir)
		return;

	if (PIXEL24{ 0, 0, 248 } == collPixelColor || PIXEL24{ 248, 0, 248 } == collPixelColor)
	{
		if (m_GravitySpeed > 0.f)
		{
			if (!m_isCollide)
			{
				if (dir & DIR_LEFT || dir & DIR_RIGHT)
					m_Speed = 0.f;

				if (dir & DIR_BOTTOM)
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
							pixelCollide->vecPixel[addr].g ==   collPixelColor.g &&
							pixelCollide->vecPixel[addr].b ==   collPixelColor.b))
						{
							break;
						}
						++count;
					}
					m_Info.Pos_Y -= count;
					m_isCollide = true;

					SetFall(true);

					if (dir & DIR_LEFT || dir & DIR_RIGHT)
						m_Speed = 0.f;

					m_GravitySpeed = -350;
					m_AdditionalGravity = 6.f;
				}
			}
			else
			{
				if (dir & DIR_BOTTOM)
				{
					if (!m_isDead)
					{
						GameObject* effect = AbstractFactory<GranadeExplosion>::CreateObj();
						effect->SetPosition(m_Info.Pos_X, m_Info.Pos_Y - 80.f);
						GETMGR(ObjectManager)->AddObject(effect, OBJ_PLAYER_BULLET);
						m_isDead = true;
					}
				}
			}
		}
		else
		{
			if (PIXEL24{ 0, 0, 248 } == collPixelColor && m_isCollide)
				if (dir & DIR_LEFT || dir & DIR_RIGHT)
					m_Speed = 0.f;

			/*if (dir & DIR_TOP)
			{
				GameObject* effect = AbstractFactory<GranadeExplosion>::CreateObj();
				effect->SetPosition(m_Info.Pos_X, m_Info.Pos_Y - 80.f);
				GETMGR(ObjectManager)->AddObject(effect, OBJ_PLAYER_BULLET);
				m_isDead = true;
			}*/
		}
	}
}

void Bomb::CollisionActivate(GameObject* collideTarget)
{
	if (!collideTarget->GetCollideCheck())
	{
		collideTarget->Hit(m_Damage);
		GameObject* effect = AbstractFactory<GranadeExplosion>::CreateObj();
		effect->SetPosition(m_Info.Pos_X, m_Info.Pos_Y - 80.f);
		GETMGR(ObjectManager)->AddObject(effect, OBJ_PLAYER_BULLET);
		m_isDead = true;
	}
}
