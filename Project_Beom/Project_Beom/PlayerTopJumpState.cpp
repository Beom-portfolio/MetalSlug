#include "pch.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopUnderState.h"
#include "PlayerTopStandAttState.h"
#include "PlayerTopJumpAttState.h"
#include "PlayerTopUpAttState.h"
#include "PlayerTopJumpBombAttState.h"
#include "PlayerTop.h"
#include "GameObject.h"
#include "Player.h"

PlayerTopJumpState::PlayerTopJumpState()
{
}

PlayerTopJumpState::~PlayerTopJumpState()
{
}

void PlayerTopJumpState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_jump_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_jump_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_jump_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_jump_heavy_l";
	}
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 6;
	info.Speed = 15.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopJumpState::HandleInput(GameObject* object, KeyManager* input)
{
	if (input->GetKeyState(STATE_PUSH, VK_UP))
			return new PlayerTopUpState();

	if (input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopUnderState();

	if (!object->GetFallCheck())
		return new PlayerTopStandState();

	// 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
			return new PlayerTopJumpAttState();

	// 수류탄
	if ((0 < ((Player*)object->GetParent())->GetBombCount()) &&
		input->GetKeyState(STATE_DOWN, 'D'))
		return new PlayerTopJumpBombAttState();


	return nullptr;
}

void PlayerTopJumpState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex -= 1.f;

	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_jump_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_jump_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_jump_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_jump_heavy_l";
	}

	object->SetSpriteInfo(info);
}
