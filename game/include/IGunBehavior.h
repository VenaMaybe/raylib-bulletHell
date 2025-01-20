// Implementation of a Strategy Pattern from https://en.wikipedia.org/wiki/Strategy_pattern
#pragma once
#include <memory>
#include "IBulletBehavior.h"
#include "IBulletModifier.h"
#include "IGunEffect.h"

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
	// Add a modifier to this behavior // Todo: Have remove methods
	virtual void addModifier(std::unique_ptr<IBulletModifier> modifier);
	virtual void addEffect(std::unique_ptr<IGunEffect> effect);
	// From a certain gun shoots a bullet with a certain behavior
	virtual void shoot(Gun& gun, const IBulletBehavior& bulletBehavior) = 0; 

protected:
	// Stores all the modifiers
	std::vector<std::unique_ptr<IBulletModifier>> bulletModifiers;
	// Stores all the effects
	std::vector<std::unique_ptr<IGunEffect>> effects;
};

inline void IGunBehavior::addModifier(std::unique_ptr<IBulletModifier> modifier) {
	bulletModifiers.push_back(std::move(modifier));
}

inline void IGunBehavior::addEffect(std::unique_ptr<IGunEffect> effect) {
	effects.push_back(std::move(effect));
}
