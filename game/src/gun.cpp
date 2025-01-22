#include "gun.h"

#include "bulletBehaviors.h"

Gun::Gun(
		std::unique_ptr<IGunBehavior> gunBehavior,
		std::unique_ptr<IBulletBehavior> bulletBehavior,
		std::unique_ptr<IAmmoBehavior> ammoBehavior,
		std::shared_ptr<Entity> ownedByEntity,
		std::vector<Bullet>* bullets
	):
		gunBehavior(std::move(gunBehavior)), 
			// behavior is now empty and its contents are moved into gunBehavior
			// without std::move, the compiler tries to copy behavior but std::unique_ptr isn't copyable
		bulletBehavior(std::move(bulletBehavior)),
		ammoBehavior(std::move(ammoBehavior)),
		owner(ownedByEntity),
		bullets(bullets)
{}

void Gun::render() {
	// DrawCircleV(getOwner()->getPos(), 30, BROWN); // For Debugging
	posMuzzle = Vector2Add(getOwner()->getPos(), Vector2Scale(getOwner()->getDir(), 16));
	DrawLineEx(getOwner()->getPos(), posMuzzle, 10, RAYWHITE);
	std::cout << getOwner()->getPos().x<<std::endl;

	// Lmao Eventually move this somewhere else

	AmmoInfo ammoInfo = ammoBehavior->getAmmoInfo();
	Position drawPos {0, 30};
	Position offset {0, 12};

	for (const auto& info : ammoInfo) {
		DrawText(info.ammoTypeName.c_str(), drawPos.x, drawPos.y, 10, RAYWHITE);
		drawPos += offset;

		std::string ammoCount = std::to_string(info.currentAmmo) + "/" + std::to_string(info.maxAmmo);
		DrawText(ammoCount.c_str(), drawPos.x, drawPos.y, 10, RAYWHITE);
		drawPos += offset;
	}

	DrawText("[R-Mouse] shoot", drawPos.x, drawPos.y, 10, RAYWHITE);
	drawPos += offset;
	DrawText("[R] reload", drawPos.x, drawPos.y, 10, RAYWHITE);
	drawPos += offset;
	DrawText("[WASD] move", drawPos.x, drawPos.y, 10, RAYWHITE);
	drawPos += offset;
	DrawText("[Esc] close", drawPos.x, drawPos.y, 10, RAYWHITE);
}

// Updates all the bullets cuz I'm lazy
void Gun::update(float dt) {
	// Update the position of the Muzzle
	posMuzzle = Vector2Add(getOwner()->getPos(), Vector2Scale(getOwner()->getDir(), 16));

	// Uh here cuz funnnn
	if (false) {
		processClick();
	}

	if (IsKeyPressed(KEY_R)) {
		ammoBehavior->reloadAmmo(*this);
	}
}

// This should spawn the bullets and add to entity manager
// 		Todo: Make it use a command architecture 
void Gun::processClick() {
	if (gunBehavior) {
		gunBehavior->shoot(*this, *bulletBehavior.get()); // Shoot itself
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
IBulletBehavior* Gun::getBulletBehavior() const { return bulletBehavior.get(); }
IAmmoBehavior* Gun::getAmmoBehavior() const { return ammoBehavior.get(); }