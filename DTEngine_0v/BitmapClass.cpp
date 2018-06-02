#include "pch.h"
#include "BitmapClass.h"
#include "Asset.h"


BitmapClass::BitmapClass(ID3D11Device* device, int screenWidth, int screenHeight, WCHAR* textureFilename, int bitmapWidth, int bitmapHeight) :
	_screenWidth(screenWidth), _screenHeight(screenHeight), _bitmapWidth(bitmapWidth), _bitmapHeight(bitmapHeight), _previousPosX(-1), _previousPosY(-1)
{
	initializeBuffers(device);
	loadTexture(textureFilename);
}

BitmapClass::BitmapClass(const BitmapClass& other)
{
}

BitmapClass::~BitmapClass()
{
	shutdownBuffers();
}

bool BitmapClass::render(ID3D11DeviceContext* deviceContext, int positionX, int positionY)
{
	bool result;

	result = updateBuffers(deviceContext, positionX, positionY);
	if (!result) {
		return false;
	}

	renderBuffers(deviceContext);

	return true;
}

int BitmapClass::getIndexCount()
{
	return _indexCount;
}

bool BitmapClass::initializeBuffers(ID3D11Device* device)
{
	VertexType* vertices;
	unsigned long* indices;
	D3D11_BUFFER_DESC vertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, indexData;
	HRESULT result;

	_vertexCount = 6;
	_indexCount = _vertexCount;

	vertices = new VertexType[_vertexCount];
	if (!vertices) {
		return false;
	}

	indices = new unsigned long[_indexCount];
	if (!indices) {
		return false;
	}

	memset(vertices, 0, (sizeof(VertexType) * _vertexCount));

	for (int i = 0; i < _indexCount; i++) {
		indices[i] = i;
	}

	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * _vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;

	vertexData.pSysMem = vertices;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &_vertexBuffer);
	if (FAILED(result)) {
		return false;
	}

	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * _indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	result = device->CreateBuffer(&indexBufferDesc, &indexData, &_indexBuffer);
	if (FAILED(result)) {
		return false;
	}

	delete[] vertices;
	vertices = nullptr;

	delete[] indices;
	indices = nullptr;

	return true;
}

void BitmapClass::shutdownBuffers()
{
	if (_indexBuffer) {
		_indexBuffer->Release();
		_indexBuffer = nullptr;
	}

	if (_vertexBuffer) {
		_vertexBuffer->Release();
		_vertexBuffer = nullptr;
	}

	return;
}

bool BitmapClass::updateBuffers(ID3D11DeviceContext* deviceContext, int positionX, int positionY)
{
	float left, right, top, bottom;
	VertexType* vertices;
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	VertexType* verticesPtr;
	HRESULT result;

	if ((positionX == _previousPosX) && positionY == _previousPosY) {
		return true;
	}

	_previousPosX = positionX;
	_previousPosY = positionY;

	left = (float)((_screenWidth / 2) * -1) + (float)positionX;
	right = left + (float)_bitmapWidth;
	top = (float)(_screenHeight / 2) - (float)positionY;
	bottom = top - (float)_bitmapHeight;

	vertices = new VertexType[_vertexCount];
	if (!vertices) {
		return false;
	}

	vertices[0].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[0].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[1].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[1].texture = D3DXVECTOR2(1.0f, 1.0f);

	vertices[2].position = D3DXVECTOR3(left, bottom, 0.0f);
	vertices[2].texture = D3DXVECTOR2(0.0f, 1.0f);

	vertices[3].position = D3DXVECTOR3(left, top, 0.0f);
	vertices[3].texture = D3DXVECTOR2(0.0f, 0.0f);

	vertices[4].position = D3DXVECTOR3(right, top, 0.0f);
	vertices[4].texture = D3DXVECTOR2(1.0f, 0.0f);

	vertices[5].position = D3DXVECTOR3(right, bottom, 0.0f);
	vertices[5].texture = D3DXVECTOR2(1.0f, 1.0f);

	result = deviceContext->Map(_vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	if (FAILED(result)) {
		return false;
	}

	verticesPtr = (VertexType*)mappedResource.pData;

	memcpy(verticesPtr, (void*)vertices, (sizeof(VertexType) * _vertexCount));

	deviceContext->Unmap(_vertexBuffer, 0);

	delete[] vertices;
	vertices = nullptr;

	return true;
}

void BitmapClass::renderBuffers(ID3D11DeviceContext* deviceContext)
{
	unsigned int stride;
	unsigned int offset;

	stride = sizeof(VertexType);
	offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &_vertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(_indexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return;
}

bool BitmapClass::loadTexture(WCHAR* filename)
{
	_texture = asset.getTexture(filename);

	return true;
}