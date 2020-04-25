#pragma once
#include "GameObject.h"

class Item
	: public GameObject
{
public:
	Item();
	virtual ~Item();

public:
	void SetItem(ITEMTYPE type);

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor);
	virtual void CollisionActivate(GameObject* collideTarget);

private:
	ITEMTYPE m_type = ITEM_BOMB;
	UINT m_mazentaColor = 0;
};



