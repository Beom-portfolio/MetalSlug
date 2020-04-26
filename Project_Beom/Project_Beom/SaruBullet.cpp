#include "pch.h"
#include "SaruBullet.h"
#include "SaruExplosion.h"

SaruBullet::SaruBullet()
	: GameObject()
{
}

SaruBullet::~SaruBullet()
{
}

bool SaruBullet::Initialize()
{
	GETMGR(SoundManager)->PlaySound(L"SaruAtt.wav", CH_MONSTER);
	m_Info = GAMEOBJINFO{ 0, 0, 60, 60 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 40, 40 };
	m_ObjType = OBJ_MONSTER_BULLET;
	m_RenderType = RENDER_OBJ;
	m_SpriteInfo.key = L"saru_bullet";
	m_SpriteInfo.MaxFrame = 18;
	if (DIR_RIGHT == m_Direction)
		m_SpriteInfo.SpriteIndex = 0.f;
	else
		m_SpriteInfo.SpriteIndex = m_SpriteInfo.MaxFrame - 1.f;
	m_SpriteInfo.Speed = 20.f;
	
	m_Speed = 150.f;

	return true;
}

int SaruBullet::Update(const float& TimeDelta)
{
	{
		if (m_fallCheck)
		{
			m_GravityTime += TimeDelta;
			m_GravitySpeed += GRAVITY_ACC * m_GravityTime;
			m_Info.Pos_Y += m_GravitySpeed * TimeDelta;
		}
		else
		{
			if (DIR_RIGHT == m_Direction)
			{
				m_SpriteInfo.SpriteIndex -= m_SpriteInfo.Speed * TimeDelta;
				m_Info.Pos_X += m_Speed * TimeDelta;
			}
			if (DIR_LEFT == m_Direction)
			{
				m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
				m_Info.Pos_X -= m_Speed * TimeDelta;
			}
		}
	}

	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
		m_SpriteInfo.SpriteIndex = 0.f;
	else if (0.f >= m_SpriteInfo.SpriteIndex)
		m_SpriteInfo.SpriteIndex = (float)m_SpriteInfo.MaxFrame - 1.f;


	if (m_cullingCheck)
		m_isDead = true;

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void SaruBullet::Render(HDC hdc)
{
	HDC hMemDC;
	hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC, (int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(0, 248, 0));
}

void SaruBullet::Release()
{
}

void SaruBullet::CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor)
{
	if (PIXEL24{ 0, 0, 248 } == collPixelColor)
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
			if (m_fallCheck || m_GravitySpeed < 0)
				return;

			int x = (int)m_Info.Pos_X;
			int y = (int)m_CollideRect.bottom - (int)GETMGR(CameraManager)->GetPos().Y;

			const PIXELCOLLIDERINFO* pixelCollide = PixelTarget->GetPixelCollider();
			if (nullptr == pixelCollide)
				return;

			// 빨간 충돌 픽셀이면 아래로 내림
			int count = 0;
			for (int i = 0; i < 1000; ++i)
			{
				int addr = (int)(y + i) * pixelCollide->Width + (int)x;
				if (addr < 0 || addr >= (int)pixelCollide->vecPixel.size()) return;
				if (pixelCollide->vecPixel[addr].r == collPixelColor.r &&
					pixelCollide->vecPixel[addr].g == collPixelColor.g &&
					pixelCollide->vecPixel[addr].b == collPixelColor.b)
				{
					break;
				}
				++count;
			}
			m_Info.Pos_Y += count;
		}
	}
}

void SaruBullet::CollisionActivate(GameObject* collideTarget)
{

	GameObject* effect = AbstractFactory<SaruExplosion>::CreateObj();
	effect->SetPosition(m_Info.Pos_X, m_Info.Pos_Y - 160.f);
	GETMGR(ObjectManager)->AddObject(effect, OBJ_EFFECT);
	m_isDead = true;
}
