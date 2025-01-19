#pragma once
#include "IGunBehavior.h"
#include "audioBit.h"

// How a pistol that shoots one bullet at a time behaves
class PistolBehavior : public IGunBehavior {
public:
	PistolBehavior();

	void shoot (Gun& gun) override;

private:
	int maxBullets = 10;
	float bulletSpeed = 1000.f;
	float maxBulletAge = 3.f;
	float percentOfOwnerVelocity = 0.15f; // Todo: Change this based on speed of bullet!!!
	float recoilPercent = 2.f;
	AudioBit gunSound;
};

