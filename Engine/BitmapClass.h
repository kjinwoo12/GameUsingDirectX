#pragma once

#include <D3D11.h>
#include <d3dx10math.h>

#include "TextureClass.h"

class BitmapClass {
private:
	struct VertexType {
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};
public:
	BitmapClass();
	~BitmapClass();

	bool initialize(ID3D11Device*, int, int, WCHAR*, int, int);
	void shutdown();
	bool render(ID3D11DeviceContext*, int, int);

	int getIndexCount();
	ID3D11ShaderResourceView* getTexture();
private:
	bool initializeBuffers(ID3D11Device*);
	void shutdownBuffers();
	bool updateBuffers(ID3D11DeviceContext*, int, int);
	void renderBuffers(ID3D11DeviceContext*);

	bool loadTexture(ID3D11Device*, WCHAR*);
	void releaseTexture();


	ID3D11Buffer *m_pVertexBuffer, *m_pIndexBuffer;
	int m_vertexCount, m_indexCount;
	TextureClass *m_pTexture;

	int m_screenWidth, m_screenHeight;
	int m_bitmapWidth, m_bitmapHeight;
	int m_previousPosX, m_previousPosY;
};

