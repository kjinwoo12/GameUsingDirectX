#pragma once
#include<D3D11.h>
#include<D3DX10math.h>
#include<D3DX11async.h>
#include<fstream>
using namespace std;

class LightShaderClass {
private:
	struct MatrixBufferType {
		D3DXMATRIX world;
		D3DXMATRIX view;
		D3DXMATRIX projection;
	};

	struct CameraBufferType {
		D3DXVECTOR3 cameraPosition;
		float padding;
	};

	struct LightBufferType {
		D3DXVECTOR4 ambientColor;
		D3DXVECTOR4 diffuseColor;
		D3DXVECTOR3 lightDirection;
		float specularPower;
		D3DXVECTOR4 specularColor;
	};

public:
	LightShaderClass();
	~LightShaderClass();

	bool initialize(ID3D11Device*, HWND);
	void shutdown();
	bool render(ID3D11DeviceContext*,
							int,
							D3DXMATRIX,
							D3DXMATRIX,
							D3DXMATRIX,
							ID3D11ShaderResourceView*,
							D3DXVECTOR3,
							D3DXVECTOR4,
							D3DXVECTOR4,
							D3DXVECTOR3,
							D3DXVECTOR4,
							float);

private:
	bool initializeShader(ID3D11Device*, HWND, WCHAR*, WCHAR*);
	void shutdownShader();
	void outputShaderErrorMessage(ID3D10Blob*, HWND, WCHAR*);

	bool setShaderParameters(ID3D11DeviceContext*,
													 D3DXMATRIX,
													 D3DXMATRIX,
													 D3DXMATRIX,
													 ID3D11ShaderResourceView*,
													 D3DXVECTOR3, 
													 D3DXVECTOR4,
													 D3DXVECTOR4,
													 D3DXVECTOR3,
													 D3DXVECTOR4,
													 float);
	void renderShader(ID3D11DeviceContext*, int);

	ID3D11VertexShader* m_vertexShader;
	ID3D11PixelShader* m_pixelShader;
	ID3D11InputLayout* m_layout;
	ID3D11SamplerState* m_sampleState;
	ID3D11Buffer* m_matrixBuffer;
	ID3D11Buffer* m_cameraBuffer;
	ID3D11Buffer* m_lightBuffer;
};