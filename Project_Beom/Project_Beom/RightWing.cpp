#include "pch.h"
#include "RightWing.h"
#include "Boost.h"
#include "Fire.h"
#include "Pro.h"
#include "Smog.h"

RightWing::RightWing()
{
}

RightWing::~RightWing()
{
}

void RightWing::SetState(DWORD state)
{
	m_Pro->SetState(state);
	m_Fire->SetState(state);
	m_Smog->SetState(state);
}

bool RightWing::Initialize()
{
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 150, 150 };
	m_Boost = AbstractFactory<Boost>::CreateObj();
	m_Boost->SetDirection(DIR_RIGHT);
	m_Fire = AbstractFactory<Fire>::CreateObj();
	m_Fire->SetDirection(DIR_RIGHT);
	m_Pro = AbstractFactory<Pro>::CreateObj();
	m_Pro->SetDirection(DIR_RIGHT);
	m_Smog = AbstractFactory<Smog>::CreateObj();

	SetState(BOSS_IDLE);

	return true;
}

int RightWing::Update(const float& TimeDelta)
{
	m_Boost->SetPosition(m_Info.Pos_X, m_Info.Pos_Y);
	m_Fire->SetPosition(m_Info.Pos_X + 5.f, m_Info.Pos_Y + 20.f);
	m_Pro->SetPosition(m_Info.Pos_X + 20.f, m_Info.Pos_Y - 80.f);
	m_Smog->SetPosition(m_Info.Pos_X, 100.f);
	m_Boost->Update(TimeDelta);
	m_Fire->Update(TimeDelta);
	m_Pro->Update(TimeDelta);
	m_Smog->Update(TimeDelta);
	GameObject::Update(TimeDelta);

	return 0;
}

void RightWing::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	m_Boost->Render(hdc);
	m_Fire->Render(hdc);
	m_Smog->Render(hdc);
}

void RightWing::Release()
{
	SAFE_RELEASE(m_Boost);
	SAFE_RELEASE(m_Fire);
	SAFE_RELEASE(m_Pro);
	SAFE_RELEASE(m_Smog);
}

void RightWing::RenderAfter(HDC hdc)
{
	m_Pro->Render(hdc);
}
