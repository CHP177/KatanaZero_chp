#pragma once

//Console Windows
//#ifdef _DEBUG
//#pragma comment(linker, "/entry:wWinMainCRTStartup /subsystem:console")
//#endif

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

//DirectX D3D11
#include <d3d11.h>
#include <d3dcompiler.h>
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

//WRL
#include <wrl.h>
using namespace Microsoft;
using namespace WRL;

//DirectXTK & TK
#include "_Libraries/DirectXTK/SimpleMath.h"
using namespace DirectX;
using namespace SimpleMath;

#include <DirectXTex.h>


//FMOD
#include "_Libraries/FMOD/fmod.hpp"
#ifdef _M_X64
	#pragma comment(lib, "_Libraries/FMOD/x64/fmodL_vc.lib")
#elif _M_IX86
	#pragma comment(lib, "_Libraries/FMOD/x86/fmodL_vc.lib")
#endif

//Macros
#define WIN_DEFAULT_WIDTH 1280.0f
#define WIN_DEFAULT_HEIGHT 720.0f

#define CHECK(hr) { assert(SUCCEEDED(hr)); }

//Vector Macros
#define RIGHT Vector2(1.0f, 0.0f)
#define UP Vector2(0.0f, 1.0f)

//Extern Globals
extern HWND gHandle;
extern HDC gHDC;
extern float gWinWidth;
extern float gWinHeight;

//Declare Singleton Macro
#define DECLARE_SINGLETON(CLASS_NAME)						\
private:													\
CLASS_NAME();												\
~CLASS_NAME();												\
CLASS_NAME(const CLASS_NAME& other) = delete;				\
CLASS_NAME& operator=(const CLASS_NAME& other) = delete;	\
CLASS_NAME(const CLASS_NAME&& other) = delete;				\
CLASS_NAME& operator=(const CLASS_NAME&& other) = delete;	\
public:														\
static CLASS_NAME* Get()									\
{															\
	static CLASS_NAME instance;								\
	return &instance;										\
}

//Systems
#include "Systems/Input.h"
#include "Systems/Time.h"
#include "Systems/Graphics.h"
#include "Systems/Sound.h"
#include "Systems/Camera.h"

//Singleton Getter Macros
#define INPUT Input::Get()
#define TIME Time::Get()
#define GRAPHICS Graphics::Get()
#define DEVICE GRAPHICS->GetDevice()
#define DC GRAPHICS->GetDC()
#define CAMERA Camera::Get()

//Headers
#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"

#include "Renders/Shaders/IShader.h"
#include "Renders/Shaders/VertexShader.h"
#include "Renders/IA/InputLayout.h"
#include "Renders/Shaders/PixelShader.h"

#include "Renders/Resources/ConstantBuffer.h"
#include "Renders/Resources/GlobalBuffers.h"

//Utillities
#include "Utillities/Collision.h"
#include "Utillities/String.h"
#include "Utillities/Path.h"


//Component
#include "Component/Component.h"

//Object
#include "Object/Object.h"

//Scene
#include "Scenes/IScene.h"