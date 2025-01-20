#pragma once

#include "IBulletModifier.h"

////////////////////////////////////////

class AddOwnerVelocityModifier : public IBulletModifier {
public:
	AddOwnerVelocityModifier(float percentOfOwnerVelocity);
	void modifyBullet(Bullet& bullet, Gun& gun, const IBulletBehavior& bulletBehavior) override;
private:
	float percentOfOwnerVelocity;
};