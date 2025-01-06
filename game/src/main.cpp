#include "raylib.h"
#include "raymath.h"
#include "rlgl.h"

#include <iostream>
#include "player.h"

int main() {
	const int screenWidth = 800;
    const int screenHeight = 600;
	Vector2 screenRes = { (float)screenWidth, (float)screenHeight };

	// Initialize the window and set up raylib
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	InitWindow(screenWidth, screenHeight, "Game");
	SetTargetFPS(90);


	// create a player
	Player player;

	// Begin the frame
	while (!WindowShouldClose()) {
		// Draw
		BeginDrawing();
		ClearBackground(BLACK);

		float dt = GetFrameTime();
		player.update(dt);
		player.render();


		DrawFPS(10, 10);
		EndDrawing();

	}

	CloseWindow(); // Close the window
	return 0;
}