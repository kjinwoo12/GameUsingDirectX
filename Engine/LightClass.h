#pragma once
#include<D3DX10math.h>

class LightClass {
public:
	LightClass();
	~LightClass();

	void setAmbientColor(float, float, float, float);
	void setDiffuseColor(float, float, float, float);
	void setDirection(float, float, float);

	D3DXVECTOR4 getAmbientColor();
	D3DXVECTOR4 getDiffuseColor();
	D3DXVECTOR3 getDirection();

private:
	D3DXVECTOR4 ambientColor;
	D3DXVECTOR4 diffuseColor;
	D3DXVECTOR3 direction;
};

