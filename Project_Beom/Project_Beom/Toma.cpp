#include "pch.h"
#include "Toma.h"
#include "TomaIdleState.h"
#include "BigExplosion.h"

Toma::Toma()
{
}

Toma::~Toma()
{
}

bool Toma::Initialize()
{
	m_Info = GAMEOBJINFO{ 0, 0, 300, 300 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 150, 100 };
	m_ObjType = OBJ_MONSTER;
	m_RenderType = RENDER_OBJ;

	m_State = new TomaIdleState;
	m_State->Enter(this);
	m_Speed = 105.f;

	m_Hp = 45;
	return true;
}

int Toma::Update(const float& TimeDelta)
{
	m_State->Update(this, TimeDelta);
	AI();

	m_SpriteInfo.SpriteIndex += m_SpriteInfo.Speed * TimeDelta;
	
	if ((float)m_SpriteInfo.MaxFrame <= m_SpriteInfo.SpriteIndex)
	{
		m_SpriteInfo.SpriteIndex = 0.f;
	}

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Toma::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
		m_SpriteInfo.StateIndex * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(0, 248, 0));
}

void Toma::Release()
{
}

void Toma::CollisionActivate(GameObject* collideTarget)
{
	if (!m_isCollide && OBJ_PLAYER_BULLET == collideTarget->GetObjectType())
	{
		if (0 >= m_Hp)
		{
			GameObject* effect = AbstractFactory<BigExplosion>::CreateObj();
			effect->SetPosition(m_Info.Pos_X, m_Info.Pos_Y);
			GETMGR(ObjectManager)->AddObject(effect, OBJ_EFFECT);
			m_isDead = true;
		}
	}
}

void Toma::AI()
{
	State* state = m_State->HandleInput(this, nullptr);
	if (nullptr != state)
	{
		SAFE_DELETE(m_State);
		m_State = state;

		m_State->Enter(this);
	}
}
