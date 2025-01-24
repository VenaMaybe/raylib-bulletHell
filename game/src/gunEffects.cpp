#include "gunEffects.h"
#include "gun.h"
#include "raylib.h"

RecoilEffect::RecoilEffect(float recoilPercent)
	: recoilPercent(recoilPercent) {}

void RecoilEffect::apply(Gun& gun) {
	IBulletBehavior* bulletBehavior = gun.getBulletBehavior();
	if (!bulletBehavior) { return; }

	const auto& owner = gun.getOwner();
	if (!owner) { return; }

	// Last bullet shot's velocity causes recoil
	if (gun.bullets->empty()) { return; }
	const Bullet& lastBullet = gun.bullets->back();

	Velocity playerVelDueToRecoil(0, 0); // Some percent of the velocity goes into the player
	playerVelDueToRecoil = -Velocity(Vector2Lerp(playerVelDueToRecoil, lastBullet.getVel(), recoilPercent));
	owner->setVel((owner->getVel() + playerVelDueToRecoil)); // Add the recoil to the player's velocity
}

/////////////////////////////////

SoundOnShootEffect::SoundOnShootEffect()
	: onShootSound("sounds/gunEx1.wav")
{}

void SoundOnShootEffect::apply(Gun& gun) {
	onShootSound.playSound();
}

BloomOnHitEffect::BloomOnHitEffect()
{}

void BloomOnHitEffect::apply(Gun& gun){
	// std::cout << "meow" << std::endl;
	DrawCircleV({333.f, 333.f}, 20.f, PINK);
}