#pragma once
#include <memory>

// Forward Declaration of Gun
class Gun;

// Implementation of a Strategy Pattern from https://en.wikipedia.org/wiki/Strategy_pattern

// Strategy interface for how a gun fires
class IGunBehavior {
public:
	virtual ~IGunBehavior() = default;

	// Called when the gun is fired
	virtual void shoot(Gun& gun) = 0;

	// Called when the gun is reloaded
//	virtual void reload(Gun& gun) = 0;
};