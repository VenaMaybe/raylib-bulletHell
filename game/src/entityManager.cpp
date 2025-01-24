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

EntityManager::EntityManager() : score(0), difficulty(1), tempThing(0) {}

void EntityManager::setPlayer(Player* player) {
	this->player = player;
}

void EntityManager::setPlayerGun(Gun* gun) {
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
		//gunBehavior.setSpeed()
		auto bulletBehavior = std::make_unique<StraightBulletBehavior>(333.f);
		auto ammoBehavior = std::make_unique<UnlimitedAmmoBehavior>();

		//gunBehavior->addBulletModifier(std::make_unique<AddOwnerVelocityModifier>(-0.8f));

		//gunBehavior->addEffect(std::make_unique<RecoilEffect>(5.f));
//		gunBehavior->addEffect(std::make_unique<SoundOnShootEffect>()); // Gets really annoying cuz happening all at once


		std::shared_ptr<Gun> gunForEnemies = std::make_shared<Gun>(
			std::move(gunBehavior),
			std::move(bulletBehavior),
			std::move(ammoBehavior),
			enemy,
			&getBullets()
		);

		

		enemy->giveGun(gunForEnemies);
	}
}

void EntityManager::playerScreenWrap() {
	int playerX = (int)player->getPos().x;
	int playerY = (int)player->getPos().y;
	float width = (float)(GetScreenWidth());
	float height = (float)(GetScreenHeight());
	if(playerX >= GetScreenWidth()){
		player->setPos({width, player->getPos().y});
	}
	if(playerY >= GetScreenHeight()){
		player->setPos({player->getPos().x, height});
	}

	if(playerX <= 0){
		player->setPos({0, player->getPos().y});
	}
	if(playerY <= 0){
		player->setPos({player->getPos().x, 0});
	}


}
void EntityManager::updateEntities(float dt) {
	playerScreenWrap();
	player->update(dt);
	playerGun->update(dt);
	tempThing += 1;
	tempThing = tempThing%10;
	if(tempThing == 0)
	if(IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
	playerGun->processClick();
	int bob = GetRandomValue(0, 200);
	if(bob == 0){
		int newEnemyX = GetRandomValue(0, GetRenderWidth());
		int newEnemyY = GetRandomValue(0, GetRenderHeight());
		addEnemy(std::make_shared<Enemy>(Pos(newEnemyX, newEnemyY), Vel(0, 0), 25, PINK, Acl(0,0)));
		giveEnemiesAGun();
	}
	// This is really bad, eventually use grid partitioning for better performance
	// For ever bullet, check every enemy to see if they're colliding, ideally we only check nearby enemies
	for (auto& bullet : bullets) {
		// If we hit the player
		if(!bullet.isShooter(player) && checkPlayerCollide(bullet)){
			player->hitBy(bullet);
			bullet.markForDeletion();
			std::cout << "Player hit" << std::endl;
		}
		
		for (auto& enemy : enemies) {
			//if (!bullet.isShooter(enemy.get()) && checkCollide(bullet, *enemy)) {
			if (bullet.isShooter(player) && checkCollide(bullet, *enemy)) {
				// Mark the bullet hitting for deletion

				// Enemies getting hit by their own bullets
				bullet.markForDeletion();
				
				bullet.setPos(enemy->getPos()); // Update pos so line segment drawn correctly
				enemy->playHitSound();
				enemy->hitBy(bullet);
				std::cout << "An Enemy was hit" << std::endl;
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
		initializeEntities();
		giveEnemiesAGun();
	}
	giveEnemiesAGun();
	
	// Deletes all the entities that have been marked for deletion
	deleteEntitiesMarked();
	
}

void EntityManager::initializeEntities() {
	addEnemy(std::make_shared<Enemy>(Pos(400, 100), Vel(0, 0), 25, PINK, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(800, 100), Vel(0, 0), 25, PINK, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(200, 500), Vel(0, 0), 25, PINK, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(1000, 500), Vel(0, 0), 25, PINK, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(400, 900), Vel(0, 0), 25, PINK, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(800, 900), Vel(0, 0), 25, PINK, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(600, 300), Vel(0, 0), 25, PINK, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(600, 700), Vel(0, 0), 25, PINK, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(200, 900), Vel(0, 0), 25, PINK, Acl(0,0)));
	addEnemy(std::make_shared<Enemy>(Pos(1000, 900), Vel(0, 0), 25, PINK, Acl(0,0)));
}

bool EntityManager::checkCollide(const Bullet& bullet, const Enemy& enemy) const {
	return CheckCollisionPointCircle(bullet.getPos(), enemy.getPos(), enemy.getRadius());
}

bool EntityManager::checkPlayerCollide(const Bullet& bullet){
	return CheckCollisionPointCircle(player->getPos(), bullet.getPos(), 20);
}