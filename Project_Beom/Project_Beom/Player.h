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
	virtual void CollisionPixelPart(DIRECTION dir, GameObject* PixelTarget);

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

	int m_bulletCount = 10;
	int m_bombCount = 10;
};

