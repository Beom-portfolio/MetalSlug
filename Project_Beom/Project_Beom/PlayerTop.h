#pragma once
#include "GameObject.h"

class State;
class PlayerTop
	: public GameObject
{
public:
	PlayerTop();
	virtual ~PlayerTop();

public:
	const PLAYERWEAPON& GetPlayerWeapon() { return m_playerWeapon; }
	void SetPlayerWeapon(PLAYERWEAPON weapon) { m_playerWeapon = weapon; }

public:
	virtual bool Initialize();
	virtual int  Update(const float& TimeDelta);
	virtual void Render(HDC hdc);
	virtual void Release();

private:
	void HandleInput();

private:
	State* m_State = nullptr;
	PLAYERWEAPON m_playerWeapon = PLAYER_HEAVY;
};

