#include "pch.h"
#include "PrisonerRunoutState.h"
#include "GameObject.h"

PrisonerRunoutState::PrisonerRunoutState()
{
}

PrisonerRunoutState::~PrisonerRunoutState()
{
}

void PrisonerRunoutState::Enter(GameObject* object)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"prisoner_runout_r";
	else
		info.key = L"prisoner_runout_l";
	info.Type = SPRITE_REPEAT;
	info.MaxFrame = 8;
	info.Speed = 12.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
	object->SetSpeed(250.f);
}

State* PrisonerRunoutState::HandleInput(GameObject* object, KeyManager* input)
{
	// 계속 쭉 앞으로 가니까 화면에 안보이면 지워준다.
	if (object->GetCullingCheck())
		object->SetDead(true);

	return nullptr;
}

void PrisonerRunoutState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	POSITION pos = object->GetPosition();
	if (DIR_RIGHT == object->GetDirection())
	{
		info.key = L"prisoner_runout_r";
		object->SetPosition(pos.X + object->GetSpeed() * TimeDelta, pos.Y);
	}
	else
	{
		info.key = L"prisoner_runout_l";
		object->SetPosition(pos.X - object->GetSpeed() * TimeDelta, pos.Y);
	}

	if ((float)info.MaxFrame <= info.SpriteIndex)
		info.SpriteIndex = 0.f;

	object->SetSpriteInfo(info);
}
