#pragma once
#include "GameObject.h"

class State;
class Player 
	: public GameObject
{
public:
	Player();
	virtual ~Player();

public:
	void AddBomb(int count) { m_bombCount += count; }
	void AddBullet(int count) { m_bulletCount += count; }
	void MinusBullet(int count) { m_bulletCount -= count; }
	void MinusBomb(int count) { m_bombCount -= count; }

public:
	int GetBombCount() { return m_bombCount; }
	int GetBulletCount() { return m_bulletCount; }

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

public:
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget, PIXEL24 collPixelColor);

public:
	virtual void CollisionActivate(GameObject* collideTarget);
	virtual void CollisionDeactivate(GameObject* collideTarget);

private:
	int UpdateInput(const float& TimeDelta);

private:
	GameObject* m_Bottom = nullptr;
	GameObject* m_Top = nullptr;
	GameObject* m_Slug = nullptr;
	bool m_rideCheck = false;
	bool m_spawnCheck = false;

	int m_bulletCount = 0;
	int m_bombCount = 10;

	int m_timeCount = 59;
	float m_DecreaseStack = 0.f;
	GameObject* m_TimeUI = nullptr;
	GameObject* m_Infinite = nullptr;
	GameObject* m_BulletUI = nullptr;
	GameObject* m_BombUI = nullptr;
};

