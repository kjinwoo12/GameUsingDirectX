#include "ColorShaderClass.h"



ColorShaderClass::ColorShaderClass() {
	m_vertexShader = 0;
	m_pixelShader = 0;
	m_layout = 0;
	m_matrixBuffer = 0;
}


ColorShaderClass::~ColorShaderClass() {
}

bool ColorShaderClass::initialize(ID3D11Device* device, HWND hwnd) {
	bool result;

	result = initializeShader(device, hwnd, L"../Engine/color.vs", L"../Engine/color.ps");
	if (!result) {
		return false;
	}

	return true;
}

void ColorShaderClass::shutdown() {
	shutdownShader();
	return;
}

bool ColorShaderClass::initializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFileName, WCHAR* psFileName) {
	HRESULT result;
	ID3D10Blob* errorMessage = 0;
	ID3D10Blob* vertexShaderBuffer = 0;
	ID3D10Blob* pixelShaderBuffer = 0;

	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	//Á¤Á¡ ¼ÎÀÌ´õ ÄÄÆÄÀÏ
	result = D3DX11CompileFromFile(vsFileName, NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL,
																 &vertexShaderBuffer, &errorMessage, NULL);
	if (FAILED(result)) {
		if (errorMessage) {
			outputShaderErrorMessage(errorMessage, hwnd, vsFileName);
		} else {
			MessageBox(hwnd, vsFileName, L"Missing Shader File", MB_OK);
		}
	}

	//ÇÈ¼¿ ¼ÎÀÌ´õ ÄÄÆÄÀÏ
	result = D3DX11CompileFromFile(psFileName, NULL, NULL, "ColorPixelShader", "ps_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL,
																 &pixelShaderBuffer, &errorMessage, NULL);
	if (FAILED(result)) {
		if (errorMessage) {
			outputShaderErrorMessage(errorMessage, hwnd, psFileName);
		} else {
			MessageBox(hwnd, psFileName, L"Missing Shader File", MB_OK);
		}
		return false;
	}
	
	result = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(), NULL, &m_vertexShader);
	if (FAILED(result)) {
		return false;
	}

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);)
}