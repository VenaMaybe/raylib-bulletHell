#pragma once
#include "IGunBehavior.h"
#include "audioBit.h"

//
// Bullet Behaviors
//

class StraightBulletBehavior : public IBulletBehavior {
public:
	StraightBulletBehavior();
	std::function<void(Bullet&, float)> getBehaviorFunction() const override;

private:
	std::function<void(Bullet&, float)> behavior;
};

class ZigzagBulletBehavior : public IBulletBehavior {
public:
	ZigzagBulletBehavior();
	std::function<void(Bullet&, float)> getBehaviorFunction() const override;
	
private:
	std::function<void(Bullet&, float)> behavior;
};

//
// Ammo Behaviors
//

class UnlimitedAmmoBehavior : public IAmmoBehavior {
public:
	bool canFire(const Gun& gun) const override;
	void consumeAmmo(Gun& gun) override;
	void reloadAmmo(Gun& gun) override;
};

//
// Gun Behaviors
//

// Just shoots 1 shot
class SingleShotShooting : public IGunBehavior {
	SingleShotShooting();
	void shoot(Gun& gun, const IBulletBehavior& bulletBehavior) override;
};

// Shoot x shots with t duration and s spread 
// class MultiShotShooting : public IGunBehavior {
// 	MultiShotShooting();
// 	void shoot(Gun& gun, const IBulletBehavior& bulletBehavior) override;
// };


// How a pistol that shoots one bullet at a time behaves
class PistolBehavior : public IGunBehavior {
public:
	PistolBehavior();

	void shoot(Gun& gun, const IBulletBehavior& bulletBehavior) override;

private:
	int maxBullets = 10;					// Ammo Behavior

	float bulletSpeed = 1000.f;				// Bullet Behavior
	float maxBulletAge = 3.f;				// Bullet Behavior
	float percentOfOwnerVelocity = 0.15f; 	// Bullet Behavior    // Todo: Change this based on speed of bullet!!!

	float recoilPercent = 2.f;				// Impact Behavior
	AudioBit gunSound;						// Impact Behavior
};

