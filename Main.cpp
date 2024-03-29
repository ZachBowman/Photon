// Photon

#include "stdafx.h"

#include <sstream>
#include <string>
#include <vector>
#include <windows.h>

#include "Debug.h"
#include "Keyboard.h"
#include "Photon.h"
#include "Player2D.h"
#include "Timing.h"
#include "Transparent_Bitmap.h"

#define MAX_LOADSTRING 100

int window_width = 1000;
int window_height = 600;

HWND Window;
WCHAR szTitle[MAX_LOADSTRING];
WCHAR szWindowClass[MAX_LOADSTRING];

Photon photon;

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
  {
  UNREFERENCED_PARAMETER (hPrevInstance);
  UNREFERENCED_PARAMETER (lpCmdLine);

  // Initialize global strings
  LoadStringW (hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
  LoadStringW (hInstance, IDC_PHOTON, szWindowClass, MAX_LOADSTRING);
  MyRegisterClass (hInstance);

  // Perform application initialization:
  if (!InitInstance (hInstance, nCmdShow))
    {
    return FALSE;
    }

  HACCEL hAccelTable = LoadAccelerators (hInstance, MAKEINTRESOURCE (IDC_PHOTON));
  MSG msg;

  photon.Init(Window);
  
  // Main message loop:
  while (!photon.Exit)
    {
    while (PeekMessage (&msg, nullptr, 0, 0, PM_REMOVE))
      {
      DispatchMessage (&msg);
      }
    photon.Main_Loop ();
    }

  return TRUE;
  }

// Registers the window class.
ATOM MyRegisterClass (HINSTANCE hInstance)
  {
  WNDCLASSEXW wcex;

  wcex.cbSize = sizeof (WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon (hInstance, MAKEINTRESOURCE (IDI_PHOTON));
  wcex.hCursor = LoadCursor (nullptr, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH) (COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCEW (IDC_PHOTON);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon (wcex.hInstance, MAKEINTRESOURCE (IDI_SMALL));

  return RegisterClassExW (&wcex);
  }

BOOL InitInstance (HINSTANCE hInstance, int nCmdShow)
  {
  Window = CreateWindowW (szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0, window_width, window_height, nullptr, nullptr, hInstance, nullptr);

  if (!Window) return FALSE;

  SetMenu (Window, NULL);
  ShowWindow (Window, nCmdShow);
  UpdateWindow (Window);

  return TRUE;
  }

// Processes messages for the main window.
LRESULT CALLBACK WndProc (HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
  {
  switch (message)
    {
      case WM_SIZE:

        // TODO: Respond to Window resize (in progress).

        //RECT window_rect;
        //if (GetWindowRect (Window, &window_rect))
        //  {
        //  hdc = GetDC (Window);
        //  bitmap_buffer = CreateCompatibleBitmap (hdc, photon.screen_width, photon.screen_height);
        //  SelectObject (hdc_buffer, bitmap_buffer);

        //  photon.screen_width = window_rect.right - window_rect.left;
        //  photon.screen_height = window_rect.bottom - window_rect.top;
        //  }
        break;

      case WM_DESTROY:
        photon.Exit = true;
        PostQuitMessage (0);
        break;

      default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
  return 0;
  }
