#include "TextureClass.h"



TextureClass::TextureClass() {
	m_texture = 0;
}


TextureClass::~TextureClass() {
}

bool TextureClass::initialize(ID3D11Device* device, WCHAR* fileName) {
	HRESULT result;

	result = D3DX11CreateShaderResourceViewFromFile(device, fileName, NULL, NULL, &m_texture, NULL);
	if (FAILED(result)) {
		return false;
	}

	return true;
}

void TextureClass::shutdown() {
	if (m_texture) {
		m_texture->Release();
		m_texture = 0;
	}
	return;
}


ID3D11ShaderResourceView* TextureClass::getTexture() {
	return m_texture;
}