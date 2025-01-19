#include "bullet.h"

Bullet::Bullet(Position pos, Velocity vel, float speed, float maxAge) 
	:	Entity(pos, vel, speed, vel),
		maxAge(maxAge) 
	{}

void Bullet::render() {
	DrawCircleV(pos, radius, colorInit);
	DrawSplineSegmentLinear(pos, priorPos, radius, colorInit);

}

void Bullet::update(float dt) {
	setPriorPos(pos);
	age += dt;
	colorInit = ColorLerp(colorInit, colorFinal, .001);

	// std::cout << "Age: " << age << ", MaxAge: " << maxAge << "\n";
	if (age > maxAge) {
		markedForDeletion = true;
		std::cout << "Bullet marked for deletion\n";
	}

	pos += vel * speed * dt;
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

void Bullet::setPriorPos(Pos pos) {
	this->priorPos = pos;
}

Position Bullet::getPriorPos() const {
	return priorPos;
}