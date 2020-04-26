#include "pch.h"
#include "Number.h"

Number::Number()
{
}

Number::~Number()
{
}

void Number::SetNumberStyle(NUMBERSTYLE style)
{
	switch (style)
	{
	case NUMSTYLE_BIG:
		SetSize(300, 300);
		m_SpriteInfo.key = L"big_numbers";
		m_mazenta = RGB(255, 255, 255);
		break;
	case NUMSTYLE_SMALL:
		SetSize(22, 16);
		m_SpriteInfo.key = L"small_numbers";
		m_mazenta = RGB(255, 0, 255);
		break;
	case NUMSTYLE_NOTNUMBER:
		m_mazenta = RGB(255, 255, 255);
		break;
	}

	m_style = style;
}

bool Number::Initialize()
{
	m_isNoScroll = true;
	m_isNotDead = true;
	m_RenderType = RENDER_UI;
	return true;
}

int Number::Update(const float& TimeDelta)
{
	if (-1 == GameObject::Update(TimeDelta))
		return -1;

	return 0;
}

void Number::Render(HDC hdc)
{
	if (NUMSTYLE_NOTNUMBER == m_style)
	{
		HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

		TransparentBlt(hdc, m_Rect.left, m_Rect.top, m_Info.Size_X, m_Info.Size_Y,
			hMemDC,
			(int)m_SpriteInfo.SpriteIndex * m_Info.Size_X,
			0 * m_Info.Size_Y,
			m_Info.Size_X, m_Info.Size_Y, m_mazenta);
	}
	else
	{
		vector<int> numbers;
		int count = 0;
		while (0 != m_numberValue / (int)pow(10, count))
		{
			++count;
		}
		int tmpNumber = m_numberValue;
		for (int i = count - 1; i >= 0; --i)
		{
			int resultNum = tmpNumber / (int)pow(10, i);
			numbers.push_back(resultNum);
			tmpNumber -= resultNum * (int)pow(10, i);
		}
		if(0 == count)
			numbers.push_back(0);

		int Count = 0;
		int Size = 0;
		m_style == NUMSTYLE_BIG ? Size = 50 : Size = 16;
		for (auto rIter = numbers.rbegin(); rIter != numbers.rend(); ++rIter)
		{
			HDC hMemDC = GET_MANAGER<GdiManager>()->FindImage(m_SpriteInfo.key)->GetGdiImageDefault();

			TransparentBlt(hdc, m_Rect.left - Size * Count, m_Rect.top, 
				m_Info.Size_X, m_Info.Size_Y,
				hMemDC,
				(*rIter) * m_Info.Size_X,
				0 * m_Info.Size_Y,
				m_Info.Size_X, m_Info.Size_Y, m_mazenta);

			++Count;
		}
		Count = 0;
	}
}

void Number::Release()
{
}
