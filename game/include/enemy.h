#pragma once
#include "raylib.h"
#include <string>
#include "entity.h"
#include "player.h"
#include "com_comps.h"

class Enemy : public Entity {
public:
    // Constructor
    Enemy(Position startPosition, Velocity startVelocity, float startRadius, Color startColor);

    // Draw the Enemy
    void render();
    void update(float deltaTime);
    // Setters and Getters
    void SetPosition(Position newPosition);
    Position GetPosition() const;
    void ChangeDirection();
    void UpdateMovement();
    // Pick the player to focus on
    void focusPlayer(Player* focusedPlayer);
    Position GetPlayerPos();
    void ChangeColor( Color color);
    Position position;
    bool markedForDeletion;
private:
    
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