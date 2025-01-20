#include "bullet.h"

Bullet::Bullet(Position pos, Velocity vel, float speed, float maxAge,
			std::function<void(Bullet&, float)> behavior) 
	:	Entity(pos, vel, speed, vel),
		maxAge(maxAge),
		behavior(std::move(behavior))
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

	if (age > maxAge) {
		markedForDeletion = true;
		std::cout << "Bullet marked for deletion\n";
	}

	behavior(*this, dt);
//	pos += vel * speed * dt; // Part of the behavior
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