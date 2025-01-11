#include "com_comps.h"

Position& Position::operator*=(float scalar) {
	x *= scalar;
	y *= scalar;
	return *this;
}

Position& Position::operator+=(const Position& other) {
	x += other.x;
	y += other.y;
	return *this;
}

Position& Position::operator+=(const Velocity& other) {
	x += other.dx;
	y += other.dy;
	return *this;
}

Position& Position::operator-=(const Position& other) {
	x -= other.x;
	y -= other.y;
	return *this;
}

// Move the x= vel methods here later