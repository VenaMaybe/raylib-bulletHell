#pragma once

#include <iostream>
#include "IGunEffect.h"
#include "audioBit.h"

class RecoilEffect : public IGunEffect {
public:
	RecoilEffect(float recoilPercent = 2.f);
	void apply(Gun& gun) override;
private:
	float recoilPercent;
};


class SoundOnShootEffect : public IGunEffect {
public:
	SoundOnShootEffect();
	void apply(Gun& gun) override;
private:
	AudioBit onShootSound;
};

class BloomOnHitEffect : public IGunEffect {
public:
	BloomOnHitEffect();
	void apply(Gun& gun) override;
};
