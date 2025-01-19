#pragma once
#include <memory>
#include <functional>

// Forward Declaration of Gun
class Gun;

// Forward Declaration of Bullet
class Bullet;

// Implementation of a Strategy Pattern from https://en.wikipedia.org/wiki/Strategy_pattern



// Sort of like sub behaviors:

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

// Define behavior of the bullet fired, e.g. bullet velocity and max bullet age
class IBulletBehavior {
public:
	virtual ~IBulletBehavior() = default;

	// Get bullet behavior, returns a function with inputs bullet and dt
	virtual std::function<void(Bullet&, float)> getBehaviorFunction() const = 0;

	// An identification method
	virtual const char* name() const { return behaviorName; }

protected:
	const char* behaviorName;
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