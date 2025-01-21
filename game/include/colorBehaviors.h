#pragma once

#include <stdexcept>
#include "IColorBehavior.h"

/*

BIG WIP!!!

*/

class StaticColorBehavior : public IColorBehavior {
public:
	StaticColorBehavior(Color color);

	Color getColor() const override;
	void update(float dt) override;

};

inline StaticColorBehavior::StaticColorBehavior(Color color) {
	colors.push_back(color);
}

inline Color StaticColorBehavior::getColor() const {
	if (colors.size() > 1) { throw std::runtime_error("Something weird with colors happening"); }
	return colors[0];
}

inline void StaticColorBehavior::update(float dt) {

}