#pragma once
#include<D3D11.h>
#include<D3DX11tex.h>


class TextureClass {
public:
	TextureClass();
	~TextureClass();

	bool initialize(ID3D11Device*, WCHAR*);
	void shutdown();

	ID3D11ShaderResourceView* getTexture();

private:
	ID3D11ShaderResourceView* m_pTexture;
};

