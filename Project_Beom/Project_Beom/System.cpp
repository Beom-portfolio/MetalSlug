#include "pch.h"
#include "System.h"
#include "Resource.h"
#include "Timer.h"
#include "Maingame.h"

#define MAX_LOADSTRING 100

// 전역 변수:
HWND g_hWnd;

HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

// 현재 사용할 제한 프레임
const TCHAR* strFrame = L"Frame_75";

System::System()
{
}

System::~System()
{
}

bool System::Initialize(HINSTANCE hInstance, int nCmdShow)
{
	// 전역 문자열을 초기화합니다.
	wsprintf(szTitle, L"Game");
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_PROJECTBEOM, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	if (!InitInstance(hInstance, nCmdShow))
		return false;

	Timer* pTimer = new Timer;
	if (false == pTimer->Initialize())
		SAFE_DELETE(pTimer);
	
	m_TimerManager = GETMGR(TimerManager);
	m_TimerManager->Add_Timer(L"Timer_Default", pTimer);

	m_FrameManager = GETMGR(FrameManager);

	// 각각 60, 75, 200 프레임으로 제한을 거는 프레임을 만들어 추가한다.
	if (false == m_FrameManager->Add_Frame(L"Frame_60", 60.f))
		return FALSE;

	if (false == m_FrameManager->Add_Frame(L"Frame_75", 75.f))
		return FALSE;

	if (false == m_FrameManager->Add_Frame(L"Frame_200", 200.f))
		return FALSE;

	m_KeyManager = GETMGR(KeyManager);
	m_MouseManager = GETMGR(MouseManager);

	return true;
}

int System::Logic()
{
	HACCEL hAccelTable = LoadAccelerators(hInst, MAKEINTRESOURCE(IDC_PROJECTBEOM));
	
	MSG msg;
	msg.message = WM_NULL;

	// MainGame
	Maingame* game = new Maingame;
	if (!game->Initialize())
	{
		ERRORMSG(L"Initialize Scene Fail!")
		SAFE_RELEASE(game);
		return 0;
	}

	// 기본 메시지 루프입니다:
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			m_TimerManager->Compute_Timer(L"Timer_Default");
			float TimeDelta = m_TimerManager->Get_TimeDelta(L"Timer_Default");

			m_timeCount += TimeDelta;
			if (m_FrameManager->Permit_Call(strFrame, TimeDelta))
			{
				PrintFPS();

				m_KeyManager->UpdateKey();
				m_MouseManager->Update();
				// Game Loop
				game->Update(m_frameTimeDelta);
				game->Render();
			}
		}
	}

	SAFE_RELEASE(game);

	return (int)msg.wParam;
}

void System::Release()
{
	m_FrameManager->DestroyInstance();
	m_TimerManager->DestroyInstance();
	m_KeyManager->DestroyInstance();
	m_MouseManager->DestroyInstance();
}

void System::PrintFPS()
{
	m_frameTimeDelta = m_FrameManager->Get_FrameTimeDelta(strFrame);

	if (m_timeCount >= 1.f)
	{
		char	strFPS[128] = {};
		sprintf_s(strFPS, "Delta Time : %.5f  FPS : %d", m_frameTimeDelta, m_frameCount);
		SetWindowTextA(g_hWnd, strFPS);

		m_timeCount = 0.f;
		m_frameCount = 0;
	}

	++m_frameCount;
}

ATOM System::MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_PROJECTBEOM));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

BOOL System::InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

	RECT rc = { 0, 0, WINSIZE_X, WINSIZE_Y };
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU |
		WS_BORDER | WS_SYSMENU;
	// Style에 맞는 윈도우 영역의 크기를 제공해준다.
	AdjustWindowRect(&rc, dwStyle, FALSE);

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, dwStyle,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top,
		nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	g_hWnd = hWnd;

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			DestroyWindow(hWnd);
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		GETMGR(MouseManager)->SetMouseLButton(true);
		break;
	case WM_LBUTTONUP:
		GETMGR(MouseManager)->SetMouseLButton(false);
		break;
	case WM_RBUTTONDOWN:
		GETMGR(MouseManager)->SetMouseRButton(true);
		break;
	case WM_RBUTTONUP:
		GETMGR(MouseManager)->SetMouseRButton(false);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
