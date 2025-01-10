#pragma once

#include "com_comps.h"

struct Bullet {
public:
	Bullet(Position pos, Velocity vel, float maxAge);
	Bullet(Position pos, Vector2 velV, float maxAge); // lame and old

	void render();
	void update(float dt);

	Position pos;
	Velocity vel;
	float maxAge;
	bool markedForDeletion = false;

private:
	float age = 0;
	float radius = 5;
	Color colorInit = RED;
	Color colorFinal = BLUE;
};