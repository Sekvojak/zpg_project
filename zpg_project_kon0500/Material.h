#pragma once
#include "Texture.h"

struct Material
{
	float ra;
	float rd;
	float rs;
	float h;
	Texture* texture = nullptr;

	Material(float ra_ = 0.08f, float rd_ = 1.0f, float rs_ = 0.3f, float h_ = 1.0f) {
		ra = ra_;
		rd = rd_;
		rs = rs_;
		h = h_;
	}
};