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
#include <DirectXTex.h>

using namespace DirectX;
using namespace SimpleMath;

//ImGui
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx11.h>

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

#define SUPER __super

#define CENTER_X (WIN_DEFAULT_WIDTH / 2)
#define CENTER_Y (WIN_DEFAULT_HEIGHT/ 2)
#define CENTER Vector2(CENTER_X, CENTER_Y)

//Color Macros
#define NONECOLOR Color(0, 0, 0, 0)
#define WHITE Color(1, 1, 1, 1)
#define BLACK Color(0, 0, 0, 1)
#define RED Color(1, 0, 0, 1)
#define GREEN Color(0, 1, 0, 1)
#define BLUE Color(0, 0, 1, 1)
#define YELLOW Color(1, 1, 0, 1)
#define MAGENTA Color(1, 0, 1, 1)
#define CYAN Color(0, 1, 1, 1)
#define ORANGE Color(1, 0.5f, 0, 1)
#define ROSE Color(1, 0, 0.5f, 1)
#define CHARTREUSEGREEN Color(0.5f, 1, 0, 1)
#define SPRINGGREEN Color(0, 1, 0.5f, 1)
#define VIOLET Color(0.5f, 0, 1, 1)
#define AZURE Color(0, 0.5f, 1, 1)

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
#include "Renders/Resources/ConstantBuffer.h"
#include "Renders/Resources/GlobalBuffers.h"
#include "Renders/Resources/VertexType.h"

#include "Renders/IA/VertexBuffer.h"
#include "Renders/IA/IndexBuffer.h"

#include "Renders/Shaders/IShader.h"
#include "Renders/Shaders/VertexShader.h"
#include "Renders/IA/InputLayout.h"
#include "Renders/Shaders/PixelShader.h"

//Utillities
#include "Utillities/Collision.h"
#include "Utillities/String.h"
#include "Utillities/Path.h"
#include "Utillities/RenderTexture.h"
#include "Utillities/Animator.h"

//Component
#include "Component/Component.h"
#include "Component/ColliderComponent.h"
#include "Component/ColorComponent.h"
#include "Component/TextureComponent.h"
#include "Component/SelectionComponent.h"

//Object
#include "Object/Object.h"
#include "Object/Drawable.h"
#include "Object/LineRect.h"
#include "Object/TextureRect.h"
#include "Object/AnimationRect.h"

//TileMap
#include "TileMap/TileMap.h"

//GetComponent Macro
#define GET_COMP(COMPNENT_NAME) GetComponent<COMPONENT_NAME##Component>(#COMPNENT_NAME)

//Scene
#include "Scenes/IScene.h"