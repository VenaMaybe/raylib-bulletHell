#pragma once

#include "raylib.h"
#include <iostream>

inline void printVector2(Vector2 v) {
	std::cout << v.x << "\t" << v.y << std::endl;
}

struct Position { // has a...
	float x;
	float y;

	// Default constructor
	Position() : x(0.), y(0.) {}

	// Default constructor with inputs
	Position(float x, float y) : x(x), y(y) {};

	// Constructor to convert
	Position(const Vector2& vec) : x(vec.x), y(vec.y) {}

	operator Vector2() const {
		return {x, y};
	}

	Position& operator=(const Vector2& other) {
		this->x = other.x;
		this->y = other.y;
		return *this;
	}

	// Overload call operator
	void operator()(const Vector2& other) {
		this->x = other.x;
		this->y = other.y;
	}

	// Generic comparisons
	bool operator==(const Position& other) const  {
		return x == other.x && y == other.y;
	}

	bool operator!=(const Position& other) const  {
		return !(*this == other); // Just the not
	}

	// Scale it by a float scalar
	Position operator*(float scalar) const {
		return Position(x * scalar, y * scalar);
	}

	Position& operator*=(float scalar) {
		x *= scalar;
		y *= scalar;
		return *this;
	}

	// Common operations bla bla
	Position operator+(const Position other) const {
		return Position(x + other.x, y + other.y);
	}

	Position& operator+=(const Position& other) {
		x += other.x;
		y += other.y;
		return *this;
	}

	Position operator-(const Position other) const {
		return Position(x - other.x, y - other.y);
	}

	Position& operator-=(const Position& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
};

// Practice with operator overloading again
struct Velocity {
	float dx;
	float dy;

	// Default constructor
	Velocity() : dx(0.), dy(0.) {}

	// Default constructor with inputs
	Velocity(float dx, float dy) : dx(dx), dy(dy) {};

	// Constructor to convert
	Velocity(const Vector2& vec) : dx(vec.x), dy(vec.y) {}

	// Overload conversion operator, i.e. "Vector2 vec = vel"
	operator Vector2() const {
		return {dx, dy};
	}

	// Overload assignment operator
	Velocity& operator=(const Vector2& other) {
		this->dx = other.x;
		this->dy = other.y;
		return *this; // return current obj for chaning stupid
	}

	// Overload call operator
	void operator()(const Vector2& other) {
		this->dx = other.x;
		this->dy = other.y;
	}

	// Generic comparisons
	bool operator==(const Velocity& other) const  {
		return dx == other.dx && dy == other.dy;
	}

	bool operator!=(const Velocity& other) const  {
		return !(*this == other); // Just the not
	}

	// Scale it by a float scalar
	Velocity operator*(float scalar) const {
		return Velocity(dx * scalar, dy * scalar);
	}

	Velocity& operator*=(float scalar) {
		dx *= scalar;
		dy *= scalar;
		return *this;
	}

	// Common operations bla bla
	Velocity operator+(const Velocity other) const {
		return Velocity(dx + other.dx, dy + other.dy);
	}

	Velocity& operator+=(const Velocity& other) {
		dx += other.dx;
		dy += other.dy;
		return *this;
	}

	Velocity operator-(const Velocity other) const {
		return Velocity(dx - other.dx, dy - other.dy);
	}

	Velocity& operator-=(const Velocity& other) {
		dx -= other.dx;
		dy -= other.dy;
		return *this;
	}
};