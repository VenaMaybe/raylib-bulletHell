#pragma once

#include "raylib.h"
#include <vector>
#include "com_comps.h"
// #include "entity.h"
#include "player.h"
#include "enemy.h"
#include "gun.h"
#include "bullet.h"

class EntityManager {
public:
	EntityManager();

	void setPlayer(Player* player);
	void setPlayerGun(Gun* gun);
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
	Gun* playerGun;
	std::vector<Bullet> bullets;
	std::vector<Enemy> enemies;
};