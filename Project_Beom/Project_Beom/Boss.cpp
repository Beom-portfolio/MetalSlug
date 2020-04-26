#include "pch.h"
#include "Boss.h"
#include "RightWing.h"
#include "LeftWing.h"
#include "BossIdleState.h"
#include "BossDieState.h"
#include "MediumExplosion.h"
#include "Soldier.h"

Boss::Boss()
{
}

Boss::~Boss()
{
}

void Boss::GetWings(GameObject** right, GameObject** left)
{
	*right = m_RightWing;
	*left = m_LeftWing;
}

bool Boss::Initialize()
{
	m_Info = GAMEOBJINFO{ 600, 160, 900, 450 };
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 700, 260 };

	m_Speed = 50.f;
	m_ObjType = OBJ_MONSTER;
	m_RenderType = RENDER_OBJ;

	m_SpriteInfo.key = L"boss_body_idle";
	m_SpriteInfo.Speed = 0.f;
	m_SpriteInfo.SpriteIndex = 0.f;

	m_RightWing = AbstractFactory<RightWing>::CreateObj();
	m_LeftWing = AbstractFactory<LeftWing>::CreateObj();

	m_State = new BossIdleState();
	m_State->Enter(this);

	// 내려오는 동작을 위함
	m_OriginPosY = m_Info.Pos_Y;
	m_Info.Pos_Y = -50.f;

	m_Hp = 1500;
	m_TotalHp = m_Hp;

	m_isCollideOn = false;

	return true;
}

int Boss::Update(const float& TimeDelta)
{
	// 내려오는 동작을 위함
	if (m_firstCheck)
	{
		m_Info.Pos_Y += m_Speed * TimeDelta;

		if (m_Info.Pos_Y > m_OriginPosY)
		{
			m_isCollideOn = true;
			m_firstCheck = false;
		}
	}
	else
	{
		m_State->Update(this, TimeDelta);
		m_TimeSpawn += TimeDelta;
		AI();
	}

	if ((float)m_Hp / m_TotalHp <= 0.5f)
	{
		if (m_TimeStack > 0.25f)
		{
			GameObject* effect = nullptr;
			effect = AbstractFactory<MediumExplosion>::CreateObj(true);
			effect->SetPosition(m_Info.Pos_X - float(rand() % 300) + float(rand() % 300),
				m_Info.Pos_Y - float(rand() % 200) + float(rand() % 200));
			GETMGR(ObjectManager)->AddObject(effect, OBJ_EFFECT);
			m_TimeStack = 0.f;
		}
	}


	m_RightWing->SetPosition(m_Info.Pos_X + 278.f, m_Info.Pos_Y + 90.f);
	m_RightWing->Update(TimeDelta);
	m_LeftWing->SetPosition(m_Info.Pos_X - 262.f, m_Info.Pos_Y + 90.f);
	m_LeftWing->Update(TimeDelta);

	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Boss::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	if (m_isRenderPart)
	{
		m_SpriteInfo.key = L"boss_body_idle";
		m_RightWing->Render(hdc);
		m_LeftWing->Render(hdc);
	}

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		0 * m_Info.Size_X,
		0 * m_Info.Size_Y,
		m_Info.Size_X, m_Info.Size_Y, RGB(0, 248, 0));

	if (m_isRenderPart)
	{
		m_RightWing->RenderAfter(hdc);
		m_LeftWing->RenderAfter(hdc);
	}
}

void Boss::Release()
{
	SAFE_RELEASE(m_LeftWing);
	SAFE_RELEASE(m_RightWing);
}

void Boss::CollisionActivate(GameObject* collideTarget)
{
	if (OBJ_PLAYER_BULLET == collideTarget->GetObjectType())
	{
		if (m_isCollideOn)
		{
			Hit(collideTarget->GetDamage());
			if (0 >= m_Hp)
			{
				for (auto& monster : GETMGR(ObjectManager)->GetObjFromType(OBJ_MONSTER))
				{
					if (this == monster.second)
						continue;
					monster.second->SetDead(true);
				}

				m_SpriteInfo.key = L"boss_body_destroy";
				SAFE_DELETE(m_State);
				m_State = new BossDieState;
				m_State->Enter(this);
				m_isCollideOn = false;
				m_isRenderPart = false;
				return;
			}
			m_SpriteInfo.key = L"boss_body_hit";
		}
	}
}

void Boss::AI()
{
	State* state = m_State->HandleInput(this, nullptr);
	if (nullptr != state)
	{
		SAFE_DELETE(m_State);
		m_State = state;

		m_State->Enter(this);
	}

	if(0 < m_Hp)
	{
		if (2.f <= m_TimeSpawn)
		{
			int posX = rand() % 2 ? (int)m_Info.Pos_X - 70 : (int)m_Info.Pos_X + 70;
			GameObject* mon = AbstractFactory<Soldier>::CreateObj(true);
			mon->SetPosition((float)posX, m_Info.Pos_Y - 200.f);
			GETMGR(ObjectManager)->AddObject(mon, OBJ_MONSTER);
			m_TimeSpawn = 0.f;
		}
	}
}
