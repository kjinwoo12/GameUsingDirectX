#pragma once

#include<D3D11.h>
#include<D3DX10math.h>
#include<fstream>
using namespace std;

#include"TextureClass.h"

class ModelClass {
private:
	struct VertexType {
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
		D3DXVECTOR3 normal;
	};

	struct ModelType {
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	ModelClass();
	~ModelClass();

	bool initialize(ID3D11Device*, char*, WCHAR*);
	void shutdown();
	void render(ID3D11DeviceContext*);

	int getIndexCount();

	ID3D11ShaderResourceView* getTexture();

private:
	bool initializeBuffers(ID3D11Device*);
	void shutdownBuffers();
	void renderBuffers(ID3D11DeviceContext*);

	bool loadTexture(ID3D11Device*, WCHAR*);
	void releaseTexture();
	bool loadModel(char*);
	void releaseModel();

	ID3D11Buffer *m_pVertexBuffer, *m_pIndexBuffer;
	int m_vertexCount, m_indexCount;

	TextureClass* m_pTexture;
	ModelType* m_pModel;
};

