#pragma once

#include "IBulletRenderer.h"

class BasicCircleRenderer : public IBulletRenderer {
public:
	virtual void render(const Bullet& bullet) const override;
};

class BasicCircleAndSplineRenderer : public IBulletRenderer {
public:
	virtual void render(const Bullet& bullet) const override;
};