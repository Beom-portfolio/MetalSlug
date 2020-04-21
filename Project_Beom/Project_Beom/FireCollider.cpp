#include "pch.h"
#include "FireCollider.h"

FireCollider::FireCollider()
{
}

FireCollider::~FireCollider()
{
}

bool FireCollider::Initialize()
{
	m_CollideInfo = { 0, 0, 90, 600 };

	return true;
}

int FireCollider::Update(const float& TimeDelta)
{
	GameObject::Update(TimeDelta);

	return 0;
}

void FireCollider::Render(HDC hdc)
{
	if (true == GET_MANAGER<CollisionManager>()->GetRenderCheck())
		Rectangle(hdc, m_CollideRect.left, m_CollideRect.top, m_CollideRect.right, m_CollideRect.bottom);
}

void FireCollider::Release()
{
}

void FireCollider::CollisionActivate(GameObject* collideTarget)
{
}
