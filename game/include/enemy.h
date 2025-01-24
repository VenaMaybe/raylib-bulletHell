#pragma once
#include "raylib.h"
#include <string>
#include <memory>
#include "com_comps.h"
#include "entity.h"
#include "gun.h"
#include "bullet.h"
#include "audioBit.h"
#include "player.h"

class Enemy : public EntityWithAcceleration {
public:
	// Constructor
	Enemy(Pos startPosition, Vel startVelocity, float startRadius, Color startColor, Acl startAcceleration);

	// Draw the Enemy
	void render();
	void update(float deltaTime);
	void ChangeDirection();
	void UpdateMovement();
	void avoidEnemy(Enemy* other);
	void playHitSound();
	// Pick the player to focus on
	void focusPlayer(Player* focusedPlayer);
	Position GetPlayerPos();
	void ChangeColor( Color color);
	bool markedForDeletion;

	float getRadius() const;
	void hitBy(Bullet other);
	
	void giveGun(std::shared_ptr<Gun> gunToBeGiven);

private:
	int attackTimer;
	float hp;
	float radius;
	Color color;
	float engageRange;
	bool inRange;
	float engageTolerance;
	float movementChangeCounter;
	std::string movementState;
	// Store a pointer to the focused player
	Player* focusedPlayer;
	AudioBit enemyHit;

	// weak_ptr to a gun (i.e. maybe it has a gun, maybe it doesn't)
	std::shared_ptr<Gun> ownedGun;
};