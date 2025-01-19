#pragma once
#include "IBulletBehavior.h"

//
// Bullet Behaviors
//

class StraightBulletBehavior : public IBulletBehavior {
public:
	StraightBulletBehavior(float bulletSpeed = 1000.f, float maxBulletAge = 3.f);
	std::function<void(Bullet&, float)> getBehaviorFunction() const override;

private:
	std::function<void(Bullet&, float)> behavior;
};

class ZigzagBulletBehavior : public IBulletBehavior {
public:
	ZigzagBulletBehavior(float bulletSpeed = 1000.f, float maxBulletAge = 3.f);
	std::function<void(Bullet&, float)> getBehaviorFunction() const override;
	
private:
	std::function<void(Bullet&, float)> behavior;
};
