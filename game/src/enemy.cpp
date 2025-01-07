#include "enemy.h"
#include "raylib.h"
#include "raymath.h"

#include <cmath>
#include <iostream>

#include "com_comps.h"
#include "player.h"

// Constructor
Enemy::Enemy(Vector2 startPosition, Vector2 startVelocity, float startRadius, Color startColor)
    : position(startPosition), velocity(startVelocity), radius(startRadius), color(startColor), speed(100), engageRange(200), inRange(false), engageTolerance(50), movementChangeCounter(0), movementState("ccw"){}

// Update the Enemy's position based on its velocity
void Enemy::Update(float deltaTime) {
    UpdateMovement();
    ChangeDirection();
    //move
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
}

void Enemy::focusPlayer(Player* focusedPlayer) {
	this->focusedPlayer = focusedPlayer;
}

Vector2 Enemy::GetPlayerPos() {
	if (!focusedPlayer) {
		throw std::runtime_error("focusedPlayer pointer is null");
	}

    return *focusedPlayer->getPos();
}


// Draw the Enemy
void Enemy::Draw() const {
    DrawCircleV(position, radius, color);
}
void Enemy::UpdateMovement(){
    float dist = Vector2Distance(GetMousePosition(), position);
    if(dist > engageRange + engageTolerance){
        movementState = "in";
    }
    if(dist < engageRange - engageTolerance){
        movementState = "out";
    }
    if(dist < engageRange + engageTolerance/2 && dist > engageRange - engageTolerance/2){
        movementState = "ccw";
    }

}
void Enemy::ChangeDirection(){
    // chase mouse 
    Vector2 playerPos = GetMousePosition();
    float dx = playerPos.x - position.x;
    float dy = playerPos.y - position.y;
    float angle =  atan2(dy, dx);
    Vector2 angleVector;
    angleVector.x = cos(angle);
    angleVector.y = sin(angle);
    if(movementState == "in"){
        velocity = {angleVector.x*speed, angleVector.y*speed};
    }
    if(movementState == "out"){
        velocity = {-angleVector.x*speed, -angleVector.y*speed};        
    }
    if(movementState == "cw"){
        velocity = {angleVector.y*speed, -angleVector.x*speed};
    }
    if(movementState == "ccw"){
        velocity = {-angleVector.y*speed, angleVector.x*speed};
    }
}


// Setters and Getters
void Enemy::SetPosition(Vector2 newPosition) {
    position = newPosition;
}

Vector2 Enemy::GetPosition() const {
    return position;
}