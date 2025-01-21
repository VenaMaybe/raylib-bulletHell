#pragma once

#include <functional>
#include <memory>
#include "com_comps.h"
#include "entity.h"

//forward declaration for enemy


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
	void setShooter(Entity* shooterPtr);
	bool isShooter(Entity* shooterInQuestion);
	bool isShooterEnemy();

private:
	Position priorPos;
	float maxAge;
	bool markedForDeletion = false;
	float age = 0; // In seconds
	float radius = 5;

	float colorMixAmount = 0.f;
	float colorTransferRate = 1.f;
	Color colorInit = RED;
	Color colorFinal = BLUE;
	Color currentColor;

	// Function to control the bullet's behavior with inputs bullet and dt
	std::function<void(Bullet&, float)> behavior; // Maybe someday abstract this to all entities lol

	// Non-owning reference to the shooter
	Entity* shooter;

	// Todo: Add flag so certain enemies can't shoot certain other enemies
};