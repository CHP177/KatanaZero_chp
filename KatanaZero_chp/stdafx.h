#pragma once

//Console Windows
#ifdef _DEBUG
#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
#endif

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows Header
#include <windows.h>
#include <windowsx.h>
#include <commdlg.h>

// C Runtime Header
#include <cassert>

// C++ Runtime Header
#include <string>
#include <memory>
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <vector>
#include <array>
#include <map>
#include <list>
#include <unordered_map>

using namespace std;

//Macros
#define WIN_DEFAULT_WIDTH 1280.0f
#define WIN_DEFAULT_HEIGHT 720.0f

//Extern Globals
extern HWND gHandle;
extern HDC gHDC;
extern float gWinWidth;
extern float gWinHeight;