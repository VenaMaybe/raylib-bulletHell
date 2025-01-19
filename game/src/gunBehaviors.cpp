#include "gun.h"
#include "gunBehaviors.h"
#include "IAmmoBehavior.h"
#include <iostream>

/////////////////////////////////////////

void SingleShotShooting::shoot(Gun& gun, const IBulletBehavior& bulletBehavior) {
	// Get a possibly existing pointer to ammo behavior
	IAmmoBehavior* ammoBehavior = gun.getAmmoBehavior();

	// If this behavior is implemented, use it
	if (ammoBehavior) {
		// Can fire
		if (ammoBehavior->canFire(gun)) {
			ammoBehavior->consumeAmmo(gun, 1); // Consumes 1 bullet, change to variable amount later



		} else {
		// Can't fire

		}		
	} else {
	// Not implemented so can fire

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