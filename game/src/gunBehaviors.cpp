#include "gun.h"
#include "gunBehaviors.h"
#include "raymath.h"
#include <iostream>

StraightBulletBehavior::StraightBulletBehavior() {
	behaviorName = "StraightBulletBehavior";
	behavior = [](Bullet& bullet, float dt) {
		Pos pos = bullet.getPos();
		Vel vel = bullet.getVel();
		float speed = bullet.getSpeed();

		bullet.setPos(pos + ( vel * speed * dt ) );
	};
}

std::function<void(Bullet&, float)> StraightBulletBehavior::getBehaviorFunction() const {
	return behavior;
}

ZigzagBulletBehavior::ZigzagBulletBehavior() {
	behaviorName = "ZigzagBulletBehavior";
	behavior = [](Bullet& bullet, float dt) {
		Pos pos = bullet.getPos();
		Vel vel = bullet.getVel();
		float speed = bullet.getSpeed();
		float timeAccumulator = bullet.getAge();

		float zigzagOffset = sin(timeAccumulator * 100.f) * 10.f;

		Dir dir = bullet.getDir();
		Vel orthogonal = Vel(dir.y, -dir.x);

		orthogonal *= zigzagOffset;
		vel *= 0.1;

		printVector2(orthogonal);

		bullet.setPos(pos + ( ( orthogonal + vel ) ) * speed * dt );
	};
}

std::function<void(Bullet&, float)> ZigzagBulletBehavior::getBehaviorFunction() const {
	return behavior;
}

/////////////////////////////////////////

bool UnlimitedAmmoBehavior::canFire(const Gun& gun) const {
	return true; // Can always fire
}

// Does nothing
void UnlimitedAmmoBehavior::consumeAmmo(Gun& gun) {}
void UnlimitedAmmoBehavior::reloadAmmo(Gun& gun) {}

/////////////////////////////////////////

void SingleShotShooting::shoot(Gun& gun, const IBulletBehavior& bulletBehavior) {
	// Get a possibly existing pointer to ammo behavior
	IAmmoBehavior* ammoBehavior = gun.getAmmoBehavior();

	// If this behavior is implemented, use it
	if (ammoBehavior) {
		// Can fire
		if (ammoBehavior->canFire(gun)) {
			ammoBehavior->consumeAmmo(gun); // Consumes 1 bullet, change to variable amount later



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
			maxBulletAge,	// Duration of Bullet
			bulletBehavior.getBehaviorFunction()
		);
	}
}