#include "enemy.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "com_comps.h"
#include "player.h"

// Constructor
Enemy::Enemy(Pos startPosition, Vel startVelocity, float startRadius, Color startColor, Acl startAcelleration)
	:   EntityWithAcelleration(startPosition, startVelocity, 100.0f, startVelocity, startAcelleration),
		radius(startRadius), 
		color(startColor), 
		engageRange(200), 
		inRange(false), 
		engageTolerance(50), 
		movementChangeCounter(0), 
		movementState("ccw"),
		markedForDeletion(false),
		enemyHit("game/sounds/enemyHit1.wav")
	{}

// Update the Enemy's position based on its velocity
void Enemy::update(float deltaTime) {
	//move 
	pos.x += getScaledVel().dx * deltaTime;
	pos.y += getScaledVel().dy * deltaTime;
}

void Enemy::avoidEnemy(Enemy* other){
	float accelerationConst = 1;
	float range = 45;
	float dist = sqrt((pos.x-other->pos.x)*(pos.x-other->pos.x) + (pos.y-other->pos.y)*(pos.y-other->pos.y));
	if(dist < range){
   		pos.x += (range-dist)*(-other->pos.x + pos.x)/(dist*accelerationConst);
   		pos.y += (range-dist)*(-other->pos.y + pos.y)/(dist*accelerationConst);
    }
}

void Enemy::focusPlayer(Player* focusedPlayer) {
	this->focusedPlayer = focusedPlayer;
}

Position Enemy::GetPlayerPos() {
	if (focusedPlayer == nullptr) {
		throw std::runtime_error("focusedPlayer pointer is null");
	}
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

void Enemy::playHitSound() {
	enemyHit.playSound();
}

// Setters and Getters
void Enemy::ChangeColor(Color color) {
	this->color = color;
}

float Enemy::getRadius() const {
	return radius;
};