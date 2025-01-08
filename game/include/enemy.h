#pragma once
#include "raylib.h"
#include <string>

#include "player.h"

class Enemy {
public:
    // Constructor
    Enemy(Position startPosition, Velocity startVelocity, float startRadius, Color startColor);

    // Draw the Enemy
    void Draw() const;
    void Update(float deltaTime);
    // Setters and Getters
    void SetPosition(Position newPosition);
    Position GetPosition() const;
    void ChangeDirection();
    void UpdateMovement();
    
    // Pick the player to focus on
    void focusPlayer(Player* focusedPlayer);
    Position GetPlayerPos();
    void ChangeColor( Color color);

private:
    Position position;
    Velocity velocity;
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