#pragma once

#include <functional>
#include "com_comps.h"
#include "entity.h"

struct Bullet : Entity {
public:
	Bullet(Position pos, Velocity vel, float speed, float maxAge,
		std::function<void(Bullet&, float)> behavior);
	void render() override;
	void update(float dt) override;

	void markForDeletion();
	bool isMarkedForDeletion() const;


	void setMaxAge(float maxAge);
	float getMaxAge() const;
	float getAge() const;
	
	void setPriorPos(Pos pos);
	Position getPriorPos() const; // Returns pos 1 tick ago

private:
	Position priorPos;
	float maxAge;
	bool markedForDeletion = false;
	float age = 0; // In seconds
	float radius = 5;
	Color colorInit = RED;
	Color colorFinal = BLUE;

	// Function to control the bullet's behavior with inputs bullet and dt
	std::function<void(Bullet&, float)> behavior; // Maybe someday abstract this to all entities lol
};