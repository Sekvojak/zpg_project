#pragma once

struct Material
{
	float ra;
	float rd;
	float rs;
	float h;

	Material(float ra_ = 0.07f, float rd_ = 1.0f, float rs_ = 0.3f, float h_ = 32.0f) {
		ra = ra_;
		rd = rd_;
		rs = rs_;
		h = h_;
	}
};