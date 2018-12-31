#include "ModelClass.h"



ModelClass::ModelClass() {
	m_vertexBuffer = 0;
	m_indexBuffer = 0;
	m_texture = 0;
	m_model = 0;
}


ModelClass::~ModelClass() {
}


bool ModelClass::initialize(ID3D11Device* device, 
														char* modelFileName,
														WCHAR* textureFileName) {
	bool result;

	result = loadModel(modelFileName);
	if (!result) {
		return false;
	}

	result = initializeBuffers(device);
	if (!result) {
		return false;
	}

	result = loadTexture(device, textureFileName);
	if (!result) {
		return false;
	}

	return true;
}


void ModelClass::shutdown() {
	releaseTexture();
	shutdownBuffers();
	releaseModel();
	return;
}

void ModelClass::render(ID3D11DeviceContext* deviceContext) {	
	renderBuffers(deviceContext);
	return;
}


int ModelClass::getIndexCount() {
	return m_indexCount;
}

ID3D11ShaderResourceView* ModelClass::getTexture() {
	return m_texture->getTexture();
}


bool ModelClass::initializeBuffers(ID3D11Device* device) {
	VertexType* vertices;
	unsigned long *indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	vertices = new VertexType[m_vertexCount];
	if (!vertices) {
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if (!indices) {
		return false;
	}

	//Load the vertex array and index array with data.
	for (int i = 0; i < m_vertexCount; i++) {
		vertices[i].position = D3DXVECTOR3(m_model[i].x,
																			 m_model[i].y,
																			 m_model[i].z);
		vertices[i].texture = D3DXVECTOR2(m_model[i].tu,
																			m_model[i].tv);
		vertices[i].normal = D3DXVECTOR3(m_model[i].nx,
																		 m_model[i].ny,
																		 m_model[i].nz);
		indices[i] = i;
	}
	
	vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = 0;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result)) {
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) *m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result)) {
		return false;
	}

	delete[] vertices;
	vertices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void ModelClass::shutdownBuffers() 	{
	if (m_indexBuffer) {
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer) {
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}

void ModelClass::renderBuffers(ID3D11DeviceContext* deviceContext) {
	unsigned int stride = sizeof(VertexType);
	unsigned int offset = 0;

	//input assembler에 정점 버퍼를 활성화하여 그려질 수 있게 합니다.
	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);

	//input assembler에 인덱스 버퍼를 활성화하여 그려질 수 있게 합니다.
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	//정점 버퍼로 그릴 기본형을 설정합니다. 삼각형
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}


bool ModelClass::loadTexture(ID3D11Device* device, WCHAR* fileName) {
	bool result;

	m_texture = new TextureClass;
	if (!m_texture) {
		return false;
	}

	result = m_texture->initialize(device, fileName);
	if (!result) {
		return false;
	}
	
	return true;
}


void ModelClass::releaseTexture() {
	if (m_texture) {
		m_texture->shutdown();
		delete m_texture;
		m_texture = 0;
	}
	
	return;
}

bool ModelClass::loadModel(char* fileName) {
	ifstream fin;
	char input;
	int i;

	fin.open(fileName);
	if (fin.fail()) {
		return false;
	}

	//Read up to the value of vertex count.
	fin.get(input);
	while (input != ':') {
		fin.get(input);
	}
	//Read in the vertex count;
	fin >> m_vertexCount;

	m_indexCount = m_vertexCount;

	m_model = new ModelType[m_vertexCount];
	if (!m_model) {
		return false;
	}

	fin.get(input);
	while (input != ':') {
		fin.get(input);
	}
	fin.get(input);
	fin.get(input);

	for (int i = 0; i < m_vertexCount; i++) {
		fin >> m_model[i].x >> m_model[i].y >> m_model[i].z;
		fin >> m_model[i].tu >> m_model[i].tv;
		fin >> m_model[i].nx >> m_model[i].ny >> m_model[i].nz;
	}

	fin.close();

	return true;
}

void ModelClass::releaseModel() {
	if (m_model) {
		delete[] m_model;
		m_model = 0;
	}

	return;
}