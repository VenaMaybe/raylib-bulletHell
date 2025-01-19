#pragma once

#include "com_comps.h"
#include "entity.h"

struct Bullet : Entity{
public:
	Bullet(Position pos, Velocity vel, float speed, float maxAge);
	void render() override;
	void update(float dt) override;

	void markForDeletion();
	bool isMarkedForDeletion() const;

	void setMaxAge(float maxAge);
	float getMaxAge() const;
	
	void setPriorPos(Pos pos);
	Position getPriorPos() const; // Returns pos 1 tick ago

private:
	Position priorPos;
	float maxAge;
	bool markedForDeletion = false;
	float age = 0;
	float radius = 5;
	Color colorInit = RED;
	Color colorFinal = BLUE;
};