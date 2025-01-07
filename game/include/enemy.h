#pragma once
#include "raylib.h"
#include <string>

#include "player.h"

class Enemy {
public:
    // Constructor
    Enemy(Vector2 startPosition, Vector2 startVelocity, float startRadius, Color startColor);

    // Update the Enemy's position
 

    // Draw the Enemy
    void Draw() const;
    void Update(float deltaTime);
    // Setters and Getters
    void SetPosition(Vector2 newPosition);
    Vector2 GetPosition() const;
    void ChangeDirection();
    void UpdateMovement();

	// Pick the player to focus on
	void focusPlayer(Player* focusedPlayer);
	Vector2 GetPlayerPos();

private:
    Vector2 position;
    Vector2 velocity;
    float speed;
    float radius;
    Color color;
    float engageRange;
    bool inRange;
    float engageTolerance;
    float movementChangeCounter;
    std::string movementState;

	// Store a pointer to the focused player
	Player* focusedPlayer;
};