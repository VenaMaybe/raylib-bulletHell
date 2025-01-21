#pragma once
#include <functional>

// Forward Declaration of Bullet
class Bullet;

// Define behavior of the bullet fired, e.g. bullet velocity and max bullet age
class IBulletBehavior {
public:
	virtual ~IBulletBehavior() = default;

	// Get bullet behavior, returns a function with inputs bullet and dt
	virtual std::function<void(Bullet&, float)> getBehaviorFunction() const = 0;

	// Required to construct a bullet
	float getBulletSpeed() const { return bulletSpeed; }
	float getMaxBulletAge() const { return maxBulletAge; }

	// An identification method
	virtual const char* name() const { return behaviorName; }

protected:
	// Forcing these variables to be initalized or else
	IBulletBehavior(const char* name, float speed, float ageLimit)
		: behaviorName(name), bulletSpeed(speed), maxBulletAge(ageLimit) {}

private:
	const char* behaviorName;
	float bulletSpeed;
	float maxBulletAge;
};

