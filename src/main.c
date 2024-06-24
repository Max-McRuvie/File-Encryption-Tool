#include <windows.h>
#include <tchar.h>

#define MAX_LOADSTRING 100
#define ID_BUTTON_ENCRYPT 1
#define ID_BUTTON_DECRYPT 2

// Global variables
HINSTANCE hInst;
TCHAR szTitle[MAX_LOADSTRING] = _T("Sample Window");
TCHAR szWindowClass[MAX_LOADSTRING] = _T("SampleWindowClass");

// Function prototypes
ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hwndEncryptButton, hwndDecryptButton;

    switch (message) {            
        case WM_CREATE:
            hwndEncryptButton = CreateWindow(
                TEXT("BUTTON"),
                TEXT("Encrypt"),
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                90, 320, 100, 30,
                hWnd,
                (HMENU)ID_BUTTON_ENCRYPT,
                hInst,
                NULL
            );

            hwndDecryptButton = CreateWindow(
                TEXT("BUTTON"),
                TEXT("Decrypt"),
                WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                200, 320, 100, 30,
                hWnd,
                (HMENU)ID_BUTTON_DECRYPT,
                hInst,
                NULL
            );
            break;

        case WM_COMMAND:
            switch (LOWORD(wParam)) {
                case ID_BUTTON_ENCRYPT:
                    MessageBox(hWnd, TEXT("Encrypt button clicked"), TEXT("Info"), MB_OK | MB_ICONINFORMATION);
                    break;

                case ID_BUTTON_DECRYPT:
                    MessageBox(hWnd, TEXT("Decrypt button clicked"), TEXT("Info"), MB_OK | MB_ICONINFORMATION);
                    break;
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow)) {
        MessageBox(NULL, TEXT("Window Initialization Failed!"), TEXT("Error"), MB_ICONERROR);
        return 1;
    }

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance) {
    WNDCLASSEX wc = { 0 };

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = szWindowClass;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    ATOM result = RegisterClassEx(&wc);
    if (!result) {
        DWORD error = GetLastError();
        TCHAR buffer[256];
        _stprintf(buffer, _T("RegisterClassEx Failed! Error code: %lu"), error);
        MessageBox(NULL, buffer, TEXT("Error"), MB_ICONERROR);
    }
    return result;
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {
    hInst = hInstance;

    HWND hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 400, 400, NULL, NULL, hInstance, NULL);

    if (!hWnd) {
        DWORD error = GetLastError();
        TCHAR buffer[256];
        _stprintf(buffer, _T("CreateWindow Failed! Error code: %lu"), error);
        MessageBox(NULL, buffer, TEXT("Error"), MB_ICONERROR);
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}