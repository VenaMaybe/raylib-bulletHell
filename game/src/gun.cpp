#include "gun.h"

Gun::Gun(
		std::function<void(Gun&)> onFireCallback,
		std::shared_ptr<Entity> ownedByEntity
	): 
		onFire(onFireCallback), // Pass in a function to describe onFire behavior
		owner(ownedByEntity)
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

	for (auto& bullet : bullets) {
		bullet.update(dt);
		bullet.render();
	}

	// Remove those marked for deletion
	bullets.erase(
		std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return b.markedForDeletion; }),
		bullets.end()
	);
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

	int currentBullets = gun.bullets.size();

	// Can fire
	if (currentBullets < maxBullets) {
		std::cout << "Bullet Added, current count: " << currentBullets << "\n";
		gun.bullets.emplace_back(
			gun.posMuzzle,
			(gun.getOwner()->getDir() * bulletSpeed) + (gun.getOwner()->getScaledVel()),
			maxBulletAge
		);
	}
};
