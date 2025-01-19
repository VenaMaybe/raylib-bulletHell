#include "gun.h"
#include "gunBehaviors.h"
#include <iostream>

PistolBehavior::PistolBehavior()
	: gunSound("game/sounds/gunEx1.wav")
{}

void PistolBehavior::shoot(Gun& gun) {
	std::cout << "Shoot Clicked\n";

	const int& currentBullets = gun.bullets->size();
	const auto& owner = gun.getOwner();

	// Can fire
	if (currentBullets < maxBullets) {
		std::cout << "Bullet Added, current count: " << currentBullets << "\n";
		gunSound.playSound();

		Velocity bulletVel = (owner->getDir()) + (owner->getVel() * percentOfOwnerVelocity);

		// Recoil
		Velocity playerVelDueToRecoil(0, 0); // Some percent of the velocity goes into the player
		playerVelDueToRecoil = -Velocity(Vector2Lerp(playerVelDueToRecoil, bulletVel, recoilPercent));
		owner->setVel((owner->getVel() + playerVelDueToRecoil)); // Add the recoil to the player's velocity

		// Add the bullet to be simulated to list of bullets
		gun.bullets->emplace_back(
			gun.posMuzzle,	// Spawn Location
			bulletVel,		// Velocity
			bulletSpeed,	// Speed of bullet
			maxBulletAge	// Duration of Bullet
		);
	}
}