#pragma once

class Timer;
class System
{
public:
	System();
	~System();

public:
	bool Initialize(HINSTANCE hInstance, int nCmdShow);
	int Logic();
	void Release();

private:
	void PrintFPS();

private:
	ATOM MyRegisterClass(HINSTANCE hInstance);
	BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);

private:
	TimerManager* m_TimerManager = nullptr;
	FrameManager* m_FrameManager = nullptr;
	KeyManager* m_KeyManager = nullptr;
	MouseManager* m_MouseManager = nullptr;

	int m_frameCount = 0;
	float m_timeCount = 0.f;
	float m_frameTimeDelta = 0.f;
};

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
