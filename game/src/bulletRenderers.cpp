#include "bulletRenderers.h"

#include "raylib.h"
#include "bullet.h"

inline void BasicCircleRenderer::render(const Bullet& bullet) const {
	std::cout << "Trying to render\n";
	DrawCircleV(bullet.getPos(), 20.f, bullet.getCurrentColor());
}