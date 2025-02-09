#pragma once
#include "IGunBehavior.h"
#include "IBulletModifier.h"
#include "audioBit.h"

//
// Gun Behaviors
//

// Just shoots 1 shot
class SingleShotShooting : public IGunBehavior {
public:
	SingleShotShooting();
	 
	void shoot(Gun& gun, const IBulletBehavior& bulletBehavior) override;
private:

	// Controls what percent of the owner's velocity is added to the bullet
	// float percentOfOwnerVelocity = 0.15f;
};
class SingleShotSpreadShooting : public IGunBehavior {
public:
	SingleShotSpreadShooting();
	 
	void shoot(Gun& gun, const IBulletBehavior& bulletBehavior) override;
private:

	// Controls what percent of the owner's velocity is added to the bullet
	// float percentOfOwnerVelocity = 0.15f;
};
// Shoot x shots with t duration and s spread 
// class MultiShotShooting : public IGunBehavior {
// 	MultiShotShooting();
// 	void shoot(Gun& gun, const IBulletBehavior& bulletBehavior) override;
// };

