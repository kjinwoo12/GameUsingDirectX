#pragma once


#include "D3DClass.h"
#include "CameraClass.h"
#include "ModelClass.h"
#include "ColorShaderClass.h"

const int DEFAULT_WIDTH = 1600;
const int DEFAULT_HEIGHT = 900;
const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;


class GraphicsClass
{
public:
	GraphicsClass();
	GraphicsClass(const GraphicsClass&);
	~GraphicsClass();

	bool initialize(int, int, HWND);
	void shutdown();
	bool frame();

private:
	bool render();

private:
	D3DClass* m_d3d;
	CameraClass* m_camera;
	ModelClass* m_model;
	ColorShaderClass* m_colorShader;
};