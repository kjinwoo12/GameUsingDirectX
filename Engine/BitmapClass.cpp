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

	m_previousPosY = -1;
	m_previousPosY = -1;

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

void BitmapClass::shutdown() {
	releaseTexture();
	shutdownBuffers();
	return;
}

bool BitmapClass::render(ID3D11DeviceContext* deviceContext, int positionX, int positionY) {
	bool result;

	result = updateBuffers(deviceContext, positionX, positionY);
	if (!result) {
		return false;
	}

	renderBuffers(deviceContext);

	return true;
}

int BitmapClass::getIndexCount() {
	return m_indexCount;
}

ID3D11ShaderResourceView* BitmapClass::getTexture() {
	return m_texture->getTexture();
}

bool BitmapClass::initializeBuffers(ID3D11Device* device) {
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	m_vertexCount = 6;

	m_indexCount = m_vertexCount;

	vertices = new VertexType[m_vertexCount];
	if (!vertices) {
		return false;
	}

	indices = new unsigned long[m_indexCount];
	if (!indices) {
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType) * m_vertexCount));

	for (int i = 0; i < m_indexCount; i++) {
		indices[i] = i;
	}

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
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
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result)) {
		return false;
	}

	delete[] vertices;
	indices = 0;

	delete[] indices;
	indices = 0;

	return true;
}

void BitmapClass::shutdownBuffers() {
	if (m_indexBuffer) {
		m_indexBuffer->Release();
		m_indexBuffer = 0;
	}

	if (m_vertexBuffer) {
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}
}

bool BitmapClass::updateBuffers(ID3D11DeviceContext* deviceContext, int positionX, int positionY) {
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;

	if ((positionX == m_previousPosX) && (positionY == m_previousPosY)) {
		return true;
	}

	m_previousPosX = positionX;
	m_previousPosY = positionY;

	left = (float)((m_screenWidth / 2) *-1) + (float)positionX;
	right = left + (float)m_bitmapWidth;
	top = (float)(m_screenHeight / 2) - (float)positionY;
	bottom = top - (float) m_bitmapHeight;

	vertices = new VertexType[m_vertexCount];
	if (!vertices) {
		return false;
	}

	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.f, 0.f);
	vertices[1].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[1].texture = D3DXVECTOR2(1.f, 1.f);
	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);
	vertices[2].texture = D3DXVECTOR2(0.f, 1.f);
	vertices[3].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[3].texture = D3DXVECTOR2(0.f, 0.f);
	vertices[4].position = D3DXVECTOR3(right, top, 0.0f);
	vertices[4].texture = D3DXVECTOR2(1.f, 0.f);
	vertices[5].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[5].texture = D3DXVECTOR2(1.f, 1.f);

	result = deviceContext->Map(m_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) {
		return false;
	}
	verticesPtr = (VertexType*)mappedResource.pData;

	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * m_vertexCount));

	deviceContext->Unmap(m_vertexBuffer, 0);

	delete[] vertices;
	vertices = 0;

	return true;
}


void BitmapClass::renderBuffers(ID3D11DeviceContext* deviceContext) {
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool BitmapClass::loadTexture(ID3D11Device* device, WCHAR* fileName) {
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

void BitmapClass::releaseTexture() {
	if (m_texture) {
		m_texture->shutdown();
		delete m_texture;
		m_texture = 0;
	}

	return;
}

