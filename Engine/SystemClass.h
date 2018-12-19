#pragma once

#include <windows.h>

#include "inputclass.h"
#include "graphicsclass.h"


class SystemClass
{
public:
	SystemClass();
	SystemClass(const SystemClass&);
	~SystemClass();

	bool initialize();
	void shutdown();
	void run();

	LRESULT CALLBACK messageHandler(HWND, UINT, WPARAM, LPARAM);

private:
	bool frame();
	void initializeWindows(int, int);
	void shutdownWindows();

private:
	LPCWSTR m_applicationName;
	HINSTANCE m_hinstance;
	HWND m_hwnd;

	InputClass* m_Input;
	GraphicsClass* m_Graphics;
};


/////////////////////////
// FUNCTION PROTOTYPES //
/////////////////////////
static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


/////////////
// GLOBALS //
/////////////
static SystemClass* ApplicationHandle = 0;