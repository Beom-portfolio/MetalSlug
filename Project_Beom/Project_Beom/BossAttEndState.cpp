#include "pch.h"
#include "BossAttEndState.h"
#include "BossIdleState.h"
#include "GameObject.h"
#include "Boss.h"

BossAttEndState::BossAttEndState()
{
}

BossAttEndState::~BossAttEndState()
{
}

void BossAttEndState::Enter(GameObject* object)
{
	GETMGR(SoundManager)->PlaySound(L"BossAttEnd.mp3", CH_MONSTER);
	SPRITEINFO info = object->GetSpriteInfo();
	info.MaxFrame = 16;
	info.Speed = 11.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);

	GameObject* r, * l;
	((Boss*)object)->GetWings(&r, &l);
	r->SetState(BOSS_ATT_END);
	l->SetState(BOSS_ATT_END);
}

State* BossAttEndState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if ((float)(info.MaxFrame) <= info.SpriteIndex)
	{
		return new BossIdleState();
	}

	return nullptr;
}

void BossAttEndState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	object->SetSpriteInfo(info);
}
