#pragma once
#include "raylib.h"
#include "com_comps.h"
#include "entity.h"
#include "bullet.h"

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
	int getHp();
	void hitBy(Bullet b);
private:
	int hp;
	ControlTypes controlSystem = ControlTypes::WASD_Soft;
};