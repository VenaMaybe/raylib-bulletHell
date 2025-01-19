#include "IAmmoBehavior.h"

//
// Ammo Behaviors
//

class UnlimitedAmmoBehavior : public IAmmoBehavior {
public:
	bool canFire(const Gun& gun) const override;
	void consumeAmmo(Gun& gun, int amount) override;
	void reloadAmmo(Gun& gun, int amount) override;
	void reloadAmmo(Gun& gun) override;
	AmmoInfo getAmmoInfo() const override;
};

//

class StandardAmmoBehavior : public IAmmoBehavior {
public:
	StandardAmmoBehavior(int maxAmmo)
		: maxAmmo(maxAmmo), currentAmmo(maxAmmo) {}
	StandardAmmoBehavior(int maxAmmo, int startingAmmo)
		: maxAmmo(maxAmmo), currentAmmo(startingAmmo) {}
	
	bool canFire(const Gun& gun) const override;
	void consumeAmmo(Gun& gun, int amount) override;
	void reloadAmmo(Gun& gun, int amount) override;
	void reloadAmmo(Gun& gun) override;
	AmmoInfo getAmmoInfo() const override;
private:
	int maxAmmo;
	int currentAmmo;
};