#include "GraphicsClass.h"


GraphicsClass::GraphicsClass()
{
	m_d3d = 0;
	m_camera = 0;
	m_model = 0;
	//m_colorShader = 0;
	m_textureShader = 0;
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
	m_camera->setPosition(0.0f, 0.0f, -10.0f);

	m_model = new ModelClass;
	if (!m_model) {
		return false;
	}

	result = m_model->initialize(m_d3d->getDevice(), L"../Engine/data/seafloor.dds");
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the model object", L"Error", MB_OK);
		return false;
	}

	/*m_colorShader = new ColorShaderClass;
	if (!m_colorShader) {
		return false;
	}
	
	result = m_colorShader->initialize(m_d3d->getDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the color shader object", L"Error", MB_OK);
		return false;
	}*/


	m_textureShader = new TextureShaderClass;
	if (!m_textureShader) {
		return false;
	}

	result = m_textureShader->initialize(m_d3d->getDevice(), hwnd);
	if (!result) {
		MessageBox(hwnd, L"Could not initialize the texture shader object.", 
							 L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::shutdown()
{
	//// Release the color shader
	//if (m_colorShader) {
	//	m_colorShader->shutdown();
	//	delete m_colorShader;
	//	m_colorShader = 0;
	//}

	if (m_textureShader) {
		m_textureShader->shutdown();
		delete m_textureShader;
		m_textureShader = 0;
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

	// Put the model vertex and indexbuffers on the graphics pipeline to prepare them for drawing
	m_model->render(m_d3d->getDeviceContext());

	/*result = m_colorShader->render(m_d3d->getDeviceContext(), m_model->getIndexCount(), worldMatrix, viewMatrix, projectionMatrix);
	if (!result) {
		return false;
	}*/

	result = m_textureShader->render(m_d3d->getDeviceContext(),
																	 m_model->getIndexCount(),
																	 worldMatrix, 
																	 viewMatrix, 
																	 projectionMatrix,
																	 m_model->getTexture());
	if (!result) {
		return false;
	}

	// Present the rendered scene to the screen.
	m_d3d->endScene();

	return true;
}