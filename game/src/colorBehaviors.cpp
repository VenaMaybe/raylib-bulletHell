#include <colorBehaviors.h>

#include <stdexcept>


StaticColorBehavior::StaticColorBehavior(Color color) {
	colors.push_back(color);
}

Color StaticColorBehavior::getColor() const {
	if (colors.size() > 1) { throw std::runtime_error("Something weird with colors happening"); }
	return colors[0];
}

void StaticColorBehavior::update(float dt) {}

/////////////////////////////////////////

GradientOverTime::GradientOverTime(Color initialColor, Color finalColor, float colorTransferRate, float colorMixAmount)
	: colorTransferRate(colorTransferRate), colorMixAmount(colorMixAmount) {
	setVectorOfColors({initialColor, finalColor});
}

Color GradientOverTime::getColor() const {
	return outputColor;
}

void GradientOverTime::update(float dt) {
	outputColor = ColorLerp(colors[0], colors[1], colorMixAmount);
	colorMixAmount += colorTransferRate * dt;
}