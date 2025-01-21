#pragma once

#include "IColorBehavior.h"

class StaticColorBehavior : public IColorBehavior {
public:
	StaticColorBehavior(Color color);

	Color getColor() const override;
	void update(float dt) override;

};

/////////////////////////////////////////

// Forms a gradient over time
class GradientOverTime : public IColorBehavior {
public:
	GradientOverTime(Color initialColor, Color finalColor, float colorTransferRate, float colorMixAmount = 0.f);
	Color getColor() const override;
	void update(float dt) override;

private:
	float colorMixAmount;
	float colorTransferRate;
	Color outputColor;

};

/////////////////////////////////////////
// If you want a color dependent on the bullet itself, just pass in a reference in the constructor