#include "gun.h"

Gun::Gun(
		std::unique_ptr<IGunBehavior> gunBehavior,
		std::shared_ptr<Entity> ownedByEntity,
		std::vector<Bullet>* bullets,
		std::unique_ptr<IReloadBehavior> reloadBehavior,
		std::unique_ptr<IAmmoBehavior> ammoBehavior
	):
		gunBehavior(std::move(gunBehavior)), 
			// behavior is now empty and its contents are moved into gunBehavior
			// without std::move, the compiler tries to copy behavior but std::unique_ptr isn't copyable
		owner(ownedByEntity),
		bullets(bullets),
		reloadBehavior(std::move(reloadBehavior)),
		ammoBehavior(std::move(ammoBehavior))
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

	ZigzagBulletBehavior meow;

	std::cout << "Using Bullet Behavior: " <<  meow.name() << std::endl;

	if (gunBehavior) {
		gunBehavior->shoot(*this, meow); // Shoot itself
	} else {
		throw std::runtime_error("Gun shot that doesn't have behavior");
	}
}

std::shared_ptr<Entity> Gun::getOwner() {
	auto ownerPtr = owner.lock();
	if (!ownerPtr) {
		throw std::runtime_error("Gun using owner when doesn't exist");
	}
	return ownerPtr;
}

IGunBehavior* Gun::getGunBehavior() const { return gunBehavior.get(); }
IReloadBehavior* Gun::getReloadBehavior() const { return reloadBehavior.get(); }
IAmmoBehavior* Gun::getAmmoBehavior() const { return ammoBehavior.get(); }