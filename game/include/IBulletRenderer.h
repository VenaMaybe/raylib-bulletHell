#pragma once

#include <stdexcept>
#include <memory>
#include "IColorBehavior.h"

// Forward declaration of bullet
class Bullet;

class IBulletRenderer {
public:
	virtual ~IBulletRenderer() = default;

	virtual void render(const Bullet& bullet) const = 0;

	// Add this later
 	// get getRenderOnCollisionFunction()
	//

	void setColorBehavior(std::shared_ptr<IColorBehavior> colorBehavior) {
		// Todo: do this for all setters
		if (!colorBehavior) { throw std::invalid_argument("colorBehavior can't be null stupid"); }
		this->colorBehavior = std::move(colorBehavior);
	}

	IColorBehavior& getColorBehavior() const {
		if (!colorBehavior) { throw std::runtime_error("colorBehavior is not set"); }
		return *colorBehavior;
	}

private:
	// A color behavior for this renderer
	std::shared_ptr<IColorBehavior> colorBehavior;
};