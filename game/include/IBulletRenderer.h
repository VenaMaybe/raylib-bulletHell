#pragma once

// Forward declaration of bullet
class Bullet;

class IBulletRenderer {
public:
	virtual ~IBulletRenderer() = default;
	virtual void render(const Bullet& bullet) const = 0;

	// get getRenderOnCollisionFunction()
};