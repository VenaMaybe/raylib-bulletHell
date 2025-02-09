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
#include "IBulletBehavior.h"
#include "IAmmoBehavior.h"
#include "gunBehaviors.h"
#include "IShootBehaviour.h"

class Gun {
public:
	Gun( // Eventually change this to using a builder/factory pattern
		std::unique_ptr<IGunBehavior> gunBehavior,
		std::unique_ptr<IBulletBehavior> bulletBehavior,
		std::unique_ptr<IAmmoBehavior> ammoBehavior,
		std::unique_ptr<IShootBehaviour> shootBehaviour,
		std::shared_ptr<Entity> ownedByEntity,
		std::vector<Bullet>* bullets,
		float attackTime
	);

	void render();
	void renderBullets();
	void update(float dt);
	void processClick(); // This should take in a command
	std::shared_ptr<Entity> getOwner();

	// Getters for the behaviors
	IGunBehavior* getGunBehavior() const;
	IBulletBehavior* getBulletBehavior() const;
	IAmmoBehavior* getAmmoBehavior() const;
	IShootBehaviour* getShootBehaviour() const;
	bool getIsAuto() const;
	Position posMuzzle; // Distance from posBase in dir by some scalar, where bullets come from
	
	// TODO: Bullets themselves should be a component later lol
	std::vector<Bullet>* bullets;

private:
	// entity that owns the gun
	std::weak_ptr<Entity> owner;
	// Polymorphic pointer to the chosen behavior
	std::unique_ptr<IGunBehavior> gunBehavior;
	std::unique_ptr<IBulletBehavior> bulletBehavior;
	std::unique_ptr<IAmmoBehavior> ammoBehavior;
	std::unique_ptr<IShootBehaviour> shootBehaviour;
	float attackTimer;
	float attackTime;
};
