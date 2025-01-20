#pragma once

// Forward Declaration
class Gun;

// Holds an effect like recoil or sound when firing
class IGunEffect {
public:
	virtual ~IGunEffect() = default;
	virtual void apply(Gun& gun) = 0;
};