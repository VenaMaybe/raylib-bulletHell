#pragma once

#include "raylib.h"
#include <iostream>

void printVector2(Vector2 v) {
	std::cout << v.x << "\t" << v.y << std::endl;
}

struct Position { // has a...
	float x;
	float y;

	operator Vector2() const {
		return {x, y};
	}

	Position& operator=(const Vector2& otherVec) {
		this->x = otherVec.x;
		this->y = otherVec.y;
		return *this;
	}
};

// Practice with operator overloading again
struct Velocity {
	float dx;
	float dy;

	// Default constructor
	Velocity(float dx, float dy) : dx(dx), dy(dy) {};

	// Constructor to convert
	Velocity(const Vector2& vec) : dx(vec.x), dy(vec.y) {}

	// Overload conversion operator, i.e. "Vector2 vec = vel"
	operator Vector2() const {
		return {dx, dy};
	}

	// Overload assignment operator
	Velocity& operator=(const Vector2& otherVec) {
		this->dx = otherVec.x;
		this->dy = otherVec.y;
		return *this; // return current obj for chaning stupid
	}

	// Overload call operator
	void operator()(const Vector2& otherVec) {
		this->dx = otherVec.x;
		this->dy = otherVec.y;
	}
};