#pragma once

#include<d3dx10math.h>

class CameraClass {
public:
	CameraClass();
	~CameraClass();

	void setPosition(float, float, float);
	void setRotation(float, float, float);
	
	D3DXVECTOR3 getPosition();
	D3DXVECTOR3 getRotation();
	
	void render();
	void getViewMatrix(D3DXMATRIX&);
	void getFixedMatrix(D3DXMATRIX&);

private:
	void setMatrix(D3DXMATRIX& matrix);

	D3DXVECTOR3 m_position, m_rotation;
	D3DXMATRIX m_viewMatrix;
	D3DXMATRIX m_fixedMatrix;
};

