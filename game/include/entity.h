#pragma once
#include "raylib.h"
#include "com_comps.h"

// Abstract class for all Entities
struct Entity {
public:
	Entity(Position p, Velocity v, float speed, Direction d);
	virtual ~Entity() = default;
	virtual void render() = 0;
	virtual void update(float dt) = 0;
	virtual Position getPos() const;
	virtual Velocity getVel() const;
	virtual Velocity getScaledVel() const;
	virtual Direction getDir() const;
protected:
// Every entity has to have these
	Position pos;
	Velocity vel;
	Direction dir;
	float speed;
};

inline Entity::Entity(Position p, Velocity v, float speed, Direction d)
	: pos(p), vel(v), speed(speed), dir(d) {}

inline Position  Entity::getPos() const 		{ return pos; }
inline Velocity  Entity::getVel() const 		{ return vel; }
inline Velocity  Entity::getScaledVel() const 	{ return vel * speed;}
inline Direction Entity::getDir() const 		{ return dir; }

/* NOT USING RIGHT NOW
// Mixin for entities with direction, i.e. not static entities
struct HasDirection {
	HasDirection(Vector2 d);
	virtual ~HasDirection() = default;
	virtual Vector2 getDir();
protected:
	Vector2 dir;
};

inline HasDirection::HasDirection(Vector2 d)
	: dir(d) {}

inline Vector2 HasDirection::getDir() { return dir; }
*/