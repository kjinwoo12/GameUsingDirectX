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

bool ColorShaderClass::render(ID3D11DeviceContext* deviceContext, int indexCount, D3DXMATRIX worldMatrix, D3DXMATRIX viewMatrix,
															D3DXMATRIX projectionMatrix) {
	bool result;

	//렌더링에 사용할 셰이더의 인자를 입력합니다.
	result = setShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	if (!result) {
		return false;
	}

	//셰이더를 이용하여 준비된 버퍼를 그립니다.
	renderShader(deviceContext, indexCount);

	return true;
}

bool ColorShaderClass::initializeShader(ID3D11Device* device, HWND hwnd, WCHAR* vsFileName, WCHAR* psFileName) {
	HRESULT result;
	ID3D10Blob* errorMessage = 0;
	ID3D10Blob* vertexShaderBuffer = 0;
	ID3D10Blob* pixelShaderBuffer = 0;

	D3D11_INPUT_ELEMENT_DESC polygonLayout[2];
	unsigned int numElements;
	D3D11_BUFFER_DESC matrixBufferDesc;

	//정점 셰이더 컴파일
	result = D3DX11CompileFromFile(vsFileName, NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL,
																 &vertexShaderBuffer, &errorMessage, NULL);
	if (FAILED(result)) {
		if (errorMessage) {
			outputShaderErrorMessage(errorMessage, hwnd, vsFileName);
		} else {
			MessageBox(hwnd, vsFileName, L"Missing Shader File", MB_OK);
		}
	}

	//픽셀 셰이더 컴파일
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

	result = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(), NULL, &m_pixelShader);
	if (FAILED(result)) {
		return false;
	}

	//정점 입력 레이아웃 description 작성
	polygonLayout[0].SemanticName = "POSITION";
	polygonLayout[0].SemanticIndex = 0;
	polygonLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
	polygonLayout[0].InputSlot = 0;
	polygonLayout[0].AlignedByteOffset = 0;
	polygonLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[0].InstanceDataStepRate = 0;

	polygonLayout[1].SemanticName = "COLOR";
	polygonLayout[1].SemanticIndex = 0;
	polygonLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	polygonLayout[1].InputSlot = 0;
	polygonLayout[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	polygonLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	polygonLayout[1].InstanceDataStepRate = 0;

	//레이아웃 요소 갯수 저장
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	//정점 입력 레이아웃 생성
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
																		 vertexShaderBuffer->GetBufferSize(), &m_layout);

	if (FAILED(result)) {
		cout << "정점 입력 레이아웃 생성 실패";
		return false;
	}

	//자원 해제
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;


	//정점 셰이더에 있는 행렬 상수 버퍼의 description 을 작성
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result)) {
		cout << "상수 버퍼 생성 실패";
		return false;
	}

	return true;
}


void ColorShaderClass::shutdownShader() {
	if (m_matrixBuffer) {
		m_matrixBuffer->Release();
		m_matrixBuffer = 0;
	}

	if (m_layout) {
		m_layout->Release();
		m_layout = 0;
	}

	if (m_pixelShader) {
		m_pixelShader->Release();
		m_pixelShader = 0;
	}

	if (m_vertexShader) {
		m_vertexShader->Release();
		m_vertexShader = 0;
	}

	return;
}


void ColorShaderClass::outputShaderErrorMessage(ID3D10Blob* errorMessage, HWND hwnd, WCHAR* shaderFileName) {
	char* compileErrors;
	unsigned long bufferSize, i;
	ofstream fout;

	compileErrors = (char*)(errorMessage->GetBufferPointer());

	bufferSize = errorMessage->GetBufferSize();

	fout.open("shader-error.txt");

	for (i = 0; i < bufferSize; i++) {
		fout << compileErrors[i];
	}

	fout.close();

	errorMessage->Release();
	errorMessage = 0;

	MessageBox(hwnd, L"Error compiling shader. Check shader-error.txt for message", shaderFileName, MB_OK);
}

bool ColorShaderClass::setShaderParameters(ID3D11DeviceContext* deviceContext,
																					 D3DXMATRIX worldMatrix,
																					 D3DXMATRIX viewMatrix,
																					 D3DXMATRIX projectionMatrix) {
	HRESULT result;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	MatrixBufferType* dataPtr;
	unsigned int bufferNumber;

	D3DXMatrixTranspose(&worldMatrix, &worldMatrix);
	D3DXMatrixTranspose(&viewMatrix, &viewMatrix);
	D3DXMatrixTranspose(&projectionMatrix, &projectionMatrix);

	//상수 버퍼의 내용을 쓸 수 있도록 잠급니다.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) {
		return false;
	}

	//상수 버퍼의 데이터에 대한 포인터를 가져옵니다.
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	
	//상수 버퍼에 행렬을 복사합니다.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	//상수 버퍼의 잠금을 풉니다.
	deviceContext->Unmap(m_matrixBuffer, 0);

	//정점 셰이더에서의 상수 버퍼의 위치를 설정합니다.
	bufferNumber = 0;

	//정점 셰이더의 상수 버퍼를 바뀐 값으로 바꿉니다
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	return true;
}

void ColorShaderClass::renderShader(ID3D11DeviceContext* deviceContext, int indexCount) {
	//정점 입력 레이아웃을 설정합니다.
	deviceContext->IASetInputLayout(m_layout);

	//삼각형을 그릴 정점 셰이더와 픽셸 셰이더를 설정합니다.
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	//삼각형을 그립니다.
	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}