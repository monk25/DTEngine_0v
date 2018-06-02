#pragma once
#include "Define.h"

class CameraClass
{
public:
	CameraClass();
	CameraClass(const CameraClass&);
	~CameraClass();
	
	void setPosition(float, float, float);
	void setRotation(float, float, float);

	D3DXVECTOR3 getPosition();
	D3DXVECTOR3 getRotation();

	void render();

public:
	float _positionX, _positionY, _positionZ;
	float _rotationX, _rotationY, _rotationZ;
	D3DXMATRIX _viewMatrix;
};

