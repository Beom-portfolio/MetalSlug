#include "pch.h"
#include "PlayerTopUnderState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopUnderAttState.h"
#include "PlayerTopJumpBombAttState.h"
#include "PlayerTop.h"
#include "GameObject.h"
#include "Player.h"

PlayerTopUnderState::PlayerTopUnderState()
{
}

PlayerTopUnderState::~PlayerTopUnderState()
{
}

void PlayerTopUnderState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_under_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_under_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_under_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_under_heavy_l";
	}
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 1;
	info.Speed = 1.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopUnderState::HandleInput(GameObject* object, KeyManager* input)
{
	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopJumpState();

	if (!object->GetFallCheck())
		return new PlayerTopStandState();

	if(input->GetKeyState(STATE_DOWN, 'A'))
		return new PlayerTopUnderAttState();

	// ¼ö·ùÅº
	if ((0 < ((Player*)object->GetParent())->GetBombCount()) &&
		input->GetKeyState(STATE_DOWN, 'D'))
		return new PlayerTopJumpBombAttState();

	return nullptr;
}

void PlayerTopUnderState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_under_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_under_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_under_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_under_heavy_l";
	}

	object->SetSpriteInfo(info);
}
