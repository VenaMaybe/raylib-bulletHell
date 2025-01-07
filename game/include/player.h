#pragma once

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "com_comps.h"

/* Outline -- Player Class

Player()	--- Simple Constructors
render()	--- Renders a sphere at player center, 		called per frame
update()	--- Processes input							called per frame

Has a:
	speed multiplier
	position
	velocity

	gun class

*/

class Player {
public:
	Player();
	void render();
	void update(float dt);
	Position* getPos();
	Velocity* getVel();
	Vector2* getDir();
private:
	const bool WASD = true;
	float speedMult;
	Position pos;
	Velocity vel;
	Vector2 dir;
};