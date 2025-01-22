#include "enemy.h"
#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "com_comps.h"
#include "player.h"
#include "gunBehaviors.h"
#include "bulletBehaviors.h"
#include "ammoBehaviors.h"
#include "bulletModifiers.h"
// Constructor
Enemy::Enemy(Pos startPosition, Vel startVelocity, float startRadius, Color startColor, Acl startAcelleration)
	:   EntityWithAcceleration(startPosition, startVelocity, 100.0f, startVelocity, startAcelleration),
		radius(startRadius), 
		color(startColor), 
		engageRange(355), 
		inRange(false), 
		engageTolerance(50), 
		movementChangeCounter(0), 
		movementState("ccw"),
		markedForDeletion(false),
		enemyHit("game/sounds/enemyHit1.wav"),
		hp(3),
		attackTimer(GetRandomValue(0, 111))
	{

	}

// Update the Enemy's position based on its velocity
void Enemy::update(float deltaTime) {
	// Get mouse pos
//	Position mousePos = GetMousePosition();

	// Get vector from player to mouse
//	dir = Vector2Normalize(Vector2Subtract(mousePosaa, pos));

	//move 
	pos.x += getScaledVel().dx * deltaTime;
	pos.y += getScaledVel().dy * deltaTime;
	ownedGun->update(deltaTime);
	attackTimer+=1;
	if(attackTimer == 111){
		ownedGun->processClick();
		attackTimer = 0;
	}
	
}

void Enemy::avoidEnemy(Enemy* other){
	float accelerationConst = 1;
	float range = radius*0.9;
	float dist = sqrt((pos.x-other->pos.x)*(pos.x-other->pos.x) + (pos.y-other->pos.y)*(pos.y-other->pos.y));
	if(dist < range){
   		other->pos.x -= (range-dist)*(-other->pos.x + pos.x)/(dist*accelerationConst);
   		other->pos.y -= (range-dist)*(-other->pos.y + pos.y)/(dist*accelerationConst);
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

	ownedGun->render();
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
		if(movementState == "in" || movementState == "out")
		if(GetRandomValue(0,1)==1)
		movementState = "ccw";
		else 
		movementState = "cw";
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
	setDir(Velocity(angleVector.x, angleVector.y));
	float moveSpdMod = 1.0f;
	if (movementState == "in") {
		vel = ( vel * 5.0f + Velocity(angleVector.x, angleVector.y)*2.0f)/6;
		
	}
	if (movementState == "out") {
		vel = (vel * 5.0f + Velocity(-angleVector.x , -angleVector.y )*2.0f)/6;
		
	}
	if (movementState == "cw") {
		vel = (vel * 5.0f + Velocity(angleVector.y , -angleVector.x )*3.0f*moveSpdMod)/6;
		
	}
	if (movementState == "ccw") {
		vel = (vel * 5.0f + Velocity(-angleVector.y , angleVector.x )*3.0f*moveSpdMod)/6;
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
}

void Enemy::hitBy(Bullet other){
	hp -=1;
	if(hp <= 0) markedForDeletion = true;
	vel.dx += 14*other.getVel().dx;
   	vel.dy += 14*other.getVel().dy;
}

void Enemy::giveGun(std::shared_ptr<Gun> gunToBeGiven) {
	// Try doing std::move() later
	ownedGun = gunToBeGiven;
}