#include "gun.h"
#include "gunBehaviors.h"
#include "IAmmoBehavior.h"
#include <iostream>

/////////////////////////////////////////

SingleShotShooting::SingleShotShooting() {}

void SingleShotShooting::shoot(Gun& gun, const IBulletBehavior& bulletBehavior) {
	// Get a possibly existing pointer to ammo behavior
	IAmmoBehavior* ammoBehavior = gun.getAmmoBehavior();
	if (!ammoBehavior || !ammoBehavior->canFire(gun)) { return; }

	// We get the owner to apply recoil
	const auto& owner = gun.getOwner();
	if (!owner) { return; }

	// Initial bullet velocity in direction of owner
	Velocity baseVel = owner->getDir();

	// Add the bullet to be simulated to list of bullets
	Bullet newBullet (
		gun.posMuzzle,	// Spawn Location
		baseVel,		// Velocity
		bulletBehavior.getBulletSpeed(),		// Speed of bullet
		bulletBehavior.getMaxBulletAge(),		// Duration of Bullet
		bulletBehavior.getBehaviorFunction()	// Callback to define behavior
	);

	// Set the shooter so doesn't collide with self
	newBullet.setShooter(owner.get());

	// Apply each bullet modifier in sequence // Todo: Later add a flag for specified order
	for (auto& modifier : bulletModifiers) {
		modifier->modifyBullet(newBullet, gun, bulletBehavior);
	}

	// Add bullet to the gun's bullets list
	gun.bullets->push_back(std::move(newBullet));

	// Consume 1 ammo
	ammoBehavior->consumeAmmo(gun, 1);

	// Todo: Also move this to it's own thing that happens after!
	// Apply each effect in sequence // Todo: Later also add flag for ordering
	for (auto& effect : effects) {
		effect->apply(gun);
	}
}

//	void MultiShotShooting::shoot(Gun& gun) {
//		
//	}