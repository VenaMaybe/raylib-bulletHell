#include "gun.h"

Gun::Gun(
		std::function<void(Gun&)> onFireCallback,
		std::shared_ptr<Entity> ownedByEntity,
		std::vector<Bullet>* bullets
	): 
		onFire(onFireCallback), // Pass in a function to describe onFire behavior
		owner(ownedByEntity),
		bullets(bullets)
{}; 

void Gun::render() {
	DrawLineEx(getOwner()->getPos(), posMuzzle, 10, RAYWHITE);
};

// Updates all the bullets cuz I'm lazy
void Gun::update(float dt) {
	// Update the position of the Muzzle
	posMuzzle = Vector2Add(getOwner()->getPos(), Vector2Scale(getOwner()->getDir(), 16));

	// Uh here cuz funnnn
	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
		processClick();
	}
};

// This should spawn the bullets and add to entity manager
void Gun::processClick() {
	if (onFire) { onFire(*this); }
	else { std::cout << "Uh oh\n"; }
};

std::shared_ptr<Entity> Gun::getOwner() {
	auto ownerPtr = owner.lock();
	if (!ownerPtr) {
		throw std::runtime_error("Gun using owner when doesn't exist");
	}
	return ownerPtr;
}

//
//	Specific
//

void GunSpecificEx::shoot(Gun& gun) {
	std::cout << "Shoot Clicked\n";

	int currentBullets = gun.bullets->size();
	const auto& owner = gun.getOwner();

	// Can fire
	if (currentBullets < maxBullets) {
		std::cout << "Bullet Added, current count: " << currentBullets << "\n";
		Velocity bulletVel = (owner->getDir()) + (owner->getVel() * percentOfOwnerVelocity);
		Velocity playerVelDueToRecoil(0, 0);
		// Some percent of the velocity goes into the player
		playerVelDueToRecoil = -Velocity(Vector2Lerp(playerVelDueToRecoil, bulletVel, recoilPercent));

		// Add the recoil to the player's velocity
		owner->setVel((owner->getVel() + playerVelDueToRecoil));

		// Add the bullet to be simulated to list of bullets
		gun.bullets->emplace_back(
			gun.posMuzzle,				// Spawn Location
			bulletVel * bulletSpeed,	// Velocity
			maxBulletAge				// Duration of Bullet
		);
	}
};
