#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include <iostream>
#include "player.h"
#include "enemy.h"
#include "gun.h"

int main() {
	const int screenWidth = 800;
    const int screenHeight = 600;
	Vector2 screenRes = { (float)screenWidth, (float)screenHeight };

	// Initialize the window and set up raylib
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Game");
	SetTargetFPS(90);

	// Create a vector of enemies
    std::vector<Enemy> enemies = {
        Enemy({100, 100}, {50, 50}, 20, RED),
        Enemy({200, 200}, {50, 50}, 20, BLUE),
        Enemy({300, 300}, {50, 50}, 20, GREEN)
    };

	// create a player
	auto player = std::make_shared<Player>();

	GunSpecificEx gunSpecific_Pistol;
	Gun playerGun(
		[&gunSpecific_Pistol](Gun& gun) { gunSpecific_Pistol.shoot(gun); },
	/* Depends on this pointer & specific instance
	   gunSpecific,shoot hasa a type pointer-to-member-function
	   and thus needs an instance.

	   We wrap it in a lambda to supply the instance,
	   The lambda has the correct signature: void(Gun&)
	   thus it is assigned to the callback
	*/
		player
	);

	// Set all enemies to focus the player
	for (Enemy& enemy : enemies) {
		enemy.focusPlayer(player.get());
	}

	// Begin the frame
	while (!WindowShouldClose()) {
		// Draw
		BeginDrawing();
		ClearBackground(BLACK);

		float dt = GetFrameTime();
		player.get()->update(dt);
		playerGun.update(dt);

		player.get()->render();
		playerGun.render();

		for (Enemy& enemy : enemies) {
            enemy.Update(dt);
            enemy.Draw();
        }

		DrawFPS(10, 10);
		EndDrawing();

	}

	CloseWindow(); // Close the window
	return 0;
}