#pragma once

#include "raylib.h"
#include "player.h"
#include "gun.h"
#include "enemy.h"
#include "bullet.h"
#include "com_comps.h"
#include <vector>
#include "entity.h"

class EntityManager {
public:
	EntityManager();
	void focusPlayer(Player* player);
	void focusGun(Gun* gun);
	void updateEntities(float dt);
	void deleteEntitiesMarked();

	void checkCollide(Bullet& bullet, Enemy& enemy);
	void spawnEnemies();
	std::vector<Bullet>& getBullets();
	void addEnemy(Enemy& enemy);

	void renderBullets();
	void renderPlayer();
	void renderEnemies();

	void initializeEntities();

private:
	Player* player;
	Gun* gun;
	std::vector<Bullet> bullets;
	std::vector<Enemy> enemies;
};