#include "pch.h"
#include "State.h"

State::State()
{
}

State::~State()
{
}

void State::Enter(GameObject* object)
{
}

State* State::HandleInput(GameObject* object, KeyManager* input)
{
	return nullptr;
}

void State::Update(GameObject* object, const float& TimeDelta)
{
}
