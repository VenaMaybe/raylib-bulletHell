#include "raylib.h"
#include "entityManager.h"
#include "gun.h"
#include <vector>
#include "bullet.h"
#include "enemy.h"
#include <iostream>
EntityManager::EntityManager() {}

void EntityManager::setPlayer(Player* player) {
	this->player = player;
}

void EntityManager::setPlayerGun(Gun* gun){
	this->playerGun = gun; 
}

void EntityManager::addEnemy(std::unique_ptr<Enemy> enemy) {
	enemies.push_back(std::move(enemy));
	enemies.back()->focusPlayer(player);
}

std::vector<Bullet>& EntityManager::getBullets() {
	return bullets;
}

void EntityManager::renderBullets() {
	for (auto& bullet : bullets) {
		bullet.render(); 
	}
}

// Rename later
void EntityManager::renderPlayer() {
	player->render();
	playerGun->render();
}

void EntityManager::renderEnemies() {
	for (auto& enemy : enemies) {
		enemy->render();
	}
}

void EntityManager::deleteEntitiesMarked() {
	enemies.erase(
		std::remove_if(
			enemies.begin(),
			enemies.end(),
			[](const std::unique_ptr<Enemy>& enemy) {
				return enemy->markedForDeletion;
			}
		),
		enemies.end()
	);

	bullets.erase(
		std::remove_if(
			bullets.begin(),
			bullets.end(),
			[](const Bullet& bullet) {
				return bullet.isMarkedForDeletion();
			}
		),
		bullets.end()
	);
}

void EntityManager::updateEntities(float dt) {
	player->update(dt);
	playerGun->update(dt);
	
	// This is really bad, eventually use grid partitioning for better performance
	// For ever bullet, check every enemy to see if they're colliding, ideally we only check nearby enemies
	for (auto& bullet : bullets) {
		bullet.update(dt);
		for (auto& enemy : enemies) {
			if (checkCollide(bullet, *enemy)) {
				// Mark the bullet hitting for deletion
				bullet.markForDeletion();
				enemy->playHitSound();
			}
		}
	}

	if (!enemies.empty()) {
		for (auto& enemy : enemies) {
			enemy->update(dt);
		}
	} else {
		std::cout << "Enemies vector is empty!" << std::endl;
	}

	// Deletes all the entities that have been marked for deletion
	deleteEntitiesMarked();
}

void EntityManager::initializeEntities() {
	addEnemy(std::make_unique<Enemy>(Pos(100, 100), Vel(40, 40), 20, RED));
	addEnemy(std::make_unique<Enemy>(Pos(200, 200), Vel(40, 40), 20, BLUE));
	addEnemy(std::make_unique<Enemy>(Pos(300, 300), Vel(40, 40), 20, GREEN));
}

bool EntityManager::checkCollide(const Bullet& bullet, const Enemy& enemy) const {
	return CheckCollisionPointCircle(bullet.getPos(), enemy.getPos(), enemy.getRadius());
}
