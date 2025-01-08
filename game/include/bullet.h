#pragma once

#include "com_comps.h"

struct Bullet {
public:
	Bullet(Position pos, Velocity vel, float maxAge);
	Bullet(Position pos, Vector2 velV, float maxAge);

	void render();
	void update(float dt);

	Position pos;
	Velocity vel;
	float maxAge;
	bool markedForDeletion = false;

private:
	float age = 0;
	Color color = RED;
};