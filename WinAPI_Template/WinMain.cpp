#include "Stdafx.h"
#include "MainGame.h"

HINSTANCE _hInstance;

HWND _hWnd;

POINT _ptMouse = { 0, 0 };

LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

MainGame* _mg;

void setWindowSize(int x, int y, int width, int height);


int APIENTRY WinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR _lpszCmdParam,
    int     nCmdShow)
{
    _mg = new MainGame();

    _hInstance = hInstance;

    WNDCLASS wndClass;

    wndClass.cbClsExtra = 0;
    wndClass.cbWndExtra = 0;
    wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wndClass.hInstance = hInstance;
    wndClass.lpfnWndProc = (WNDPROC)WndProc;
    wndClass.lpszClassName = WINNAME;
    wndClass.lpszMenuName = NULL;
    wndClass.style = CS_HREDRAW | CS_VREDRAW;

    RegisterClass(&wndClass);

#ifdef FULLSCREEN           // ���������� ���� ���鶧�� ���� �����ؼ� â���� ������

    // ����̽� ��� ����ü (ȭ�� ���÷��� ���� ����ü)
    DEVMODE dm;

    // �޸𸮰� ���������� ������ �ѹ� �޸𸮸� ���� ����
    ZeroMemory(&dm, sizeof(DEVMODE));

    dm.dmSize = sizeof(DEVMODE);
    dm.dmBitsPerPel = 32;  // 32��Ʈ Ʈ���÷��� �ǹ� WinAPI32 -> 32��Ʈ��
    dm.dmPanningWidth = 1980;//���ΰ�
    dm.dmPelsHeight = 1020;//���ΰ�
    dm.dmDisplayFrequency = 60; // �ֻ���

    // �ʵ� ����
    dm.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    // ����Ǹ� ���÷��� ������ ������� ������
    if (ChangeDisplaySettings(&dm, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
    {
        ChangeDisplaySettings(&dm, 0);
    }

    _hWnd = CreateWindow
    (
        WINNAME,
        WINNAME,
        WINSTYLE,
        WINSTART_X,
        WINSTART_Y,
        WINSIZE_X,
        WINSIZE_Y,
        NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );


#else

    _hWnd = CreateWindow
    (
        WINNAME,
        WINNAME,
        WINSTYLE,
        WINSTART_X,
        WINSTART_Y,
        WINSIZE_X,
        WINSIZE_Y,
        NULL,
        (HMENU)NULL,
        hInstance,
        NULL
    );

#endif
    setWindowSize(WINSTART_X, WINSTART_Y, WINSIZE_X, WINSIZE_Y);

    ShowWindow(_hWnd, nCmdShow);

    if (FAILED(_mg->init()))
    {
        return 0;
    }

    MSG message;

    while (true)
    {
        if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
        {
            if (message.message == WM_QUIT) break;

            TranslateMessage(&message);
            DispatchMessage(&message);
        }

        else
        {
            TIMEMANAGER->update(60.0f);
            SOUNDMANAGER->update();
        }
    }

    _mg->release();
    SAFE_DELETE(_mg);

    UnregisterClass(WINNAME, hInstance);

    return (int)message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
    return _mg->MainProc(hWnd, iMessage, wParam, lParam);
}

void setWindowSize(int x, int y, int width, int height)
{
    RECT rc = { 0, 0, width, height };

    AdjustWindowRect(&rc, WINSTYLE, false);

    SetWindowPos(_hWnd, NULL, x, y,
        (rc.right - rc.left),
        (rc.bottom - rc.top),
        SWP_NOZORDER | SWP_NOMOVE);
}

