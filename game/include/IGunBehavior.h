// Implementation of a Strategy Pattern from https://en.wikipedia.org/wiki/Strategy_pattern
#pragma once
#include "IBulletBehavior.h"
#include "IBulletModifier.h"

// Forward Declaration of Gun
class Gun;

// Define behavior on reload, e.g. Reload 2 at a time
class IReloadBehavior {
public:
	// Called when the gun is reloaded
	virtual ~IReloadBehavior() = default;
	virtual void reload(Gun& gun) = 0;
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
	// Add a modifier to this behavior // Todo: Later have this be implemented here!!!
	virtual void addModifier(std::unique_ptr<IBulletModifier> modifier);
	// From a certain gun shoots a bullet with a certain behavior
	virtual void shoot(Gun& gun, const IBulletBehavior& bulletBehavior) = 0; 

protected:
	// Stores all the modifiers
	std::vector<std::unique_ptr<IBulletModifier>> bulletModifiers;
};

inline void IGunBehavior::addModifier(std::unique_ptr<IBulletModifier> modifier) {
	bulletModifiers.push_back(std::move(modifier));
}