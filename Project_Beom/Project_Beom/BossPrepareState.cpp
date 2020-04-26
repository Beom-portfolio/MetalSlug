#include "pch.h"
#include "BossPrepareState.h"
#include "BossAttState.h"
#include "GameObject.h"
#include "Boss.h"

BossPrepareState::BossPrepareState()
{
}

BossPrepareState::~BossPrepareState()
{
}

void BossPrepareState::Enter(GameObject* object)
{
	GETMGR(SoundManager)->PlaySound(L"BossPrepare.mp3", CH_MONSTER);
	SPRITEINFO info = object->GetSpriteInfo();
	info.MaxFrame = 24;
	info.Speed = 15.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);

	GameObject *r, *l;
	((Boss*)object)->GetWings(&r, &l);
	r->SetState(BOSS_PREPARE);
	l->SetState(BOSS_PREPARE);
}

State* BossPrepareState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if ((float)(info.MaxFrame) <= info.SpriteIndex)
	{
		return new BossAttState();
	}

	return nullptr;
}

void BossPrepareState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	object->SetSpriteInfo(info);
}
