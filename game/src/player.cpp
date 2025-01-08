#include "player.h"

Player::Player() : pos{100, 100}, vel{0, 0} {}

void Player::render() {
	DrawCircleV(pos, 10., RAYWHITE);
	DrawLineEx(pos, Vector2Add(pos, Vector2Scale(dir, 100) ), 4, GREEN); // Debugging for now
}

void Player::update(float dt) {
	// Get mouse pos
	Vector2 mousePos = GetMousePosition();

	// Get vector from player to mouse
	dir = Vector2Normalize(Vector2Subtract(mousePos, pos));

	if (controlSystem == WASD) {
		vel = Velocity(0., 0.);
		if(IsKeyDown(KEY_W)) (vel.dy = -1.);
		if(IsKeyDown(KEY_A)) (vel.dx = -1.);
		if(IsKeyDown(KEY_S)) (vel.dy = 1.);
		if(IsKeyDown(KEY_D)) (vel.dx = 1.);

		vel = Vector2Normalize(vel);
	} else if (controlSystem == WASD_Soft) {
		Velocity targetVel(0., 0.);

		if(IsKeyDown(KEY_W)) (targetVel.dy = -1.);
		if(IsKeyDown(KEY_A)) (targetVel.dx = -1.);
		if(IsKeyDown(KEY_S)) (targetVel.dy = 1.);
		if(IsKeyDown(KEY_D)) (targetVel.dx = 1.);

		targetVel = Vector2Normalize(targetVel);

		// Smoothing approach the targetVel
		float accel = 10. * dt;
		vel += (targetVel - vel) * accel;

		// Eh not needed
		//float drag = 0.9;
		//vel *= drag;
		
	} else if (controlSystem == Tank) {
		if (IsKeyDown(KEY_W) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
			vel = Vector2Add(vel, Vector2Scale(dir, dt)); // constant per sec <= scale by dt
		} else {
			// Dampening
			vel = Vector2Scale(vel, 0.99);
		}
	}
	
	

	pos = Vector2Add(pos, Vector2Scale(vel, speedMult * dt));
}

// OOPing time
Position* Player::getPos() { return &pos; };
Velocity* Player::getVel() { return &vel; };
Vector2* Player::getDir() { return &dir; };
Velocity Player::getScaledVel(float dt) { return vel * (speedMult * dt);};