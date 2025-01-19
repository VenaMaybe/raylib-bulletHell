#pragma once
#include "raylib.h"
#include <string>

#include "com_comps.h"
#include "audioBit.h"
#include "entity.h"
#include "player.h"

class Enemy : public EntityWithAcelleration {
public:
	// Constructor
	Enemy(Pos startPosition, Vel startVelocity, float startRadius, Color startColor, Acl startAcelleration);

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

private:
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
};