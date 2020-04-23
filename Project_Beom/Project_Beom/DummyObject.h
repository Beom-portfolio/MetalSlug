#pragma once
#include "GameObject.h"

class DummyObject
	: public GameObject
{
public:
	DummyObject();
	virtual ~DummyObject();
public:
	const MONSTERTYPE& GetType() { return m_type; }
	void SetType(MONSTERTYPE type) { m_type = type; }
public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();
private:
	MONSTERTYPE m_type = MONSTER_SOLDIER;
};



