#include "GraphicsClass.h"


GraphicsClass::GraphicsClass()
{
	m_D3D = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	bool result;


	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::shutdown()
{
	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	return;
}


bool GraphicsClass::frame()
{
	bool result;


	// Render the graphics scene.
	result = render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::render()
{
	// Clear the buffers to begin the scene.
	m_D3D->begineScene(0.f, 0.f, 0.f, 1.f);


	// Present the rendered scene to the screen.
	m_D3D->endScene();

	return true;
}