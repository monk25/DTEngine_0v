#pragma once
#include "Define.h"
#include "TextureClass.h"

class BitmapClass
{
private:
	struct VertexType
	{
		D3DXVECTOR3 position;
		D3DXVECTOR2 texture;
	};

public:
	BitmapClass(ID3D11Device*, int, int, WCHAR*, int, int);
	BitmapClass(const BitmapClass&);
	~BitmapClass();

	bool render(ID3D11DeviceContext*, int, int);

	int getIndexCount();

private:
	bool initializeBuffers(ID3D11Device*);
	void shutdownBuffers();
	bool updateBuffers(ID3D11DeviceContext*, int, int);
	void renderBuffers(ID3D11DeviceContext*);

	bool loadTexture(WCHAR*);

private:
	ID3D11Buffer* _vertexBuffer, * _indexBuffer;
	int _vertexCount, _indexCount;

	int _screenWidth, _screenHeight;
	int _bitmapWidth, _bitmapHeight;
	int _previousPosX, _previousPosY;

public:
	TextureClass* _texture;
};

