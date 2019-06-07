#pragma once
#include<D3DX10math.h>

class LightClass {
public:
	LightClass();
	~LightClass();

	void setAmbientColor(float, float, float, float);
	void setDiffuseColor(float, float, float, float);
	void setDirection(float, float, float);
	void setSpecularColor(float, float, float, float);
	void setSpecularPower(float);

	D3DXVECTOR4 getAmbientColor();
	D3DXVECTOR4 getDiffuseColor();
	D3DXVECTOR3 getDirection();
	D3DXVECTOR4 getSpecularColor();
	float getSpecularPower();

private:
	D3DXVECTOR4 m_ambientColor;
	D3DXVECTOR4 m_diffuseColor;
	D3DXVECTOR3 m_direction;
	D3DXVECTOR4 m_specularColor;
	float m_specularPower;
};

