#include "pch.h"
#include "PlayerBottomDownMoveState.h"
#include "PlayerBottomDownState.h"
#include "PlayerBottomStandState.h"
#include "PlayerBottomJumpState.h"
#include "PlayerBottomDownAttState.h"
#include "PlayerBottomKnifeAttState.h"
#include "PlayerBottomStandState.h"
#include "PlayerBottomBombAttState.h"
#include "PlayerBottom.h"
#include "GameObject.h"
#include "Player.h"

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
	object->SetSpeed(-1.f);
}

State* PlayerBottomDownMoveState::HandleInput(GameObject* object, KeyManager* input)
{
	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
	{
		object->SetSpeed(1.f);
		return new PlayerBottomStandState();
	}

	int upCheck = 0;

	if (!input->GetKeyState(STATE_PUSH, VK_LEFT))
		upCheck |= DIR_LEFT;
	if (!input->GetKeyState(STATE_PUSH, VK_RIGHT))
		upCheck |= DIR_RIGHT;

	if ((upCheck & DIR_RIGHT) && (upCheck & DIR_LEFT))
	{
		object->SetSpeed(1.f);
		return new PlayerBottomDownState();
	}

	if (input->GetKeyState(STATE_DOWN, 'A'))
	{
		if (true == object->GetCollideCheck())
			return new PlayerBottomKnifeAttState();
		else
			return new PlayerBottomDownAttState();
	}

	if (input->GetKeyState(STATE_DOWN, 'S'))
	{
		object->SetSpeed(1.f);
		return new PlayerBottomJumpState();
	}

	// АјАн
	if ((0 < ((Player*)object->GetParent())->GetBombCount()) &&
		input->GetKeyState(STATE_DOWN, 'D'))
	{
		object->SetSpeed(1.f);
		return new PlayerBottomBombAttState();
	}

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
