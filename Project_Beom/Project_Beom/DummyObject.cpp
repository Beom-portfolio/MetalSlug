#include "pch.h"
#include "DummyObject.h"

DummyObject::DummyObject()
{
}

DummyObject::~DummyObject()
{
}

bool DummyObject::Initialize()
{
	m_Info = { 100, 100, 200, 200 };

	m_SpriteInfo.key = L"dummy_monsters";
	m_SpriteInfo.MaxFrame = 4;
	m_SpriteInfo.SpriteIndex = (float)m_type;

	m_isNoScroll = true;
	return true;
}

int DummyObject::Update(const float& TimeDelta)
{
	m_SpriteInfo.SpriteIndex = (float)m_type;
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void DummyObject::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

	TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
		hMemDC,
		(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X, 
		0, 
		m_Info.Size_X, m_Info.Size_Y, RGB(248, 248, 248));
}

void DummyObject::Release()
{
}
