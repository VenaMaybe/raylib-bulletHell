#pragma once

#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include "com_comps.h"

/* Outline -- Player Class

Player()	--- Simple Constructors
render()	--- Renders a sphere at player center, 		called per frame
update()	--- Processes input							called per frame

Has a:
	speed multiplier
	position
	velocity

	gun class

*/


class Player {
public:
	Player();
	void render();
	void update(float dt);
	Position* getPos();
	Velocity* getVel();
	Vector2* getDir();
private:
	float speedMult;
	Position pos;
	Velocity vel;
	Vector2 dir;
};

Player::Player() : pos{100, 100}, vel{0, 0}, speedMult(150.) {}

void Player::render() {
	DrawCircleV(pos, 10., RAYWHITE);
	DrawLineEx(pos, Vector2Add(pos, Vector2Scale(dir, 16) ), 10, RAYWHITE); // Debugging for now
}

void Player::update(float dt) {
	// Get mouse pos
	Vector2 mousePos = GetMousePosition();

	// Get vector from player to mouse
	dir = Vector2Normalize(Vector2Subtract(mousePos, pos));

	if (IsKeyDown(KEY_W) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		std::cout << "w pressed \n";
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