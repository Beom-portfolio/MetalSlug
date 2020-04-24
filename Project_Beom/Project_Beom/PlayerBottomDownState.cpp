#include "pch.h"
#include "PlayerBottomDownState.h"
#include "PlayerBottomStandState.h"
#include "PlayerBottomDownMoveState.h"
#include "PlayerBottomJumpState.h"
#include "PlayerBottomDownAttState.h"
#include "PlayerBottomKnifeAttState.h"
#include "PlayerBottomBombAttState.h"
#include "PlayerBottom.h"
#include "GameObject.h"
#include "Player.h"

PlayerBottomDownState::PlayerBottomDownState()
{
}

PlayerBottomDownState::~PlayerBottomDownState()
{
}

void PlayerBottomDownState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	PLAYERWEAPON weaponType = ((PlayerBottom*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"bottom_down_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"bottom_down_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"bottom_down_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"bottom_down_heavy_l";
	}
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 4;
	if (PLAYER_PISTOL == weaponType) info.Speed = 14.f;
	else if (PLAYER_HEAVY == weaponType) info.Speed = 10.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerBottomDownState::HandleInput(GameObject* object, KeyManager* input)
{
	if (!input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerBottomStandState;

	if (!object->GetFallCheck())
	{
		if (input->GetKeyState(STATE_PUSH, VK_LEFT))
			return new PlayerBottomDownMoveState();

		if (input->GetKeyState(STATE_PUSH, VK_RIGHT))
			return new PlayerBottomDownMoveState();
	}

	if (input->GetKeyState(STATE_DOWN, 'A'))
	{
		if(true == object->GetCollideCheck())
			return new PlayerBottomKnifeAttState();
		else
			return new PlayerBottomDownAttState(); 
	}

	if (input->GetKeyState(STATE_DOWN, 'S'))
		return new PlayerBottomJumpState();

	if ((0 < ((Player*)object->GetParent())->GetBombCount())  && 
		input->GetKeyState(STATE_DOWN, 'D'))
		return new PlayerBottomBombAttState();

	return nullptr;
}

void PlayerBottomDownState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	// ¼û½¬´Â ¸ð¼Ç ¿Ô´Ù°¬´Ù
	if (m_SpriteReverseCheck)
		info.SpriteIndex -= info.Speed * TimeDelta;
	else
		info.SpriteIndex += info.Speed * TimeDelta;

	if (!m_SpriteReverseCheck && (float)info.MaxFrame <= info.SpriteIndex)
	{
		m_SpriteReverseCheck = true;
		info.SpriteIndex = (float)(info.MaxFrame - 1);
	}

	if (m_SpriteReverseCheck && 0.f >= info.SpriteIndex)
	{
		m_SpriteReverseCheck = false;
		info.SpriteIndex = 0.f;
	}

	PLAYERWEAPON weaponType = ((PlayerBottom*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"bottom_down_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"bottom_down_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"bottom_down_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"bottom_down_heavy_l";
	}

	if (PLAYER_PISTOL == weaponType) info.Speed = 14.f;
	else if (PLAYER_HEAVY == weaponType) info.Speed = 10.f;

	object->SetSpriteInfo(info);
}
