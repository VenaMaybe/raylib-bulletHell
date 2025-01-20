#pragma once

#include "raylib.h"
#include <vector>
#include <memory>

#include "com_comps.h"
#include "player.h"
#include "enemy.h"
#include "gun.h"
#include "bullet.h"

class EntityManager {
public:
	EntityManager();

	void setPlayer(Player* player);
	void setPlayerGun(Gun* gun);

	//
	void giveEnemiesAGun();
	//


	void updateEntities(float dt);
	void deleteEntitiesMarked();

	void addEnemy(std::shared_ptr<Enemy> enemy);
	bool checkCollide(const Bullet& bullet, const Enemy& enemy) const;
	std::vector<Bullet>& getBullets();

	void renderBullets();
	void renderPlayer();
	void renderEnemies();

	void initializeEntities();

private:
	Player* player;
	Gun* playerGun;
	std::vector<Bullet> bullets;
	std::vector<std::shared_ptr<Enemy>> enemies;
};