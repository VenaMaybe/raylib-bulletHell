#include "bullet.h"

Bullet::Bullet(Position pos, Velocity vel, float speed, float maxAge,
			std::function<void(Bullet&, float)> behavior) 
	:	Entity(pos, vel, speed, vel),
		maxAge(maxAge),
		behavior(std::move(behavior)),
		priorPos(pos)
	{
		currentColor = currentColor;
	}

void Bullet::render() {
	DrawCircleV(pos, radius, currentColor);
	DrawSplineSegmentLinear(pos, priorPos, radius, currentColor);
}

void Bullet::update(float dt) {
	setDir(vel); // Not sure if needed
	setPriorPos(pos);
	age += dt;

	// Mixing colors
	currentColor = ColorLerp(colorInit, colorFinal, colorMixAmount * dt);
	colorMixAmount += colorTransferRate;

	// Should probably get moved to behavior or another callback at somepoint
	if (age > maxAge) {
		markedForDeletion = true;
	}

	// Implements the behavior of the bullet
	behavior(*this, dt);
}

void Bullet::markForDeletion() {
	markedForDeletion = true;
}

bool Bullet::isMarkedForDeletion() const {
	return markedForDeletion;
}

void Bullet::setMaxAge(float maxAge) {
	this->maxAge = maxAge;
}

float Bullet::getMaxAge() const {
	return maxAge;
}

float Bullet::getAge() const {
	return age;
}

void Bullet::setPriorPos(Pos pos) {
	this->priorPos = pos;
}

Position Bullet::getPriorPos() const {
	return priorPos;
}


void Bullet::setShooter(Entity* shooter) {
	this->shooter = shooter;
}

bool Bullet::isShooter(Entity* shooterInQuestion) {
	if (!shooter) {
		return false;
	}

	return (shooter == shooterInQuestion) ? true : false;
}


