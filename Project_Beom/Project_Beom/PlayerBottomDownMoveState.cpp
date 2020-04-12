#include "pch.h"
#include "PlayerBottomDownMoveState.h"
#include "PlayerBottomDownState.h"
#include "PlayerBottomStandState.h"
#include "PlayerBottomJumpState.h"
#include "PlayerBottomDownAttState.h"
#include "PlayerBottom.h"
#include "GameObject.h"

PlayerBottomDownMoveState::PlayerBottomDownMoveState()
{
}

PlayerBottomDownMoveState::~PlayerBottomDownMoveState()
{
}

void PlayerBottomDownMoveState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	PLAYERWEAPON weaponType = ((PlayerBottom*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"bottom_down_move_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"bottom_down_move_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"bottom_down_move_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"bottom_down_move_heavy_l";
	}
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 7;
	info.Speed = 13.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerBottomDownMoveState::HandleInput(GameObject* object, KeyManager* input)
{
	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerBottomStandState();

	int upCheck = 0;

	if (!input->GetKeyState(STATE_PUSH, VK_LEFT))
		upCheck |= DIR_LEFT;
	if (!input->GetKeyState(STATE_PUSH, VK_RIGHT))
		upCheck |= DIR_RIGHT;

	if ((upCheck & DIR_RIGHT) && (upCheck & DIR_LEFT))
		return new PlayerBottomDownState();

	if (input->GetKeyState(STATE_DOWN, 'A'))
		return new PlayerBottomDownAttState();

	if (input->GetKeyState(STATE_DOWN, 'S'))
		return new PlayerBottomJumpState();

	return nullptr;
}

void PlayerBottomDownMoveState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	PLAYERWEAPON weaponType = ((PlayerBottom*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"bottom_down_move_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"bottom_down_move_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"bottom_down_move_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"bottom_down_move_heavy_l";
	}

	object->SetSpriteInfo(info);
}
