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

/* Outline -- Gun Class

render()	--- Renders gun (from player in direction)

Has a:
	gun implementation 		--- on click callback // decouple firing logic from gun class
	list of bullet types	--- vector of used bullets, (oft 1)
	number of bullets		

*/

class Gun {
public:
	Gun(
		std::function<void(Gun&)> onFireCallback,
		std::shared_ptr<Entity> ownedByEntity,
		std::vector<Bullet>* bullets
	); // Pass in a function to describe onFire behavior

	void render();
	void renderBullets();
	void update(float dt);
	void processClick();
	std::shared_ptr<Entity> getOwner();

	Position posMuzzle; // Distance from posBase in dir by some scalar, where bullets come from

	// copium temporary
	std::vector<Bullet>* bullets;
private:
	std::weak_ptr<Entity> owner;
	std::function<void(Gun&)> onFire; // called everytime u click
};

// Holds the implementation of the callback + specifics for a gun type
struct GunSpecificEx {
	// Specific to this gun
	int maxBullets = 10;
	float bulletSpeed = 100.;
	float maxBulletAge = 3.;

	//
	void shoot(Gun& gun);
};