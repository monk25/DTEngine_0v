#pragma once
#include "pch.h"

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

inline int random(int to, int from)
{
	
}

inline float random(float to, float from)
{

}