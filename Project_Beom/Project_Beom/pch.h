// pch.h: 미리 컴파일된 헤더 파일입니다.
// 아래 나열된 파일은 한 번만 컴파일되었으며, 향후 빌드에 대한 빌드 성능을 향상합니다.
// 코드 컴파일 및 여러 코드 검색 기능을 포함하여 IntelliSense 성능에도 영향을 미칩니다.
// 그러나 여기에 나열된 파일은 빌드 간 업데이트되는 경우 모두 다시 컴파일됩니다.
// 여기에 자주 업데이트할 파일을 추가하지 마세요. 그러면 성능이 저하됩니다.

#ifndef PCH_H
#define PCH_H

// 여기에 미리 컴파일하려는 헤더 추가
#include "framework.h"

// Windows 헤더 파일
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <comutil.h>

// 여기서 프로그램에 필요한 추가 헤더를 참조합니다.
#include <time.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <random>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

// GDI+ 라이브러리
#include <Gdiplus.h>
using namespace Gdiplus;
#pragma comment(lib, "Gdiplus.lib")

// TransparentBlt 라이브러리
#pragma comment(lib, "msimg32.lib")

// BSTR 지원
#pragma comment(lib, "comsuppw.lib")

// 동영상 재생 라이브러리
#include <Vfw.h>
#pragma comment(lib, "vfw32.lib")

// fmod 사운드 라이브러리
#include "fmod.h"
#include "fmod.hpp"
#pragma comment(lib, "fmodex_vc.lib")

// 디버깅용 콘솔 창
#ifdef UNICODE 
#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif
#else
#ifdef _DEBUG
#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")
#endif
#endif

// 
#include "Macro.h"
#include "Define.h"
#include "Extern.h"
#include "Constant.h"
#include "Enum.h"
#include "Struct.h"
#include "Math.h"
#include "Functor.h"

// Managers
#include "FrameManager.h"
#include "TimerManager.h"
#include "KeyManager.h"
#include "AbstractFactory.h"
#include "SceneManager.h"
#include "FileManager.h"
#include "CameraManager.h"
#include "GdiManager.h"
#include "GdiPlusManager.h"
#include "ObjectManager.h"
#include "CollisionManager.h"
#include "MouseManager.h"
#include "SoundManager.h"

#endif //PCH_H
