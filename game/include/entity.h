#pragma once
#include "raylib.h"
#include "raymath.h"
#include "com_comps.h"

// Todo: give all entities a name

// Abstract class for all Entities
class Entity {
public:
	Entity(Position p, Velocity v, float speed, Direction d);
	virtual ~Entity() = default;
	virtual void render() = 0;
	virtual void update(float dt) = 0;
	virtual Position getPos() const;
	virtual Velocity getVel() const;
	virtual Direction getDir() const;
	virtual Velocity getScaledVel() const;
	virtual float getSpeed() const;
	virtual void setPos(const Position &pos);
	virtual void setVel(const Velocity &vel);
	virtual void setDir(const Direction &dir);
	virtual void setSpeed(float speed);
protected:
// Every entity has to have these
	Position pos;
	Velocity vel;
	Direction dir;
	float speed;
};

inline Entity::Entity(Position p, Velocity v, float speed, Direction d)
	: pos(p), vel(v), speed(speed), dir(Vector2Normalize(d)) {}

inline Position  Entity::getPos() const 		{ return pos; }
inline Velocity  Entity::getVel() const 		{ return vel; }
inline Direction Entity::getDir() const 		{ return dir; } // Normalized Direction
inline Velocity  Entity::getScaledVel() const 	{ return vel * speed;}
inline float Entity::getSpeed() const 			{ return speed; }
inline void Entity::setPos(const Position &pos) { this->pos = pos; }
inline void Entity::setVel(const Velocity &vel) { this->vel = vel; }
inline void Entity::setDir(const Direction &dir){ this->dir = Vector2Normalize(dir); }
inline void Entity::setSpeed(float speed) 		{ this->speed = speed; }


class EntityWithAcceleration : public Entity{
public:
	EntityWithAcceleration(Position p, Velocity v, float speed, Direction d, Acceleration a);
	Acceleration getAcl() const;
protected:
	Acceleration acl;
};
inline Acceleration EntityWithAcceleration::getAcl() const	{ return acl; }
inline EntityWithAcceleration::EntityWithAcceleration(Position p, Velocity v, float speed, Direction d, Acceleration a)
	: Entity( p, v, speed, d), acl(a) {};