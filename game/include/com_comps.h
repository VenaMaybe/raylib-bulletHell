#pragma once

#include "raylib.h"
#include <iostream>

// forward declaration
struct Position;
struct Velocity;
using Direction = Vector2;

// Just used to make constructors simpler
using Pos = Position;
using Vel = Velocity;
using Dir = Direction;
using Vec2 = Vector2;

// Lerp between two vectors -- oops already implemented 
//void mixVectorsByReference(Vector2& v1, Vector2& v2, float percentOfFirst) {
//	v1.x = (1 - t) * v1.x + t * v2.x;
//	v1.y = (1 - t) * v1.y + t * v2.y;
//}

// Shitty utility function
inline void printVector2(Vector2 v) {
	std::cout << v.x << "\t" << v.y << std::endl;
}

// Practice with operator overloading again
struct Position { // has a...
	float x;
	float y;

	// Default constructor
	Position() : x(0.), y(0.) {}

	// Default constructor with inputs
	Position(float x, float y) : x(x), y(y) {};

	// Constructor to convert
	Position(const Vector2& vec) : x(vec.x), y(vec.y) {}

	// Overload assignment operator
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

	// Overload conversion operator
	operator Vector2() const { return {x, y}; }

	// Generic comparisons
	bool operator==(const Position& other) const { return x == other.x && y == other.y; }
	bool operator!=(const Position& other) const { return !(*this == other); }

	// Scale it by a float scalar
	Position operator*(float scalar) const { return Position(x * scalar, y * scalar); }
	Position& operator*=(float scalar);

	// Common operations bla bla
	Position operator+(const Position other) const { return Position(x + other.x, y + other.y); }
	Position operator-(const Position other) const { return Position(x - other.x, y - other.y); }

	// Useful
	Position& operator+=(const Position& other);
	Position& operator+=(const Velocity& other);
	Position& operator-=(const Position& other);
};

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
	bool operator==(const Velocity& other) const { return dx == other.dx && dy == other.dy; }
	bool operator!=(const Velocity& other) const { return !(*this == other); }

	// Scale it by a float scalar
	Velocity operator*(float scalar) const { return Velocity(dx * scalar, dy * scalar); }
	Velocity& operator*=(float scalar);

	// Common operations bla bla, lazy, move these to cpp later
	Velocity operator+(const Velocity other) const { return Velocity(dx + other.dx, dy + other.dy); }
	Velocity operator-(const Velocity other) const { return Velocity(dx - other.dx, dy - other.dy); }
	// Unary operator overload, inverts velocity direction
	Velocity operator-() const { return Velocity(-dx, -dy); } 

	// Useful
	Velocity& operator+=(const Velocity& other);
	Velocity& operator-=(const Velocity& other);
};

