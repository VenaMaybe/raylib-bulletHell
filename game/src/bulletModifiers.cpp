#include "bulletModifiers.h"
#include "gun.h"
#include "bullet.h"

////////////////////////////////////////

AddOwnerVelocityModifier::AddOwnerVelocityModifier(float percentOfOwnerVelocity)
	: percentOfOwnerVelocity(percentOfOwnerVelocity)
{}

void AddOwnerVelocityModifier::modifyBullet(Bullet& bullet, Gun& gun, const IBulletBehavior& bulletBehavior) {
	if (const auto& owner = gun.getOwner()) {
		// Add a fraction of the owner's velocity to the bullet's current velocity
		bullet.setVel(bullet.getVel() + (owner->getVel() * percentOfOwnerVelocity));
	}
}