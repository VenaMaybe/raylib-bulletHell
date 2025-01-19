#include "bulletBehaviors.h"
#include "com_comps.h"
#include "bullet.h"

StraightBulletBehavior::StraightBulletBehavior(float bulletSpeed, float maxBulletAge)
	: IBulletBehavior("StraightBulletBehavior", bulletSpeed, maxBulletAge) {
	behavior = [](Bullet& bullet, float dt) {
		Pos pos = bullet.getPos();
		Vel vel = bullet.getVel();
		float speed = bullet.getSpeed();

		bullet.setPos(pos + ( vel * speed * dt ) );
	};
}

std::function<void(Bullet&, float)> StraightBulletBehavior::getBehaviorFunction() const {
	return behavior;
}

// Change this later so it uses phase transitions and not discrete simulations
// Maybe do substep simulations maybe, idk
ZigzagBulletBehavior::ZigzagBulletBehavior(float bulletSpeed, float maxBulletAge)
	: IBulletBehavior("ZigzagBulletBehavior", bulletSpeed, maxBulletAge) {
	behavior = [](Bullet& bullet, float dt) {
		Pos pos = bullet.getPos();
		Vel vel = bullet.getVel();
		float speed = bullet.getSpeed();
		float timeAccumulator = bullet.getAge(); // Multiplies by dt

		float frequency = 5.f;
		float amplitude = 5.f;

		float sineValue = sin( ( timeAccumulator * frequency * 2.0f * PI) + (PI/2) );
		float zigzagOffset = ( sineValue >= 0.f ) ? amplitude : -amplitude;

		Dir dir = bullet.getVel();
		Vel orthogonal = Vel(dir.y, -dir.x);

		Pos displacement = Vec2(orthogonal * zigzagOffset);

		bullet.setPos(pos + ( vel * speed * dt) + displacement );
	};
}

std::function<void(Bullet&, float)> ZigzagBulletBehavior::getBehaviorFunction() const {
	return behavior;
}