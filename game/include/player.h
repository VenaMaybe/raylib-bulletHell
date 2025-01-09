#pragma once
#include "raylib.h"
#include "com_comps.h"
#include "entity.h"

enum class ControlTypes {
	WASD,
	WASD_Soft,
	Tank
};

class Player : public Entity {
public:
	Player();
	void render() override;
	void update(float dt) override;
private:
	ControlTypes controlSystem = ControlTypes::WASD_Soft;
};