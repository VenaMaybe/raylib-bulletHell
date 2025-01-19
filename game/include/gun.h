#pragma once

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <algorithm>
#include <functional>
#include <memory>

#include "entity.h"
#include "com_comps.h"
#include "bullet.h"
#include "IGunBehavior.h"

class Gun {
public:
	Gun(
		std::unique_ptr<IGunBehavior> behavior,
		std::shared_ptr<Entity> ownedByEntity,
		std::vector<Bullet>* bullets
	);

	void render();
	void renderBullets();
	void update(float dt);
	void processClick(); // This should take in a command
	std::shared_ptr<Entity> getOwner();

	Position posMuzzle; // Distance from posBase in dir by some scalar, where bullets come from
	std::vector<Bullet>* bullets;

private:
	std::weak_ptr<Entity> owner;

	// Polymorphic pointer to the chosen behavior
	std::unique_ptr<IGunBehavior> gunBehavior;
};
