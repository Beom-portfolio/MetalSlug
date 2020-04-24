#include "pch.h"
#include "PlayerTopStandState.h"
#include "PlayerTopRunState.h"
#include "PlayerTopJumpState.h"
#include "PlayerTopUpState.h"
#include "PlayerTopDownState.h"
#include "PlayerTopStandAttState.h"
#include "PlayerTopKnifeAttState.h"
#include "PlayerTopBombAttState.h"
#include "PlayerTop.h"
#include "GameObject.h"
#include "Player.h"

PlayerTopStandState::PlayerTopStandState()
{
}

PlayerTopStandState::~PlayerTopStandState()
{
}

void PlayerTopStandState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_stand_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_stand_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_stand_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_stand_heavy_l";
	}
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 3;
	info.Speed = 10.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PlayerTopStandState::HandleInput(GameObject* object, KeyManager* input)
{
	// 좌우 이동
	if (!object->GetFallCheck())
	{
		if (input->GetKeyState(STATE_PUSH, VK_LEFT))
			return new PlayerTopRunState();

		if (input->GetKeyState(STATE_PUSH, VK_RIGHT))
			return new PlayerTopRunState();
	}

	// 아래 보기
	if (!object->GetFallCheck() && input->GetKeyState(STATE_PUSH, VK_DOWN))
		return new PlayerTopDownState();

	// 위로 보기
	if (input->GetKeyState(STATE_PUSH, VK_UP))
		return new PlayerTopUpState();

	// 공격
	if (input->GetKeyState(STATE_DOWN, 'A'))
	{
		if(true == object->GetCollideCheck())
			return new PlayerTopKnifeAttState();
		else
			return new PlayerTopStandAttState(); 
	}

	// 점프
	if (input->GetKeyState(STATE_DOWN, 'S'))
		return new PlayerTopJumpState();

	// 수류탄
	if ((0 < ((Player*)object->GetParent())->GetBombCount()) &&
		input->GetKeyState(STATE_DOWN, 'D'))
		return new PlayerTopBombAttState();

	return nullptr;
}

void PlayerTopStandState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	// 숨쉬는 모션 왔다갔다
	if(m_SpriteReverseCheck)
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

	// 무기 바꿈
	PLAYERWEAPON weaponType = ((PlayerTop*)object)->GetPlayerWeapon();
	if (DIR_RIGHT == object->GetDirection())
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_stand_r";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_stand_heavy_r";
	}
	else
	{
		if (PLAYER_PISTOL == weaponType) info.key = L"top_stand_l";
		else if (PLAYER_HEAVY == weaponType) info.key = L"top_stand_heavy_l";
	}


	object->SetSpriteInfo(info);
}
