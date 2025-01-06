#include "raylib.h"
#include "raymath.h"
#include <iostream>

/* Outline -- Class

render()	--- Renders a sphere at player center, 		called per frame
update()	--- Processes input							called per frame



*/

void printVector2(Vector2 v) {
	std::cout << v.x << "\t" << v.y << std::endl;
}

struct Position { // has a...
	float x;
	float y;

	operator Vector2() const {
		return {x, y};
	}

	Position& operator=(const Vector2& other) {
		this->x = other.x;
		this->y = other.y;
		return *this;
	}
};

struct Velocity {
	float dx;
	float dy;

	operator Vector2() const {
		return {dx, dy};
	}

	Velocity& operator=(const Vector2& other) {
		this->dx = other.x;
		this->dy = other.y;
		return *this; // return current obj for chaning stupid
	}
};

class Player {
public:
	Player();
	void render();
	void update(float dt);
private:
	float speedMult;
	Position pos;
	Velocity vel;
};

Player::Player() : pos{100, 100}, vel{0, 0}, speedMult(150.) {

}

void Player::render() {
	DrawCircleV(pos, 10., RAYWHITE);
}

void Player::update(float dt) {
	// Get mouse pos
	Vector2 mousePos = GetMousePosition();

	// Get vector from player to mouse
	Vector2 plToMouse = Vector2Normalize(Vector2Subtract(mousePos, pos));

	if (IsKeyDown(KEY_W) || IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
		std::cout << "w pressed \n";
		vel = Vector2Add(vel, Vector2Scale(plToMouse, speedMult * dt)); // constant per sec <= scale by dt
	}

	pos = Vector2Add(pos, Vector2Scale(vel, dt));
	DrawLineEx(pos, Vector2Add(pos, Vector2Scale(plToMouse, 100) ), 5, RAYWHITE);

	// Dampening
	vel = Vector2Scale(vel, 0.99f);
	
}