#include "bullet.h"

Bullet::Bullet(Position pos, Velocity vel, float maxAge) : pos(pos), vel(vel), maxAge(maxAge) {};
Bullet::Bullet(Position pos, Vector2 velV, float maxAge) : pos(pos), vel(velV), maxAge(maxAge) {};

void Bullet::render() {
	DrawCircleV(pos, 5, color);
}

void Bullet::update(float dt) {
	age += dt;
	color = ColorLerp(color, BLUE, .001);

	// std::cout << "Age: " << age << ", MaxAge: " << maxAge << "\n";
	if (age > maxAge) {
		markedForDeletion = true;
		std::cout << "Bullet marked for deletion\n";
	}

	pos.x += vel.dx * dt;
	pos.y += vel.dy * dt;

	// pos += vel * dt;
}