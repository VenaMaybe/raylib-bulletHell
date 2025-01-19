#include "ammoBehaviors.h"

// UnlimitedAmmoBehavior
bool UnlimitedAmmoBehavior::canFire(const Gun& gun) const {
	return true; // Can always fire
}

AmmoInfo UnlimitedAmmoBehavior::getAmmoInfo() const {
	return { { "Infinite", -1, -1 } };
}

// Does nothing
void UnlimitedAmmoBehavior::consumeAmmo(Gun& gun, int amount) {}
void UnlimitedAmmoBehavior::reloadAmmo(Gun& gun, int amount) {}
void UnlimitedAmmoBehavior::reloadAmmo(Gun& gun) {}

// StandardAmmoBehavior
bool StandardAmmoBehavior::canFire(const Gun& gun) const {
	return currentAmmo > 0;
}

void StandardAmmoBehavior::consumeAmmo(Gun& gun, int amount) {
	currentAmmo -= amount;
	if (currentAmmo < 0) {
		currentAmmo = 0;
	}
}

void StandardAmmoBehavior::reloadAmmo(Gun& gun, int amount) {
	currentAmmo += amount;
	if (currentAmmo > maxAmmo) {
		currentAmmo = maxAmmo;
	}
}

void StandardAmmoBehavior::reloadAmmo(Gun& gun) {
	currentAmmo = maxAmmo;
}

AmmoInfo StandardAmmoBehavior::getAmmoInfo() const {
	return { { "Standard", currentAmmo, maxAmmo } };
}