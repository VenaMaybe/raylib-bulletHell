#include "bulletRenderers.h"

#include "raylib.h"
#include "bullet.h"

void BasicCircleRenderer::render(const Bullet& bullet) const {
	Color finalColor = getColorBehavior().getColor();

	DrawCircleV(bullet.getPos(), 2.f, finalColor);
}