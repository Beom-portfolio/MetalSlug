#include "pch.h"
#include "LeftWing.h"
#include "Boost.h"
#include "Fire.h"
#include "Pro.h"
#include "Smog.h"

LeftWing::LeftWing()
{
}

LeftWing::~LeftWing()
{
}

void LeftWing::SetState(DWORD state)
{
	m_Pro->SetState(state);
	m_Fire->SetState(state);
	m_Smog->SetState(state);
}

bool LeftWing::Initialize()
{
	m_CollideInfo = GAMEOBJINFO{ 0, 0, 150, 150 };
	m_Boost = AbstractFactory<Boost>::CreateObj();
	m_Boost->SetDirection(DIR_LEFT);
	m_Fire = AbstractFactory<Fire>::CreateObj();
	m_Fire->SetDirection(DIR_LEFT);
	m_Pro = AbstractFactory<Pro>::CreateObj();
	m_Pro->SetDirection(DIR_LEFT);
	m_Smog = AbstractFactory<Smog>::CreateObj();

	SetState(BOSS_IDLE);

	return true;
}

int LeftWing::Update(const float& TimeDelta)
{
	m_Boost->SetPosition(m_Info.Pos_X, m_Info.Pos_Y - 10.f);
	m_Fire->SetPosition(m_Info.Pos_X - 5.f, m_Info.Pos_Y + 10.f);
	m_Pro->SetPosition(m_Info.Pos_X - 20.f, m_Info.Pos_Y - 80.f);
	m_Smog->SetPosition(m_Info.Pos_X - 5.f, 100.f);
	m_Boost->Update(TimeDelta);
	m_Fire->Update(TimeDelta);
	m_Pro->Update(TimeDelta);
	m_Smog->Update(TimeDelta);
	GameObject::Update(TimeDelta);

	return 0;
}

void LeftWing::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);

	m_Boost->Render(hdc);
	m_Fire->Render(hdc);
	m_Smog->Render(hdc);
}

void LeftWing::Release()
{
	SAFE_RELEASE(m_Boost);
	SAFE_RELEASE(m_Fire);
	SAFE_RELEASE(m_Pro);
	SAFE_RELEASE(m_Smog);
}

void LeftWing::RenderAfter(HDC hdc)
{
	m_Pro->Render(hdc);
}
