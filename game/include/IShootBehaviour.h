#pragma once

#include <string>
#include <vector>

// Forward Declaration of Gun
class Gun;



// Define behavior of ammo, e.g. Inf Ammo vs Finite Ammo
class IShootBehaviour {
public:
	virtual ~IShootBehaviour() = default;

	// Determine if the gun can fire based on ammo availability
	virtual bool isAuto() const = 0;

};