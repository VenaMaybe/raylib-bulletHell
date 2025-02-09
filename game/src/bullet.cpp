#include "bullet.h"
#include "enemy.h"
#include <typeinfo>

#include <cassert>

Bullet::Bullet(
	Position pos,
	Velocity vel,
	float speed,
	float maxAge,
	std::function<void(Bullet&, float)> behavior,
	std::shared_ptr<IBulletRenderer> renderer
):	
	Entity(pos, vel, speed, vel),
	maxAge(maxAge),
	behavior(std::move(behavior)),
	renderer(renderer),
	priorPos(pos)
{
	currentColor = currentColor;
}

void Bullet::render() {
	if (!renderer.get()) { return; }

	renderer->render(*this);

//	DrawCircleV(pos, radius, currentColor);
//	DrawSplineSegmentLinear(pos, priorPos, radius, currentColor);
}

void Bullet::update(float dt) {
	// Initial stuff on update
	setDir(vel);
	setPriorPos(pos);
	age += dt;

	// Update the renderer's color component if required
	renderer->getColorBehavior().update(dt); // Perhaps later make it so only does this if color component requires it



	// Mixing colors
//	currentColor = ColorLerp(colorInit, colorFinal, colorMixAmount * dt);
//	colorMixAmount += colorTransferRate;

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

Color Bullet::getCurrentColor() const {
	return this->currentColor;
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

bool Bullet::isShooterAnEnemy() {
	return true;
}
