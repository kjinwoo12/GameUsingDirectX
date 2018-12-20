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

private:
	float m_positionX, m_positionY, m_positionZ;
	float m_rotationX, m_rotationY, m_rotationZ;
	D3DXMATRIX m_viewMatrix;
};

