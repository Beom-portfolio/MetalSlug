#include "pch.h"
#include "PlayerTopUpState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopDownState.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopUpAttState.h"
#include "PlayerTopKnifeAttState.h"
#include "PlayerTopBombAttState.h"
#include "PlayerTop.h"
#include "GameObject.h"
#include "Player.h"

PlayerTopUpState::PlayerTopUpState()
{
}

PlayerTopUpState::~PlayerTopUpState()
{
}

void PlayerTopUpState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_up_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_up_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_up_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_up_heavy_l";
	}
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 4;
	info.Speed = 7.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopUpState::HandleInput(GameObject* object, KeyManager* input)
{
	if (!object->GetFallCheck() && 
		input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownState();

	if (!input->GetKeyState(STATE_PUSH, VK_UP))	
		return new PlayerTopJumpState();

	// 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
	{
		if (true == object->GetCollideCheck())
			return new PlayerTopKnifeAttState();
		else
			return new PlayerTopUpAttState();
	}

	// 수류탄
	if ((0 < ((Player*)object->GetParent())->GetBombCount()) &&
		input->GetKeyState(STATE_DOWN, 'D'))
		return new PlayerTopBombAttState();

	return nullptr;
}

void PlayerTopUpState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	if (!object->GetFallCheck())
	{
		PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
		if (DIR_RIGHT == object->GetDirection())
		{
			if (PLAYER_PISTOL == weaponType) info.key = L"top_up_r";
			else if (PLAYER_HEAVY == weaponType) info.key = L"top_up_heavy_r";
		}
		else
		{
			if (PLAYER_PISTOL == weaponType) info.key = L"top_up_l";
			else if (PLAYER_HEAVY == weaponType) info.key = L"top_up_heavy_l";
		}
	}

	object->SetSpriteInfo(info);
}
