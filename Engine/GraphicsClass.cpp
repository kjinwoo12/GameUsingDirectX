#include "GraphicsClass.h"


GraphicsClass::GraphicsClass()
{
	m_d3d = 0;
	m_camera = 0;
	m_model = 0;
	m_lightShader = 0;
	m_light = 0;
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
	m_d3d = new D3DClass;
	if(!m_d3d)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_d3d->initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	m_camera = new CameraClass;
	if (!m_camera) {
		return false;
	}
	m_camera->setPosition(0.0f, 0.0f, -3.0f);

	m_model = new ModelClass;
	if (!m_model) {
		return false;
	}

	result = m_model->initialize(m_d3d->getDevice(), "../Engine/Cube.txt", L"../Engine/seafloor.dds");
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object", L"Error", MB_OK);
		return false;
	}

	m_lightShader = new LightShaderClass;
	if (!m_lightShader) {
		return false;
	}
	result = m_lightShader->initialize(m_d3d->getDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the light shader object",
							 L"Error", MB_OK);
		return false;
	}

	m_light = new LightClass;
	if (!m_light) {
		return false;
	}
	m_light->setAmbientColor(0.15f, 0.15f, 0.15f, 1.0f);
	m_light->setDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->setDirection(0.0f, 0.0f, 1.0f);
	m_light->setSpecularColor(1.0f, 1.0f, 1.0f, 1.0f);
	m_light->setSpecularPower(32.0f);

	return true;
}


void GraphicsClass::shutdown()
{
	if (m_light) {
		delete m_light;
		m_light = 0;
	}

	if (m_lightShader) {
		m_lightShader->shutdown();
		delete m_lightShader;
		m_lightShader = 0;
	}

	// Release the model object
	if (m_model) {
		m_model->shutdown();
		delete m_model;
		m_model = 0;
	}

	// Release the camera object
	if (m_camera) {
		delete m_camera;
		m_camera = 0;
	}

	// Release the D3D object.
	if(m_d3d)
	{
		m_d3d->shutdown();
		delete m_d3d;
		m_d3d = 0;
	}

	return;
}


bool GraphicsClass::frame()
{
	bool result;
	static float rotation = 0.0f;


	// Render the graphics scene.
	rotation += (float)D3DX_PI * 0.005f;
	if (rotation > 360.0f) {
		rotation -= 360.0f;
	}
	result = render(rotation);
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::render(float rotation)
{
	D3DXMATRIX worldMatrix, viewMatrix, projectionMatrix;
	bool result;

	// Clear the buffers to begin the scene.
	m_d3d->begineScene(0.f, 0.f, 0.f, 1.f);

	// Generate the view matrix based on the camera's position
	m_camera->render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_camera->getViewMatrix(viewMatrix);
	m_d3d->getWorldMatrix(worldMatrix);
	m_d3d->getProjectionMatrix(projectionMatrix);

	// Rotate the world matrix by the rotation value
	// so that the triangle will spin.
	D3DXMatrixRotationY(&worldMatrix, rotation);

	// Put the model vertex and indexbuffers on the graphics pipeline to prepare them for drawing
	m_model->render(m_d3d->getDeviceContext());

	result = m_lightShader->render(m_d3d->getDeviceContext(),
																 m_model->getIndexCount(),
																 worldMatrix,
																 viewMatrix,
																 projectionMatrix,
																 m_model->getTexture(),
																 m_light->getDirection(),
																 m_light->getAmbientColor(),
																 m_light->getDiffuseColor(),
																 m_camera->getPosition(),
																 m_light->getSpecularColor(),
																 m_light->getSpecularPower());
	if (!result) {
		return false;
	}

	// Present the rendered scene to the screen.
	m_d3d->endScene();

	return true;
}