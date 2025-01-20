#pragma once

#include "IBulletBehavior.h"

// Forward Declarations
class Gun;
class Bullet;

// A generic interface for modifying bullet properties and behavior!
class IBulletModifier {
public:
	virtual ~IBulletModifier() = default;

	// Modify bullet properties durring creation
	virtual void modifyBullet(Bullet& bullet, Gun& gun, const IBulletBehavior& bulletBehavior) = 0;
};