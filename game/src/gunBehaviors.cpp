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

//
//
//

PistolBehavior::PistolBehavior()
	: gunSound("game/sounds/gunEx1.wav")
{}

void PistolBehavior::shoot(Gun& gun, const IBulletBehavior& bulletBehavior) {
	std::cout << "Shoot Clicked\n";

	IAmmoBehavior* ammoBehavior = gun.getAmmoBehavior();

	const int& currentBullets = gun.bullets->size();
	const auto& owner = gun.getOwner();

	// Can fire
	if (ammoBehavior->canFire(gun)) {
		std::cout << "Bullet Added, current count: " << currentBullets << "\n";
		gunSound.playSound();

		Velocity bulletVel = (owner->getDir()) + (owner->getVel() * percentOfOwnerVelocity);

		// Recoil
		Velocity playerVelDueToRecoil(0, 0); // Some percent of the velocity goes into the player
		playerVelDueToRecoil = -Velocity(Vector2Lerp(playerVelDueToRecoil, bulletVel, recoilPercent));
		owner->setVel((owner->getVel() + playerVelDueToRecoil)); // Add the recoil to the player's velocity

		std::cout << bulletBehavior.getBulletSpeed() << "\t" << bulletBehavior.getMaxBulletAge() << std::endl;

		// Add the bullet to be simulated to list of bullets
		gun.bullets->emplace_back(
			gun.posMuzzle,	// Spawn Location
			bulletVel,		// Velocity
			bulletBehavior.getBulletSpeed(),		// Speed of bullet
			bulletBehavior.getMaxBulletAge(),		// Duration of Bullet
			bulletBehavior.getBehaviorFunction()	// Callback to define behavior
		);

		// Consume 1 ammo
		ammoBehavior->consumeAmmo(gun, 1);
	}
}