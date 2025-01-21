#pragma once

#include <vector>
#include "raylib.h"

/* Todo

Add support for multiple gradients
Add support for adding or setting a singular color

Split this up into three, base -> with multiple + with singular

*/

class IColorBehavior {
public:
	virtual ~IColorBehavior() = default;

	// Get the color for the frame
	virtual Color getColor() const = 0;

	// Update behavior for time-dependent colors
	virtual void update(float dt) = 0;

	// Set color of colors
	virtual void setVectorOfColors(const std::vector<Color>& colors);

	// Get color or all colors
	virtual std::vector<Color> getVectorOfColors() const;

protected:
	std::vector<Color> colors;
};

inline void IColorBehavior::setVectorOfColors(const std::vector<Color>& colors) {
	this->colors = colors;
}

inline std::vector<Color> IColorBehavior::getVectorOfColors() const {
	return colors;
}