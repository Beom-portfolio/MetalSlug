#pragma once
class MouseManager : public Singleton<KeyManager>
{
public:
	MouseManager();
	virtual ~MouseManager();

public:
	void SetMouseLButton(bool check) { m_AsyncLButtonState = check; }
	void SetMouseRButton(bool check) { m_AsyncRButtonState = check; }

public:
	bool GetMouseLButtonState(KEYSTATE state) { return m_MouseLButton[state]; }
	bool GetMouseRButtonState(KEYSTATE state) { return m_MouseRButton[state]; }

public:
	const POINT GetMousePos()
	{
		POINT pos;

		GetCursorPos(&pos);
		ScreenToClient(g_hWnd, &pos);

		return pos;
	}

public:
	void Update();

private:
	bool m_MouseLButton[STATE_END];
	bool m_MouseRButton[STATE_END];
	bool m_AsyncLButtonState = false;
	bool m_AsyncRButtonState = false;
};

