#include "LightClass.h"



LightClass::LightClass() {
}


LightClass::~LightClass() {
}

void LightClass::setAmbientColor(float r, float g, float b, float a) {
	 m_ambientColor = D3DXVECTOR4(r, g, b, a);
	return;
}

void LightClass::setDiffuseColor(float r, float g, float b, float a) {
	m_diffuseColor = D3DXVECTOR4(r, g, b, a);
}

void LightClass::setPosition(float x, float y, float z) {
	m_position = D3DXVECTOR3(x, y, z);
}

void LightClass::setDirection(float x, float y, float z) {
	m_direction = D3DXVECTOR3(x, y, z);
}

void LightClass::setSpecularColor(float r, float g, float b, float a) {
	m_specularColor = D3DXVECTOR4(r, g, b, a);
	return;
}

void LightClass::setSpecularPower(float power) {
	m_specularPower = power;
	return;
}

D3DXVECTOR4 LightClass::getAmbientColor() {
	return m_ambientColor;
}

D3DXVECTOR4 LightClass::getDiffuseColor() {
	return m_diffuseColor;
}

D3DXVECTOR3 LightClass::getPosition() {
	return m_position;
}

D3DXVECTOR3 LightClass::getDirection() {
	return m_direction;
}

D3DXVECTOR4 LightClass::getSpecularColor() {
	return m_specularColor;
}

float LightClass::getSpecularPower() {
	return m_specularPower;
}