#pragma once
#include "raylib.h"
#include "com_comps.h"
#include "entity.h"

/* Outline -- Player Class

Player()	--- Simple Constructors
render()	--- Renders a sphere at player center, 		called per frame
update()	--- Processes input							called per frame

Has a:
	speed multiplier
	position
	velocity

	gun class

*/

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