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

void LightClass::setDirection(float x, float y, float z) {
	m_direction = D3DXVECTOR3(x, y, z);
}

D3DXVECTOR4 LightClass::getAmbientColor() {
	return m_ambientColor;
}

D3DXVECTOR4 LightClass::getDiffuseColor() {
	return m_diffuseColor;
}

D3DXVECTOR3 LightClass::getDirection() {
	return m_direction;
}