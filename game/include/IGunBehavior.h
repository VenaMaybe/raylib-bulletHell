// Implementation of a Strategy Pattern from https://en.wikipedia.org/wiki/Strategy_pattern
#pragma once
#include <memory>
#include "IBulletBehavior.h"

// Forward Declaration of Gun
class Gun;

// Define behavior on reload, e.g. Reload 2 at a time
class IReloadBehavior {
public:
	// Called when the gun is reloaded
	virtual ~IReloadBehavior() = default;
	virtual void reload(Gun& gun) = 0;
};

// Define behavior of ammo, e.g. Inf Ammo vs Finite Ammo
class IAmmoBehavior {
public:
	virtual ~IAmmoBehavior() = default;

	// Determine if the gun can fire based on ammo availability
	virtual bool canFire(const Gun& gun) const = 0;

	// Consumes ammo when the gun is fired
	virtual void consumeAmmo(Gun& gun) = 0;

	// Reloads the ammo
	virtual void reloadAmmo(Gun& gun) = 0;
};

// Define behavior due to firing, e.g. recoil and sound effect?
class IImpactBehavior {
public:
	virtual ~IImpactBehavior() = default;
	virtual void applyImpact(Gun& gun) = 0;
};

// Sort of like main behavior:

// Defines behavior for when a gun fires
class IGunBehavior {
public:
	virtual ~IGunBehavior() = default;
	// From a certain gun shoots a bullet with a certain behavior
	virtual void shoot(Gun& gun, const IBulletBehavior& bulletBehavior) = 0; 
};