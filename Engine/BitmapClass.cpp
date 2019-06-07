#include "BitmapClass.h"



BitmapClass::BitmapClass() {
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_texture = 0;
}


BitmapClass::~BitmapClass() {
}


bool BitmapClass::initialize(ID3D11Device* device, int screenWidth, int screenHeight,
														 WCHAR *textureFileName, int bitmapWidth, int bitmapHeight) {
	bool result;

	m_screenWidth = screenWidth;
	m_screenHeight = screenHeight;

	m_bitmapWidth = bitmapWidth;
	m_bitmapHeight = bitmapHeight;

	return result;
}