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
//		std::function<void(Gun&)> onFireCallback,
		std::unique_ptr<IGunBehavior> behavior,
		std::shared_ptr<Entity> ownedByEntity,
		std::vector<Bullet>* bullets
	); // Pass in a function to describe onFire behavior

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

	// Before, was just straight up a dogged callback lol
	// std::function<void(Gun&)> onFire; // called everytime u click
};

/*

// Holds the implementation of the callback + specifics for a gun type
struct GunSpecificEx {
	// Specific to this gun
	int maxBullets = 10;
	float bulletSpeed = 1000;
	float maxBulletAge = 3;
	float percentOfOwnerVelocity = 0.15; // Todo: Change this based on speed of bullet!!!
	float recoilPercent = 2;
	AudioBit gunSound;
	GunSpecificEx();
	//
	void shoot(Gun& gun);
};

*/