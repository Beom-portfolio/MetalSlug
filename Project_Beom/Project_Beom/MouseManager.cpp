#include "pch.h"
#include "MouseManager.h"

MouseManager::MouseManager()
{
	ZeroMemory(&m_MouseLButton, STATE_END);
}

MouseManager::~MouseManager()
{
}

void MouseManager::Update()
{
	bool& MouseLStateDown = m_MouseLButton[STATE_DOWN];
	bool& MouseLStatePush = m_MouseLButton[STATE_PUSH];
	bool& MouseLStateUp = m_MouseLButton[STATE_UP];

	if (m_AsyncLButtonState)
	{
		if (!MouseLStateDown && !MouseLStatePush)
		{
			MouseLStateDown = true;
			MouseLStatePush = false;
			MouseLStateUp = false;
		}
		else
		{
			MouseLStateDown = false;
			MouseLStatePush = true;
			MouseLStateUp = false;
		}
	}
	else
	{
		if (MouseLStateUp)
		{
			MouseLStateDown = false;
			MouseLStatePush = false;
			MouseLStateUp = false;
		}
		else if(MouseLStateDown || MouseLStatePush)
		{
			MouseLStateDown = false;
			MouseLStatePush = false;
			MouseLStateUp = true;
		}
	}
	
	bool& MouseRStateDown = m_MouseRButton[STATE_DOWN];
	bool& MouseRStatePush = m_MouseRButton[STATE_PUSH];
	bool& MouseRStateUp = m_MouseRButton[STATE_UP];

	if (m_AsyncRButtonState)
	{
		if (!MouseRStateDown && !MouseRStatePush)
		{
			MouseRStateDown = true;
			MouseRStatePush = false;
			MouseRStateUp = false;
		}
		else
		{
			MouseRStateDown = false;
			MouseRStatePush = true;
			MouseRStateUp = false;
		}
	}
	else
	{
		if (MouseRStateUp)
		{
			MouseRStateDown = false;
			MouseRStatePush = false;
			MouseRStateUp = false;
		}
		else if (MouseRStateDown || MouseRStatePush)
		{
			MouseRStateDown = false;
			MouseRStatePush = false;
			MouseRStateUp = true;
		}
	}
}
