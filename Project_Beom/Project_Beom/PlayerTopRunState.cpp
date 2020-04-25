#include "pch.h"
#include "PlayerTopRunState.h"
#include "PlayerTopStandState.h"
#include "PlayerTopJumpRunState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopDownMoveState.h"
#include "PlayerTopStandAttState.h"
#include "PlayerTopBombAttState.h"
#include "PlayerTopKnifeAttState.h"
#include "PlayerTop.h"
#include "GameObject.h"
#include "Player.h"

PlayerTopRunState::PlayerTopRunState()
{
}

PlayerTopRunState::~PlayerTopRunState()
{
}

void PlayerTopRunState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_run_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_run_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_run_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_run_heavy_l";
	}
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 12;
	info.Speed = 15.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopRunState::HandleInput(GameObject* object, KeyManager* input)
{
	int upCheck = 0;

	if (input->GetKeyState(STATE_PUSH, VK_UP))
		return new PlayerTopUpState();

	if (input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownMoveState();

	if (!input->GetKeyState(STATE_PUSH, VK_LEFT))
		upCheck |= DIR_LEFT;
	if (!input->GetKeyState(STATE_PUSH, VK_RIGHT))
		upCheck |= DIR_RIGHT;

	if ((upCheck & DIR_RIGHT) && (upCheck & DIR_LEFT))
		return new PlayerTopStandState();

	// °ø°Ý
	if (input->GetKeyState(STATE_DOWN, 'A'))
	{
		if (true == object->GetCollideCheck())
			return new PlayerTopKnifeAttState();
		else
			return new PlayerTopStandAttState();
	}

	if (input->GetKeyState(STATE_DOWN, 'S'))
		return new PlayerTopJumpRunState();

	// ¼ö·ùÅº
	if ((0 < ((Player*)object->GetParent())->GetBombCount()) &&
		input->GetKeyState(STATE_DOWN, 'D'))
		return new PlayerTopBombAttState();

	return nullptr;
}

void PlayerTopRunState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	// ¹«±â ¹Ù²Þ
	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_run_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_run_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_run_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_run_heavy_l";
	}

	object->SetSpriteInfo(info);
}
