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

	// Move player focus logic somewhere else

	enemies.back()->focusPlayer(player);
//	enemy.focusPlayer(player);
//	enemies.push_back(enemy);
}

std::vector<Bullet>&  EntityManager::getBullets() {
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
				return bullet.markedForDeletion;
			}
		),
		bullets.end()
	);
}

void EntityManager::updateEntities(float dt) {
	player->update(dt);
	playerGun->update(dt);
	
	// This is really bad, eventually use grid partitioning for better performance
	for (auto& bullet : bullets) {
		bullet.update(dt);
		for (auto& enemy : enemies) {
			checkCollide(bullet, *enemy);
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
	
	/*
	collisions:
	for enemy:
	for bullet in gun, check collision with the enemy;
	*/

}

void EntityManager::initializeEntities() {
	addEnemy(std::make_unique<Enemy>(Pos(100, 100), Vel(40, 40), 20, RED));

	// std::vector<Enemy> tempEnemies = {
	// 	Enemy({100, 100}, {40, 40}, 20, RED),
	// 	Enemy({200, 200}, {40, 40}, 20, BLUE),
	// 	Enemy({300, 300}, {40, 40}, 20, GREEN)
	// };

	// for (auto& enemy : tempEnemies) {
	// 	addEnemy(enemy);
	// }
}

// Not using this rn
// void spawnEnemies(){}

// This should not do more than checking collisions, right now it does

void EntityManager::checkCollide(Bullet& bullet, Enemy& enemy){
	Position enemyPos = enemy.getPos();
	float dist = Vector2Distance(bullet.pos, enemyPos);
//	std::cout << dist << std::endl;
	if( dist < 20 ){
		bullet.markedForDeletion = true;
		enemy.playHitSound();
	}
}