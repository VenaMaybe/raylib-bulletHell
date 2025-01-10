#include "player.h"
#include "raymath.h"

Player::Player() : Entity(Pos(100, 100), Vel(0, 0), 250, Dir{0, 0}) {}

void Player::render() {
	DrawCircleV(pos, 10, RAYWHITE);
	DrawLineEx(pos, Vector2Add(pos, Vector2Scale(dir, 100) ), 4, GREEN); // Debugging for now
}

void Player::update(float dt) {
	// Get mouse pos
	Position mousePos = GetMousePosition();

	// Get vector from player to mouse
	dir = Vector2Normalize(Vector2Subtract(mousePos, pos));

	if (controlSystem == ControlTypes::WASD) {
		vel = Velocity(0, 0);
		if(IsKeyDown(KEY_W)) (vel.dy = -1);
		if(IsKeyDown(KEY_A)) (vel.dx = -1);
		if(IsKeyDown(KEY_S)) (vel.dy = 1);
		if(IsKeyDown(KEY_D)) (vel.dx = 1);

		vel = Vector2Normalize(vel);
		
	} else if (controlSystem == ControlTypes::WASD_Soft) { // default
		Velocity targetVel(0, 0);

		if(IsKeyDown(KEY_W)) (targetVel.dy = -1);
		if(IsKeyDown(KEY_A)) (targetVel.dx = -1);
		if(IsKeyDown(KEY_S)) (targetVel.dy = 1);
		if(IsKeyDown(KEY_D)) (targetVel.dx = 1);

		targetVel = Vector2Normalize(targetVel);

		// Smoothing approach the targetVel
		float accel = 10 * dt;
		vel += (targetVel - vel) * accel;
		
	} else if (controlSystem == ControlTypes::Tank) {
		if (IsKeyDown(KEY_W) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			vel = Vector2Add(vel, Vector2Scale(dir, dt)); // constant per sec <= scale by dt
		} else {
			// Dampening
			vel = Vector2Scale(vel, 0.99);
		}
	}

	pos = Vector2Add(pos, Vector2Scale(vel, speed * dt));
}