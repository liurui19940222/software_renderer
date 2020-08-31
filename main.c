#include <windowsx.h>
#include <windows.h>
#include "renderer.h"
#include "srdprogram.h"

#define ClS_NAME L"SFRD"
#define WND_NAME L"SFRD_WND"

HWND hwnd;
Renderer* renderer;

LRESULT CALLBACK eventsHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg)
	{
		case WM_CREATE:

		break;
		case WM_DESTROY:
		case WM_QUIT:
		case WM_CLOSE:
			PostQuitMessage(0);
			break;
		case WM_SIZE:

		break;
		case WM_MOVE:

			break;
		default:
			break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

void createDevices(int w, int h)
{
	HINSTANCE mHIntance = GetModuleHandle(NULL);
	WNDCLASSEX windowClass;
	RECT       windowRect;
	HWND hwnd;

	windowRect.left = (long)0;
	windowRect.right = (long)w;
	windowRect.top = (long)0;
	windowRect.bottom = (long)h;

	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = eventsHandler;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = mHIntance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = NULL;
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = ClS_NAME;
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);

	if (!RegisterClassEx(&windowClass))
		return;

	int x = (GetSystemMetrics(0) - w) >> 1;
	int y = (GetSystemMetrics(1) - h) >> 1;

	DWORD dwStyle = WS_OVERLAPPEDWINDOW;
	AdjustWindowRectEx(&windowRect, WS_OVERLAPPEDWINDOW, 0, 0);

	hwnd = CreateWindowEx(NULL,
		ClS_NAME,
		WND_NAME,
		dwStyle,
		x, y,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		mHIntance,
		NULL);

	if (!hwnd)
		return;

	init();

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	renderer = srd_init(hwnd, w, h);
}

void dispatch()
{
	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) //处理Windows消息
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		srd_beginFrame(renderer);
		render(renderer);
		srd_endFrame(renderer);
		Sleep(16);
	}
}

int main(void)
{
	createDevices(800, 600);
	dispatch();
	return 0;
}

