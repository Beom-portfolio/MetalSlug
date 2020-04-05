#pragma once

#define PURE = 0

#define GETMGR(Class) Singleton<Class>::GetInstance()
#define ERRORMSG(Content) MessageBox(g_hWnd, Content, L"Error!", MB_OK);