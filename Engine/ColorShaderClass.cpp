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

	//�������� ����� ���̴��� ���ڸ� �Է��մϴ�.
	result = setShaderParameters(deviceContext, worldMatrix, viewMatrix, projectionMatrix);
	if (!result) {
		return false;
	}

	//���̴��� �̿��Ͽ� �غ�� ���۸� �׸��ϴ�.
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

	//���� ���̴� ������
	result = D3DX11CompileFromFile(vsFileName, NULL, NULL, "ColorVertexShader", "vs_5_0", D3D10_SHADER_ENABLE_STRICTNESS, 0, NULL,
																 &vertexShaderBuffer, &errorMessage, NULL);
	if (FAILED(result)) {
		if (errorMessage) {
			outputShaderErrorMessage(errorMessage, hwnd, vsFileName);
		} else {
			MessageBox(hwnd, vsFileName, L"Missing Shader File", MB_OK);
		}
	}

	//�ȼ� ���̴� ������
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

	//���� �Է� ���̾ƿ� description �ۼ�
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

	//���̾ƿ� ��� ���� ����
	numElements = sizeof(polygonLayout) / sizeof(polygonLayout[0]);

	//���� �Է� ���̾ƿ� ����
	result = device->CreateInputLayout(polygonLayout, numElements, vertexShaderBuffer->GetBufferPointer(),
																		 vertexShaderBuffer->GetBufferSize(), &m_layout);

	if (FAILED(result)) {
		cout << "���� �Է� ���̾ƿ� ���� ����";
		return false;
	}

	//�ڿ� ����
	vertexShaderBuffer->Release();
	vertexShaderBuffer = 0;

	pixelShaderBuffer->Release();
	pixelShaderBuffer = 0;


	//���� ���̴��� �ִ� ��� ��� ������ description �� �ۼ�
	matrixBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	matrixBufferDesc.ByteWidth = sizeof(MatrixBufferType);
	matrixBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	matrixBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	matrixBufferDesc.MiscFlags = 0;
	matrixBufferDesc.StructureByteStride = 0;

	result = device->CreateBuffer(&matrixBufferDesc, NULL, &m_matrixBuffer);
	if (FAILED(result)) {
		cout << "��� ���� ���� ����";
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

	//��� ������ ������ �� �� �ֵ��� ��޴ϴ�.
	result = deviceContext->Map(m_matrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) {
		return false;
	}

	//��� ������ �����Ϳ� ���� �����͸� �����ɴϴ�.
	dataPtr = (MatrixBufferType*)mappedResource.pData;
	
	//��� ���ۿ� ����� �����մϴ�.
	dataPtr->world = worldMatrix;
	dataPtr->view = viewMatrix;
	dataPtr->projection = projectionMatrix;

	//��� ������ ����� Ǳ�ϴ�.
	deviceContext->Unmap(m_matrixBuffer, 0);

	//���� ���̴������� ��� ������ ��ġ�� �����մϴ�.
	bufferNumber = 0;

	//���� ���̴��� ��� ���۸� �ٲ� ������ �ٲߴϴ�
	deviceContext->VSSetConstantBuffers(bufferNumber, 1, &m_matrixBuffer);

	return true;
}

void ColorShaderClass::renderShader(ID3D11DeviceContext* deviceContext, int indexCount) {
	//���� �Է� ���̾ƿ��� �����մϴ�.
	deviceContext->IASetInputLayout(m_layout);

	//�ﰢ���� �׸� ���� ���̴��� �ȼ� ���̴��� �����մϴ�.
	deviceContext->VSSetShader(m_vertexShader, NULL, 0);
	deviceContext->PSSetShader(m_pixelShader, NULL, 0);

	//�ﰢ���� �׸��ϴ�.
	deviceContext->DrawIndexed(indexCount, 0, 0);

	return;
}