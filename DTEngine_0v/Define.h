#pragma once
#include "pch.h"

#if defined(DEBUG) | defined(_DEBUG)
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLE = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class Rect :
	public RECT
{
public:
	Rect() {
		left = top = right = bottom = 0;
	}

	Rect(int left, int top, int right, int bottom) {
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
	}

	bool intersectsRect(Rect rect) {
		Rect tmpRect;
		return IntersectRect(&tmpRect, this, &rect);
	}

	bool intersectRect(Rect rect, D3DXVECTOR2 pos) {
		Rect tmpRect;
		return IntersectRect(&tmpRect, this, &rect.offset(pos));
	}

	Rect offset(D3DXVECTOR2 pos) {
		Rect r = *this;
		r.left += pos.x;
		r.top += pos.y;
		r.right += pos.x;
		r.bottom += pos.y;
		return r;
	}

	int width() {
		return right - left;
	}

	int height() {
		return bottom - top;
	}

	D3DXVECTOR2 center() {
		return D3DXVECTOR2(width(), height()) / 2;
	}
};

inline float pita(D3DXVECTOR2 v1, D3DXVECTOR2 v2)
{
	return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
}

inline float angle(D3DXVECTOR2 v1, D3DXVECTOR2 v2)
{
	return atan2(v2.y - v1.y, v2.x - v1.x);
}

inline int random(int from, int to)
{
	static default_random_engine d(timeGetTime());
	uniform_int_distribution<int> random(from, to);
	return random(d);
}

inline float random(float from, float to)
{
	static default_random_engine d(timeGetTime());
	uniform_real_distribution<float> random(from, to);
	return random(d);
}