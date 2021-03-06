#define _WIN_MAIN_

#include <windowsx.h>
#include <windows.h>
#include "renderer.h"
#include "srdprogram.h"
#include "input.h"

#define ClS_NAME L"SFRD"
#define WND_NAME L"SFRD_WND"

HWND hwnd;
Renderer* renderer;

LRESULT CALLBACK eventsHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	int width, height;
	switch (msg)
	{
	case WM_CREATE:

		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		height = HIWORD(lParam);
		width = LOWORD(lParam);
		if (renderer != NULL) {
			//srd_setSize(renderer, hwnd, width, height);
		}
		break;
	case WM_KEYDOWN:
		input_setKeyDown(wParam);
		break;
	case WM_KEYUP:
		input_setKeyUp(wParam);
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

	hwnd = CreateWindowEx(0,
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

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);

	renderer = srd_init(hwnd, w, h);
	program_init();
	//srd_enable(renderer->context, SRD_WIRE_MODE);
}

void dispatch()
{
	MSG msg;
	while (1)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) //����Windows��Ϣ
		{
			if (msg.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		srd_beginFrame(renderer);
		program_render(renderer);
		srd_endFrame(renderer);
		input_endRecord();
		Sleep(16);
	}
}


#ifdef _WIN_MAIN_

int _stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	input_init();
	createDevices(800, 600);
	dispatch();
	return 0;
}

#elif

int main(void)
{
	createDevices(800, 600);
	dispatch();
	return 0;
}

#endif