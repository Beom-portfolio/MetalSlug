#include "pch.h"
#include "PlayerTopJumpRunState.h"
#include "PlayerTopRunState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopUnderState.h"
#include "PlayerTopStandAttState.h"
#include "PlayerTopRunJumpAttState.h"
#include "PlayerTopUpAttState.h"
#include "PlayerTopJumpBombAttState.h"
#include "PlayerTop.h"
#include "GameObject.h"
#include "Player.h"

PlayerTopJumpRunState::PlayerTopJumpRunState()
{
}

PlayerTopJumpRunState::~PlayerTopJumpRunState()
{
}

void PlayerTopJumpRunState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_jump_run_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_jump_run_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_jump_run_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_jump_run_heavy_l";
	}
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 4;
	info.Speed = 10.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopJumpRunState::HandleInput(GameObject* object, KeyManager* input)
{
	if (input->GetKeyState(STATE_PUSH, VK_UP))
		return new PlayerTopUpState();

	if (input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopUnderState();

	if (!object->GetFallCheck())
		return new PlayerTopRunState();

	// °ø°Ý
	if (input->GetKeyState(STATE_DOWN, 'A'))
		if (input->GetKeyState(STATE_PUSH, VK_UP))
			return new PlayerTopUpAttState();
		else
			return new PlayerTopRunJumpAttState();

	// ¼ö·ùÅº
	if ((0 < ((Player*)object->GetParent())->GetBombCount()) &&
		input->GetKeyState(STATE_DOWN, 'D'))
		return new PlayerTopJumpBombAttState();

	return nullptr;
}

void PlayerTopJumpRunState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex -= 1.f;

	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_jump_run_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_jump_run_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_jump_run_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_jump_run_heavy_l";
	}

	object->SetSpriteInfo(info);
}
