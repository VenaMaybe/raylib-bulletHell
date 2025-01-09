#include "enemy.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "com_comps.h"
#include "player.h"

// Constructor
Enemy::Enemy(Position startPosition, Velocity startVelocity, float startRadius, Color startColor)
    :   Entity(startPosition, startVelocity, 200.0f, startVelocity),
        radius(startRadius), 
        color(startColor), 
        engageRange(200), 
        inRange(false), 
        engageTolerance(50), 
        movementChangeCounter(0), 
        movementState("ccw"),
        markedForDeletion(false)
    {}

// Update the Enemy's position based on its velocity
void Enemy::update(float deltaTime) {
    UpdateMovement();
    ChangeDirection();
    //move 
        pos.x +=  getScaledVel().dx * deltaTime;
        pos.y += getScaledVel().dy * deltaTime;
}

void Enemy::focusPlayer(Player* focusedPlayer) {
	this->focusedPlayer = focusedPlayer;
}

Position Enemy::GetPlayerPos() {
	if (focusedPlayer == nullptr) {
		throw std::runtime_error("focusedPlayer pointer is null");
	}

//    Player* playerPtr = dynamic_cast<Player*>(focusedPlayer);
//    if (playerPtr == nullptr) {
//        throw std::runtime_error("focusedPlayer is not a Player stupid");
//    }

    return focusedPlayer->getPos();
}

// Draw the Enemy
void Enemy::render()  {
    DrawCircleV(pos, radius, color);
}

void Enemy::UpdateMovement() {
    float dist = Vector2Distance(GetPlayerPos(), pos);
    if (dist > engageRange + engageTolerance) {
        movementState = "in";
    }
    if (dist < engageRange - engageTolerance) {
        movementState = "out";
    }
    if (dist < engageRange + engageTolerance/2 && dist > engageRange - engageTolerance/2) {
        movementState = "ccw";
    }
}

void Enemy::ChangeDirection() {
    // chase mouse 
    Position playerPos = GetPlayerPos();
    float dx = playerPos.x - pos.x;
    float dy = playerPos.y - pos.y;
    float angle =  atan2(dy, dx);
    Vector2 angleVector;
    angleVector.x = cos(angle);
    angleVector.y = sin(angle);
    
    if (movementState == "in") {
        vel = Velocity(angleVector.x, angleVector.y);
    }
    if (movementState == "out") {
        vel = Velocity(-angleVector.x , -angleVector.y );
    }
    if (movementState == "cw") {
        vel = Velocity(angleVector.y , -angleVector.x );
    }
    if (movementState == "ccw") {
        vel = Velocity(-angleVector.y , angleVector.x );
    }
    

}

// Setters and Getters
void Enemy::SetPosition(Position newPosition) {
    position = newPosition;
}

Position Enemy::GetPosition() const {
    return position;
}

void Enemy::ChangeColor(Color color) {
    this->color = color;
}