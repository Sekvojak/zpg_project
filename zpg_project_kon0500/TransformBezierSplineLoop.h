#pragma once
#include "TransformBezierSpline.h"

class TransformBezierSplineLoop : public TransformBezierSpline
{
public:
    using TransformBezierSpline::TransformBezierSpline;

    void update(float dt) override {
        t += speed * dt;
        if (t >= 1.0f) t = 0.0f;
    }
};
