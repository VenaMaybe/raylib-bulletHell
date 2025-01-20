#include "raylib.h"
#include "entityManager.h"
#include "gun.h"
#include <vector>
#include "bullet.h"
#include "enemy.h"
#include <iostream>

// For Enemy Guns:
#include "gunBehaviors.h"
#include "bulletBehaviors.h"
#include "ammoBehaviors.h"
#include "bulletModifiers.h"
#include "gunEffects.h"

EntityManager::EntityManager() {}

void EntityManager::setPlayer(Player* player) {
	this->player = player;
}

void EntityManager::setPlayerGun(Gun* gun){
	this->playerGun = gun; 
}

void EntityManager::addEnemy(std::shared_ptr<Enemy> enemy) {
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
			[](const std::shared_ptr<Enemy>& enemy) {
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

void EntityManager::giveEnemiesAGun() {
	for (auto& enemy : enemies) {
		// create a specific gun
		auto gunBehavior = std::make_unique<SingleShotShooting>();
		auto bulletBehavior = std::make_unique<StraightBulletBehavior>();
		auto ammoBehavior = std::make_unique<UnlimitedAmmoBehavior>();

		gunBehavior->addModifier(std::make_unique<AddOwnerVelocityModifier>(0.15f));

		gunBehavior->addEffect(std::make_unique<RecoilEffect>(1.f));
//		gunBehavior->addEffect(std::make_unique<SoundOnShootEffect>()); // Gets really annoying cuz happening all at once


		std::shared_ptr<Gun> gunForEnemies = std::make_shared<Gun>(
			std::move(gunBehavior),
			std::move(bulletBehavior),
			std::move(ammoBehavior),
			enemy,
			&getBullets()
		);

		std::cout << "\t\tmeow\n";

		enemy->giveGun(gunForEnemies);
	}
}


void EntityManager::updateEntities(float dt) {
	player->update(dt);
	playerGun->update(dt);
	
	// This is really bad, eventually use grid partitioning for better performance
	// For ever bullet, check every enemy to see if they're colliding, ideally we only check nearby enemies
	for (auto& bullet : bullets) {
		for (auto& enemy : enemies) {
			if (checkCollide(bullet, *enemy) && !bullet.isShooter(enemy.get())) {
				// Mark the bullet hitting for deletion

				// Enemies getting hit by their own bullets
				bullet.markForDeletion();
				
				bullet.setPos(enemy->getPos()); // Update pos so line segment drawn correctly
				enemy->playHitSound();
				enemy->hitBy(bullet);
			}
		}
		bullet.update(dt);
	}

	if (!enemies.empty()) {
		for (auto& enemy : enemies) {
			enemy->UpdateMovement();
			enemy->ChangeDirection();
			for (auto& guy : enemies){
				if (enemy != guy && guy)
				enemy->avoidEnemy(guy.get());
			}
			enemy->update(dt);
		}
	} else {
		// std::cout << "Enemies vector is empty!" << std::endl;
	}

	// Deletes all the entities that have been marked for deletion
	deleteEntitiesMarked();

}

void EntityManager::initializeEntities() {
	addEnemy(std::make_shared<Enemy>(Pos(100, 100), Vel(0, 0), 20, RED, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(200, 200), Vel(0, 0), 20, BLUE, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(300, 300), Vel(0, 0), 20, GREEN, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(155, 100), Vel(0, 0), 20, PURPLE, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(255, 200), Vel(0, 0), 20, ORANGE, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(355, 300), Vel(0, 0), 20, YELLOW, Acl(0,0)));
}

bool EntityManager::checkCollide(const Bullet& bullet, const Enemy& enemy) const {
	return CheckCollisionPointCircle(bullet.getPos(), enemy.getPos(), enemy.getRadius());
}
