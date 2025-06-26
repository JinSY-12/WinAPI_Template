#pragma once

// ��� ����
#pragma warning(disable : 4005)

#include<SDKDDKVER.h>

#define WIN32_LEAN_AND_MEAN

// ����� �ܼ�â
#pragma comment (linker, "/entry:WinMainCRTStartup /subsystem:console")

#include "./inc/FMOD/fmod.hpp"

// ! ���̺귯�� �߰�
#pragma comment (lib, "msimg32.lib")		// �̹��� ����� ���� �⺻ ���̺귯��
#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "./lib/FMOD/fmodex64_vc.lib")

//! Windows ��� ����
#include <Windows.h>

//fmod ���


//! C ��Ÿ�� ��� ����
// stdlib :  C����� ǥ�� ���̺귯�� �Լ��� ��� ����
#include <stdlib.h>

// malloc : C���� �޸𸮸� �Ҵ��Ҷ� ����Ѵ�
#include <malloc.h>

// memory : �޸� ���� ������� -> ex) memset / memcpy ���� �Լ����� �ִ�
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>

//! C++ ��Ÿ�� ��� ����
#include<iostream>

#include<chrono>
#include<random>
#include<vector>
#include<queue>
#include<map>

#include<unordered_map>

#include<cassert>
#include<bitset>

#include <cmath>
#include <fstream>
#include <string>

using namespace std;


// ! D2D / D3D�������
/*
#include<D2D1.h>
#include<d2d1helper.h>
#include<d3dx9.h>		// ���־��µ� �����Ȱ���
#include<D3DX11.h>		// ���� ���� �� -> �׷��Ƚ� ���̺귯�� �߰��ؾ� ��� ����
#include<d3d11shader.h>	// �׷��� ���̴��� �� �����Ͷ�
#include<dinput.h>

#pragma comment(lib, "d2d1.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dx11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

ID2D1Factory*					_ID2DFactory = nullptr;
ID2D1HwndRenderTarget*			_ID2DRenderTarget = nullptr;
*/

// # ����� ���� ������� # 
#include "CommonMacroFunction.h"
#include "RandomFunction.h"
#include "KeyManager.h"
#include "ImageManager.h"
#include "SoundManager.h"
#include "Utils.h"
#include "TimeManager.h"

using namespace MY_UTIL;

// # �̱��� #
#define RND RandomFunction::getSingleton()
#define KEYMANAGER KeyManager::getSingleton()
#define IMAGEMANAGER ImageManager::getSingleton()
#define SOUNDMANAGER SoundManager::getSingleton()
#define TIMEMANAGER TimeManager::getSingleton()


//! Ÿ��Ʋ
#define WINNAME				(LPTSTR)(TEXT("WindowsAPI"))

//! ��ü ȭ��
//#define FULLSCREEN

#ifdef FULLSCREEN

#define WINSTART_X			0
#define WINSTART_Y			0
#define WINSIZE_X			GetSystemMetrics(SM_CXSCREEN)
#define WINSIZE_Y			GetSystemMetrics(SM_CYSCREEN)
#define WINSTYLE			WS_POPUPWINDOW | WS_MAXIMIZE 
#define PI					3.1415926
#define MAGENTA				RGB(255, 0, 255)

#else

#define WINSTART_X			600
#define WINSTART_Y			50
#define WINSIZE_X			1024
#define WINSIZE_Y			896
#define WINSTYLE			WS_CAPTION | WS_SYSMENU
#define PI					3.1415926
#define MAGENTA				RGB(255, 0, 255)

#endif

#define SAFE_DELETE(p)			{if(p) {delete (p); (p) = nullptr;}}
#define SAFE_DELETE_ARRAY(p)	{if(p) {delete[] (p); (p) = nullptr;}}
#define SAFE_RELEASE(p)			{if(p) {(p)->release(); (p) = nullptr;}}

extern HINSTANCE	_hInstance;
extern HWND			_hWnd;
extern POINT		_ptMouse;
