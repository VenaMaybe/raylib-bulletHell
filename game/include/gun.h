#pragma once

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <algorithm>
#include <functional>

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
		Position* pos,
		Vector2* dir
	); // Pass in a function to describe onFire behavior

	void render();
	void update(float dt);
	void processClick();

	Position* pos; // Always has to be attached to smt
	Vector2* dir;

	// copium temporary
	int currentBullets = 0;
	std::vector<Bullet> bullets;
private:
	std::function<void(Gun&)> onFire; // called everytime u click
};

Gun::Gun(
		std::function<void(Gun&)> onFireCallback,
		Position* pos,
		Vector2* dir 
	): 
		onFire(onFireCallback), // Pass in a function to describe onFire behavior
		pos(pos),
		dir(dir)	
{}; 

void Gun::render() {
	DrawLineEx(*pos, Vector2Add(*pos, Vector2Scale(*dir, 100) ), 5, GREEN);
};

// Updates all the bullets cuz I'm lazy
void Gun::update(float dt) {
	// Uh here cuz funnnn
	if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
		processClick();
	}

	for (auto& bullet : bullets) {
		bullet.update(dt);
		bullet.render();
	}

	// Remove those marked for deletion
	auto it = bullets.erase(
		std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return b.markedForDeletion; }),
		bullets.end()
	);
	int bulletsErased = it - bullets.begin();
//	if (bulletsErased != 0)
//		std::cout << "\t" << bulletsErased << "\n";
	currentBullets -= bulletsErased;
};

// This should spawn the bullets and add to entity manager
void Gun::processClick() {
	if (onFire) { onFire(*this); }
	else { std::cout << "Uh oh\n"; }
};


// Holds the implementation of the callback + specifics for a gun type
struct GunSpecificEx {
	// Specific to this gun
	int maxBullets = 10;
	float bulletSpeed = 100.;
	float maxBulletAge = 20.;

	//
	void shoot(Gun& gun);
};

void GunSpecificEx::shoot(Gun& gun) {
	std::cout << "Shoot Clicked\n";
	// Can fire
	if (gun.currentBullets < maxBullets) {
		std::cout << "Bullet Added, current count: " << gun.currentBullets << "\n";
		gun.bullets.emplace_back(*gun.pos, Vector2Scale(*gun.dir, bulletSpeed), maxBulletAge);
		gun.currentBullets++;
	}
};
