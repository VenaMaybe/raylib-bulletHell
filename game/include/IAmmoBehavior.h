#pragma once

#include <string>
#include <vector>

// Forward Declaration of Gun
class Gun;

struct AmmoTypeInfo {
	std::string ammoTypeName;
	int currentAmmo;
	int maxAmmo;
};

// Supports multiple ammo types
using AmmoInfo = std::vector<AmmoTypeInfo>;

// Define behavior of ammo, e.g. Inf Ammo vs Finite Ammo
class IAmmoBehavior {
public:
	virtual ~IAmmoBehavior() = default;

	// Determine if the gun can fire based on ammo availability
	virtual bool canFire(const Gun& gun) const = 0;

	// Consumes ammo when the gun is fired
	virtual void consumeAmmo(Gun& gun, int amount) = 0;

	// Reloads the ammo
	virtual void reloadAmmo(Gun& gun, int amount) = 0;
	virtual void reloadAmmo(Gun& gun) = 0; // Without specifying, reloads all

	// Return vector of information about the current ammos states
	virtual AmmoInfo getAmmoInfo() const = 0;

};