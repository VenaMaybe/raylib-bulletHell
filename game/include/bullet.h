#pragma once

#include <functional>
#include <memory>
#include "bulletRenderers.h"
#include "com_comps.h"
#include "entity.h"

//forward declaration for enemy


class Bullet : public Entity {
public:
	Bullet(
		Position pos,
		Velocity vel,
		float speed,
		float maxAge,
		std::function<void(Bullet&, float)> behavior,
		std::shared_ptr<IBulletRenderer> renderer
	);
	
	void render() override;
	void update(float dt) override;

	void markForDeletion();
	bool isMarkedForDeletion() const;

	Color getCurrentColor() const;

	void setMaxAge(float maxAge);
	float getMaxAge() const;
	float getAge() const;

	void setPriorPos(Pos pos);
	Position getPriorPos() const; // Returns pos 1 tick ago

	void setShooter(Entity* shooterPtr);
	bool isShooter(Entity* shooterInQuestion);
	bool isShooterAnEnemy();

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

	// Renderer
	// shared_ptr so multiple bullets or entities can share the same rendering strategy
	//		without duplicating the renderer but sharing it between bullets
	// If the render's lifetime is guaranteed or managed elsewhere and persists as long
	//		as the bullet does, you can use a reference or std::weak_ptr 
	std::shared_ptr<IBulletRenderer> renderer; 

	// Function to control the bullet's behavior with inputs bullet and dt
	std::function<void(Bullet&, float)> behavior; // Maybe someday abstract this to all entities lol

	// Non-owning reference to the shooter
	Entity* shooter;

	// Todo: Add flag so certain enemies can't shoot certain other enemies
};

/*

On Hit	 : Explosion			- Bullet Behavior
Bullet   : How it is drawn		- Bullet Behavior

*/