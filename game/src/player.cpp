#include "player.h"

Player::Player() : pos{100, 100}, vel{0, 0}, speedMult(150.) {}

void Player::render() {
	DrawCircleV(pos, 10., RAYWHITE);
	//DrawLineEx(pos, Vector2Add(pos, Vector2Scale(dir, 100) ), 4, GREEN); // Debugging for now
}

void Player::update(float dt) {
	// Get mouse pos
	Vector2 mousePos = GetMousePosition();

	// Get vector from player to mouse
	dir = Vector2Normalize(Vector2Subtract(mousePos, pos));

	if (IsKeyDown(KEY_W) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		vel = Vector2Add(vel, Vector2Scale(dir, speedMult * dt)); // constant per sec <= scale by dt
	} else {
		// Dampening
		vel = Vector2Scale(vel, 0.99f);
	}

	pos = Vector2Add(pos, Vector2Scale(vel, dt));
}

// OOPing time
Position* Player::getPos() { return &pos; };
Velocity* Player::getVel() { return &vel; };
Vector2* Player::getDir() { return &dir; };