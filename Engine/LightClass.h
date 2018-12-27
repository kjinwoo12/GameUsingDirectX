#pragma once
#include<D3DX10math.h>

class LightClass {
public:
	LightClass();
	~LightClass();

	void setDiffuseColor(float, float, float, float);
	void setDirection(float, float, float);

	D3DXVECTOR4 getDiffuseColor();
	D3DXVECTOR3 getDirection();

private:
	D3DXVECTOR4 diffuseColor;
	D3DXVECTOR3 direction;
};

