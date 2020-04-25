#include "pch.h"
#include "SelectScreen.h"

SelectScreen::SelectScreen()
{
}

SelectScreen::~SelectScreen()
{
}

bool SelectScreen::Initialize()
{
	return true;
}

int SelectScreen::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void SelectScreen::Render(HDC hdc)
{
	HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(L"slect_screen")->GetGdiImageDefault();
	TransparentBlt(hdc, 0, -30, 800, 600, hMemDC, 0, 0, 800, 600, RGB(0, 255, 0));
}

void SelectScreen::Release()
{
}
