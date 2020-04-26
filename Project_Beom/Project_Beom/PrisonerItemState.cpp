#include "pch.h"
#include "PrisonerItemState.h"
#include "PrisonerByeState.h"
#include "GameObject.h"
#include "Item.h"

PrisonerItemState::PrisonerItemState()
{
}

PrisonerItemState::~PrisonerItemState()
{
}

void PrisonerItemState::Enter(GameObject* object)
{
	GETMGR(SoundManager)->PlaySound(L"NPC_ThankYou.mp3", CH_VOICE);
	SPRITEINFO info = object->GetSpriteInfo();
	if (DIR_RIGHT == object->GetDirection())
		info.key = L"prisoner_item_r";
	else
		info.key = L"prisoner_item_l";
	info.Type = SPRITE_ONCE;
	info.MaxFrame = 21;
	info.Speed = 12.f;
	info.SpriteIndex = 0.f;
	info.StateIndex = 0;

	object->SetSpriteInfo(info);
}

State* PrisonerItemState::HandleInput(GameObject* object, KeyManager* input)
{
	SPRITEINFO info = object->GetSpriteInfo();
	if ((float)info.MaxFrame <= info.SpriteIndex)
		return new PrisonerByeState();

	return nullptr;
}

void PrisonerItemState::Update(GameObject* object, const float& TimeDelta)
{
	SPRITEINFO info = object->GetSpriteInfo();
	info.SpriteIndex += info.Speed * TimeDelta;

	if (!m_onceCheck && 8.f <= info.SpriteIndex)
	{
		GameObject* item = AbstractFactory<Item>::CreateObj();
		((Item*)item)->SetItem(ITEMTYPE(rand() % ITEM_END));
		float X = 0.f;
		if (DIR_RIGHT == object->GetDirection())
			X = (float)object->GetOriginCollideRect().right;
		else
			X = (float)object->GetOriginCollideRect().left;
		item->SetPosition(X, object->GetOriginCollidePosition().Y - 20.f);
		GETMGR(ObjectManager)->AddObject(item, OBJ_ITEM);
		m_onceCheck = true;
	}

	object->SetSpriteInfo(info);
}
