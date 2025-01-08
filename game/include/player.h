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

enum Controls {
	WASD,
	WASD_Soft,
	Tank
};

class Player {
public:
	Player();
	void render();
	void update(float dt);
	Position* getPos();
	Velocity* getVel();
	Vector2* getDir();
	Velocity getScaledVel(float dt);
private:
	const Controls controlSystem = WASD_Soft;

	float speedMult = 250.;
	Position pos;
	Velocity vel;
	Vector2 dir;
};