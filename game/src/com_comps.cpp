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

Velocity& Velocity::operator*=(float scalar) {
	dx *= scalar;
	dy *= scalar;
	return *this;
}
Velocity& Velocity::operator-=(const Velocity& other) {
	dx -= other.dx;
	dy -= other.dy;
	return *this;
}
Velocity& Velocity::operator+=(const Velocity& other) {
	dx += other.dx;
	dy += other.dy;
	return *this;
}

